/***********************89C51_it.c***************************/

#include "89C51_it.h"
#include "timer.h"
#include "usart.h"
#include "brushDcMotor.h"
#include "stepMotor.h"
extern unsigned char LedItStatus;
//外部引用电机相对位置变量
extern unsigned int xdata relativePos;
//外部引用电机实际速度变量
extern float xdata actSpeed;
//外部引用信号量变量
extern unsigned char xdata semapher;

//外部中断使能失能函数
void ExternalITCmd(exITTypedef_t exITx, FunctionalState_t newState)
{
	//根据输入的中断号和状态对相应寄存器进行置位或复位
	if(exITx==exIT0)
	{
		EX0 = newState;
	}
	else if(exITx==exIT1)
	{
		EX1 = newState;
	}
}

/**
  * @brief	外部中断初始化
  * @note
  * @param	exITx：中断标号
*     			exIT0:中断0
*				exIT1:中断1
* @param	triggerMode:触发模式
*				EXIT_UPDOWN_TRIGGER：电平触发
*				EXIT_DOWN_TRIGGER：下降沿触发					
  * @retval none
  */
void ExternalITInit(exITTypedef_t exITx , unsigned char triggerMode)
{
	//根据输入的中断号和触发模式对相应寄存器进行配置
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

//外部中断1服务函数1KHz
void ExIT1_Handler() interrupt 2
{
	//任务周期100ms
	#define TASK_PERIOD (100)
	//计时变量
	static unsigned char xdata periodCounter = TASK_PERIOD;
	
	periodCounter--;
	//每一次任务周期对信号量置位并读取电位置
	if(periodCounter==0)
	{
		periodCounter = TASK_PERIOD;
		
		//读取电机位置
		TimerCmd(TIM0 , disable);
		relativePos = TH0<<8;
		relativePos|= TL0;
		TH0 = 0;
		TL0 = 0;
		TimerCmd(TIM0 ,enable);	
		
		//计算电机转速
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

//PCA中断
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