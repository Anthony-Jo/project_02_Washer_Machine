/*
 * LED.h
 *
 * Created: 2019-09-12 오후 3:42:15
 *  Author: Anthony Jo
 */ 


#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRA
#define LED_PORT PORTA

#define LED_4	4
#define LED_5	5
#define LED_6	6
#define LED_7	7

void LED_Init();
void OFF_LED();
void On_LED_4();
void On_LED_5();
void On_LED_6();
void On_LED_7();
void Toggle_LED_4();
void Toggle_LED_5();
void Toggle_LED_6();
void Toggle_LED_7();
void On_LED_0011();
void On_LED_0111();
void On_LED_1111();

#endif /* LED_H_ */