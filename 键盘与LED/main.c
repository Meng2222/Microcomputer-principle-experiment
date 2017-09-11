#include "HD7279.h"
#include "delay.h"
#include "main.h"
#include "basicIO.h"

typedef enum
{
	rollingLeft,
	rollingRight,
	showKeyNumTogether,
	inputRoll2Left,
	idle
}ledStatus_t;

typedef enum
{
	keyLed,
	basicIO,
	statusIdle
}status_t;

void main(void)
{
#define ROLL_PERIOD (15)
	ledStatus_t ledStatus = inputRoll2Left;
	status_t status = basicIO;
	unsigned char i,j = 0;
	unsigned char keyState = 0;
	unsigned char rollPeriod = ROLL_PERIOD;
	unsigned char keyFlag = 0;
	unsigned char ioInput = 0;
	P1 = 0x00;
	
	DelayMs(25);
	
//	for(j = 0 ; j < 10 ; j++)
//	{
//	for(i = 0 ; i < 8 ; i++)
//	{
//		LedWrite(0x97 - i, realCode[8 - i]);
//	}
//	DelayMs(250);
//	}
	while(1)
	{
		DelayMs(20);
		
		switch(status)
		{
			case keyLed:
				keyState = KeyRead();

				switch(ledStatus)
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
							ledStatus = showKeyNumTogether;
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
							ledStatus = showKeyNumTogether;				
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
								}					
							break;
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
					case inputRoll2Left:
						if(keyState!=0xff&&keyFlag==0)
						{
							HD7279SendByte(RTL_UNCYL);
							switch(keyState)
							{
								case KEY0:
									LedWrite(LED1, realCode[0]);
								break;
								case KEY1:
									LedWrite(LED1, realCode[1]);
								break;
								case KEY2:
									LedWrite(LED1, realCode[2]);
								break;
								case KEY3:
									LedWrite(LED1, realCode[3]);
								break;
								case KEY4:
									LedWrite(LED1, realCode[4]);
								break;
								case KEY5:
									LedWrite(LED1, realCode[5]);
								break;
								case KEY6:
									LedWrite(LED1, realCode[6]);
								break;
								case KEY7:
									LedWrite(LED1, realCode[7]);
								break;
								case KEY8:
									LedWrite(LED1, realCode[8]);
								break;
								case KEY9:
									LedWrite(LED1, realCode[9]);
								break;
								default:
								break;
							}
							keyFlag = 1;
						}
						if(keyState == 0xff&&keyFlag == 1)
						{
							keyFlag = 0;
						}
							
					break;
					case idle:
					break;
					default:
					break;
				}
			break;
			case basicIO:
				ioInput = chip245Adress;
				chip374Adress = ~ioInput;
				for(i = 0 ; i < 8 ; i++)
				{
					if((ioInput>>i)&0x01)
					{
						LedWrite(0x97 - 7 + i, realCode[1]);
					}
					else
					{
						LedWrite(0x97 - 7 + i, realCode[0]);					
					}
				}
				
			break;
			case statusIdle:
			break;
			default:
			break;
		}
		

	}
}