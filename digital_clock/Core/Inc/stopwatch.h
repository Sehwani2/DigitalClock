/*
 * stopwatch.h
 *
 *  Created on: Sep 19, 2024
 *      Author: hyn02
 */


#ifndef INC_STOPWATCH_H_
#define INC_STOPWATCH_H_

#include "main.h"

// STOPWATCH
typedef enum _StopWatchState{
	RUNNING,
	PAUSED,
	STOPPED
}StopWatchState;

typedef struct _StopWatchTime{
	uint8_t hours;
	uint8_t minutes;
	uint8_t second;
	uint16_t millisecond;
}StopWatchTime;

typedef struct _StopWatch{
	StopWatchState State;
	StopWatchTime Time;
}StopWatch;

extern volatile  StopWatch stopwatch;

void updateStopwatchTime(void);
void updateStopwatchState(void);
void updateStopwatchDisplay(void);

#endif /* INC_STOPWATCH_H_ */
