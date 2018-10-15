//Riley Maersch
#include "UART.h"
#include "Exp_1_Fall_2018/AT89C51RC2.h"
#include "Util.h"
#include "Exp_1_Fall_2018/Main.h"

void UART_Initialization(uint16_t baudRate) 
{	
	PCON &= 0x3F;
	PCON |= (SMOD1 << 7);
	ES=0;
	SCON |= 0x50;
	TI = 1;
	BDRCON = 0x00;
	BRL = (uint8_t) (256-(((1+(5*SPD))*(1+(1*SMOD1))*OSC_FREQ)/(32*OSC_PER_INST*(uint32_t)baudRate)));
	BDRCON = 0x1C | (SPD << 1);
}

uint8_t UART_Transmit(uint8_t sendValue)
{
	while(!TI) { delay_ms(50); }
	SBUF =  sendValue;
	TI = 0;
	return sendValue;
}

uint8_t UART_Receive(void)
{
	uint8_t tmp8 = 0x00;
	while(!RI) { delay_ms(50); }
	tmp8 = SBUF;
	RI = 0;
	return tmp8;
}