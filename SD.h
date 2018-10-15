
#ifndef SD_H
#define SD_H

#include "Exp_1_Fall_2018/Main.h"

sbit SD_select = P1^4;

extern uint8_t illegal_command;
extern uint8_t SD_timeout_error;
extern uint8_t comm_error;
extern uint8_t response_error;
extern uint8_t voltage_error;
extern uint8_t check_error;

extern uint8_t CMD0;
extern uint8_t CMD8;
extern uint8_t CMD55;
extern uint8_t CMD58;
extern uint9_t ACMD41;

static uint32_t clock_freq = 200000;

static uint8_t high_capacity = 0x00;

uint8_t Send_Command(uint8_t CMD_value, uint32_t argument);

uint8_t Receive_Response(uint8_t num_bytes, uint8_t * rec_array);

uint8_t SD_Card_Initialization(void);

#endif