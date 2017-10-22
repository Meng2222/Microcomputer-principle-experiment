#include "HD7279.h"
#include "delay.h"
#include "main.h"
#include "89C51_it.h"

#ifndef DATA_MEMORY_TEST

#include "basicIO.h"
#include "decode.h"
#include "p1IO.h"
#include "timer.h"

#endif

#ifdef DATA_MEMORY_TEST

#include "dataMemory.h"

#endif

#ifdef KEY_LED_EXP
//???????????
typedef enum
{
	rollingLeft,
	rollingRight,
	showKeyNumTogether,
	inputRoll2Left,
	idle
}ledStatus_t;

void main(void)
{
//??????????
#define ROLL_PERIOD (15)
	ledStatus_t idata ledStatus = inputRoll2Left;
	unsigned char i,j = 0;
	//????,??????0xff,???????????
	unsigned char keyState = 0;
	unsigned char rollPeriod = ROLL_PERIOD;
	//?????????
	unsigned char keyFlag = 0;
	while(1)
	{
		DelayMs(20);

		//??????
		keyState = KeyRead();

		switch(ledStatus)
		{
			//????
			case rollingLeft:
				//?????????????
				if(keyState==0xff)
				{
					rollPeriod--;
					if(rollPeriod == 0)
					{
						rollPeriod = ROLL_PERIOD;
						HD7279SendByte(RTL_CYCLE);
					}
				}
				//??KEY10???????????
				else if(keyState == KEY10)
				{
					rollPeriod = ROLL_PERIOD;
					HD7279SendByte(CMD_RESET);
					ledStatus = showKeyNumTogether;
				}
			break;
			//??????
			case rollingRight:
				//?????????????
				if(keyState == 0xff)
				{
					rollPeriod--;
					if(rollPeriod == 0)
					{
						rollPeriod = ROLL_PERIOD;
						HD7279SendByte(RTR_CYCLE);
					}
				}
				//??KEY10?????????????
				else if(keyState == KEY10)
				{
					rollPeriod = ROLL_PERIOD;
					HD7279SendByte(CMD_RESET);
					ledStatus = showKeyNumTogether;				
				}
			break;
			//?????????????????
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
				//????????????????????
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
			//????
			case idle:
				
			break;
			default:
			break;
		}
	}
}
#endif

#ifdef BASIC_IO_EXP

void main(void)
{
	//??IO???
	unsigned char ioInput = 0;
	
	while(1)
	{
		DelayMs(20);
		//?74LS245??????IO??
		ioInput = chip245Adress;
	
		//???IO?????74LS374
		chip374Adress = ~ioInput;
	
		//?????????IO????
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
	}
}
#endif

#ifdef DECODE_EXP

void main(void)
{
	//?????????
	unsigned char ioOutput = 0;
	//??????????
	unsigned short timeCounter = 0;
	while(1)
	{
		DelayMs(20);		
		timeCounter++;
		timeCounter%=20;
		if(timeCounter/10)
		{
			decodeAdress1 = ioOutput;
		}
		else
		{
			decodeAdress2 = ioOutput;
		}	
	}
}
#endif

#ifdef P1_IO_EXP
//P1IO????????
typedef enum
{
	blinkIn4,
	flow,
	showInput,
	p1Idle
}p1IOStatus_t;

void main(void)
{
	p1IOStatus_t idata p1IOStatus = flow;
	while(1)
	{
		DelayMs(20);
		
		switch(p1IOStatus)
		{
			//????????
			case blinkIn4:
				BlinkIn4(500);
			break;
			//???
			case flow:
				Flow(500);
			break;
			//?P10~P13?????P14~P17,?????LED???
			case showInput:
				ShowInput();
			break;
			case p1Idle:
			break;
			default:
			break;
		}	
	}
}
#endif

#ifdef TIMER_EXP

typedef enum
{
	timerExp1,
	timerExp2,
	timerExp3	
}timerStatus_t;

void main(void)
{
	timerStatus_t idata timerStatus = timerExp3;
	
	unsigned char triggerFlag = 0;
	
	unsigned short pulseWidth = 0;
	
	timeMode_t timeMode ={0};
	
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = halfWordAutoReload;
	
	TimeInit(TIM0 , timeMode ,200, 3);

	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = counter;
	timeMode.timeTriggerMode = outerTrigger;
	timeMode.timerMode = byteAutoReload;	
	TimeInit(TIM1 , timeMode ,0, 3);
	TimerCmd(TIM1 , disable);
	TH1 = 0xfb;
	TL1 = 0xfb;
	TimerCmd(TIM1 ,enable);
	
	timeMode.isGateCrl = GateCrl;
	timeMode.timeWorkMode = timer;
	timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = halfWordNotReload;	
	TimeInit(TIM1 , timeMode ,65535, 1);
	TimerCmd(TIM1 , disable);	
	while(1)
	{
		switch(timerStatus)
		{
			case timerExp1:
				if(TimerGetOverFlowITFlag(TIM0))
				{
					P10=!P10;
					TimerClearOverFlowFlag(TIM0);
				}
			break;
			case timerExp2:
				{
					if(TimerGetOverFlowITFlag(TIM1))
					{
						P10=!P10;
						TimerClearOverFlowFlag(TIM1);
					}							
				}
			break;
			case timerExp3:
			{
				if(P33==1)
				{
					TimerCmd(TIM1 , disable);
					if(triggerFlag==1)
					{
						pulseWidth = ((TH1<<8)|TL1);
						LEDShowInt(pulseWidth);
						triggerFlag = 0;
						TH1=0;
						TL1=0;
					}
				}
				else if(P33==0)
				{
					TimerCmd(TIM1 , enable);
					triggerFlag = 1;
				}
			}
			break;
		}	
	}
}
#endif

#ifdef INTERRUPT_EXP

typedef enum
{
	itExp1,
	itExp2,
	itExp3
}itStatus_t;

void main(void)
{
	itStatus_t idata itStatus = itExp2;
	
	timeMode_t timeMode ={0};
	
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = counter;
	timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = halfWordAutoReload;
	
	TimeInit(TIM0 , timeMode ,3-1, 1);
	TimerOverFlowItInit(TIM0 , enable);
		
	IT0 = 1;
	while(1)
	{
		DelayMs(20);
		switch(itStatus)
		{
			case itExp1:
				if(LedItStatus)
				{
					Flow(200);
				}
				else
				{
					BlinkIn4(300);
				}
			break;
			case itExp2:
				if(LedItStatus)
				{
					Flow(200);
				}
				else
				{
					BlinkIn4(300);
				}
			break;
			case itExp3:
				if(LedItStatus)
				{
					Flow(200);
				}
				else
				{
					BlinkIn4(300);
				}
			break;
		}		
	}
}

#endif

#ifdef DATA_MEMORY_TEST
void main(void)
{
	unsigned char i = 0;
	P1 = 0x00;
	DelayMs(20);
	while(1)
	{
		AUXR = 0x8e;
		for(i = 0 ; i < DIRECT_ACCESS_SIZE;i++)
		{
			directAccess[i] = i;
			LEDShowInt(directAccess[i]);
			DelayMs(300);
		}
		for(i = 0; i< BIT_ACCESS_SIZE ; i++)
		{
			bitAccess[i] = 255 - i;
			LEDShowInt(bitAccess[i]);
			DelayMs(300);		
		}
		for(i = 0; i< INDIRECT_ACCESS_SIZE ; i++)
		{
			indirectAccess[i] = 128 + i;
			LEDShowInt(indirectAccess[i]);
			DelayMs(300);		
		}
		for(i = 0; i< PAGE_ACCESS_SIZE ; i++)
		{
			pageAccess[i] = i;
			LEDShowInt(pageAccess[i]);
			DelayMs(300);		
		}
		
		for(i = 0; i< OUTER_MEM_IN_MCU_SIZE ; i++)
		{
			outerMemInMCU[i] = i;
			LEDShowInt(outerMemInMCU[i]);
			DelayMs(300);		
		}

		AUXR = 0x02;
		for(i = 0; i< OUTER_EXTEND_MEM_SIZE ; i++)
		{
			outerExtendMem[i] = 128 - i;
			LEDShowInt(outerExtendMem[i]);
			DelayMs(300);		
		}		
	}
}
#endif
