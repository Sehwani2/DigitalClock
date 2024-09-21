/*
 * lap.h
 *
 *  Created on: Aug 28, 2024
 *      Author: hyn02
 */

#ifndef INC_LAP_H_
#define INC_LAP_H_

#include "CLCD.h"
#include "main.h"
#include "stopwatch.h"

//lap
typedef enum _LapState{
	Measure,
	Display,
	Clear,
	Ready
}LapState;

typedef struct _Lap{
	int count;
	int CurrnetDisplay;
	StopWatchTime record[9];
	LapState state;
}Lap;

extern Lap lap;


void LapMeasure();
void LapDisplay();
void LapClear();
void handleLapState();

#endif /* INC_LAP_H_ */
