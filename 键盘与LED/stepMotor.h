#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H

#include "gpio.h"

#define PHASE_A_PORT (GPIOPort1)
#define PHASE_A_PIN (GPIO_PIN0)

#define PHASE_B_PORT (GPIOPort1)
#define PHASE_B_PIN (GPIO_PIN1)

#define PHASE_C_PORT (GPIOPort1)
#define PHASE_C_PIN (GPIO_PIN2)

#define PHASE_D_PORT (GPIOPort1)
#define PHASE_D_PIN (GPIO_PIN3)

#define STEP_RESOLUTION (0.9f/180.0f*PI)

void StepMotorPinInit(void);

void StepMotorSpeedControl(float vel);

#endif