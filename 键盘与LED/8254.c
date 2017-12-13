#include "8254.h"
#include "delay.h"
unsigned char xdata timer8254Timer0Base _at_ 0xf900;
unsigned char xdata timer8254Timer1Base _at_ 0xf901;
unsigned char xdata timer8254Timer2Base _at_ 0xf902;
unsigned char xdata timer8254Ctr _at_ 0xf903;

void Timer8254Cmd(timer8254TypeDef_t timerx, FunctionalState_t newState)
{
	switch(timerx)
	{
		case timer8254Timer0:
			if(newState == enable)
			{
				
			}
			else
			{
				
			}
		break;
		case timer8254Timer1:
			if(newState == enable)
			{
				
			}
			else
			{
				
			}
		break;
		case timer8254Timer2:
			if(newState == enable)
			{
				
			}
			else
			{
				
			}
		break;
		default:
		break;
	}
}

void Timer8254CounterModeInit(timer8254TypeDef_t timerx, unsigned short setCounter)
{
	unsigned char xdata initData = 0;
	
	initData|=(timerx<<6);
	
	initData|=(0x03<<4);
	
	timer8254Ctr = initData;
	
	setCounter-=1;
	
	switch(timerx)
	{
		case timer8254Timer0:
			timer8254Timer0Base = (setCounter&0xff);
			timer8254Timer0Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer1:
			timer8254Timer1Base = (setCounter&0xff);
			timer8254Timer1Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer2:
			timer8254Timer2Base = (setCounter&0xff);
			timer8254Timer2Base = ((setCounter>>8)&0xff);
		break;
		default:
		break;
	}
	Timer8254Cmd(timerx, enable);
}

void Timer8254TriggerModeInit(timer8254TypeDef_t timerx, unsigned short setCounter)
{
	unsigned char xdata initData = 0;
	
	initData|=(timerx<<6);
	
	initData|=(0x03<<4);
	
	initData|=(0x01<<1);
	
	timer8254Ctr = initData;
	
	switch(timerx)
	{
		case timer8254Timer0:
			timer8254Timer0Base = (setCounter&0xff);
			timer8254Timer0Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer1:
			timer8254Timer1Base = (setCounter&0xff);
			timer8254Timer1Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer2:
			timer8254Timer2Base = (setCounter&0xff);
			timer8254Timer2Base = ((setCounter>>8)&0xff);
		break;
		default:
		break;
	}	
}

void Timer8254StartTrigger(timer8254TypeDef_t timerx)
{
	Timer8254Cmd(timerx, enable);
	Delay10Us(1);
	Timer8254Cmd(timerx,disable);
}

void Timer8254PrescalerModeInit(timer8254TypeDef_t timerx, unsigned short prescale)
{
	unsigned char xdata initData = 0;
	
	initData|=(timerx<<6);
	
	initData|=(0x03<<4);
	
	initData|=(0x02<<1);
	
	timer8254Ctr = initData;
	
	switch(timerx)
	{
		case timer8254Timer0:
			timer8254Timer0Base = (prescale&0xff);
			timer8254Timer0Base = ((prescale>>8)&0xff);
		break;
		case timer8254Timer1:
			timer8254Timer1Base = (prescale&0xff);
			timer8254Timer1Base = ((prescale>>8)&0xff);
		break;
		case timer8254Timer2:
			timer8254Timer2Base = (prescale&0xff);
			timer8254Timer2Base = ((prescale>>8)&0xff);
		break;
		default:
		break;
	}

	Timer8254Cmd(timerx, enable);
	
}

void Timer8254SquareWaveModeInit(timer8254TypeDef_t timerx, unsigned short period)
{
	unsigned char xdata initData = 0;
	
	initData|=(timerx<<6);
	
	initData|=(0x03<<4);
	
	initData|=(0x03<<1);
	
	timer8254Ctr = initData;
	
	switch(timerx)
	{
		case timer8254Timer0:
			timer8254Timer0Base = (period&0xff);
			timer8254Timer0Base = ((period>>8)&0xff);
		break;
		case timer8254Timer1:
			timer8254Timer1Base = (period&0xff);
			timer8254Timer1Base = ((period>>8)&0xff);
		break;
		case timer8254Timer2:
			timer8254Timer2Base = (period&0xff);
			timer8254Timer2Base = ((period>>8)&0xff);
		break;
		default:
		break;
	}
	
	Timer8254Cmd(timerx, enable);
}

void Timer8254SoftwareStrobeModeInit(timer8254TypeDef_t timerx, unsigned short setCounter)
{
	unsigned char xdata initData = 0;
	
	initData|=(timerx<<6);
	
	initData|=(0x03<<4);
	
	initData|=(0x04<<1);
	
	timer8254Ctr = initData;
	
	switch(timerx)
	{
		case timer8254Timer0:
			timer8254Timer0Base = (setCounter&0xff);
			timer8254Timer0Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer1:
			timer8254Timer1Base = (setCounter&0xff);
			timer8254Timer1Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer2:
			timer8254Timer2Base = (setCounter&0xff);
			timer8254Timer2Base = ((setCounter>>8)&0xff);
		break;
		default:
		break;
	}

	Timer8254Cmd(timerx, enable);	
}

void Timer8254HardwareStrobeModeInit(timer8254TypeDef_t timerx, unsigned short setCounter)
{
	unsigned char xdata initData = 0;
	
	initData|=(timerx<<6);
	
	initData|=(0x03<<4);
	
	initData|=(0x05<<1);
	
	timer8254Ctr = initData;
	
	switch(timerx)
	{
		case timer8254Timer0:
			timer8254Timer0Base = (setCounter&0xff);
			timer8254Timer0Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer1:
			timer8254Timer1Base = (setCounter&0xff);
			timer8254Timer1Base = ((setCounter>>8)&0xff);
		break;
		case timer8254Timer2:
			timer8254Timer2Base = (setCounter&0xff);
			timer8254Timer2Base = ((setCounter>>8)&0xff);
		break;
		default:
		break;
	}

	Timer8254Cmd(timerx,enable);	
}

void Timer8254StartHardStrobe(timer8254TypeDef_t timerx)
{
	Timer8254Cmd(timerx, disable);
	Delay10Us(1);
	Timer8254Cmd(timerx,enable);
}

unsigned short Timer8254GetCounter(timer8254TypeDef_t timerx)
{
	unsigned short xdata returnValue = 0;
	
	timer8254Ctr = timerx<<6;
	
	switch(timerx)
	{
		case timer8254Timer0:
			returnValue = timer8254Timer0Base;
			returnValue|=(timer8254Timer0Base<<8);
		break;
		case timer8254Timer1:
			returnValue = timer8254Timer1Base;
			returnValue|=(timer8254Timer1Base<<8);
		break;
		case timer8254Timer2:
			returnValue = timer8254Timer1Base;
			returnValue|=(timer8254Timer1Base<<8);
		break;
		default:
		break;
	}

	return returnValue;
}
