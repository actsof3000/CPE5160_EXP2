#ifndef SPI_H
#define SPI_H

#include "Exp_1_Fall_2018/Main.h"

static uint8_t CPOL = 0;
static uint8_t CPHA = 0;

extern uint8_t no_errors;
extern uint8_t clock_rate_error;
extern uint8_t timeout_error;
extern uint8_t SPI_error;

uint8_t SPI_Master_Init(uint32_t clock_freq);

uint8_t SPI_Transfer(uint8_t send_value, uint8_t * rec_value);

#endif