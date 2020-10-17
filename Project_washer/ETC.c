/*
 * ETC.c
 *
 * Created: 2019-09-29 오후 2:28:44
 *  Author: kccistc
 */ 
#include "ETC.h"
#include "./Device/Button.h"

void Mode_State_Button()
{
	if(GetButton_0() == 1)
	{
		LCD_clear();
		switch(Get_WasherMode())
		{
			case REDEY:
			Set_WasherMode(POWER_SET);
			break;
			
			case POWER_SET:
			LCD_clear();
			Set_WasherMode(MINU_SET);
			break;
			
			case MINU_SET:
			Set_WasherMode(SEC_SET);
			break;
			
			case SEC_SET:
			Set_WasherMode(RUN);
			break;
			
			case RUN:
			Set_WasherMode(STOP);
			break;
			
			case STOP:
			Set_WasherMode(RUN);
			break;
			
			case END:
			Set_WasherMode(REDEY);
			break;
		}
	}
}

void Power_state_Button()
{
	if(GetButton_1() == 1)
	{
		LCD_clear();
		switch(Get_WasherPower())
		{
			case POWER_LV1:
			Set_WasherPower(POWER_LV2);
			break;
			
			case POWER_LV2:
			Set_WasherPower(POWER_LV3);
			break;
			
			case POWER_LV3:
			Set_WasherPower(POWER_LV1);
			break;
		}
	}
	else if(GetButton_2() == 1)
	{
		LCD_clear();
		switch(Get_WasherPower())
		{
			case POWER_LV1:
			Set_WasherPower(POWER_LV3);
			break;
			
			case POWER_LV2:
			Set_WasherPower(POWER_LV1);
			break;
			
			case POWER_LV3:
			Set_WasherPower(POWER_LV2);
			break;
		}
	}
}

void Stop_state_Button()
{
	if(GetButton_3() == 1)
	{
		LCD_clear();
		switch(Get_WasherMode())
		{	
			case POWER_SET:
			Set_WasherMode(REDEY);
			break;
			
			case MINU_SET:
			Set_WasherMode(POWER_SET);
			break;
			
			case SEC_SET:
			Set_WasherMode(MINU_SET);
			break;
			
			case RUN:
			Set_WasherMode(SEC_SET);
			break;
			
			case STOP:
			Set_WasherMode(REDEY);
			break;
			
			case END:
			Set_WasherMode(REDEY);
			break;
		}
	}
}

void Minu_state_Button(uint8_t m)
{
	if(GetButton_1() == 1)
	{
		m += 5;
		Set_Minu(m);
		if(Get_Minu() >= 59)
		{
			m = 0;
			Set_Minu(m);
		}
	}
	else if(GetButton_2() == 1)
	{
		m -= 5;
		Set_Minu(m);
		if(Get_Minu() >= 59)
		{
			m = 55;
			Set_Minu(m);
		}
	}
}

void Sec_state_Button(uint8_t s)
{
	if(GetButton_1() == 1)
	{
		s += 5;
		Set_Sec(s);
		if(Get_Sec() >= 59)
		{
			s = 0;
			Set_Sec(s);
		}
	}
	else if(GetButton_2() == 1)
	{
		s -= 5;
		Set_Sec(s);
		if(Get_Sec() >= 59)
		{
			s = 55;
			Set_Sec(s);
		}
	}
}