/*
 * btn.c
 *
 *  Created on: Sep 17, 2024
 *      Author: hyn02
 */
#include "btn.h"

Button Btn1;
Button Btn2;
Button Btn3;
Button Btn4;


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

	} else if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin_Num) == GPIO_PIN_RESET)
	{
		if (btn->is_pressed == true) // to reduce debouncing
		{

			btn->is_pressed = false;

			if (btn->state == Pressing)
			{
				btn->state = Released;
				CheckButtonPressTime(btn);
				btn->millisecond = 0;
			}
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
	if((HAL_GPIO_ReadPin(GPIO, GPIO_PIN) == GPIO_PIN_SET)|| btn->state == Pressing)
	{
		if (btn->millisecond <= LONG_PRESS_TIME + 1)
		{
			btn->millisecond++;
		}
	}
}
