################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc.c \
../Core/Src/eth.c \
../Core/Src/fdcan.c \
../Core/Src/gpio.c \
../Core/Src/guide_sensor.c \
../Core/Src/i2c.c \
../Core/Src/imu.c \
../Core/Src/main.c \
../Core/Src/mcp23017.c \
../Core/Src/memorymap.c \
../Core/Src/pca9685.c \
../Core/Src/rs232.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32h7xx.c \
../Core/Src/tim.c \
../Core/Src/usart.c \
../Core/Src/xsens_mdata2.c \
../Core/Src/xsens_mti.c \
../Core/Src/xsens_utility.c 

OBJS += \
./Core/Src/adc.o \
./Core/Src/eth.o \
./Core/Src/fdcan.o \
./Core/Src/gpio.o \
./Core/Src/guide_sensor.o \
./Core/Src/i2c.o \
./Core/Src/imu.o \
./Core/Src/main.o \
./Core/Src/mcp23017.o \
./Core/Src/memorymap.o \
./Core/Src/pca9685.o \
./Core/Src/rs232.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32h7xx.o \
./Core/Src/tim.o \
./Core/Src/usart.o \
./Core/Src/xsens_mdata2.o \
./Core/Src/xsens_mti.o \
./Core/Src/xsens_utility.o 

C_DEPS += \
./Core/Src/adc.d \
./Core/Src/eth.d \
./Core/Src/fdcan.d \
./Core/Src/gpio.d \
./Core/Src/guide_sensor.d \
./Core/Src/i2c.d \
./Core/Src/imu.d \
./Core/Src/main.d \
./Core/Src/mcp23017.d \
./Core/Src/memorymap.d \
./Core/Src/pca9685.d \
./Core/Src/rs232.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32h7xx.d \
./Core/Src/tim.d \
./Core/Src/usart.d \
./Core/Src/xsens_mdata2.d \
./Core/Src/xsens_mti.d \
./Core/Src/xsens_utility.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../CANopenNode/ -I../CANopenNode_STM32/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc.cyclo ./Core/Src/adc.d ./Core/Src/adc.o ./Core/Src/adc.su ./Core/Src/eth.cyclo ./Core/Src/eth.d ./Core/Src/eth.o ./Core/Src/eth.su ./Core/Src/fdcan.cyclo ./Core/Src/fdcan.d ./Core/Src/fdcan.o ./Core/Src/fdcan.su ./Core/Src/gpio.cyclo ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/gpio.su ./Core/Src/guide_sensor.cyclo ./Core/Src/guide_sensor.d ./Core/Src/guide_sensor.o ./Core/Src/guide_sensor.su ./Core/Src/i2c.cyclo ./Core/Src/i2c.d ./Core/Src/i2c.o ./Core/Src/i2c.su ./Core/Src/imu.cyclo ./Core/Src/imu.d ./Core/Src/imu.o ./Core/Src/imu.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mcp23017.cyclo ./Core/Src/mcp23017.d ./Core/Src/mcp23017.o ./Core/Src/mcp23017.su ./Core/Src/memorymap.cyclo ./Core/Src/memorymap.d ./Core/Src/memorymap.o ./Core/Src/memorymap.su ./Core/Src/pca9685.cyclo ./Core/Src/pca9685.d ./Core/Src/pca9685.o ./Core/Src/pca9685.su ./Core/Src/rs232.cyclo ./Core/Src/rs232.d ./Core/Src/rs232.o ./Core/Src/rs232.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32h7xx.cyclo ./Core/Src/system_stm32h7xx.d ./Core/Src/system_stm32h7xx.o ./Core/Src/system_stm32h7xx.su ./Core/Src/tim.cyclo ./Core/Src/tim.d ./Core/Src/tim.o ./Core/Src/tim.su ./Core/Src/usart.cyclo ./Core/Src/usart.d ./Core/Src/usart.o ./Core/Src/usart.su ./Core/Src/xsens_mdata2.cyclo ./Core/Src/xsens_mdata2.d ./Core/Src/xsens_mdata2.o ./Core/Src/xsens_mdata2.su ./Core/Src/xsens_mti.cyclo ./Core/Src/xsens_mti.d ./Core/Src/xsens_mti.o ./Core/Src/xsens_mti.su ./Core/Src/xsens_utility.cyclo ./Core/Src/xsens_utility.d ./Core/Src/xsens_utility.o ./Core/Src/xsens_utility.su

.PHONY: clean-Core-2f-Src

