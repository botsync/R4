/*
 * pca9685.c
 *
 *  Created on: 20.01.2019
 *      Author: Mateusz Salamon
 *		mateusz@msalamon.pl
 *
 *      Website: https://msalamon.pl/nigdy-wiecej-multipleksowania-na-gpio!-max7219-w-akcji-cz-3/
 *      GitHub:  https://github.com/lamik/Servos_PWM_STM32_HAL
 */

#include "main.h"
#include "i2c.h"

#include "pca9685.h"
#include "math.h"


PCA9685_STATUS PCA9685_SetBit(PCA9685_handle * handle,uint8_t Register, uint8_t Bit, uint8_t Value)
{
	uint8_t tmp[2] = {0,0};
	if(Value) Value = 1;

	if(HAL_I2C_Mem_Read(handle->pca9685_i2c, handle->device_address, Register, 1, tmp, 1, 10) != HAL_OK)
	{
		////printmsg("1. %s  0x%x error\n",__func__,handle->device_address);
		return PCA9685_ERROR;
	}
//	//printmsg("3. %s  %x %x \n",__func__,Register,tmp[0]);
	tmp[0] &= ~((1<<PCA9685_MODE1_RESTART_BIT)|(1<<Bit));
	tmp[0] |= (Value&1)<<Bit;

	if( HAL_I2C_Mem_Write(handle->pca9685_i2c, handle->device_address, Register, 1, tmp, 1, 10)!= HAL_OK)
	{
		//printmsg("3. %s  0x%x error\n",__func__,handle->device_address);
		return PCA9685_ERROR;
	}

	return PCA9685_OK;
}

PCA9685_STATUS PCA9685_SoftwareReset(PCA9685_handle * handle)
{
	uint8_t cmd[2] = {0x6,0};
//	if( HAL_I2C_Master_Transmit(handle->pca9685_i2c, handle->device_address, cmd, 1, 10) == HAL_OK)
//	{
//		return PCA9685_OK;
//	}
	if(PCA9685_SetBit(handle, 0, 6, 1) == PCA9685_OK)
	{
		return PCA9685_OK;
	}

	//printmsg("%s  0x%x error\n",__func__,handle->device_address);
	return PCA9685_ERROR;
}

PCA9685_STATUS PCA9685_SleepMode(PCA9685_handle * handle,uint8_t Enable)
{
	return PCA9685_SetBit(handle,PCA9685_MODE1, PCA9685_MODE1_SLEEP_BIT, Enable);
}

PCA9685_STATUS PCA9685_RestartMode(PCA9685_handle * handle,uint8_t Enable)
{
	return PCA9685_SetBit(handle,PCA9685_MODE1, PCA9685_MODE1_RESTART_BIT, Enable);
}

PCA9685_STATUS PCA9685_AutoIncrement(PCA9685_handle * handle,uint8_t Enable)
{
	return PCA9685_SetBit(handle,PCA9685_MODE1, PCA9685_MODE1_AI_BIT, Enable);
}

PCA9685_STATUS PCA9685_SubaddressRespond(PCA9685_handle * handle,SubaddressBit Subaddress, uint8_t Enable)
{
	return PCA9685_SetBit(handle,PCA9685_MODE1, Subaddress, Enable);
}

PCA9685_STATUS PCA9685_AllCallRespond(PCA9685_handle * handle,uint8_t Enable)
{
	return PCA9685_SetBit(handle,PCA9685_MODE1, PCA9685_MODE1_ALCALL_BIT, Enable);
}

//
//	Frequency - Hz value
//
PCA9685_STATUS PCA9685_SetPwmFrequency(PCA9685_handle * handle,uint16_t Frequency)
{
	float PrescalerVal;
	uint8_t Prescale;

	if(Frequency >= 1526)
	{
		Prescale = 0x03;
	}
	else if(Frequency <= 24)
	{
		Prescale = 0xFF;
	}
	else
	{
		PrescalerVal = (25000000 / (4096.0 * (float)Frequency)) - 1;
		Prescale = floor(PrescalerVal + 0.5);
	}

	//
	//	To change the frequency, PCA9685 have to be in Sleep mode.
	//
	PCA9685_SleepMode(handle,1);
	if(HAL_I2C_Mem_Write(handle->pca9685_i2c, handle->device_address, PCA9685_PRESCALE, 1, &Prescale, 1, 10)!= HAL_OK)
	{
		//printmsg("%s device_address %x error\n",__func__,handle->device_address);
	}// Write Prescale value
	PCA9685_SleepMode(handle,0);
	PCA9685_RestartMode(handle,1);
	return PCA9685_OK;
}

PCA9685_STATUS PCA9685_SetPwm(PCA9685_handle * handle,uint8_t Channel, uint16_t OnTime, uint16_t OffTime)
{
	uint8_t RegisterAddress;
	uint8_t Message[4];

	RegisterAddress = PCA9685_LED0_ON_L + (4 * Channel);
	Message[0] = OnTime & 0xFF;
	Message[1] = OnTime>>8;
	Message[2] = OffTime & 0xFF;
	Message[3] = OffTime>>8;

	if(HAL_OK != HAL_I2C_Mem_Write(handle->pca9685_i2c, handle->device_address, RegisterAddress, 1, Message, 4, 10))
	{
		//printmsg("%s device_address %x error\n",__func__,handle->device_address);
		return PCA9685_ERROR;
	}

	return PCA9685_OK;
}

PCA9685_STATUS PCA9685_SetPin(PCA9685_handle * handle,uint8_t Channel, uint16_t Value, uint8_t Invert)
{
	if(Value > 4095) Value = 4095;

	if (Invert) {
		if (Value == 0) {
			// Special value for signal fully on.
			return PCA9685_SetPwm(handle,Channel, 4096, 0);
		}
		else if (Value == 4095) {
			// Special value for signal fully off.
			return PCA9685_SetPwm(handle,Channel, 0, 4096);
		}
		else {
			return PCA9685_SetPwm(handle,Channel, 0, 4095-Value);
		}
	}
	else {
		if (Value == 4095) {
			// Special value for signal fully on.
			return PCA9685_SetPwm(handle,Channel, 4096, 0);
		}
		else if (Value == 0) {
			// Special value for signal fully off.
			return PCA9685_SetPwm(handle,Channel, 0, 4096);
		}
		else {
			return PCA9685_SetPwm(handle,Channel, 0, Value);
		}
	}
}

#ifdef PCA9685_SERVO_MODE
PCA9685_STATUS PCA9685_SetServoAngle(uint8_t Channel, float Angle)
{
	float Value;
	if(Angle < MIN_ANGLE) Angle = MIN_ANGLE;
	if(Angle > MAX_ANGLE) Angle = MAX_ANGLE;

	Value = (Angle - MIN_ANGLE) * ((float)SERVO_MAX - (float)SERVO_MIN) / (MAX_ANGLE - MIN_ANGLE) + (float)SERVO_MIN;

	return PCA9685_SetPin(Channel, (uint16_t)Value, 0);
}
#endif

PCA9685_STATUS PCA9685_Init(PCA9685_handle * handle)
{

#ifdef PCA9685_SERVO_MODE
	PCA9685_SetPwmFrequency(48);
#else
	PCA9685_SetPwmFrequency(handle,1000);
#endif
	PCA9685_AutoIncrement(handle,1);

	return PCA9685_OK;
}
uint8_t PCA9685_duty_cycle(PCA9685_handle * handle, unsigned channel, float duty_cycle)
{
	assert(duty_cycle >= 0.0);
	assert(duty_cycle <= 1.0);

	if (duty_cycle == 0.0) {
		return PCA9685_SetPwm(handle, channel, 0, 4096); // Special value for always off
	} else if (duty_cycle == 1.0) {
		return PCA9685_SetPwm(handle, channel, 4096, 0); // Special value for always on
	} else {

		unsigned required_on_time;

		required_on_time = (unsigned)roundf(4095 * duty_cycle);

		// Offset on and off times depending on channel to minimise current spikes.
		unsigned on_time = (channel == 0) ? 0 : (channel * 256) - 1;
		unsigned off_time = (on_time + required_on_time) & 0xfffu;

		return PCA9685_SetPwm(handle, channel, on_time, off_time);
	}
}
