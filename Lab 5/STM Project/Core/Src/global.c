/*
 * global.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Admin
 */
#include "global.h"

UART_HandleTypeDef huart2;
ADC_HandleTypeDef hadc1;

enum status state = INIT;
enum status_uart state_uart = INIT_UART;
enum identify cmd = none;
int parse_flag = 0;


int temp = 0;
int buffer[MAX_BUFFER_SIZE];
int buffer_flag = 0;
int index_buffer = 0;
uint32_t ADC_value = 0;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		buffer[index_buffer++] = temp;
		// Check index
		if (index_buffer == MAX_BUFFER_SIZE)
			index_buffer = 1;
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}