#include "lcd.h"

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04

static void LCD_SendInternal(uint8_t data, uint8_t flags)
{
    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up | flags | LCD_BACKLIGHT | LCD_ENABLE;
    data_arr[1] = up | flags | LCD_BACKLIGHT;
    data_arr[2] = lo | flags | LCD_BACKLIGHT | LCD_ENABLE;
    data_arr[3] = lo | flags | LCD_BACKLIGHT;

    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_arr, 4, HAL_MAX_DELAY);
}

void LCD_SendCommand(uint8_t cmd)
{
    LCD_SendInternal(cmd, 0x00);
}

void LCD_SendData(uint8_t data)
{
    LCD_SendInternal(data, 0x01);
}

void LCD_Init(void)
{
    HAL_Delay(50);

    LCD_SendCommand(0x33);
    LCD_SendCommand(0x32);
    LCD_SendCommand(0x28); // 4-bit, 2 line
    LCD_SendCommand(0x0C); // display ON
    LCD_SendCommand(0x06); // increment
    LCD_SendCommand(0x01); // clear
    HAL_Delay(5);
}

void LCD_Clear(void)
{
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_SendCommand(addr);
}

void LCD_PrintString(char *str)
{
    while (*str)
    {
        LCD_SendData(*str++);
    }
}
void LCD_PrintFloat(float value, uint8_t decimals)
{
    int int_part = (int)value;
    int frac_part = (int)((value - int_part) * 10);

    char buf[16];
    sprintf(buf, "%d.%d", int_part, frac_part);
    LCD_PrintString(buf);
}
