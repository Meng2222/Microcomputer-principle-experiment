#include "HD7279.h"
#include "delay.h"
#include "main.h"
#include "basicIO.h"
#include "decode.h"
#include "p1IO.h"

//数码管显示状态枚举变量
typedef enum
{
	rollingLeft,
	rollingRight,
	showKeyNumTogether,
	inputRoll2Left,
	idle
}ledStatus_t;

//程序运行状态枚举变量
typedef enum
{
	keyLed,
	basicIO,
	decode,
	p1IO,
	statusIdle
}status_t;

//P1IO输出状态枚举变量
typedef enum
{
	blinkIn4,
	flow,
	showInput,
	p1Idle
}p1IOStatus_t;

void main(void)
{
//数码管滚动显示的周期
#define ROLL_PERIOD (15)
	ledStatus_t ledStatus = inputRoll2Left;
	status_t status = p1IO;
	p1IOStatus_t p1IOStatus = flow;
	unsigned char i,j = 0;
	//按键状态，没有按下时为0xff，按下时为按下按键的编号
	unsigned char keyState = 0;
	unsigned char rollPeriod = ROLL_PERIOD;
	//按键是否按下标志位
	unsigned char keyFlag = 0;
	//简单IO输入值
	unsigned char ioInput = 0;
	//译码实验输出用变量
	unsigned char ioOutput = 0;
	//译码实验闪烁计时变量
	unsigned short timeCounter = 0;
	
//	//将HD7279对应引脚全部拉低
//	P1 = 0x00;
	
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
			//按键和LED
			case keyLed:
				
				//读取按键状态
				keyState = KeyRead();

				switch(ledStatus)
				{
					//向左滚动
					case rollingLeft:
						//没有按键按下时循环向左滚动
						if(keyState==0xff)
						{
							rollPeriod--;
							if(rollPeriod == 0)
							{
								rollPeriod = ROLL_PERIOD;
								HD7279SendByte(RTL_CYCLE);
							}
						}
						//按下KEY10后进入一同显示数字状态
						else if(keyState == KEY10)
						{
							rollPeriod = ROLL_PERIOD;
							HD7279SendByte(CMD_RESET);
							ledStatus = showKeyNumTogether;
						}
					break;
					//循环向右滚动
					case rollingRight:
						//没有按键按下时循环向右滚动
						if(keyState == 0xff)
						{
							rollPeriod--;
							if(rollPeriod == 0)
							{
								rollPeriod = ROLL_PERIOD;
								HD7279SendByte(RTR_CYCLE);
							}
						}
						//按下KEY10时进入一同显示按下数字状态
						else if(keyState == KEY10)
						{
							rollPeriod = ROLL_PERIOD;
							HD7279SendByte(CMD_RESET);
							ledStatus = showKeyNumTogether;				
						}
					break;
					//所有数码管一同显示按下按键对应数字
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
						//每次按键时不循环左移并显示按键对应的数字
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
					//空闲状态
					case idle:
						
					break;
					default:
					break;
				}
			break;
			//简单IO实验
			case basicIO:
				
				//从74LS245地址读取简单IO输入
				ioInput = chip245Adress;
			
				//将简单IO输入输出到74LS374
				chip374Adress = ~ioInput;
			
				//在数码管上显示简单IO输入状态
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
			//译码器实验
			case decode:
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
			
			break;
			case statusIdle:
			break;
			//P1IO口实验
			case p1IO:
				switch(p1IOStatus)
				{
					//四个一组循环闪烁
					case blinkIn4:
						BlinkIn4(500);
					break;
					//流水灯
					case flow:
						Flow(500);
					break;
					//将P10~P13输入输出到P14~P17，用输入控制LED的亮灭
					case showInput:
						ShowInput();
					break;
					case p1Idle:
					break;
					default:
					break;
				}
			break;
			default:
			break;
		}
	}
}
