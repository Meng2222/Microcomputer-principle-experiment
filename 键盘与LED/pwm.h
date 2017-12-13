#ifndef __PWM_H
#define __PWM_H

#include "main.h"

void PWM0Init(void);

void PWM0SetCompare(float compareValue);

void PWMCmd(FunctionalState_t newState);

void CCP1Init(void);

#endif