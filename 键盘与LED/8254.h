#ifndef __8254_H
#define __8254_H

#include "main.h"

typedef enum
{
	timer8254Timer0,
	timer8254Timer1,
	timer8254Timer2
}timer8254TypeDef_t;

void Timer8254Cmd(timer8254TypeDef_t timerx, FunctionalState_t newState);

void Timer8254CounterModeInit(timer8254TypeDef_t timerx, unsigned short setCounter);

void Timer8254TriggerModeInit(timer8254TypeDef_t timerx, unsigned short setCounter);

void Timer8254StartTrigger(timer8254TypeDef_t timerx);

void Timer8254PrescalerModeInit(timer8254TypeDef_t timerx, unsigned short prescale);

void Timer8254SquareWaveModeInit(timer8254TypeDef_t timerx, unsigned short period);

void Timer8254SoftwareStrobeModeInit(timer8254TypeDef_t timerx, unsigned short setCounter);

void Timer8254HardwareStrobeModeInit(timer8254TypeDef_t timerx, unsigned short setCounter);

void Timer8254StartHardStrobe(timer8254TypeDef_t timerx);

unsigned short Timer8254GetCounter(timer8254TypeDef_t timerx);

#endif