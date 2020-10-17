/*
 * ETC.h
 *
 * Created: 2019-09-29 오후 2:29:07
 *  Author: kccistc
 */ 


#ifndef ETC_H_
#define ETC_H_
#include <avr/io.h>

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


void Mode_State_Button();
void Power_state_Button();
void Stop_state_Button();
void Minu_state_Button(uint8_t m);
void Sec_state_Button(uint8_t s);

#endif /* ETC_H_ */