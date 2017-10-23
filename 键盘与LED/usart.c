#include "usart.h"
#include "timer.h"

/****************************串口UART2部分代码存在问题，还没有更改****************************/

void UARTModeInit(UARTTypeDef_t UARTx, unsigned char UARTMode, unsigned char isBaudrateDouble)
{
	if(UARTx==UART1)
	{
		SCON&(0x3f|(UARTMode<<6));
		PCON&(0xef|(isBaudrateDouble<<7));
	}
	else if(UARTx==UART2)
	{
		S2CON&(0xff&(UARTMode<<6));
	}
}

void UARTBaudrateInit(UARTTypeDef_t UARTx, unsigned int baudRate)
{

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
		SCON&(~UARTFlag);
	}
	else if(UARTx==UART2)
	{
		S2CON&(~UARTFlag);
	}
}

void UARTSendByte(UARTTypeDef_t UARTx, unsigned char sendData)
{

}

void UARTInit(UARTTypeDef_t UARTx, UARTMode_t UARTMode, unsigned int baudRate)
{

}

void UARTITConfig(UARTTypeDef_t UARTx, unsigned char UARTPriority)
{

}
