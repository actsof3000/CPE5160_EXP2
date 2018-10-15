#include "SPI.h"
#include "Exp_1_Fall_2018/Main.h"

uint8_t no_errors = 0;
uint8_t clock_rate_error = 1;
uint8_t timeout_error = 2;
uint8_t SPI_error = 3;

uint8_t SPI_Master_Init(uint32_t clock_freq)
{
	uint8_t divider;
	divider = (OSC_FREQ*6) / (OSC_PER_INST*clock_freq);
	
	if(divider < 2)
		SPCON=0x70|(CPOL<<3)|(CPHA<<2);
	else if(divider < 4)
		SPCON=0x71|(CPOL<<3)|(CPHA<<2);
	else
		return clock_rate_error;
	return no_errors;
}

uint8_t SPI_Transfer(uint8_t send_value, uint8_t * rec_value)
{
	uint8_t error_flag, status, timeout;
	timeout = 0;
	SPDAT = send_value;
	do
	{
		status = SPSTA;
		timeout++;
	} while(((status&0xF0)==0)&&(timeout!=0));
	
	if(timeout==0)
	{
		*rec_value = 0xFF;
		error_flag = timeout_error;
	}
	else if((status & 0x70) != 0)
	{
		*rec_value = 0xFF;
		error_flag = timeout_error;
	}
	else
	{
		*rec_value = SPDAT;
		error_flag = no_errors;
	}
	return error_flag;
}