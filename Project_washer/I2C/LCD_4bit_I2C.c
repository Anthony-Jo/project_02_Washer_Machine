/*
 * LCD_4bit.c
 *
 * Created: 2019-09-11 오후 3:19:45
 *  Author: Anthony Jo
 */ 

#include "LCD_4bit_I2C.h"

static uint8_t I2CData = 0;

void LCD_pulse_enable()
{
	I2CData |= (1<<LCD_ENABLE); //Enable high
	I2C_TxByte(LCD_SLA, I2CData);
	_delay_ms(1); //data 간의 delay
	I2CData &= ~(1<<LCD_ENABLE); //Enable return to low
	I2C_TxByte(LCD_SLA, I2CData);
	_delay_ms(1);
}
void LCD_clear()
{
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY);
	_delay_ms(2);
}
void LCD_BackLightOn()
{
	I2CData |= (1<<LCD_BACKLIGHT);
}
void LCD_BackLightOff()
{
	I2CData &= ~(1<<LCD_BACKLIGHT);
}
void LCD_Init()
{
	I2C_Init();
	
	_delay_ms(20);	//data sheet에서 15ms 이상 요구
	LCD_WriteCommandInit(0x30);
	_delay_ms(5);	//data sheet에서 4ms 이상 요구
	LCD_WriteCommandInit(0x30);
	_delay_ms(200); //data sheet에서 100ms 이상 요구
	LCD_WriteCommandInit(0x30);
	LCD_WriteCommandInit(COMMAND_4_BIT_MODE);
	LCD_WriteCommand(COMMAND_4_BIT_MODE);				//display off
	LCD_WriteCommand(COMMAND_DISPLAY_OFF);
	LCD_WriteCommand(COMMAND_CLEAR_DISPLAY);
	LCD_WriteCommand(COMMAND_ENTRY_MODE);				//entry mode set
	LCD_BackLightOn();
	LCD_WriteCommand(COMMAND_DISPLAY_ON);
}
void LCD_write_string(char *string)
{
	for(uint8_t i=0; i<string[i]; i++) //종료 문자를 만날 때 까지
	{
		LCD_WriteData(string[i]); //문자 단위 출력
	}
}
void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;	 //[0 15]
	row %= 2;	// [0  1]
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_WriteCommand(command); //커서이동
}
void LCD_WriteCommand(uint8_t cmdData)
{
	I2CData &= ~(1<<LCD_RS);  //RS low
	I2CData = (I2CData & 0x0f) | (cmdData & 0xf0); //cmdData output 상위 4bit
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
	
	I2CData = (I2CData & 0x0f) | ( (cmdData & 0x0f)<<4 ); //cmdData를 4bit shift 하여 하위 data 출력
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
}
void LCD_WriteCommandInit(uint8_t cmdData)
{
	I2CData &= ~(1<<LCD_RS);  //RS low
	I2CData = (I2CData & 0x0f) | (cmdData & 0xf0);
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
}
void LCD_WriteData(uint8_t data)
{
	I2CData |= (1<<LCD_RS);  //RS high
	I2CData = (I2CData & 0x0f) | (data & 0xf0); //data output 상위 4bit
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
	
	I2CData = (I2CData & 0x0f) | ( (data & 0x0f)<<4 ); //data를 4bit shift 하여 하위 data 출력
	I2C_TxByte(LCD_SLA, I2CData);
	LCD_pulse_enable();
}
