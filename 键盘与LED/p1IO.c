#include "p1IO.h"
#include "delay.h"
#include "main.h"

void BlinkIn4(unsigned short period)
{
	static unsigned short blinkTimeCounter  = 0;
	blinkTimeCounter+=20;
	blinkTimeCounter%=2*period;
	if(blinkTimeCounter/period)
	{
		P1 = 0x0f;
	}
	else
	{
		P1 = 0xf0;
	}
}

void Flow(unsigned short flowPeriod)
{
	static unsigned short flowCounter = 0;
	static unsigned char flowState = 0x01;
	flowCounter+=20;
	flowCounter%=flowPeriod;
	P1 = ~flowState;
	if(flowCounter == 0)
	{
		if(flowState!=0x80)
		{
			flowState<<=1;
		}
		else
		{
			flowState = 0x01;
		}
	}
	
}

void ShowInput(void)
{
	unsigned char p1Input = 0;
	P1 |= P1_INPUT;
	p1Input = P1&P1_INPUT;
	p1Input<<=4;
	P1 = ~p1Input;
	
}