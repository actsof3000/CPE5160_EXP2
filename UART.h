//Riley Maersch
#ifndef UART_H
#define UART_H

#include "Exp_1_Fall_2018/Main.h"

#define SMOD1 1
#define SPD 0

void UART_Initialization(uint16_t baudRate);

uint8_t UART_Transmit(uint8_t sendValue);

uint8_t UART_Receive(void);

#endif