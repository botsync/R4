#include "rs232.h"
#include "usart.h"
#include "xsens_mti.h"
#include "guide_sensor.h"

#define RX_BUFFER_SIZE 1
#define BUFFER_SIZE 8

uint8_t rx_buffer[9]={0};  // Buffer for storing received data
uint8_t data_received=0;
uint8_t rx_index=0;
char rx_buffer_3[10]={0};
uint8_t rx_buffer_6[8]={0};
uint8_t rx_buffer_10[8]={0};
uint16_t rx_index_3=0;
uint8_t rx_index_6=0;
uint8_t rx_index_10=0;
uint8_t data=0;
uint8_t result_arr[8]={1,2,3,4,5,6,7,8};
xsens_interface_t test_usart={0};
uint8_t rx_buffer_data_6[8]={0};
uint8_t rx_buffer_data_3[8]={0};
uint32_t last_rx_time=0;
#define RX_TIMEOUT_MS 50
uint8_t count=0;
uint32_t errorcode=0;









// Initialize RS485 communication (both GPIO and UART)
void RS232_Init(void) {
	HAL_UART_Receive_IT(&huart3, rx_buffer_3, RX_BUFFER_SIZE);
	HAL_UART_Receive_IT(&huart1, rx_buffer, RX_BUFFER_SIZE);
	HAL_UART_Receive_IT(&huart6, rx_buffer_6, RX_BUFFER_SIZE);
	HAL_UART_Receive_IT(&huart10, rx_buffer_10, RX_BUFFER_SIZE);
}







// Transmit data over RS485
void RS232_Transmit(uint8_t *data, uint16_t size) {
	if (HAL_UART_Transmit(&huart3, data, size, HAL_MAX_DELAY) != HAL_OK) {
		Error_Handler();  // Define your error handler here
	}

	// Optionally, add a small delay for the bus to stabilize after transmission
	HAL_Delay(10);
	if (HAL_UART_Transmit(&huart1, data, size, HAL_MAX_DELAY) != HAL_OK) {
		Error_Handler();  // Define your error handler here
	}
	if (HAL_UART_Transmit(&huart6, data, size, HAL_MAX_DELAY) != HAL_OK) {
		Error_Handler();  // Define your error handler here
	}
	if (HAL_UART_Transmit(&huart10, data, size, HAL_MAX_DELAY) != HAL_OK) {
		Error_Handler();  // Define your error handler here
	}
}






void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART3) {
		rx_index_3++;
		if(rx_index_3 == 5)
		{
			//if(rx_buffer_3[rx_index_3] == 'M')
			//{
			handleCommand(rx_buffer_3);
			count++;
			//xsens_mti_parse_buffer(&test_usart, rx_buffer_3, rx_index_3);
			memset(rx_buffer_3, 0, sizeof(rx_buffer_3));
			rx_index_3=0;
		}
		//last_rx_time=HAL_GetTick();
		//parse_imu_data(&test_usart);
		if(HAL_UART_Receive_IT(&huart3, &rx_buffer_3[rx_index_3], RX_BUFFER_SIZE) != HAL_OK)
		{
			Error_Handler();
		}
		//rx_index_3++;
	}

	if (huart->Instance == USART1) {
		rx_index++;
		if(rx_index == 8)
		{
			rx_index =0;
			memset(rx_buffer , 0, sizeof(rx_buffer));
		}
		// Handle the received data
		// Example: Toggle an LED or process the data
		if(HAL_UART_Receive_IT(&huart1, &rx_buffer[rx_index], RX_BUFFER_SIZE) != HAL_OK)
		{
			Error_Handler();
		}
	}

	if (huart->Instance == USART6) {
		rx_index_6++;
		            last_rx_time = HAL_GetTick(); // Update last byte received time
		if(HAL_UART_Receive_IT(&huart6, &rx_buffer_6[rx_index_6], RX_BUFFER_SIZE) != HAL_OK)
		{
			Error_Handler();
		}
	}

	if (huart->Instance == USART10) {
		rx_index_10++;
		if(rx_index_10 == 8)
		{
			rx_index_10=0;
			memset(rx_buffer_10, 0, sizeof(rx_buffer_10));
		}
		// Handle the received data
		// Example: Toggle an LED or process the data
		if(HAL_UART_Receive_IT(&huart10, &rx_buffer_10[rx_index_10], RX_BUFFER_SIZE) != HAL_OK)
		{
			Error_Handler();
		}
	}


}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART3)
	{
//		if(HAL_UART_Receive_IT(&huart3, &rx_buffer_3[rx_index_3], RX_BUFFER_SIZE) != HAL_OK)
//				{
//					Error_Handler();
//				}

		errorcode=HAL_UART_GetError(huart);
		huart->RxState = HAL_UART_STATE_READY;

		if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE)) {
			__HAL_UART_CLEAR_OREFLAG(huart);  // Clear Overrun Error Flag
		}
		if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE)) {
			__HAL_UART_CLEAR_FEFLAG(huart);   // Clear Framing Error Flag
		}
		if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE)) {
			__HAL_UART_CLEAR_NEFLAG(huart);   // Clear Noise Error Flag
		}
		if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE)) {
			__HAL_UART_CLEAR_PEFLAG(huart);   // Clear Parity Error Flag
		}


		if(HAL_UART_Receive_IT(&huart3, &rx_buffer_3[rx_index_3], RX_BUFFER_SIZE) != HAL_OK)
						{

							Error_Handler();
						}
		//rx_index_3++;
	}
}

uint8_t check_data(uint8_t *data)
{
	for(uint8_t i=0;i<4;i++)
	{
		if(data[i]!=result_arr[i])
		{
			return 1;
		}
		if(i==3)
		{
			return 8;
		}
	}
}


//void test()
//{
//	if (huart->Instance == USART1) {
//	        	rx_buffer[rx_index]=huart->Instance->RDR;
//	        	rx_index++;
//	        	if(rx_index == 8)
//	        	{
//	        	//parse_modbus_frame(rx_buffer);
//	        		if(check_data(rx_buffer) == 8)
//	        		{
//	        	rx_index =0;
//	        	memset(rx_buffer , 0, sizeof(rx_buffer));
//	        		}
//	        	}
//	            // Handle the received data
//	            // Example: Toggle an LED or process the data
//	        	if(HAL_UART_Receive_IT(&huart1, rx_buffer, RX_BUFFER_SIZE) != HAL_OK)
//	        	{
//	        		Error_Handler();
//	        	}
//	        }
//
//	    if (huart->Instance == USART6) {
//	        	rx_buffer_6[rx_index_6]=huart->Instance->RDR;
//	        	rx_index_6++;
//	        	if(rx_index_6 == 8)
//	        	{
//	        	//parse_modbus_frame(rx_buffer);
//	        		if(check_data(rx_buffer_6) == 8)
//	        		{
//	        	rx_index_6=0;
//	        	memset(rx_buffer_6, 0, sizeof(rx_buffer_6));
//	        		}
//	        	}
//	            // Handle the received data
//	            // Example: Toggle an LED or process the data
//	        	if(HAL_UART_Receive_IT(&huart6, rx_buffer_6, RX_BUFFER_SIZE) != HAL_OK)
//	        	{
//	        		Error_Handler();
//	        	}
//	        }
//
//	    if (huart->Instance == USART10) {
//	        	rx_buffer_10[rx_index_10]=huart->Instance->RDR;
//	        	rx_index_10++;
//	        	if(rx_index_10 == 8)
//	        	{
//	        	//parse_modbus_frame(rx_buffer);
//	        		if(check_data(rx_buffer_10) == 8)
//	        		{
//	        	rx_index_10=0;
//	        	memset(rx_buffer_10, 0, sizeof(rx_buffer_10));
//	        		}
//	        	}
//	            // Handle the received data
//	            // Example: Toggle an LED or process the data
//	        	if(HAL_UART_Receive_IT(&huart10, rx_buffer_10, RX_BUFFER_SIZE) != HAL_OK)
//	        	{
//	        		Error_Handler();
//	        	}
//	        }
//}

void check_uart_rx6_timeout(void)//needs to be called everytime in main
{
    if (((HAL_GetTick() - last_rx_time) > RX_TIMEOUT_MS))
    {
    	handleCommand(rx_buffer_6);//rx buffer should be of char
    	memcpy(rx_buffer_data_6, rx_buffer_6, sizeof(rx_buffer_6));
    	memset(rx_buffer_6, 0, sizeof(rx_buffer_6));
        rx_index_6= 0;
    }
}

uint8_t get_rx_buffer_data_6()
{
	return &rx_buffer_data_6;
}

void check_uart_rx3_timeout(void)
{
    if (((HAL_GetTick() - last_rx_time) > RX_TIMEOUT_MS))
    {
    	memcpy(rx_buffer_data_3, rx_buffer_3, sizeof(rx_buffer_3));
    	memset(rx_buffer_3, 0, sizeof(rx_buffer_3));
        rx_index_3= 0;
    }
}

uint8_t get_rx_buffer_data_3()
{
	return &rx_buffer_3;
}






















