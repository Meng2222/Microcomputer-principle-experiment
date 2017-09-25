#include "p1IO.h"
#include "delay.h"
#include "main.h"

//P1口输出控制LED四个一组循环闪烁，输入为闪烁周期，单位毫秒
void BlinkIn4(unsigned short period)
{
	static unsigned short idata blinkTimeCounter  = 0;
	
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

//P1口输出控制LED流水灯，输入为流水等的周期，单位：毫秒
void Flow(unsigned short flowPeriod)
{
	static unsigned short idata flowCounter = 0;
	static unsigned char idata flowState = 0x01;
	
	flowCounter+=20;
	flowCounter%=flowPeriod;
	
	//电路连接为输出低时LED亮
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

//将P1口0~3位的输入输出到P1口4~7位，用开关控制LED亮灭
void ShowInput(void)
{
	unsigned char p1Input = 0;
	
	//P1为准双向，在读取前要写入1，避免读取出错
	P1 |= P1_INPUT;
	
	p1Input = P1&P1_INPUT;
	
	p1Input<<=4;
	P1 = ~p1Input;
	
}