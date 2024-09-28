/*
 * alarm.h
 *
 *  Created on: Sep 27, 2024
 *      Author: hyn02
 */

#ifndef INC_ALARM_H_
#define INC_ALARM_H_

#include "main.h"

#define MAX_ALARMS 5

typedef struct _AlarmTime{
	uint8_t hour;
	uint8_t minute;
	uint8_t isEnabled;
}AlarmTime;

typedef struct _Alarm{
	uint8_t alarmIndex;
	uint8_t alertFlag;
	uint8_t ledState;
	uint8_t ledTimer;
	AlarmTime alarmTime[MAX_ALARMS];
}Alarm;



void displayAlarmSettings(void);
void alert(void);
extern Alarm alarm;



#endif /* INC_ALARM_H_ */
