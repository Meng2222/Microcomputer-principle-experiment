/*************************timer.h********************************/
#ifndef __TIMER_H
#define __TIMER_H

#include "main.h"

//定时器标号枚举类型定义
typedef enum
{
	TIM0 = 0,
	TIM1	
}TimerTypeDef_t;

//是否门控枚举类型定义
typedef enum
{
	noGateCrl = 0,
	GateCrl
}timerIsGateCrl_t;

//工作模式枚举类型的定义 
typedef enum
{
	halfWordAutoReload = 0,
	halfWordNotReload,
	byteAutoReload,
	modeThree	
}timerMode_t;

//定时器或计数器枚举类型定义
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

//初始化结构体类型定义
typedef struct
{
	timerIsGateCrl_t isGateCrl;
	timeWorkMode_t timeWorkMode;
//	timeTriggerMode_t timeTriggerMode;
	timerMode_t timerMode;
}timeMode_t;



void TimerCmd(TimerTypeDef_t TIMx , FunctionalState_t newState);
unsigned char TimerGetOverFlowITFlag(TimerTypeDef_t TIMx);
void TimerClearOverFlowFlag(TimerTypeDef_t TIMx);
void TimeModeInit(TimerTypeDef_t TIMx , timeMode_t timeMode);
void TimeReloadNumInit(TimerTypeDef_t TIMx,timerMode_t timerMode,unsigned long timerPeriod, unsigned int mechinePeriod);
void TimeInit(TimerTypeDef_t TIMx , timeMode_t timeMode ,unsigned long timerPeriod, unsigned int mechinePeriod);
void TimerOverFlowItInit(TimerTypeDef_t TIMx , FunctionalState_t newState);

#endif
