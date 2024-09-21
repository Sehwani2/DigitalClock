/*
 * stopwatch.c
 *
 *  Created on: Sep 19, 2024
 *      Author: hyn02
 */
#include "stopwatch.h"
#include "CLCD.h"
#include "7SEG.h"

volatile StopWatch stopwatch = {STOPPED,{0,0,0,0}};



void updateStopwatchTime(void)
{
	if(stopwatch.Time.millisecond >= 1000)
	{
		stopwatch.Time.millisecond = 0;
		stopwatch.Time.second++;
	}
	if(stopwatch.Time.second >= 60)
	{
		stopwatch.Time.second = 0;
		stopwatch.Time.minutes++;
	}
	if(stopwatch.Time.minutes >= 60)
	{
		stopwatch.Time.minutes = 0;
		stopwatch.Time.hours++;
	}
	if(stopwatch.Time.hours >= 24)
	{
		stopwatch.Time.hours = 0;
	}
}

void updateStopwatchState(void)
{
    if(stopwatch.State == RUNNING)
    {
    	stopwatch.Time.millisecond++;
        updateStopwatchTime();
    }

    if(stopwatch.State == STOPPED)
    {
    	stopwatch.Time.hours = 0;
    	stopwatch.Time.minutes = 0;
    	stopwatch.Time.second = 0;
    	stopwatch.Time.millisecond = 0;
    }
}

void updateStopwatchDisplay(void)
{
    // 7SEG
    _7SEG_SetNumber(DGT1, stopwatch.Time.second % 10, ON);
    _7SEG_SetNumber(DGT2, stopwatch.Time.millisecond / 100, OFF);

    // CLCD
    sprintf(clcd.str1, "STW %02d:%02d:%02d.%03d",
    		stopwatch.Time.hours,
			stopwatch.Time.minutes,
			stopwatch.Time.second,
			stopwatch.Time.millisecond);

    CLCD_Puts(0, 0, clcd.str1);
}
