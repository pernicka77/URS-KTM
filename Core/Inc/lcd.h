#ifndef LCD_H
#define LCD_H

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR (0x27 << 1)  // ako ne radi, kasnije probamo 0x3F

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_PrintString(char *str);
void LCD_PrintFloat(float value, uint8_t decimals);

#endif
