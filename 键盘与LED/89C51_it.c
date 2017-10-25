#include "89C51_it.h"
#include "timer.h"
extern unsigned char LedItStatus;

void ExternalITCmd(exITTypedef_t exITx, FunctionalState_t newState)
{
	if(exITx==exIT0)
	{
		EX0 = newState; 
	}
	else if(exITx==exIT1)
	{
		EX1 = newState;
	}
}

void ExternalITInit(exITTypedef_t exITx , unsigned char triggerMode)
{
	if(exITx==exIT0)
	{
		IT0 = triggerMode;
		ExternalITCmd(exIT0 , enable);
	}
	else if(exITx==exIT1)
	{
		IT1  = triggerMode;
		ExternalITCmd(exIT1 , enable);		
	}
}

//外部中断0中断服务函数
void interint0()interrupt 0
{
	if(LedItStatus)
	{
		LedItStatus = 0;
	}
	else
	{
		LedItStatus = 1;
	}
}

//定时器0溢出中断服务函数
void time0()interrupt 1
{
	TimerClearOverFlowFlag(TIM0);
	if(LedItStatus)
	{
		LedItStatus = 0;
	}
	else
	{
		LedItStatus = 1;
	}
}
