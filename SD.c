#include "SD.h"
#include "SPI.h"
#include "Exp_1_Fall_2018/Main.h"

uint8_t illegal_command = 1;
uint8_t SD_timeout_error = 2;
uint8_t comm_error = 4;
uint8_t response_error = 5;
uint8_t voltage_error = 6;
uint8_t check_error = 7;

uint8_t CMD0 = 0;
uint8_t CMD8 = 8;
uint8_t CMD55 = 55;
uint8_t CMD58 = 58;
uint9_t ACMD41 = 41;

uint8_t Send_Command(uint8_t CMD_value, uint32_t argument)
{
	uint8_t return_value, send_value, rec_value, error_flag;
	if(CMD_value < 64)
	{
		send_value = 0x40 | CMD_value;
		error_flag = SPI_Transfer(send_value, &rec_value);
		if(error_flag != no_errors)
		{
			return_value = SPI_error;
		}
		if(error_flag == no_errors)
		{
			send_value = (uint8_t) (argument >> 24);
			error_flag = SPI_Transfer(send_value, &rec_value);
			if(error_flag != no_errors)
			{
				return_value = SPI_error;
			}
		}
		if(error_flag == no_errors)
		{
			send_value = (uint8_t) (argument >> 16);
			error_flag = SPI_Transfer(send_value, &rec_value);
			if(error_flag != no_errors)
			{
				return_value = SPI_error;
			}
		}
		if(error_flag == no_errors)
		{
			send_value = (uint8_t) (argument >> 8);
			error_flag = SPI_Transfer(send_value, &rec_value);
			if(error_flag != no_errors)
			{
				return_value = SPI_error;
			}
		}
		if(error_flag == no_errors)
		{
			send_value = (uint8_t) (argument);
			error_flag = SPI_Transfer(send_value, &rec_value);
			if(error_flag != no_errors)
			{
				return_value = SPI_error;
			}
		}
		if(error_flag == no_errors)
		{
			if(CMD_value == CMD0)
				send_value = 0x95;
			else if(CMD_value == CMD8)
				send_value = 0x87;
			else
				send_value = 0x01;
			
			error_flag = SPI_Transfer(send_value, &rec_value);
			if(error_flag != no_errors)
			{
				return_value = SPI_error;
			}
		}
	}
	else
		return_value = illegal_command;
	return return_value;
}

uint8_t Receive_Response(uint8_t num_bytes, uint8_t * rec_array)
{
	uint8_t return_value, error_flag, SPI_value, index;
	uint16_t timeout;
	return_value = no_errors;
	timeout = 0;
	do
	{
		error_flag = SPI_Transfer(0xFF, &SPI_value);
		timeout++;
	} while((SPI_value == 0xFF) && (timeout != 0) && (error_flag == no_errors));
	
	if(error_flag != no_errors)
		return_value = SPI_error;
	else if(timeout == 0)
		return_value = SD_timeout_error;
	else if((SPI_value&0xFE) != 0x00)
	{
		*rec_array = SPI_value;
		return_value = comm_error;
	}
	else
	{
		*rec_array = SPI_value;
		if(num_bytes > 1)
		{
			for(index = 1; index < num_bytes; index++)
			{
				error_flag = SPI_Transfer(0xFF, &SPI_value);
				*(rec_array + index) = SPI_value;
			}
		}
		error_flag = SPI_Transfer(0xFF, &SPI_value);
	}
	return return_value;
}

uint8_t SD_Card_Initialization(void)
{
	uint8_t error_flag, rec_value, index, timeout;
	uint8_t rec_array [5];
	SD_select = 1;
	error_flag = SPI_Master_Init(clock_freq);
	if(error_flag == no_errors)
	{
		for(index = 0; index < 10; index++)
		{
			error_flag = SPI_Transfer(0x00, &rec_value);
		}
	}
	if(error_flag == no_errors)
	{
		SD_select = 0;
		error_flag = Send_Command(CMD0, 0x00000000);
		if(error_flag == no_errors)
		{
			error_flag = Recieve_Response(1, rec_array);
		}
		SD_select = 1;
		if(error_flag != no_errors)
		{
			error_flag = comm_error;
		}
		else if(rec_array[0] != 0x01)
		{
			error_flag = response_error;
		}
	}
	if(error_flag == no_errors)
	{
		SD_select = 0;
		error_flag = Send_Command(CMD8, 0x000001AA);
		if(error_flag == no_errors)
		{
			error_flag = Recieve_Response(5, rec_array);
		}
		SD_select = 1;
		
		if(error_flag != no_errors)
		{
			error_flag = comm_error;
		}
		else if(rec_array[0] != 0x01)
		{
			error_flag = response_error;
		}
		else if(rec_array[3] != 0x01)
		{
			error_flag = voltage_error;
		}
		else if(rec_array[4] != 0xAA)
		{
			error_flag = check_error;
		}
	}
	if(error_flag == no_errors)
	{
		SD_select = 0;
		error_flag = Send_Command(CMD58, 0x00000000);
		if(error_flag == no_errors)
		{
			error_flag = Recieve_Response(5, rec_array);
		}
		SD_select = 1;
		if(error_flag != no_errors)
		{
			error_flag = comm_error;
		}
		else if(rec_array[0] != 0x01)
		{
			error_flag = response_error;
		}
		else if(rec_array[2] != 0x20)
		{
			error_flag = voltage_error;
		}
	}
	if(error_flag == no_errors)
	{
		SD_select - 0;
		timeout = 0;
		do
		{
			error_flag = Send_Command(CMD55, 0x00000000);
			if(error_flag == no_errors)
			{
				error_flag = Recieve_Response(1, rec_array);
			}
			if(error_flag != no_errors)
			{
				error_flag = comm_error;
			}
			else if(rec_array[0] != 0x01)
			{
				error_flag = response_error;
			}
			if(error_flag == no_errors) //ACMD41
			{
				error_flag = Send_Command(ACMD41, 0x40000000);
				if(error_flag == no_errors)
				{
					error_flag = Recieve_Response(1, rec_array);
				}
				if(error_flag != no_errors)
				{
					error_flag = comm_error;
				}
			}
			timeout++;
		} while((error_flag == no_errors) && (rec_array[0] == 0x01) && (timeout != 0);
		SD_select = 1;
		
		if(rec_array[0] != 0x00 && rec_array[0] != 0x01)
		{
			error_flag = response_error;
		}
		else if(timeout == 0)
		{
			error_flag = timeout_error;
		}
	}
	
	if(error_flag == no_errors)
	{
		SD_select = 0;
		error_flag = Send_Command(CMD58, 0x00000000);
		if(error_flag == no_errors)
		{
			error_flag = Recieve_Response(5, rec_array);
		}
		SD_select = 1;
		if(error_flag != no_errors)
		{
			error_flag = comm_error;
		}
		else if(rec_array[0] != 0x01)
		{
			error_flag = response_error;
		}
		else if((rec_array[1] & 0x80) == 0x80)
		{
			if((rec_array[1]&0xC0) == 0xC0)
			{
				//High capacity card
				high_capacity = 0x01;
			}
		}
	}
	return error_flag;
}