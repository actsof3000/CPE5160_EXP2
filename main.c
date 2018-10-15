#include "Exp_1_Fall_2018/Main.h"
#include "Exp_1_Fall_2018/PORT.h"
#include "stdio.h"
#include "UART.h"
#include "Util.h"
#include "LCD.h"
#include "Exp_1_Fall_2018/print_bytes.h"
#include "Exp_1_Fall_2018/memory_test.h"

//Riley Maersch
void main()
{
	uint8_t string[] = "This is a test";
//	uint8_t *ptr;
//	UART_Initialization((uint16_t)9600);
	LCD_Init();
	GREENLED = 0;
	delay_ms(1000);
	GREENLED = 1;

	LCD_Print(string, 1);
	
//	ptr = code_memory_init();
//	print_memory(ptr, 80);
//	UART_Transmit('\n');
//	ptr = xdata_memory_init();
//	print_memory(ptr, 80);
	
	
	 
	while(1) 
	{	
	} 
}