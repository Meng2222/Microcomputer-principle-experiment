#ifndef __HD7279_H
#define __HD7279_H

#include "main.h"

sbit dat = P1^4;
sbit key = P1^5;
sbit cs = P1^6;
sbit clk = P1^7;

#define CMD_RESET 0xa4
#define CMD_TEST 0xbf
#define DECODE0 0x80
#define DECODE1 0xc8
#define CMD_READ 0x15
#define UNDECODE 0x90
#define RTL_CYCLE 0xa3
#define RTR_CYCLE 0xa2
#define RTL_UNCYL 0xa1
#define RTR_UNCYL 0xa0
#define ACTCTL 0x98
#define SEGON 0xe0
#define SEGOFF 0xc0
#define BLINKCTL 0x88

#define KEY0 (27)
#define KEY1 (19)
#define KEY2 (11)
#define KEY3 (3)
#define KEY4 (26)
#define KEY5 (18)
#define KEY6 (10)
#define KEY7 (2)
#define KEY8 (25)
#define KEY9 (17)
#define KEY10 (9)
#define KEY11 (1)
#define KEY12 (24)
#define KEY13 (16)
#define KEY14 (8)
#define KEY15 (0)

#define LED1 (0x97 - 7)
#define LED2 (0x97 - 6)
#define LED3 (0x97 - 5)
#define LED4 (0x97 - 4)
#define LED5 (0x97 - 3)
#define LED6 (0x97 - 2)
#define LED7 (0x97 - 1)
#define LED8 (0x97)

extern unsigned char code realCode[];

void HD7279SendByte(unsigned char sendData);
unsigned char HD7279ReceiveByte(void);
void LedWrite(unsigned char cmd , unsigned char dataSend);
unsigned char KeyRead(void);
void LEDShowInt(unsigned short showData);

#endif