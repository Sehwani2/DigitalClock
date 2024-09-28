/*
 * buzzer.c
 *
 *  Created on: Sep 17, 2024
 *      Author: hyn02
 */

#include "buzzer.h"
#include "watch.h"
#include "tim.h"
 Buz Buz1;

 void InitializeBuzzer(void)
 {
     Buz1.BuzOnOff = false;
     Buz1.BuzCount = 0;
     Buz1.BuzFlag = false;
     Buz1.BuzTone = BUZ_TONE_LOW_PSC;
     BuzLock = false;
 }

void activateBuzzer30msOn( Buz* buzzer, TIM_HandleTypeDef* htim, uint32_t channel,uint32_t psc)
{
	if(buzzer->BuzOnOff == false)
	{
		__HAL_TIM_SET_PRESCALER(htim, psc);
		HAL_TIM_PWM_Start(htim, channel);
		buzzer->BuzCount = 0;
		buzzer->BuzOnOff = true;
	}

}

void activateBuzzer30msOff( Buz* buzzer, TIM_HandleTypeDef* htim, uint32_t channel)
{
	if (buzzer->BuzOnOff)
	{
		buzzer->BuzCount++;

		if (buzzer->BuzCount >= 30)
		{
			HAL_TIM_PWM_Stop(htim, channel);
			buzzer->BuzOnOff = false;
			buzzer->BuzCount = 0;
		}
	}
}

void checkAndRingBuzzer(void)
{
    // 매일 0시 정각에 부저를 고음으로 울리기
    if (watch.Time.hours == 0 && watch.Time.minutes == 0 && watch.Time.second == 0  && watch.Time.millisecond < 100)
    {
        Buz1.BuzTone = BUZ_TONE_HIGH_PSC;
        Buz1.BuzFlag = true;
    }
    // 매시 정각에 부저를 중간 음으로 울리기
    else if (watch.Time.minutes == 0 && watch.Time.second == 0 && watch.Time.millisecond < 100)
    {
        Buz1.BuzTone = BUZ_TONE_MID_PSC;
        Buz1.BuzFlag = true;
    }
}
void handleBuzzerActivation(void)
{
	if (Buz1.BuzFlag)
	{
		Buz1.BuzFlag = false;

		if (!BuzLock) {
			switch (Buz1.BuzTone)
			{
			case BUZ_TONE_LOW_PSC:
				activateBuzzer30msOn(&Buz1, &htim2, TIM_CHANNEL_1,
						BUZ_TONE_LOW_PSC);
				break;
			case BUZ_TONE_MID_PSC:
				activateBuzzer30msOn(&Buz1, &htim2, TIM_CHANNEL_1,
						BUZ_TONE_MID_PSC);
				break;
			case BUZ_TONE_HIGH_PSC:
				activateBuzzer30msOn(&Buz1, &htim2, TIM_CHANNEL_1,
						BUZ_TONE_HIGH_PSC);
				break;
			}
		}

	}
}

