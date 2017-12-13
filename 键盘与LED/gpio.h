#ifndef __GPIO_H
#define __GPIO_H

#include "main.h"

typedef enum
{
	GPIOPort0 = 0,
	GPIOPort1,
	GPIOPort2,
	GPIOPort3
}GPIOTypeDef_t;

#define GPIO_PORT0 (P0)
#define GPIO_PORT1 (P1)
#define GPIO_PORT2 (P2)
#define GPIO_PORT3 (P3)

#define GPIO_PIN0 (0x01)
#define GPIO_PIN1 (0x02)
#define GPIO_PIN2 (0x04)
#define GPIO_PIN3 (0x08)
#define GPIO_PIN4 (0x10)
#define GPIO_PIN5 (0x20)
#define GPIO_PIN6 (0x40)
#define GPIO_PIN7 (0x80)

#define GPIO_MULTIDIREC (0x00)
#define GPIO_PUSHPULL (0x01)
#define GPIO_HIGHRES (0x02)
#define GPIO_OPENDRAIN (0x03)

void GPIOInit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin, unsigned char GPIOMode);
void GPIOSetBit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin);

void GPIOResetBit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin);

unsigned char GPIOReadBit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin);


#endif
