/*
 * alarm.c
 *
 *  Created on: Sep 27, 2024
 *      Author: hyn02
 */


#include "alarm.h"
#include "clcd.h"
#include "watch.h"
#include "btn.h"
#include "7SEG.h"
#include "buzzer.h"

Alarm alarm;

void displayAlarmSettings(void)
{

	int displayHour = alarm.alarmTime[alarm.alarmIndex].hour;
	const char* period = "AM";
	const char* OnOff;

	// 7SEG
	 _7SEG_SetNumber(DGT1, watch.Time.second / 10, OFF);
	 _7SEG_SetNumber(DGT2, watch.Time.second % 10, OFF);


	if(alarm.alarmTime[alarm.alarmIndex].isEnabled)
	{
		OnOff = "ON ";
	}
	else
	{
		OnOff = "OFF";
	}

	if (displayHour == 0)
	{
		displayHour = 12; // 0시를 12시로 표시
		period = "AM"; // 자정
	}
	else if (displayHour < 12)
	{
		period = "AM"; // 오전
	} else
	{
		period = "PM"; // 오후
		if (displayHour > 12)
		{
			displayHour -= 12;
		}
	}

	sprintf(clcd.str1,"ALARM #%d %s",
			alarm.alarmIndex+1,
			OnOff);
	sprintf(clcd.str2,"        %s %02d:%02d",
			period,
			alarm.alarmTime[alarm.alarmIndex].hour,
			alarm.alarmTime[alarm.alarmIndex].minute);

	CLCD_Puts(0, 0, clcd.str1);
	CLCD_Puts(0, 1, clcd.str2);

}

void alert(void)
{
	/////////////LCD///////////////////////////
			if(watch.Time.millisecond < 500)
			{
				sprintf(clcd.str1,"                ");
			}
			else
			{
				sprintf(clcd.str1,"ALARM TRIGGERED!");
			}

			sprintf(clcd.str2,"                ");
			CLCD_Puts(0, 0,clcd.str1);
			CLCD_Puts(0, 1,clcd.str2);
////////////////////////////LED/////////////////////////////
			if(alarm.ledState)
			{
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);

				HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
			}
			else
			{
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
			}
////////////////////////buzzer/////////////////////////
			Buz1.BuzTone = BUZ_TONE_HIGH_PSC;
			Buz1.BuzFlag = true;

	/////////////alarm off////////////////////////////////
			if(Btn1.state == Pressing ||
			   Btn2.state == Pressing ||
			   Btn3.state == Pressing ||
			   Btn4.state == Pressing)
			{
				Btn1.state = Idle;
				Btn2.state = Idle;
				Btn3.state = Idle;
				Btn4.state = Idle;

				mode = previousMode;
				alarm.alertFlag = 0;
			}
}
