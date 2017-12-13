#include "brushDcMotor.h"
#include "pwm.h"

unsigned int xdata relativePos = 0;
float xdata actSpeed = 0.0f;

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
	
	dutyCycle = (135.1f - expVel)/161.6f;
	
	error = expVel - actVel;
	
	dutyCycle-=(error*VEL_CRL_P);
	
	if(dutyCycle<=0.05)
	{
		dutyCycle = 0.05;
	}
	
	PWM0SetCompare(dutyCycle);
	
}

