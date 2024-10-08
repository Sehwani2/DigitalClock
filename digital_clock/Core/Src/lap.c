/*
 * lap.c
 *
 *  Created on: Aug 28, 2024
 *      Author: hyn02
 */


#include "lap.h"

Lap lap;

void LapMeasure()
{
	// when lap is full
	if(lap.count >= 9)
	{
		sprintf(clcd.str2,"LAP FULL(9/9)   ");
	}
	else // measure lap and store it
	{
		lap.record[lap.count].hours 		= stopwatch.Time.hours;
		lap.record[lap.count].minutes		= stopwatch.Time.minutes;
		lap.record[lap.count].second		= stopwatch.Time.second;
		lap.record[lap.count].millisecond	= stopwatch.Time.millisecond;

		sprintf(clcd.str2,"LP%1d %02d:%02d:%02d.%03d",
					lap.count+1,
					lap.record[lap.count].hours,
					lap.record[lap.count].minutes,
					lap.record[lap.count].second,
					lap.record[lap.count].millisecond
				);
		lap.count++;
	}

	CLCD_Puts(0, 1, clcd.str2);
	lap.CurrnetDisplay =0;
	lap.state = Ready;

}

void LapDisplay()
{
	if(lap.count == 0 ) sprintf(clcd.str2, "NO LAP          ");
	else
	{
		if(lap.count == lap.CurrnetDisplay)
		{
			lap.CurrnetDisplay = 0;
		}
		sprintf(clcd.str2,"%d/%d %02d:%02d:%02d.%03d",
						lap.CurrnetDisplay+1,
						lap.count,
						lap.record[lap.CurrnetDisplay].hours,
						lap.record[lap.CurrnetDisplay].minutes,
						lap.record[lap.CurrnetDisplay].second,
						lap.record[lap.CurrnetDisplay].millisecond
				);
		lap.CurrnetDisplay++;
	}
	CLCD_Puts(0, 1, clcd.str2);
	lap.state = Ready;
}

void LapClear()
{
	sprintf(clcd.str2,"                ");
	CLCD_Puts(0, 1, clcd.str2);
	lap.count = 0;
	lap.CurrnetDisplay = 0;
	lap.state  = Ready;
}

void handleLapState()
{
    switch (lap.state)
    {
        case Measure:
            LapMeasure();
            break;

        case Display:
            LapDisplay();
            break;

        case Clear:
            LapClear();
            break;
    }
}
