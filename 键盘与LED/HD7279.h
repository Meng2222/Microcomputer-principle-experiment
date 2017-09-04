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

void HD7279SendByte(unsigned char sendData);
unsigned char HD7279ReceiveByte(void);
void LedWrite(unsigned char cmd , unsigned char dataSend);
unsigned char KeyRead(void);

#endif