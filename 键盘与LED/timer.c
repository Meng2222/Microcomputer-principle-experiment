#include "timer.h"
#include "HD7279.h"

//定时器使能和失能函数，输入变量为定时器编号和使能失能命令
void TimerCmd(TimerTypeDef_t TIMx , FunctionalState_t newState)
{
	//根据输入的定时器和命令对TCON寄存器进行配置
	if(newState == enable)
	{
		TCON|=(0x10<<(TIMx * 2));
	}
	else 
	{
		TCON&=(~(0x10<<(TIMx * 2)));
	}
	
}

//读取定时器溢出中断标志位，输入变量为定时器编号
unsigned char TimerGetOverFlowITFlag(TimerTypeDef_t TIMx)
{
	unsigned char xdata tempItFlag = 0;
	//根据输入的定时器读取对应的寄存器
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

//清除定时器溢出中断标志位，输入变量为定时器编号
void TimerClearOverFlowFlag(TimerTypeDef_t TIMx)
{
	//根据输入的定时器编号清除对应寄存器
	if(TIMx==TIM0)
	{
		TF0 = 0;
	}
	else if(TIMx==TIM1)
	{
		TF1 = 0;
	}
}

//对定时器模式进行初始化
void TimeModeInit(TimerTypeDef_t TIMx , timeMode_t timeMode)
{
	unsigned char xdata tempCrl = 0;
	
	//根据输入的模式配置TMOD寄存器
	
	tempCrl|=(timeMode.timerMode<<(TIMx * 4));
	
	tempCrl|=((timeMode.timeWorkMode<<2)<<(TIMx * 4));
	
	tempCrl|=((timeMode.isGateCrl<<3)<<(TIMx * 4));
	
	TMOD=tempCrl|(TMOD&(0xf0>>(TIMx * 4)));
}

//对定时器重装载值进行初始化
void TimeReloadNumInit(TimerTypeDef_t TIMx,timerMode_t timerMode,unsigned long timerPeriod, unsigned int mechinePeriod)
{
	unsigned int xdata bitNum = 0;
	unsigned int xdata reloadNum = 0;
	
	//根据不同的模式选择最大重装载值 
	if(timerMode<=1)
	{
		bitNum = 65535;
	}
	else
	{
		bitNum = 255;
	}
	
	//根据实际配置的周期以及机器周期计算实际的重装载值
	reloadNum = bitNum - timerPeriod/mechinePeriod;

	
	//根据所选择的定时器配置相应的寄存器
	if(TIMx == TIM0)
	{
		TL0 = reloadNum&0x00ff;
		TH0 = reloadNum>>8;
	}
	else if(TIMx == TIM1)
	{
		TL1 = reloadNum&0x00ff;
		TH1 = reloadNum>>8;
	}
	
}

//定时器初始化函数
void TimeInit(TimerTypeDef_t TIMx , timeMode_t timeMode ,unsigned long timerPeriod, unsigned int mechinePeriod)
{
	
	//配置定时器工作模式
	TimeModeInit(TIMx , timeMode);
	
	//配置定时器重装载值
	TimeReloadNumInit(TIMx,timeMode.timerMode,timerPeriod,mechinePeriod);
	if(timeMode.timeWorkMode==counter)
	{
		if(TIMx == TIM0)
		{
			TL0 = 0;
			TH0 = 0;
		}
		else if(TIMx == TIM1)
		{
			TL1 = 0;
			TH1 = 0;
		}		
	}
	
	//使能定时器
	TimerCmd(TIMx , enable);
}

sbit ETx = IE^1;

//定时器溢出中断使能函数
void TimerOverFlowItInit(TimerTypeDef_t TIMx , FunctionalState_t newState)
{
	//根据输入的定时器编号配置对应IE中断寄存器
	if(newState == enable)
	{
		EA = 1;
	}
	ETx = IE^(1 + TIMx * 2);
	ETx = newState;
}
