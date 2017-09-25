#include "timer.h"
#include "STC15F2K60S2.h"

void TimerCmd(TimerTypeDef_t TIMx , FunctionalState_t newState)
{
	if(newState == enable)
	{
		TCON|=(0x10<<(TIMx * 2));
	}
	else
	{
		TCON&=(~(0x10<<(TIMx * 2)));
	}
	
}

unsigned char TimerGetOverFlowITFlag(TimerTypeDef_t TIMx)
{
	unsigned char tempItFlag = 0;
	if(TIMx==TIM0)
	{
		tempItFlag = TF0;
	}
	else if(TIMx==TIM1)
	{
		tempItFlag = TF1;
	}
	return tempItFlag;
}

void TimerClearOverFlowFlag(TimerTypeDef_t TIMx)
{
	if(TIMx==TIM0)
	{
		TF0 = 0;
	}
	else if(TIMx==TIM1)
	{
		TF1 = 0;
	}
}

void TimeModeInit(TimerTypeDef_t TIMx , timeMode_t timeMode)
{
	unsigned char tempCrl = 0;
	
	tempCrl|=(timeMode.timerMode<<(TIMx * 4));
	
	tempCrl|=((timeMode.timeWorkMode<<2)<<(TIMx * 4));
	
//	tempCrl|=((timeMode.timeTriggerMode<<3)<<(TIMx * 4));
	
	tempCrl|=((timeMode.isGateCrl<<3)<<(TIMx * 4));
	
	TMOD=tempCrl|(TMOD&(0xf0>>(TIMx * 4)));
}

void TimeReloadNumInit(TimerTypeDef_t TIMx,timerMode_t timerMode,unsigned short timerPeriod, unsigned short mechinePeriod)
{
	unsigned short bitNum = 0;
	unsigned short reloadNum = 0;
	if(timerMode<=1)
	{
		bitNum = 65535;
	}
	else
	{
		bitNum = 255;
	}
	
	reloadNum = bitNum - timerPeriod/mechinePeriod;
	
	if(TIMx == TIM0)
	{
		TL0 = reloadNum;
		TH0 = reloadNum>>8;
	}
	else if(TIMx == TIM1)
	{
		TL1 = reloadNum;
		TH1 = reloadNum>>8;
	}
	
}

void TimeInit(TimerTypeDef_t TIMx , timeMode_t timeMode ,unsigned short timerPeriod, unsigned short mechinePeriod)
{
	
	TimeModeInit(TIMx , timeMode);
	
	TimeReloadNumInit(TIMx,timeMode.timerMode,timerPeriod,mechinePeriod);
	
	TimerCmd(TIMx , enable);
}
