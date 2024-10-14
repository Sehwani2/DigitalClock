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

#define MAX_LAP 9
//lap

typedef struct _Lap{
	int count;
	int CurrnetDisplay;
	StopWatchTime record[MAX_LAP];
}Lap;

extern Lap lap;


void LapMeasure();
void LapDisplay();
void LapClear();

#endif /* INC_LAP_H_ */
