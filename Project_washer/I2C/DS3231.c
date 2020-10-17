/*
 * DS3231.c
 *
 * Created: 2019-09-24 오후 4:03:27
 *  Author: kccistc
 */ 
#include "DS3231.h"

static uint8_t B2D(uint8_t bcd);
static uint8_t D2B(uint8_t decimal);

char *wday[7] = {"SUN","MON","TUE","WED","THR","FRI","SAT"};
	
void DS3231_Init()
{
	I2C_Init();
}
void DS3231_SetTimeDate(DS3231 rtc)
{
	uint8_t clock[7];
	
	clock[0] = D2B(rtc.sec);
	clock[1] = D2B(rtc.minu);
	clock[2] = D2B(rtc.hour);
	clock[3] = D2B(rtc.wday);
	clock[4] = D2B(rtc.date);
	clock[5] = D2B(rtc.month);
	clock[6] = D2B(rtc.year);
	
	I2C_TxBuffer(DS3231_SLA, 0x00, clock, sizeof(clock));
}
void DS3231_SetTime(DS3231 rtc)
{
	uint8_t clock[3];
	
	clock[0] = D2B(rtc.sec);
	clock[1] = D2B(rtc.minu);
	clock[2] = D2B(rtc.hour);
	
	I2C_TxBuffer(DS3231_SLA, 0x00, clock, sizeof(clock));
}
void DS3231_SetDate(DS3231 rtc)
{
	uint8_t clock[4];
	
	clock[0] = D2B(rtc.wday);
	clock[1] = D2B(rtc.date);
	clock[2] = D2B(rtc.month);
	clock[3] = D2B(rtc.year);
	
	I2C_TxBuffer(DS3231_SLA, 0x00, clock, sizeof(clock));
}

void DS3231_GetTimeDate(DS3231 *rtc)
{
	uint8_t clock[7];
	
	I2C_RxBuffer(DS3231_SLA, 0x00, clock, sizeof(clock));
	
	rtc->sec	= B2D(clock[0]);
	rtc->minu	= B2D(clock[1]);
	rtc->hour	= B2D(clock[2]);
	rtc->wday	= B2D(clock[3]);
	rtc->date	= B2D(clock[4]);
	rtc->month	= B2D(clock[5]);
	rtc->year	= B2D(clock[6]);
}
void DS3231_GetTime(DS3231 *rtc)
{
	uint8_t clock[3];
	
	I2C_RxBuffer(DS3231_SLA, 0x00, clock, sizeof(clock));
	
	rtc->sec	= B2D(clock[0]);
	rtc->minu	= B2D(clock[1]);
	rtc->hour	= B2D(clock[2]);
}
void DS3231_GetDate(DS3231 *rtc)
{
	uint8_t clock[4];
	
	I2C_RxBuffer(DS3231_SLA, 0x00, clock, sizeof(clock));
	
	rtc->wday	= B2D(clock[0]);
	rtc->date	= B2D(clock[1]);
	rtc->month	= B2D(clock[2]);
	rtc->year	= B2D(clock[3]);
}
void DS3231_SetAlarm_1(DS3231 alm)
{
	uint8_t clock[4];
	
	clock[0] = D2B(alm.sec);
	clock[1] = D2B(alm.minu);
	clock[2] = D2B(alm.hour);
	clock[3] = D2B(alm.date);
	
	I2C_TxBuffer(DS3231_SLA, 0x07, clock, sizeof(clock));
}
void DS3231_SetAlarm_2(DS3231 alm)
{
	uint8_t clock[3];
	
	clock[0] = D2B(alm.minu);
	clock[1] = D2B(alm.hour);
	clock[2] = D2B(alm.date);
	
	I2C_TxBuffer(DS3231_SLA, 0x0B, clock, sizeof(clock));
}
void DS3231_GetAlram_1(DS3231 *alm)
{
	uint8_t clock[4];
	
	I2C_RxBuffer(DS3231_SLA, 0x07, clock, sizeof(clock));
	
	alm->sec	= B2D(clock[0]);
	alm->minu	= B2D(clock[1]);
	alm->hour	= B2D(clock[2]);
	alm->date	= B2D(clock[3]) | (1<<7);
}
void DS3231_GetAlram_2(DS3231 *alm)
{
	uint8_t clock[3];
	
	I2C_RxBuffer(DS3231_SLA, 0x0b, clock, sizeof(clock));
	
	alm->minu	= B2D(clock[0]);
	alm->hour	= B2D(clock[1]);
	alm->date	= B2D(clock[2]) | (1<<7);
}
void DS3231_SetAlarmFlag(FLAG ala)
{
	uint8_t flag[1];
	
	flag[0] = D2B(ala.alarm);
	
	I2C_TxBuffer(DS3231_SLA, 0x0F, flag, sizeof(flag));
}
void DS3231_GetAlarmFlag(FLAG *ala)
{
	uint8_t flag[1];
	
	I2C_RxBuffer(DS3231_SLA, 0x0F, flag, sizeof(flag));
	
	ala->alarm = B2D(flag[0]);
}
uint8_t B2D(uint8_t bcd)
{
	return (bcd >> 4) * 10 + (bcd & 0x0F);
}
uint8_t D2B(uint8_t decimal)
{
	return (((decimal / 10) << 4) | (decimal % 10));
}
