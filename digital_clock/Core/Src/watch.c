/*
 * watch.c
 *
 *  Created on: Sep 21, 2024
 *      Author: hyn02
 */


#include "watch.h"
#include "CLCD.h"
#include "7SEG.h"

Watch watch;

bool isLeapYear(uint16_t year)
{
	 if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
}

int getDaysInMonth(Watch* watch)
{
	 uint16_t year = watch->Time.years;
	 uint8_t months = watch->Time.months;
	switch(months)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
	    return 30;
	case 2:
		if(isLeapYear(year))
		{
			return 29;
		}
		else
		{
			return 28;
		}
	default :
		return -1;
	}
}

void updateWatchTime(void)
{
	watch.Time.millisecond++;
	//printf("Seconds1: %d\n", watch.Time.second);

	if(watch.Time.millisecond >= 1000)
	{
		watch.Time.millisecond = 0;
		watch.Time.second++;
	}
	if(watch.Time.second >= 60)
	{
		watch.Time.second = 0;
		watch.Time.minutes++;
	}
	if(watch.Time.minutes >= 60)
	{
		watch.Time.minutes = 0;
		watch.Time.hours++;
	}
	if(watch.Time.hours >= 24)
	{
		watch.Time.hours = 0;
		watch.Time.days++;
	}
	if(watch.Time.days > getDaysInMonth(&watch))
	{
		watch.Time.days = 1;
		watch.Time.months++;
	}
	if(watch.Time.months > 12)
	{
		watch.Time.months = 1;
		watch.Time.years++;
	}
	watch.isLeap = isLeapYear(watch.Time.years);
}

void updateWatchDisplay(void)
{
	char* BuzState;

    // 7SEG
    _7SEG_SetNumber(DGT1, watch.Time.second / 10, OFF);
    _7SEG_SetNumber(DGT2, watch.Time.second % 10, OFF);

    // CLCD
    if(watch.isLeap)
    {
    	sprintf(clcd.str1, "LEAP  %04d.%02d.%02d",
    			watch.Time.years,
				watch.Time.months,
				watch.Time.days);
    }
    else
    {
    	sprintf(clcd.str1, "      %04d.%02d.%02d",
    	    	watch.Time.years,
    			watch.Time.months,
    			watch.Time.days);
    }


    if (BuzLock == 0)
    {
        BuzState = "BZ OFF";
    }
    else if(BuzLock == 1)
    {
    	BuzState = "BZ ON";
    }

    if(watch.WatchMode == MODE_12_HOUR)
    {
    	int displayHour = watch.Time.hours;
    	const char* period = "AM";

    	if (displayHour == 0)
    	{
    	    displayHour = 12; // 0시를 12시로 표시
    	    period = "AM"; // 자정
    	}
    	else if (displayHour < 12)
    	{
    	    period = "AM"; // 오전
    	}
    	else
    	{
    	    period = "PM"; // 오후
    	    if (displayHour > 12)
    	    {
    	        displayHour -= 12;
    	    }
    	}
    	printf("Hours: %d, Minutes: %02d\n", watch.Time.hours, watch.Time.minutes);

    	sprintf(clcd.str2,"%s  %s %02d:%02d",
    			BuzState,
    			period,
				displayHour,
    			watch.Time.minutes);

    }
    else if(watch.WatchMode == MODE_24_HOUR)
    {
    	sprintf(clcd.str2,"%s     %02d:%02d",
    			BuzState,
    			watch.Time.hours,
				watch.Time.minutes
    			);
    }

    CLCD_Puts(0, 0, clcd.str1);
    CLCD_Puts(0, 1, clcd.str2);
}

