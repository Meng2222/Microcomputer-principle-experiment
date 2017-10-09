#include "89C51_it.h"
#include "timer.h"
extern unsigned char LedItStatus;
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
