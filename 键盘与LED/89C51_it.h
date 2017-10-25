#ifndef __89C51_IT_H
#define __89C51_IT_H
#include "main.h"

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