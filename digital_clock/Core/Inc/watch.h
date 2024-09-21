/*
 * watch.h
 *
 *  Created on: Sep 21, 2024
 *      Author: hyn02
 */

#ifndef INC_WATCH_H_
#define INC_WATCH_H_

#include "main.h"

typedef struct _WatchTime{
	volatile uint16_t years;
	volatile uint8_t months;
	volatile uint8_t days;
	volatile uint8_t hours;
	volatile uint8_t minutes;
	volatile uint8_t second;
	volatile uint16_t millisecond;
}WatchTime;

typedef enum _WatchMode {
    MODE_12_HOUR,
    MODE_24_HOUR,
} WatchMode;

typedef struct _Watch{
	volatile	WatchTime Time;
	bool isLeap;
	WatchMode WatchMode;
}Watch;

extern Watch watch;

bool isLeapYear(uint16_t year);
int getDaysInMonth(Watch* watch);
void updateWatchTime(void);
void updateWatchDisplay(void);

#endif /* INC_WATCH_H_ */
