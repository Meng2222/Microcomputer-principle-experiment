/*********************89C51_it.h***************************/

#ifndef __89C51_IT_H
#define __89C51_IT_H
#include "main.h"

//中断标号枚举类型定义
typedef enum
{
	exIT0,
	exIT1
}exITTypedef_t;

#define EXIT_UPDOWN_TRIGGER (0x00)
#define EXIT_DOWN_TRIGGER (0x01)

void ExternalITCmd(exITTypedef_t exITx, FunctionalState_t newState);

void ExternalITInit(exITTypedef_t exITx , unsigned char triggerMode);

#endif