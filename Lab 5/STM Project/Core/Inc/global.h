/*
 * global.h
 *
 *  Created on: Dec 8, 2022
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include "fsm_command_parser.h"
#include "fsm_uart_communication.h"
#include "software_timer.h"
#include <stdio.h>
#include <stdlib.h>

#define CLOCK_TICK	10
#define MAX_BUFFER_SIZE	200
#define UART_TIMEOUT	3000

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

extern int command_flag;

enum status
{
	INIT = 0,
	START = 1,			// When typing "!"
	R_O = 2,				// When typing "R"
	S = 3,				// When typing "S"
	T = 4,				// When typing "T"
	K = 5,				// When typing "K"
	WRONG_SYNTAX = 6,	// When typing some wrong chars
	END = 7,			// When typing "#"
	PARSE_COMPLETE = 8,
};

enum status_uart
{
	INIT_UART = 0,
	STANDBY = 1,
	DATA = 2,
};

enum identify
{
	none = 0,
	RST = 1,
	OK = 2
};

extern enum status state;
extern enum status_uart state_uart;
extern enum identify cmd;
extern int cmd_flag;
extern int parse_flag;

extern int temp;
extern int buffer[MAX_BUFFER_SIZE];
extern int buffer_flag;
extern int index_buffer;
extern uint32_t ADC_value;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif /* INC_GLOBAL_H_ */