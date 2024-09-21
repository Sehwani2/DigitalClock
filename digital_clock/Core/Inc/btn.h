/*
 * btn.h
 *
 *  Created on: Sep 17, 2024
 *      Author: hyn02
 */

#ifndef INC_BTN_H_
#define INC_BTN_H_

#include "main.h"
#include "buzzer.h"

///////////////////////////// BTN
typedef enum _BtnHold{
	BtnHold_Short,
	BtnHold_Mid,
	BtnHold_Long,
}BtnHold;

typedef enum _BtnState{
	Idle,
	Pressing,
	Released,
}BtnState;

typedef enum _ButtonRT{
	Idle_Released,
	Short_Released,
	Mid_Released,
	Long_Released,
}ButtonPT;


typedef struct _Button{
	int millisecond;
	bool is_pressed;
	BtnState state;
	ButtonPT ReleasedTime;
	BtnHold holdTime;
}Button;

extern Button Btn1;
extern Button Btn2;
extern Button Btn3;
extern Button Btn4;


void HandleButtonPress(Button* btn, GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_Num);
void CheckButtonPressTime(Button* Btn);
void BtnHoldEvent(Button* btn,GPIO_TypeDef* GPIO,uint16_t GPIO_PIN );
#endif /* INC_BTN_H_ */
