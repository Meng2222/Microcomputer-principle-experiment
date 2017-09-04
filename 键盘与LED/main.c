#include "HD7279.h"
#include "delay.h"
#include "main.h"


unsigned char code realCode[] = \
	{0x7e , 0x30 , 0x6d , 0x79 , 0x33 , 0x5b , 0x5f , 0x70 , 0x7f , 0x7b , 0x01 , 0x80 , 0x00 , 0x6f};
//	0		1		2		3		4		5	6		7		8	9		-		.		blank	error

void main(void)
{
	unsigned char i,j = 0;
	
	P1 = 0x00;
	
	DelayMs(25);
	
//	for(j = 0 ; j < 10 ; j++)
//	{
	for(i = 0 ; i < 8 ; i++)
	{
		LedWrite(0x97 - i, realCode[8 - i]);
	}
//	DelayMs(250);
//	}
	while(1)
	{
		DelayMs(250);
		HD7279SendByte(RTL_CYCLE);
	}
}