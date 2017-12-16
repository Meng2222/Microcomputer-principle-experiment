/***********************pwm.c****************************/

#include "pwm.h"
/*****************还没有完成硬件驱动层程序，暂时直接配置寄存器******************/

//PWM0初始化
void PWM0Init(void)
{
	//选择PWM输出引脚
	P_SW1&=(~(0x03<<4));
	//复位PCA控制寄存器
	CCON = 0;
	CL = 0;
	CH = 0;
	//配置时钟源
	CMOD |= 0x02;
	//8位PWM
	PCA_PWM0 = 0x00;
	//允许比较器和脉宽调节模式
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

//配置PWM占空比
void PWM0SetCompare(float compareValue)
{
	CCAP0H = (unsigned char)(256.0f * (1.0f - compareValue));
	CCAP0L = (unsigned char)(256.0f * (1.0f - compareValue));
}

//PWM使能失能函数
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
