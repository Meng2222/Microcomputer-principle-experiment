/****************************main.h***********************************/
#ifndef __MAIN_H
#define __MAIN_H

#include "STC15F2K60S2.h"
#include <intRIns.h>
#include <ABSACC.h>
#include <math.h>
#include <stdio.h>

//系统时钟定于
#define SYSCLK (4068000L)

//一微妙时间定义
#define TIMERUS (int)(12.0f/(float)(SYSCLK/1000000))

//返回错误宏定义
#define RETURN_ERROR (0xff)

//圆周率宏定义
#define PI (3.1415926f)

//#define DATA_MEMORY_TEST

//#define KEY_LED_EXP

//#define BASIC_IO_EXP

//#define DECODE_EXP

//#define P1_IO_EXP

//#define TIMER_EXP

//#define INTERRUPT_EXP

//#define UART_EXP

//#define IO8255_EXP

//#define TIMER_8254_EXP

//#define STEPMOTOR_EXP

#define FINAL_EXAM

//状态位枚举类型定义
typedef enum {RESET = 0, SET = 1} FlagStatus, ITStatus;
//使能失能状态枚举类型定义
typedef enum {disable = 0, enable}FunctionalState_t;

//引用 7279输出数码
extern unsigned char xdata realCode[];
#endif