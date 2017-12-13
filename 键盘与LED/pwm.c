#include "pwm.h"

void PWM0Init(void)
{
	P_SW1&=(~(0x03<<4));
	CCON = 0;
	CL = 0;
	CH = 0;
	CMOD |= 0x02;
	PCA_PWM0 = 0x00;
	CCAPM0 |= 0x42;
}

void CCP1Init(void)
{
	P_SW1&=(~(0x03<<4));
	CCON = 0;
	CL = 0;
	CH = 0;
	CMOD|=0x01;
	CCAP1H = 0;
	CCAP1L = 0;
	CCAPM1 = 0x21;
	EA = 1;
}

void PWM0SetCompare(float compareValue)
{
	CCAP0H = (unsigned char)(256.0f * (1.0f - compareValue));
	CCAP0L = (unsigned char)(256.0f * (1.0f - compareValue));
}

void PWMCmd(FunctionalState_t newState)
{
	if(newState)
	{
		CR = 1;
	}
	else
	{
		CR = 0;
	}
}
