/*
 * buzzer.h
 *
 *  Created on: Sep 17, 2024
 *      Author: hyn02
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

typedef enum _BuzTonePsc{
	BUZ_TONE_LOW_PSC = 15000,
	BUZ_TONE_MID_PSC = 10000,
	BUZ_TONE_HIGH_PSC = 7500,
}BuzTonePsc;

typedef struct _Buz{
	volatile bool BuzOnOff;
	volatile uint16_t BuzCount;
	volatile bool BuzFlag;
	BuzTonePsc BuzTone;
}Buz;

extern Buz Buz1;

void activateBuzzer30msOn(Buz* buzzer, TIM_HandleTypeDef* htim, uint32_t channel,uint32_t psc);
void activateBuzzer30msOff(Buz* buzzer, TIM_HandleTypeDef* htim, uint32_t channel);
void checkAndRingBuzzer(void);
#endif /* INC_BUZZER_H_ */
