/*
 * Button.h
 *
 * Created: 2019-09-12 오전 10:35:11
 *  Author: Anthony Jo
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

#define F_CPU	16000000UL
#include <avr/io.h>

#define BUTTON_DDR		DDRA
#define BUTTON_PIN		PINA
#define BUTTON_0		0			
#define BUTTON_1		1 
#define BUTTON_2		2
#define BUTTON_3		3

void Button_Init();
uint8_t GetButton_0(); 
uint8_t GetButton_1(); 
uint8_t GetButton_2(); 
uint8_t GetButton_3();
uint8_t GetButton(uint8_t button, uint8_t *prevButtonState);

#endif /* BUTTON_H_ */