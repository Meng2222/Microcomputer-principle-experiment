#include "HD7279.h"
#include "delay.h"
#include "main.h"

typedef enum
{
	rollingLeft,
	rollingRight,
	showKeyNumTogether,
	idle
}ledStatus_t;

unsigned char code realCode[] = \
	{0x7e , 0x30 , 0x6d , 0x79 , 0x33 , 0x5b , 0x5f , 0x70 , 0x7f , 0x7b , 0x01 , 0x80 , 0x00 , 0x6f};
//	0		1		2		3		4		5	6		7		8	9		-		.		blank	error


void main(void)
{
#define ROLL_PERIOD (15)
	ledStatus_t status = rollingLeft;
	unsigned char i,j = 0;
	unsigned char keyState = 0;
	unsigned char rollPeriod = ROLL_PERIOD;
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
		DelayMs(20);

		keyState = KeyRead();

		switch(status)
		{
			case rollingLeft:
				if(keyState==0xff)
				{
					rollPeriod--;
					if(rollPeriod == 0)
					{
						rollPeriod = ROLL_PERIOD;
						HD7279SendByte(RTL_CYCLE);
					}
				}
				else if(keyState == KEY10)
				{
					rollPeriod = ROLL_PERIOD;
					HD7279SendByte(CMD_RESET);
					status = showKeyNumTogether;
				}
			break;
			case rollingRight:
				if(keyState == 0xff)
				{
					rollPeriod--;
					if(rollPeriod == 0)
					{
						rollPeriod = ROLL_PERIOD;
						HD7279SendByte(RTR_CYCLE);
					}
				}
				else if(keyState == KEY10)
				{
					rollPeriod = ROLL_PERIOD;
					HD7279SendByte(CMD_RESET);
					status = showKeyNumTogether;				
				}
			break;
			case showKeyNumTogether:
				switch(keyState)
				{
					case KEY0:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[0]);
						}
					break;
					case KEY1:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[1]);
						}
					break;
					case KEY2:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[2]);
						}
					break;
					case KEY3:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[3]);
						}
					break;
					case KEY4:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[4]);
						}					
					break;
					case KEY5:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[5]);
						}					
					break;
					case KEY6:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[6]);
						}					
					break;
					case KEY7:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[7]);
						}					break;
					case KEY8:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[8]);
						}					
					break;
					case KEY9:
						for(i = 0 ; i < 8 ; i++)
						{
							LedWrite(0x97 - i, realCode[9]);
						}					
					break;
					default:
					break;
				}	
			break;
			case idle:
			break;
		}

	}
}