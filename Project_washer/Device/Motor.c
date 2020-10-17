/*
 * Motor.c
 *
 * Created: 2019-09-26 오후 5:24:38
 *  Author: kccistc
 */ 
#include "Motor.h"

void Motor_Init()
{
	MOTOR_DDR |= (1<<MOTOR_DDR_3) | (1<<MOTOR_DDR_4);
	TCCR3B |= (0<<WGM33) | (1<<WGM32); //Fast PWM 10bit mode
	TCCR3A |= (1<<WGM31) | (1<<WGM30); //Fast PWM 10bit mode
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0); //비반전모드
	TCCR3A |= (1<<COM3B1) | (0<<COM3B0);
	
	TCCR3B |= (0<<CS32) | (1<<CS31) | (0<<CS30); // 8분주비
	//TCCR3B |= (0<<CS32) | (1<<CS31) | (1<<CS30); // 64분주비
}
void Motor_Stop()
{
	OCR3A = 0;
	OCR3B = 0;
}
void Motor_ClockWise(uint16_t PWM)
{
	OCR3A = PWM;
	OCR3B = 0;
}
void Motor_CounterClockWise(uint16_t PWM)
{
	OCR3A = 0;
	OCR3B = PWM;
}