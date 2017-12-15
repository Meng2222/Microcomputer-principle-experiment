#include "89C51_it.h"
#include "timer.h"
#include "usart.h"
#include "brushDcMotor.h"
#include "stepMotor.h"
extern unsigned char LedItStatus;
extern unsigned int xdata relativePos;
extern float xdata actSpeed;
extern unsigned char xdata semapher;

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


void ExIT1_Handler() interrupt 2
{
	#define TASK_PERIOD (100)
	static unsigned char xdata periodCounter = TASK_PERIOD;
	
	periodCounter--;
	if(periodCounter==0)
	{
		periodCounter = TASK_PERIOD;
		TimerCmd(TIM0 , disable);
		relativePos = TH0<<8;
		relativePos|= TL0;
		TH0 = 0;
		TL0 = 0;
		TimerCmd(TIM0 ,enable);	

		actSpeed = relativePos*10/COUNT_PER_CIRCLE*2.0*PI;
		semapher = 1;
	}
	
	StepMotorSpeedControl(actSpeed/6.366f);
}
//定时器0溢出中断服务函数
void time0()interrupt 1
{
	TimerClearOverFlowFlag(TIM0);

//	relativePos = CCAP1H<<8;
//	relativePos|= CCAP1L;
//	CCAP1H = 0;
//	CCAP1L = 0;
	
}

extern unsigned char UART1Recieve;

void UART1_ITHandler()interrupt 4
{
	if(UARTGetFlagStatus(UART1,UART_Rx_IT_FLAG)==SET)
	{
		UART1Recieve = UARTRecieveByte(UART1);
		UARTClearFlagStatus(UART1, UART_Rx_IT_FLAG);
	}
	else if(UARTGetFlagStatus(UART1,UART_Tx_IT_FLAG)==SET)
	{
//		UARTClearFlagStatus(UART1, UART_Tx_IT_FLAG);
	}
}

void PCA_ITHandler()interrupt 7 using 1
{
	if(CF)
	{
		CF = 0;
		
	}
	if(CCF0)
	{
		CCF0=0;
	}
		
		
}