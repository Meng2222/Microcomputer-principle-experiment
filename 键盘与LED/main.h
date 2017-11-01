#ifndef __MAIN_H
#define __MAIN_H

#include "STC15F2K60S2.h"
#include <intRIns.h>
#include <ABSACC.h>
#include <math.h>
#include <stdio.h>

#define SYSCLK (4508000L)

#define TIMERUS ((int)(SYSCLK/1000000))

//#define DATA_MEMORY_TEST

//#define KEY_LED_EXP

//#define BASIC_IO_EXP

//#define DECODE_EXP

//#define P1_IO_EXP

//#define TIMER_EXP

//#define INTERRUPT_EXP

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {disable = 0, enable}FunctionalState_t;

extern unsigned char code realCode[];
#endif