/*
 * Motor.h
 *
 * Created: 2019-09-26 오후 5:24:52
 *  Author: kccistc
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include <avr/io.h>

#define MOTOR_DDR		DDRE
#define MOTOR_DDR_3		DDRE3
#define MOTOR_DDR_4		DDRE4

void Motor_Init();
void Motor_Stop();
void Motor_ClockWise(uint16_t PWM);
void Motor_CounterClockWise(uint16_t PWM);

#endif /* MOTOR_H_ */