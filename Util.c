//Riley Maersch
#include "Util.h"
#include "Exp_1_Fall_2018/Main.h"

void delay_ms(uint8_t num_ms)
{
	uint16_t index1,index2;
	for(index1=0;index1<num_ms;index1++)
	{
		for(index2=0;index2<1000;index2++);
	}
}
