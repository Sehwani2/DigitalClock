/*
 * btn.c
 *
 *  Created on: Sep 17, 2024
 *      Author: hyn02
 */
#include "btn.h"
#include "watch.h"

Button Btn1;
Button Btn2;
Button Btn3;
Button Btn4;

void InitializeButtons(void)
{
    Btn1.is_pressed = false;
    Btn2.is_pressed = false;
    Btn3.is_pressed = false;
    Btn4.is_pressed = false;

    Btn1.ReleasedTime = Idle_Released;
    Btn2.ReleasedTime = Idle_Released;
    Btn3.ReleasedTime = Idle_Released;
    Btn4.ReleasedTime = Idle_Released;

    Btn1.holdTime = BtnHold_Idle;
    Btn2.holdTime = BtnHold_Idle;
    Btn3.holdTime = BtnHold_Idle;
    Btn4.holdTime = BtnHold_Idle;

    Btn1.btnThreshold = Idle_Threshold;
    Btn2.btnThreshold = Idle_Threshold;
    Btn3.btnThreshold = Idle_Threshold;
    Btn4.btnThreshold = Idle_Threshold;
}

void HandleButtonPress(Button *btn, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin_Num)
{
	if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin_Num) == GPIO_PIN_SET)
	{
		if (btn->is_pressed == false)// to reduce debouncing
		{
			btn->is_pressed = true;


			if (btn->state == Idle)
			{
				btn->state = Pressing;
			}
		}
	}
	else if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin_Num) == GPIO_PIN_RESET)
	{
		if (btn->is_pressed == true) // to reduce debouncing
		{

			btn->is_pressed = false;

			if (btn->state == Pressing)
			{
				btn->state = Released;
				CheckButtonPressTime(btn);

			}
			btn->millisecond = 0;
			btn->state = Idle;
		}
	}
}

void CheckButtonPressTime(Button* Btn)
{
	if(Btn->millisecond < SHORT_PRESS_TIME)
	{
		Btn->ReleasedTime = Short_Released;
	}
	else if(Btn->millisecond < LONG_PRESS_TIME)
	{
		Btn->ReleasedTime = Mid_Released;
	}
	else
	{
		Btn->ReleasedTime = Long_Released;
	}
}

void BtnHoldEvent(Button* btn,GPIO_TypeDef* GPIO,uint16_t GPIO_PIN )
{	// HOLD EVENT
	if((HAL_GPIO_ReadPin(GPIO, GPIO_PIN) == GPIO_PIN_SET) && btn->state == Pressing)
	{
		if (btn->millisecond < LONG_PRESS_TIME + 51)
		{
			btn->millisecond++;
		}

	}
}

void CheckBtnHoldingTime(Button* btn,GPIO_TypeDef* GPIO,uint16_t GPIO_PIN )
{
	// Holding Time
	if(btn->millisecond < SHORT_PRESS_TIME)
	{
		btn->holdTime = BtnHold_Short;
	}
	else if(btn->millisecond < LONG_PRESS_TIME)
	{
		btn->holdTime = BtnHold_Mid;
	}
	else
	{
		btn->holdTime = BtnHold_Long;
	}
}

void BtnThresHoldEvent(Button* btn,GPIO_TypeDef* GPIO,uint16_t GPIO_PIN )
{
	if(btn->millisecond >= (SHORT_PRESS_TIME - 50) &&
	   btn->millisecond <= (SHORT_PRESS_TIME + 50)	)
	{
		btn->btnThreshold = Short_Mid_Threshold;
		Buz1.BuzTone = BUZ_TONE_MID_PSC;
		Buz1.BuzFlag = true;
	}
	else if(btn->millisecond >= (LONG_PRESS_TIME - 50) &&
			btn->millisecond <= (LONG_PRESS_TIME + 50))
	{
		btn->btnThreshold = Mid_Long_Threshold;
		Buz1.BuzTone = BUZ_TONE_HIGH_PSC;
		Buz1.BuzFlag = true;
	}
}
///////////////////////////////////////////////////
// watch Btn
void WatchHandleButton1(void)
{
	if (Btn1.state == Pressing)
	{
		CheckBtnHoldingTime(&Btn1, GPIOE, GPIO_PIN_3);
		BtnThresHoldEvent(&Btn1, GPIOE, GPIO_PIN_3);

		if (Btn1.btnThreshold == Short_Mid_Threshold)
		{
			watchConfig.SubMode = !watchConfig.SubMode;
			CLCD_Clear();
			Btn1.btnThreshold = Idle_Threshold;
		}
	}
	else // released
	{
		if(Btn1.ReleasedTime == Short_Released)
		{
			if (watchConfig.SubMode == WATCH_NORMAL)
			{
				CLCD_Clear();
				mode = (mode + 1) % NUM_MODES;
			}
			Btn1.ReleasedTime = Idle_Released;
		}
	}
}

void WatchHandleButton2(void)
{
	if (Btn2.state == Pressing)
	{
		CheckBtnHoldingTime(&Btn2, GPIOC, GPIO_PIN_15);
		BtnThresHoldEvent(&Btn2, GPIOC, GPIO_PIN_15);

		if (watchConfig.NextItem
				&& watchConfig.SubMode == WATCH_CLOCK_SETTING)
		{
			watchConfig.NextItem = 0;
			watchConfig.WatchTime = (watchConfig.WatchTime + 1) % NUM_ITEM;
		}
	}
	else	// released
	{
		if(Btn2.ReleasedTime == Short_Released)
		{
			if (watchConfig.SubMode == WATCH_NORMAL)
			{
				BuzLock = !BuzLock;
			}
			Btn2.ReleasedTime = Idle_Released;
		}
	}
}

void WatchHandleButton3(void)
{
	if (Btn3.state == Pressing)
	{
		CheckBtnHoldingTime(&Btn3, GPIOD, GPIO_PIN_4);
		BtnThresHoldEvent(&Btn3, GPIOD, GPIO_PIN_4);

		if (watchConfig.flags.increaseFlagOnce)
		{
			watchConfig.flags.increaseFlagOnce = 0;
			IncreaseTimeOnce();
		}

		switch (Btn3.holdTime)
		{
		case BtnHold_Mid:
			if (watchConfig.flags.increaseFlag150ms)
			{
				watchConfig.flags.increaseFlag150ms = 0;
				IncreaseTimeOnce();
			}
			break;
		case BtnHold_Long:
			if (watchConfig.flags.increaseFlag20ms)
			{
				watchConfig.flags.increaseFlag20ms = 0;
				IncreaseTimeOnce();
			}
			break;
		}

	}
	else 	// released
	{
		if(Btn3.ReleasedTime == Short_Released)
		{
			if (watchConfig.SubMode == WATCH_NORMAL)
			{
				watch.WatchMode = !watch.WatchMode;
			}
			Btn3.ReleasedTime = Idle_Released;
		}
	}
}

void WatchHandleButton4(void)
{
	if (Btn4.state == Pressing)
	{
		CheckBtnHoldingTime(&Btn4, GPIOD, GPIO_PIN_10);
		BtnThresHoldEvent(&Btn4, GPIOD, GPIO_PIN_10);

		if (watchConfig.flags.decreaseFlagOnce)
		{
			watchConfig.flags.decreaseFlagOnce = 0;
			DecreaseTimeOnce();
		}
		switch (Btn4.holdTime)
		{
		case BtnHold_Mid:
			if (watchConfig.flags.decreaseFlag150ms)
			{
				watchConfig.flags.decreaseFlag150ms = 0;
				DecreaseTimeOnce();
			}
			break;
		case BtnHold_Long:
			if (watchConfig.flags.decreaseFlag20ms)
			{
				watchConfig.flags.decreaseFlag20ms = 0;
				DecreaseTimeOnce();
			}
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////
