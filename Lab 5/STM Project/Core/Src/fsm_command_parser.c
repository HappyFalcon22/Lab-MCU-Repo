/*
 * fsm_commang_parser.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Admin
 */

#include "global.h"


void command_parser_fsm()
{
	switch(state)
	{
	case INIT:;
		state = START;
		break;
	case START:
		if (buffer_flag == 1)
		{
			// Reset params here
			cmd = none;
			buffer_flag = 0;
			int received = buffer[index_buffer - 1];
			if (received == 33)
			{
				char str[1];
				sprintf(str, "%c", received);
				HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
				state = R_O;
			}
			else
				state = WRONG_SYNTAX;
		}
		break;
	case R_O:
		if (buffer_flag == 1)
		{
			buffer_flag = 0;
			int received = buffer[index_buffer - 1];
			if (received == 82) // Type "S"
			{
				char str[1];
				sprintf(str, "%c", received);
				HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
				state = S;
			}
			else
			{
				if (received == 79) // Type "O"
				{
					char str[1];
					sprintf(str, "%c", received);
					HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
					state = K;
				}
				else
					state = WRONG_SYNTAX;
			}
		}
		break;
	case S:
		cmd = RST;
		if (buffer_flag == 1)
		{
			buffer_flag = 0;
			int received = buffer[index_buffer - 1];
			if (received == 83)
			{
				char str[1];
				sprintf(str, "%c", received);
				HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
				state = T;
			}
			else
				state = WRONG_SYNTAX;
		}
		break;
	case T:
		if (buffer_flag == 1)
		{
			buffer_flag = 0;
			int received = buffer[index_buffer - 1];
			if (received == 84)
			{
				char str[1];
				sprintf(str, "%c", received);
				HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
				state = END;
			}
			else
				state = WRONG_SYNTAX;
		}
		break;
	case K:
		cmd = OK;
		if (buffer_flag == 1)
		{
			buffer_flag = 0;
			int received = buffer[index_buffer - 1];
			if (received == 75)
			{
				char str[1];
				sprintf(str, "%c", received);
				HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
				state = END;
			}
			else
				state = WRONG_SYNTAX;
		}
		break;
	case END:
		if (buffer_flag == 1)
		{
			buffer_flag = 0;
			int received = buffer[index_buffer - 1];
			if (received == 35)		// Type "#"
			{
				char str[1];
				sprintf(str, "%c", received);
				HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
				state = PARSE_COMPLETE;
			}
			else
				state = WRONG_SYNTAX;
		}
		break;
	case WRONG_SYNTAX:;
		char str[] = "\r\nType again\r\n";
		HAL_UART_Transmit(&huart2, str, sizeof(str), 1000);
		state = INIT;
		break;
	case PARSE_COMPLETE:;
		parse_flag = 1;
		if (cmd == RST)
		{
			char str1[] = "\r\nCompleted : !RST#\r\n";
			HAL_UART_Transmit(&huart2, str1, sizeof(str1), 1000);
		}
		if (cmd == OK)
		{
			char str1[] = "\r\nCompleted : !OK#\r\n";
			HAL_UART_Transmit(&huart2, str1, sizeof(str1), 1000);
		}
		state = INIT;
		break;
	default:
		break;
	}
}