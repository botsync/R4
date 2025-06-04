#ifndef INC_RS232_H_
#define INC_RS232_H_

#include "stm32h7xx_hal.h"

#define RS232_RX_BUFFER_SIZE 8
#define RS232_TX_BUFFER_SIZE 8

void RS232_Init();
    // RX Callback function - triggered when a byte is received
    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

    void RS232_Transmit(uint8_t *data, uint16_t size);


// Example interrupt handler for USART1 (modify as per your USART)
void USART1_IRQHandler(void);
uint8_t check_data(uint8_t *data);

void check_uart_rx6_timeout(void);

uint8_t get_rx_buffer_data_6();

void check_uart_rx3_timeout(void);

uint8_t get_rx_buffer_data_3();





#endif /* INC_RS232_H_ */
