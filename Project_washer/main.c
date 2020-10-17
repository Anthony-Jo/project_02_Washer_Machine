/*
 * Project_washer.c
 *
 * Created: 2019-09-21 오후 8:46:11
 * Author : Anthony Jo
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ETC.h"
#include "./I2C/LCD_4bit_I2C.h"
#include "./I2C/DS3231.h"
#include "./Device/Button.h"
#include "./Device/LED.h"
#include "./Device/Motor.h"

#define REDEY		0
#define POWER_SET	1
#define MINU_SET	2
#define SEC_SET		3
#define RUN			4
#define STOP		5
#define END			6

#define POWER_LV1	0
#define POWER_LV2	1
#define POWER_LV3	2

volatile uint8_t WasherMode = REDEY;
volatile uint8_t WasherPower = POWER_LV1;
volatile uint8_t WasherTime = MINU_SET;

volatile char lv1[5] = "lv1";
volatile char lv2[5] = "lv2";
volatile char lv3[5] = "lv3";

uint8_t minu = 0, sec = 0;

DS3231 curTime;
DS3231 setTime;

uint8_t Get_WasherMode()
{
	return WasherMode;
}
void Set_WasherMode(uint8_t Mode)
{
	WasherMode = Mode;
}
uint8_t Get_WasherPower()
{
	return WasherPower;
}
void Set_WasherPower(uint8_t Power)
{
	WasherPower = Power;
}
uint8_t Get_WasherTime()
{
	return WasherTime;
}
void Set_WasherTime(uint8_t Time)
{
	WasherTime = Time;
}
uint8_t Get_Minu()
{
	return minu;
}
void Set_Minu(uint8_t m)
{
	minu = m;
}
uint8_t Get_Sec()
{
	return sec;
}
void Set_Sec(uint8_t s)
{
	sec = s;
}
char* Level_Display(uint8_t level)
{
	switch(level)
	{
		case POWER_LV1:
		return lv1;
	
		case POWER_LV2:
		return lv2;
		
		case POWER_LV3:
		return lv3;
		
	}
}

int main(void)
{
	Button_Init();
	DS3231_Init();
	LED_Init();
	LCD_Init();
	Motor_Init();
	
	setTime.sec = 0;
	setTime.minu = 0;
	
	char buff[20] = {0};
	char lv[3] = {0};
		
    while (1) 
    {
		if(WasherMode == REDEY)
		{
			Mode_State_Button();
			OFF_LED();
			
			LCD_goto_XY(0,0);
			sprintf(buff,"Mode: REDEY    ");
			LCD_write_string(buff);
			
			DS3231_GetTimeDate(&curTime);
			LCD_goto_XY(1,0);
			sprintf(buff,"%02d%02d%02d-%02d:%02d:%02d",
			curTime.year, curTime.month, curTime.date, curTime.hour, curTime.minu, curTime.sec);
			LCD_write_string(buff);
		}
		if(WasherMode == POWER_SET)
		{
			Mode_State_Button();
			Stop_state_Button();
			
			switch(WasherPower)
			{
				case POWER_LV1:
				Power_state_Button();
				LCD_goto_XY(0,0);
				sprintf(buff,"Mode: POWER LV1");
				LCD_write_string(buff);
				On_LED_7();
				break;
				
				case  POWER_LV2:
				Power_state_Button();
				LCD_goto_XY(0,0);
				sprintf(buff,"Mode: POWER LV2");
				LCD_write_string(buff);
				On_LED_0011();
				break;
				
				case POWER_LV3:
				Power_state_Button();
				LCD_goto_XY(0,0);
				sprintf(buff,"Mode: POWER LV3");
				LCD_write_string(buff);
				On_LED_0111();
				break;
			}
			LCD_goto_XY(1,0);
			sprintf(buff,"                ");
			LCD_write_string(buff);
		}
		if(WasherMode == MINU_SET)
		{
			Mode_State_Button();
			Stop_state_Button();
			Minu_state_Button(minu);
			
			LCD_goto_XY(0,0);
			sprintf(buff,"Mode: SET MINU ");
			LCD_write_string(buff);
			LCD_goto_XY(1,0);
			sprintf(buff,"%s, %02d:%02d",Level_Display(WasherPower), Get_Minu(), Get_Sec());
			LCD_write_string(buff);
		}
		if(WasherMode == SEC_SET)		
		{
			Mode_State_Button();
			Stop_state_Button();
			Sec_state_Button(sec);
			
			LCD_goto_XY(0,0);
			sprintf(buff,"Mode: SET SEC  ");
			LCD_write_string(buff);
			LCD_goto_XY(1,0);
			sprintf(buff,"%s, %02d:%02d",Level_Display(WasherPower), Get_Minu(), Get_Sec());
			LCD_write_string(buff);	
		}
		if(WasherMode == RUN)
		{
			Mode_State_Button();
			Stop_state_Button();
			LCD_goto_XY(0,0);
			sprintf(buff,"Mode: RUN     ");
			LCD_write_string(buff);
		}
		if(WasherMode == STOP)
		{
			Mode_State_Button();
			Stop_state_Button();
			OFF_LED();
			LCD_goto_XY(0,0);
			sprintf(buff,"Mode: STOP    ");
			LCD_write_string(buff);
		}
		if(WasherMode == END)
		{
			Mode_State_Button();
			Stop_state_Button();
			On_LED_1111();
			sprintf(buff,"Mode: END     ");
			LCD_write_string(buff);
		}
    }

}

