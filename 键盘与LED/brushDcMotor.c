/***********************brushDcMotor.c*****************************/

#include "brushDcMotor.h"
#include "pwm.h"
//电机位置变量
unsigned int xdata relativePos = 0;
//电机实际速度变量
float xdata actSpeed = 0.0f;

//电机速度控制函数
void MotorVelCrl(float expVel,float actVel)
{
	#define VEL_CRL_P (0.003f)
	float xdata dutyCycle = 0.0f;
	float xdata error = 0.0f;
	//对输入速度进行限制
	if(expVel>=120.0f)
	{
		expVel = 120.0f;
	}
	
	//计算速度对应占空比
	dutyCycle = (135.1f - expVel)/161.6f;
	
	//对速度进行P调节
	error = expVel - actVel;
	
	dutyCycle-=(error*VEL_CRL_P);
	
	//对输出进行限幅
	if(dutyCycle<=0.05)
	{
		dutyCycle = 0.05;
	}
	
	//输出占空比
	PWM0SetCompare(dutyCycle);
	
}

