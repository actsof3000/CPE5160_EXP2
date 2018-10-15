//Riley Maersch
#ifndef LCD_H
#define LCD_H

#include "Exp_1_Fall_2018/Main.h"

void LCD_Init(void);

void LCD_Print(uint8_t* string, uint8_t lineNum);

void LCD_Clear(void);

#endif