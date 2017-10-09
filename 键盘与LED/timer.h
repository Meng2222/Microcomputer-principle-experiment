#ifndef __TIMER_H
#define __TIMER_H

typedef enum {disable = 0, enable}FunctionalState_t;
typedef enum
{
	TIM0 = 0,
	TIM1	
}TimerTypeDef_t;

typedef enum
{
	noGateCrl = 0,
	GateCrl
}timerIsGateCrl_t;

typedef enum
{
	halfWordAutoReload = 0,
	halfWordNotReload,
	byteAutoReload,
	modeThree	
}timerMode_t;

typedef enum
{
	timer = 0,
	counter
}timeWorkMode_t;

typedef enum
{
	innerTrigger = 0,
	outerTrigger
}timeTriggerMode_t;

typedef struct
{
	timerIsGateCrl_t isGateCrl;
	timeWorkMode_t timeWorkMode;
	timeTriggerMode_t timeTriggerMode;
	timerMode_t timerMode;
}timeMode_t;



void TimerCmd(TimerTypeDef_t TIMx , FunctionalState_t newState);
unsigned char TimerGetOverFlowITFlag(TimerTypeDef_t TIMx);
void TimerClearOverFlowFlag(TimerTypeDef_t TIMx);
void TimeModeInit(TimerTypeDef_t TIMx , timeMode_t timeMode);
void TimeReloadNumInit(TimerTypeDef_t TIMx,timerMode_t timerMode,unsigned short timerPeriod, unsigned short mechinePeriod);
void TimeInit(TimerTypeDef_t TIMx , timeMode_t timeMode ,unsigned short timerPeriod, unsigned short mechinePeriod);
void TimerOverFlowItInit(TimerTypeDef_t TIMx , FunctionalState_t newState);

#endif
