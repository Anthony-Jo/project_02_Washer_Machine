/*
 * Button.c
 *
 * Created: 2019-09-12 오전 10:34:03
 * Author : Anthony Jo
*/

#include "Button.h"


void Button_Init()
{
	BUTTON_DDR &= ~( (1<<BUTTON_0) | (1<<BUTTON_1) |(1<<BUTTON_2) |(1<<BUTTON_3) );

}
uint8_t GetButton_0() //if push the button_0
{
	static uint8_t prevButton_0State = 1; 
	return GetButton(BUTTON_0, &prevButton_0State); //changed at low edge
}
uint8_t GetButton_1() //if push the button_1
{
	static uint8_t prevButton_1State = 1;
	return GetButton(BUTTON_1, &prevButton_1State); //changed at low edge
}
uint8_t GetButton_2() //if push the button_2
{
	static uint8_t prevButton_2State = 1;
	return GetButton(BUTTON_2, &prevButton_2State); //changed at low edge
}
uint8_t GetButton_3() //if push the button_3
{
	static uint8_t prevButton_3State = 1;
	return GetButton(BUTTON_3, &prevButton_3State); //changed at low edge
}
uint8_t GetButton(uint8_t button, uint8_t *prevButtonState)
{
	uint8_t curButtonState = 1;
	
	curButtonState = (PINA & (1<<button)) >> button;
	if ( (curButtonState == 0) && (*prevButtonState == 1) ) //if button has kept pressed, isn't work
	{
		*prevButtonState = curButtonState;
		return 0;
	}
	else if ( (curButtonState == 1) && (*prevButtonState == 0) ) //if button has kept pressed, isn't work
	{
		*prevButtonState = curButtonState;
		return 1;
	}
	return 0;
}


