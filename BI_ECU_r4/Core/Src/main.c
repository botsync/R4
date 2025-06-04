/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "eth.h"
#include "fdcan.h"
#include "i2c.h"
#include "memorymap.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pca9685.h"
#include "mcp23017.h"
#include "CO_app_STM32.h"
#include "OD.h"
#include "CANopen.h"
#include "rs232.h"
//#include "unity.h"
#include <string.h>

// MODULE UNDER TEST
#include "xsens_mti.h"
#include "xsens_mti_private.h"
#include "xsens_constants.h"
#include "xsens_mdata2.h"
#include "xsens_utility.h"
#include "imu.h"
#include "guide_sensor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// FDCAN1 Defines
FDCAN_TxHeaderTypeDef   TxHeader1;
//FDCAN_RxHeaderTypeDef   RxHeader1;
uint8_t               TxData1[12];
uint8_t state=1;
char *buff;
//uint8_t               RxData1[12];


// FDCAN2 Defines
//FDCAN_TxHeaderTypeDef   TxHeader2;
//FDCAN_RxHeaderTypeDef   RxHeader2;
//uint8_t               TxData2[12];
//uint8_t               RxData2[12];
//
//
//int indx = 0;
//
//// FDCAN1 Callback
//void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
//{
//  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
//  {
//    /* Retreive Rx messages from RX FIFO0 */
//    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader1, RxData1) != HAL_OK)
//    {
//    /* Reception Error */
//    Error_Handler();
//    }
//
////    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
////    {
////      /* Notification Error */
////      Error_Handler();
////    }
//  }
//}
//
////// FDCAN2 Callback
//void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
//{
//  if((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
//  {
//    /* Retreive Rx messages from RX FIFO0 */
//    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &RxHeader2, RxData2) != HAL_OK)
//    {
//    /* Reception Error */
//    Error_Handler();
//    }
//
////    if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
////    {
////      /* Notification Error */
////      Error_Handler();
////    }
//
////	  sprintf ((char *)TxData2, "FDCAN2TX %d", indx++);
////
////	  if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader2, TxData2)!= HAL_OK)
////	  {
////		  Error_Handler();
////	  }
//  }
//}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
PCA9685_handle __pca9685 = {.device_address=PCA9685_ADDRESS,.pca9685_i2c=&hi2c3};
MCP23017_HandleTypeDef mcp1={};
MCP23017_HandleTypeDef mcp2={};
MCP23017_HandleTypeDef mcp3={};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
CO_SDO_abortCode_t
read_SDO(CO_SDOclient_t* SDO_C, uint8_t nodeId, uint16_t index, uint8_t subIndex, uint8_t* buf, size_t bufSize,
		size_t* readSize) {
	CO_SDO_return_t SDO_ret;

	// setup client (this can be skipped, if remote device don't change)
	SDO_ret = CO_SDOclient_setup(SDO_C, CO_CAN_ID_SDO_CLI + nodeId, CO_CAN_ID_SDO_SRV + nodeId, nodeId);
	if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
		return CO_SDO_AB_GENERAL;
	}

	// initiate upload
	SDO_ret = CO_SDOclientUploadInitiate(SDO_C, index, subIndex, 1000, false);
	if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
		return CO_SDO_AB_GENERAL;
	}

	// upload data
	do {
		uint32_t timeDifference_us = 10000;
		CO_SDO_abortCode_t abortCode = CO_SDO_AB_NONE;

		SDO_ret = CO_SDOclientUpload(SDO_C, timeDifference_us, false, &abortCode, NULL, NULL, NULL);
		if (SDO_ret < 0) {
			return abortCode;
		}

		sleep_us(timeDifference_us);
	} while (SDO_ret > 0);

	// copy data to the user buffer (for long data function must be called several times inside the loop)
	*readSize = CO_SDOclientUploadBufRead(SDO_C, buf, bufSize);

	return CO_SDO_AB_NONE;
}

CO_SDO_abortCode_t
write_SDO(CO_SDOclient_t* SDO_C, uint8_t nodeId, uint16_t index, uint8_t subIndex, uint8_t* data, size_t dataSize) {
	CO_SDO_return_t SDO_ret;
	bool_t bufferPartial = false;

	// setup client (this can be skipped, if remote device is the same)
	SDO_ret = CO_SDOclient_setup(SDO_C, CO_CAN_ID_SDO_CLI + nodeId, CO_CAN_ID_SDO_SRV + nodeId, nodeId);
	if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
		return -1;
	}

	// initiate download
	SDO_ret = CO_SDOclientDownloadInitiate(SDO_C, index, subIndex, dataSize, 1000, false);
	if (SDO_ret != CO_SDO_RT_ok_communicationEnd) {
		return -1;
	}

	// fill data
	size_t nWritten = CO_SDOclientDownloadBufWrite(SDO_C, data, dataSize);
	if (nWritten < dataSize) {
		bufferPartial = true;
		// If SDO Fifo buffer is too small, data can be refilled in the loop.
	}

	// download data
	do {
		uint32_t timeDifference_us = 10000;
		CO_SDO_abortCode_t abortCode = CO_SDO_AB_NONE;

		SDO_ret = CO_SDOclientDownload(SDO_C, timeDifference_us, false, bufferPartial, &abortCode, NULL, NULL);
		if (SDO_ret < 0) {
			return abortCode;
		}

		sleep_us(timeDifference_us);
	} while (SDO_ret > 0);

	return CO_SDO_AB_NONE;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FDCAN1_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  MX_USART10_UART_Init();
  MX_I2C3_Init();
  MX_TIM23_Init();
  MX_UART4_Init();
  MX_ADC1_Init();
  MX_TIM14_Init();
  //MX_FDCAN2_Init();
  //MX_ETH_Init();
  /* USER CODE BEGIN 2 */
//	CANopenNodeSTM32 canopenNodeSTM32;
//
//	canopenNodeSTM32.CANHandle  = &hfdcan1;
//	canopenNodeSTM32.HWInitFunction = MX_FDCAN1_Init;
//	canopenNodeSTM32.timerHandle = &htim14;
//	canopenNodeSTM32.desiredNodeID = 32;
//	canopenNodeSTM32.baudrate = 1000;
//	canopen_app_init(&canopenNodeSTM32);
//
//
//	FDCAN_FilterTypeDef sFilterConfig;
//
//	sFilterConfig.IdType = FDCAN_STANDARD_ID;
//	sFilterConfig.FilterIndex = 0;
//	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
//	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
//	sFilterConfig.FilterID1 = 0x22;
//	sFilterConfig.FilterID2 = 0x22;
//	sFilterConfig.RxBufferIndex = 0;
//	if (HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig) != HAL_OK)
//	{
//		/* Filter configuration Error */
//		Error_Handler();
//	}
//
//	// STart FDCAN1
//	if(HAL_FDCAN_Start(&hfdcan2)!= HAL_OK)
//	{
//		Error_Handler();
//	}
//	//
//	////	  // STart FDCAN2
//	////	  if(HAL_FDCAN_Start(&hfdcan2)!= HAL_OK)
//	////	  {
//	////		  Error_Handler();
//	////	  }
//	//
//	//	  // Activate the notification for new data in FIFO0 for FDCAN1
//		  if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//		  {
//		    /* Notification Error */
//		    Error_Handler();
//		  }
//
//
//	// Activate the notification for new data in FIFO1 for FDCAN2
//	//	  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
//	//	  {
//	//	    /* Notification Error */
//	//	    Error_Handler();
//	//	  }
//
//
//	// Configure TX Header for FDCAN1
//	TxHeader1.Identifier = 0x11;
//	TxHeader1.IdType = FDCAN_STANDARD_ID;
//	TxHeader1.TxFrameType = FDCAN_DATA_FRAME;
//	TxHeader1.DataLength = FDCAN_DLC_BYTES_8;
//	TxHeader1.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//	TxHeader1.BitRateSwitch = FDCAN_BRS_OFF;
//	TxHeader1.FDFormat = FDCAN_FD_CAN;
//	TxHeader1.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	TxHeader1.MessageMarker = 0;
//
//
//	// Configure TX Header for FDCAN2
//	//	  TxHeader2.Identifier = 0x22;
//	//	  TxHeader2.IdType = FDCAN_STANDARD_ID;
//	//	  TxHeader2.TxFrameType = FDCAN_DATA_FRAME;
//	//	  TxHeader2.DataLength = FDCAN_DLC_BYTES_12;
//	//	  TxHeader2.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
//	//	  TxHeader2.BitRateSwitch = FDCAN_BRS_OFF;
//	//	  TxHeader2.FDFormat = FDCAN_FD_CAN;
//	//	  TxHeader2.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
//	//	  TxHeader2.MessageMarker = 0;
//
//
//	TIM23->CCR1 = 0;
//	TIM23->CCR2 = 0;
//	TIM23->CCR3 = 0;
//	TIM23->CCR4 = 0;
//	HAL_TIM_PWM_Start(&htim23, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim23, TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim23, TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim23, TIM_CHANNEL_4);
//
//	HAL_Delay(100);
//
//	PCA9685_Init(&__pca9685);
//
//
//	mcp23017_init(&mcp1,&hi2c3,0x44);
//	mcp23017_init(&mcp2,&hi2c3,0x40);
//	mcp23017_init(&mcp3,&hi2c3,0x42);
//
//	if(mcp23017_iodir(&mcp1, MCP23017_PORTA, MCP23017_IODIR_ALL_OUTPUT) != HAL_OK)
//	{
//		//printmsg("mcp1 error \n");
//	}
//	if(mcp23017_iodir(&mcp1, MCP23017_PORTB, MCP23017_IODIR_ALL_INPUT) != HAL_OK)
//	{
//		//printmsg("mcp1 error \n");
//	}
//	if(mcp23017_iodir(&mcp2, MCP23017_PORTA, MCP23017_IODIR_ALL_OUTPUT) != HAL_OK)
//	{
//		//printmsg("mcp2 error \n");
//	}
//	if(mcp23017_iodir(&mcp2, MCP23017_PORTB, MCP23017_IODIR_ALL_OUTPUT) != HAL_OK)
//	{
//		//printmsg("mcp2 error \n");
//	}
//
//	if(mcp23017_iodir(&mcp3, MCP23017_PORTA, MCP23017_IODIR_ALL_OUTPUT) != HAL_OK)
//	{
//		//printmsg("mcp3 error \n");
//	}
//	if(mcp23017_iodir(&mcp3, MCP23017_PORTB, MCP23017_IODIR_ALL_OUTPUT) != HAL_OK)
//	{
//		//printmsg("mcp3 error \n");
//	}
//
//
//	TIM23->CCR1 = 50;
//	TIM23->CCR2 = 50;
//	TIM23->CCR3 = 50;
//	TIM23->CCR4 = 50;
//
//	sprintf ((char *)TxData1, "TX");
//	if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &TxHeader1, TxData1)!= HAL_OK)
//	{
//		HAL_FDCAN_Stop(&hfdcan2);
//		HAL_FDCAN_Start(&hfdcan2);
//	}
//	for(int i= 0;i<16;i++)
//	{
//		PCA9685_duty_cycle(&__pca9685, i, .5);
//	}
//
//
//	//	//printmsg("init \n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	uint32_t toggleLed  = 0;
//	uint32_t count  = 0;


	    // Initialize system clocks, GPIOs, and peripherals (USART1 for example)
  // RS232 handle structure
	    RS232_Init();
	    test_request_reqfirmwareversion();
	    guide_sensor1_send_real_time_init();

	while (1)
	{
		canopen_app_process();
//
//		if(HAL_GetTick() - toggleLed >= 1000)
//		{
//			//count++;
			OD_PERSIST_COMM.x6000_counter++;
//
			OD_set_u32(OD_find(OD, 0x6000),0x00, OD_PERSIST_COMM.x6000_counter, false);
//
//			//			OD_PERSIST_COMM.x6001_count1+=10;
//			OD_set_u32(OD_find(OD, 0x6001),0x00, 0x222, false);
//
			CO_TPDOsendRequest(&canopenNodeSTM32.canOpenStack->TPDO[0]);
			CO_TPDOsendRequest(&canopenNodeSTM32.canOpenStack->TPDO[1]);
//
						 sprintf ((char *)TxDaTxta1, "TX %d", indx++);
//			//
//			//				  if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader1, TxData1)!= HAL_OK)
//			//				  {
//			//					  HAL_FDCAN_Stop(&hfdcan1);
//			//					  HAL_FDCAN_Start(&hfdcan1);
//			//				  }
//
//
//			toggleLed = HAL_GetTick();
//			HAL_GPIO_TogglePin(CTRL_PC_GPIO_Port	, CTRL_PC_Pin);
//			HAL_GPIO_TogglePin(CTRL_1_GPIO_Port	, CTRL_1_Pin);
//			HAL_GPIO_TogglePin(CTRL_2_GPIO_Port	, CTRL_2_Pin);
//			HAL_GPIO_TogglePin(CTRL_3_GPIO_Port	, CTRL_3_Pin);
//			HAL_GPIO_TogglePin(CTRL_4_GPIO_Port	, CTRL_4_Pin);
//			HAL_GPIO_TogglePin(CTRL_5_GPIO_Port	, CTRL_5_Pin);
//			HAL_GPIO_TogglePin(CTRL_6_GPIO_Port	, CTRL_6_Pin);
//			HAL_GPIO_TogglePin(CTRL_7_GPIO_Port	, CTRL_7_Pin);
//			HAL_GPIO_TogglePin(CTRL_8_GPIO_Port	, CTRL_8_Pin);
//			HAL_GPIO_TogglePin(CTRL_9_GPIO_Port	, CTRL_9_Pin);
//			HAL_GPIO_TogglePin(CTRL_10_GPIO_Port	, CTRL_10_Pin);
//
//			mcp1.gpio[0] = 0xff;
//
//			mcp2.gpio[0] ^= 0xff;
//			mcp2.gpio[1] ^= 0xff;
//
//			mcp3.gpio[0] ^= 0xff;
//			mcp3.gpio[1] ^= 0xff;
//
//			if(mcp23017_write_gpio(&mcp1,MCP23017_PORTA) != HAL_OK)
//			{
//				//printmsg("submodule ->   mcp3 wrote failed\n");
//			}
//			if(mcp23017_read_gpio(&mcp1,MCP23017_PORTB) != HAL_OK)
//			{
//				//printmsg("submodule ->   mcp2 wrote failed\n");
//			}
//
//			if(mcp23017_write_gpio(&mcp2,MCP23017_PORTA) != HAL_OK)
//			{
//				//printmsg("submodule ->   mcp3 wrote failed\n");
//			}
//			if(mcp23017_write_gpio(&mcp2,MCP23017_PORTB) != HAL_OK)
//			{
//				//printmsg("submodule ->   mcp3 wrote failed\n");
//			}
//
//			if(mcp23017_write_gpio(&mcp3,MCP23017_PORTA) != HAL_OK)
//			{
//				//printmsg("submodule ->   mcp3 wrote failed\n");
//			}
//			if(mcp23017_write_gpio(&mcp3,MCP23017_PORTB) != HAL_OK)
//			{
//				//printmsg("submodule ->   mcp3 wrote failed\n");
//			}
//		}
        // Transmit some data (for example)
        uint8_t message[8] = {1,2,3,4,5,6,7,8};
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
        //RS232_Transmit(message, sizeof(message));
        //HAL_Delay(1000);
        message[7]=message[7]+1;
        //RS232_Transmit(message, sizeof(message));
        //test_request_baud();
        //HAL_Delay(2000);
        //test_request_reqfirmwareversion();
        if(state==1)
        {
        //guide_sensor1_send_real_time(MGD);
        state=0;
        }
        //HAL_Delay(1000);
        //test_request_baud();
        //imu_test_data();
        if(state==0)
        {
        	//buff = get_rx_buffer_data_3();
        guide_sensor1_send_real_time();
        //handleCommand(buff);
        state=1;
        }
        //guide_sensor1_send_real_time(MGD);
        HAL_Delay(100);  // Wait for 1 second before transmitting again
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 104;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC|RCC_PERIPHCLK_FDCAN;
  PeriphClkInitStruct.PLL2.PLL2M = 2;
  PeriphClkInitStruct.PLL2.PLL2N = 16;
  PeriphClkInitStruct.PLL2.PLL2P = 2;
  PeriphClkInitStruct.PLL2.PLL2Q = 4;
  PeriphClkInitStruct.PLL2.PLL2R = 2;
  PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_3;
  PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
  PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
  PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_PLL2;
  PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLL2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void
HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
	if (htim == canopenNodeSTM32->timerHandle) {
		canopen_app_interrupt();
	}
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32B;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
