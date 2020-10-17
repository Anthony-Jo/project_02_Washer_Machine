/*
 * LED.c
 *
 * Created: 2019-09-12 오후 3:42:03
 *  Author: Anthony Jo
 */ 

#include "LED.h"

void LED_Init()
{
	LED_DDR |= (1<<LED_4) | (1<<LED_5) | (1<<LED_6) | (1<<LED_7);
}
void OFF_LED()
{
	LED_PORT &= ~((1<<LED_4) | (1<<LED_5) | (1<<LED_6) | (1<<LED_7));
}
void On_LED_4()
{
	LED_PORT |= (1<<LED_4); 
	LED_PORT &= ~((1<<LED_5) | (1<<LED_6) | (1<<LED_7));
}
void On_LED_5()
{
	LED_PORT |= (1<<LED_5);
	LED_PORT &= ~((1<<LED_4) | (1<<LED_6) | (1<<LED_7));
}
void On_LED_6()
{
	LED_PORT |= (1<<LED_6);
	LED_PORT &= ~((1<<LED_4) | (1<<LED_5) | (1<<LED_7));
}
void On_LED_7()
{
	LED_PORT |= (1<<LED_7);
	LED_PORT &= ~((1<<LED_4) | (1<<LED_5) | (1<<LED_6));
}
void Toggle_LED_4()
{
	LED_PORT ^= (1<<LED_4);
}
void Toggle_LED_5()
{
	LED_PORT ^= (1<<LED_5);
}
void Toggle_LED_6()
{
	LED_PORT ^= (1<<LED_6);
}
void Toggle_LED_7()
{
	LED_PORT ^= (1<<LED_7);
}
void On_LED_0011()
{
	LED_PORT |= (1<<LED_6) | (1<<LED_7);
	LED_PORT &= ~((1<<LED_4) | (1<<LED_5));
}
void On_LED_0111()
{
	LED_PORT |= (1<<LED_5) | (1<<LED_6) | (1<<LED_7);
	LED_PORT &= ~((1<<LED_4));
}
void On_LED_1111()
{
	LED_PORT |= (1<<LED_4) | (1<<LED_5) | (1<<LED_6) | (1<<LED_7);
}