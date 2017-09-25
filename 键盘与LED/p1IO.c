#include "p1IO.h"
#include "delay.h"
#include "main.h"

//P1���������LED�ĸ�һ��ѭ����˸������Ϊ��˸���ڣ���λ����
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

//P1���������LED��ˮ�ƣ�����Ϊ��ˮ�ȵ����ڣ���λ������
void Flow(unsigned short flowPeriod)
{
	static unsigned short idata flowCounter = 0;
	static unsigned char idata flowState = 0x01;
	
	flowCounter+=20;
	flowCounter%=flowPeriod;
	
	//��·����Ϊ�����ʱLED��
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

//��P1��0~3λ�����������P1��4~7λ���ÿ��ؿ���LED����
void ShowInput(void)
{
	unsigned char p1Input = 0;
	
	//P1Ϊ׼˫���ڶ�ȡǰҪд��1�������ȡ����
	P1 |= P1_INPUT;
	
	p1Input = P1&P1_INPUT;
	
	p1Input<<=4;
	P1 = ~p1Input;
	
}