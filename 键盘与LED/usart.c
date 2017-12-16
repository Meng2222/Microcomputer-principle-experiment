/*************************usart.c******************************/

#include "usart.h"
#include "timer.h"
#include "HD7279.h"

/****************************串口UART2部分代码存在问题，还没有更改****************************/

//串口模式初始化
void UARTModeInit(UARTTypeDef_t UARTx, unsigned char UARTMode)
{
	//根据输入的串口号和模式对相应寄存器进行配置
	if(UARTx==UART1)
	{
		SCON=(UARTMode<<6)+(SCON&0x3f);
	}
	else if(UARTx==UART2)
	{
		S2CON=(UARTMode<<6)+(S2CON&0x3f);
	}
}

//串口波特率初始化
void UARTBaudrateInit(UARTTypeDef_t UARTx,unsigned char UARTMode, unsigned char isBaudrateDouble, unsigned int baudRate)
{
	//对波特率是否加倍进行配置
	if(UARTx==UART1)
	{
		PCON=(isBaudrateDouble<<7)+(PCON&0x7f);
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
//				timeMode.timeTriggerMode = innerTrigger;
				timeMode.timerMode = halfWordAutoReload;
				
				//计算波特率对应重装载值并对定时器进行初始化
				TimeInit(TIM1 ,timeMode ,(int)(1000000/(baudRate*4)), TIMERUS);
				
				//选择定时器1作为串口波特率发生器
				AUXR&=0xfe;
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
//				timeMode.timeTriggerMode = innerTrigger;
				timeMode.timerMode = halfWordAutoReload;
				
				//计算波特率对应重装载值并对定时器进行初始化
				TimeInit(TIM1 ,timeMode ,(int)(1000000/(baudRate*4)), TIMERUS);
				
				//选择定时器1作为串口波特率发生器
				AUXR&=0xfe;		
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
//串口使能和失能函数
void UARTRxCmd(UARTTypeDef_t UARTx, FunctionalState_t newState)
{
	//根据输入串口号和状态对相应寄存器进行配置
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

//读取串口中断标志为函数
FlagStatus UARTGetFlagStatus(UARTTypeDef_t UARTx, unsigned char UARTFlag)
{
	//根据输入的串口号和要读取的标志位返回对应的标志位值
	if(UARTx==UART1)
	{
		if(SCON&UARTFlag)
		{
			return SET;
		}
		else
		{
			return RESET;
		}
	}
	else if(UARTx==UART2)
	{
		if(S2CON&UARTFlag)
		{
			return SET;
		}
		else
		{
			return RESET;
		}
	}
	else
	{
		return RETURN_ERROR;
	}
}

//清除串口中断标志位函数
void UARTClearFlagStatus(UARTTypeDef_t UARTx, unsigned char UARTFlag)
{
	//根据输入的串口号和标志位对相应寄存器进行复位
	if(UARTx==UART1)
	{
		SCON&=(~UARTFlag);
	}
	else if(UARTx==UART2)
	{
		S2CON&=(~UARTFlag);
	}
}

//串口发送一个字节函数
void UARTSendByte(UARTTypeDef_t UARTx, unsigned char sendData)
{
	//根据串口号将发送的数据填入发送寄存器
	if(UARTx==UART1)
	{
		SBUF = sendData;
	}
	else if(UARTx==UART2)
	{
		S2BUF = sendData;

	}
	//等待发送成功
	while(UARTGetFlagStatus(UARTx,UART_Tx_IT_FLAG)==RESET);
	UARTClearFlagStatus(UARTx, UART_Tx_IT_FLAG);
}

//串口接收字节函数
unsigned char UARTRecieveByte(UARTTypeDef_t UARTx)
{
	//根据属于的串口号读取接收数据寄存器
	if(UARTx==UART1)
	{
		return SBUF;
	}
	else if(UARTx==UART2)
	{
		return S2BUF;
	}
	else
	{
		return RETURN_ERROR;
	}
}

//串口初始化函数
void UARTInit(UARTTypeDef_t UARTx, UARTMode_t UARTMode, unsigned int baudRate)
{
	//根据输入进行初始化并使能串口和中断
	UARTModeInit(UARTx, UARTMode.UARTMode);
	
	UARTBaudrateInit(UARTx,UARTMode.UARTMode, UARTMode.isUARTBaudrateDouble, baudRate);
	
	UARTITConfig(UARTx, UARTMode.itPriority);
	
	UARTRxCmd(UARTx, enable);
	
}

//串口中断初始化函数
void UARTITConfig(UARTTypeDef_t UARTx, unsigned char UARTPriority)
{
	//使能中断
	EA = 1;	
	//根据输入的串口号和优先级配置相应寄存器
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


