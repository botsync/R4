/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_ERR_Pin|LED_SYS_Pin|LED_BOOT_Pin|CTRL_2_Pin
                          |CTRL_PC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, CTRL_9_Pin|CTRL_10_Pin|CTRL_8_Pin|CTRL_7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CTRL_5_Pin|CTRL_6_Pin|CTRL_3_Pin|CTRL_4_Pin
                          |CTRL_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_ERR_Pin LED_SYS_Pin LED_BOOT_Pin CTRL_2_Pin
                           CTRL_PC_Pin */
  GPIO_InitStruct.Pin = LED_ERR_Pin|LED_SYS_Pin|LED_BOOT_Pin|CTRL_2_Pin
                          |CTRL_PC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD10 PD11 PD0 PD1
                           PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : CTRL_9_Pin CTRL_10_Pin CTRL_8_Pin CTRL_7_Pin */
  GPIO_InitStruct.Pin = CTRL_9_Pin|CTRL_10_Pin|CTRL_8_Pin|CTRL_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : CTRL_5_Pin CTRL_6_Pin CTRL_3_Pin CTRL_4_Pin
                           CTRL_1_Pin */
  GPIO_InitStruct.Pin = CTRL_5_Pin|CTRL_6_Pin|CTRL_3_Pin|CTRL_4_Pin
                          |CTRL_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Configure PB14 (TX) and PB15 (RX) as Alternate Function pins
        GPIO_InitStruct.Pin = GPIO_PIN_14 | GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           // Alternate function, push-pull mode
        GPIO_InitStruct.Pull = GPIO_NOPULL;               // No pull-up or pull-down resistors
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     // High speed for USART communication
        GPIO_InitStruct.Alternate = GPIO_AF4_USART1;      // Alternate function AF7 for USART1

        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);           // Initialize the GPIOB pins

        // Configure PB14 (TX) and PB15 (RX) as Alternate Function pins
          GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
          GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           // Alternate function, push-pull mode
          GPIO_InitStruct.Pull = GPIO_NOPULL;               // No pull-up or pull-down resistors
          GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     // High speed for USART communication
          GPIO_InitStruct.Alternate = GPIO_AF7_USART3;      // Alternate function AF7 for USART1

          HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);           // Initialize the GPIOB pins

          // Configure PB14 (TX) and PB15 (RX) as Alternate Function pins
            GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           // Alternate function, push-pull mode
            GPIO_InitStruct.Pull = GPIO_NOPULL;               // No pull-up or pull-down resistors
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     // High speed for USART communication
            GPIO_InitStruct.Alternate = GPIO_AF7_USART6;      // Alternate function AF7 for USART1

            HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);           // Initialize the GPIOB pins


            // Configure PB14 (TX) and PB15 (RX) as Alternate Function pins
              GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_2;
              GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;           // Alternate function, push-pull mode
              GPIO_InitStruct.Pull = GPIO_NOPULL;               // No pull-up or pull-down resistors
              GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     // High speed for USART communication
              GPIO_InitStruct.Alternate = GPIO_AF4_USART10;      // Alternate function AF7 for USART1

              HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);           // Initialize the GPIOB pins

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
