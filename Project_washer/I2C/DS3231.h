/*
 * DS3231.h
 *
 * Created: 2019-09-24 오후 4:03:40
 *  Author: kccistc
 */ 


#ifndef DS3231_H_
#define DS3231_H_
#include <avr/io.h>
#include "I2C_Master.h"

#define DS3231_SLA 0x68

typedef struct _ds3231
{
	uint8_t sec;
	uint8_t minu;
	uint8_t hour;
	uint8_t wday;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} DS3231;
typedef struct _flag
{
	uint8_t alarm;
} FLAG;
extern char *wday[7];

void DS3231_Init();
void DS3231_SetTimeDate(DS3231 rtc);
void DS3231_SetTime(DS3231 rtc);
void DS3231_SetDate(DS3231 rtc);

void DS3231_GetTimeDate(DS3231 *rtc);
void DS3231_GetTime(DS3231 *rtc);
void DS3231_GetDate(DS3231 *rtc);

void DS3231_SetAlarm_1(DS3231 alm);
void DS3231_SetAlarm_2(DS3231 alm);
void DS3231_GetAlram_1(DS3231 *alm);
void DS3231_GetAlram_2(DS3231 *alm);

void DS3231_SetAlarmFlag(FLAG ala);
void DS3231_GetAlarmFlag(FLAG *ala);
#endif /* DS3231_H_ */