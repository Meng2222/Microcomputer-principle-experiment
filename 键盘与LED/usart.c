#include "usart.h"
#include "timer.h"

/****************************串口UART2部分代码存在问题，还没有更改****************************/

void UARTModeInit(UARTTypeDef_t UARTx, unsigned char UARTMode)
{
	if(UARTx==UART1)
	{
		SCON&=(0x3f|(UARTMode<<6));
	}
	else if(UARTx==UART2)
	{
		S2CON&=(0x3f|(UARTMode<<6));
	}
}

void UARTBaudrateInit(UARTTypeDef_t UARTx,unsigned char UARTMode, unsigned char isBaudrateDouble, unsigned int baudRate)
{
	if(UARTx==UART1)
	{
		PCON&=(0xef|(isBaudrateDouble<<7));
	}
	else if(UARTx==UART2)
	{
	
	}
	switch(UARTMode)
	{
		case UART_MODE_0:
		break;
		case UART_MODE_1:
			if(UARTx==UART1)
			{
				//定时器初始化结构体 
				timeMode_t timeMode ={0};

				//对结构体进行赋值
				timeMode.isGateCrl = noGateCrl;
				timeMode.timeWorkMode = timer;
				timeMode.timeTriggerMode = innerTrigger;
				timeMode.timerMode = halfWordAutoReload;
				
				TimeInit(TIM1 ,timeMode ,(int)1000000/baudRate, TIMERUS);
			}
			else if(UARTx==UART2)
			{
			
			}
		break;
		case UART_MODE_2:

		break;
		case UART_MODE_3:
			if(UARTx==UART1)
			{
				//定时器初始化结构体 
				timeMode_t timeMode ={0};

				//对结构体进行赋值
				timeMode.isGateCrl = noGateCrl;
				timeMode.timeWorkMode = timer;
				timeMode.timeTriggerMode = innerTrigger;
				timeMode.timerMode = halfWordAutoReload;
				
				TimeInit(TIM1 ,timeMode ,(int)1000000/baudRate, TIMERUS);				
			}
			else if(UARTx==UART2)
			{
			
			}
		break;
		default:
		break;
	}
}

sbit RENx = SCON^4;
void UARTRxCmd(UARTTypeDef_t UARTx, FunctionalState_t newState)
{
	if(UARTx == UART1)
	{
		RENx = newState;
	}
	else if(UARTx == UART2)
	{
		RENx = S2CON^4;
		RENx = newState;
	}
}

FlagStatus UARTGetFlagStatus(UARTTypeDef_t UARTx, unsigned char UARTFlag)
{
	if(UARTx==UART1)
	{
		return SCON&UARTFlag;
	}
	else if(UARTx==UART2)
	{
		return S2CON&UARTFlag;
	}
}

void UARTClearFlagStatus(UARTTypeDef_t UARTx, unsigned char UARTFlag)
{
	if(UARTx==UART1)
	{
		SCON&=(~UARTFlag);
	}
	else if(UARTx==UART2)
	{
		S2CON&=(~UARTFlag);
	}
}

void UARTSendByte(UARTTypeDef_t UARTx, unsigned char sendData)
{
	if(UARTx==UART1)
	{
		SBUF = sendData;
	}
	else if(UARTx==UART2)
	{
		S2BUF = sendData;
	}
	while(UARTGetFlagStatus(UARTx,UART_Tx_IT_FLAG)!=SET);	

}

void UARTInit(UARTTypeDef_t UARTx, UARTMode_t UARTMode, unsigned int baudRate)
{

}

void UARTITConfig(UARTTypeDef_t UARTx, unsigned char UARTPriority)
{
	EA = 1;	
	if(UARTx==UART1)
	{
	
		ES = 1;
		PS = UARTPriority;
	}
	else if(UARTx==UART2)
	{
		IE2|=0x01;
		IP2|=UARTPriority;
	}
}
