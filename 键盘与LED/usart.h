#ifndef __USART_H
#define __USART_H

#include "main.h"

typedef enum
{
	UART1,
	UART2
}UARTTypeDef_t;

typedef struct
{
	unsigned char UARTMode;
	unsigned char UARTIsMulti;
	unsigned char isUARTBaudrateDouble;
}UARTMode_t;

#define UART_BAUDRATE_DOUBLE (0x01)
#define UART_BAUDRATE_NORMAL (0x00)

#define UART_MODE_0 (0x00)
#define UART_MODE_1 (0x01)
#define UART_MODE_2 (0x02)
#define UART_MODE_3 (0x03)

#define UART_MULT_DEVICE (0x10)
#define UART_SINGLE_DEVICE (0x00)

#define	UART_Rx_IT_FLAG (0x01)
#define UART_Tx_IT_FLAG (0x02)

void UARTModeInit(UARTTypeDef_t UARTx, unsigned char UARTMode);

void UARTBaudrateInit(UARTTypeDef_t UARTx,unsigned char UARTMode, unsigned char isBaudrateDouble, unsigned int baudRate);

void UARTRxCmd(UARTTypeDef_t UARTx, FunctionalState_t newState);

FlagStatus UARTGetFlagStatus(UARTTypeDef_t UARTx, unsigned char UARTFlag);

void UARTClearFlagStatus(UARTTypeDef_t UARTx, unsigned char UARTFlag);

void UARTSendByte(UARTTypeDef_t UARTx, unsigned char sendData);

void UARTInit(UARTTypeDef_t UARTx, UARTMode_t UARTMode, unsigned int baudRate);

void UARTITConfig(UARTTypeDef_t UARTx, unsigned char UARTPriority);

#endif
