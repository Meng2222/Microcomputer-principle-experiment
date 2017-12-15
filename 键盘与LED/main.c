#include "HD7279.h"
#include "delay.h"
#include "main.h"
#include "89C51_it.h"

#ifndef DATA_MEMORY_TEST

#include "8255.h"
#include "basicIO.h"
#include "decode.h"
#include "p1IO.h"
#include "timer.h"
#include "usart.h"
#include "8254.h"
#include "stepMotor.h"
#include "pwm.h"
#include "brushDcMotor.h"
#include "CS5550.h"

#endif

#ifdef DATA_MEMORY_TEST

#include "dataMemory.h"

#endif

//键盘与LED实验
#ifdef KEY_LED_EXP
//键盘与LED实验状态枚举变量
typedef enum
{
	//循环左移
	rollingLeft,
	//循环右移
	rollingRight,
	//所有数码管显示按键输入的数字（0~9）
	showKeyNumTogether,
	//数码管显示按键输入数字并在每次输入后左移一位
	inputRoll2Left,
	//空闲状态
	idle
}ledStatus_t;

void main(void)
{
//循环移位的周期数宏定义
#define ROLL_PERIOD (15)
	//状态指示变量
	ledStatus_t idata ledStatus = inputRoll2Left;
	//循环用计数变量
	unsigned char i,j = 0;
	//按键状态，没有按下时为0xff，按下时为按下按键的编号
	unsigned char keyState = 0;
	//循环移位周期变量
	unsigned char rollPeriod = ROLL_PERIOD;
	//按键是否按下标志位
	unsigned char keyFlag = 0;
	while(1)
	{
		//每隔20ms循环一次
		DelayMs(20);

		//读取按键状态
		keyState = KeyRead();

		switch(ledStatus)
		{
			//数码管显示内容循环左移
			case rollingLeft:
				//没有按键按下时循环向左滚动
				if(keyState==0xff)
				{
					rollPeriod--;
					if(rollPeriod == 0)
					{
						rollPeriod = ROLL_PERIOD;
						//每间隔一个周期发送一个左移命令
						HD7279SendByte(RTL_CYCLE);
					}
				}
				//按下KEY10时进入所有数码管显示同一数字状态
				else if(keyState == KEY10)
				{
					rollPeriod = ROLL_PERIOD;
					HD7279SendByte(CMD_RESET);
					ledStatus = showKeyNumTogether;
				}
			break;
			//数码管显示内容循环右移
			case rollingRight:
				//没有按键按下时数码管显示内容循环右移
				if(keyState == 0xff)
				{
					rollPeriod--;
					if(rollPeriod == 0)
					{
						rollPeriod = ROLL_PERIOD;
						HD7279SendByte(RTR_CYCLE);
					}
				}
				//按下KEY10时进入所有数码管显示同一数字状态
				else if(keyState == KEY10)
				{
					rollPeriod = ROLL_PERIOD;
					HD7279SendByte(CMD_RESET);
					ledStatus = showKeyNumTogether;				
				}
			break;
			//所有数码管一通显示按下按键对应数字
			case showKeyNumTogether:
				//根据按键状态显示数字（按键编号与数字对应）
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
				//每次按键时左移并在最后一位显示对应数字
			case inputRoll2Left:
				if(keyState!=0xff&&keyFlag==0)
				{
					//发送不循环左移命令
					HD7279SendByte(RTL_UNCYL);
					//根据按键状态在最后一位显示对应数字
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
					//对按键状态进行置位
					keyFlag = 1;
				}
				//当没有按键按下时对按键状态进行复位
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
	}
}
#endif

//简单IO实验
#ifdef BASIC_IO_EXP

void main(void)
{
	//IO输入记录变量
	unsigned char ioInput = 0;
	//循环计数用变量
	unsigned char i = 0;
	
	while(1)
	{
		//每20MS循环一次
		DelayMs(20);
		
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
	}
}
#endif

//译码器实验
#ifdef DECODE_EXP

void main(void)
{
	//译码实验输出变量
	unsigned char ioOutput = 0;
	//计数用变量
	unsigned short timeCounter = 0;
	while(1)
	{
		//每20ms循环一次
		DelayMs(20);
		
		//记录循环次数
		timeCounter++;
		timeCounter%=20;
		
		//每隔一定周期将输出输出到不同的地址
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

//通用IOP1实验
#ifdef P1_IO_EXP
//P1IO实验状态指示枚举变量
typedef enum
{
	//四个LED灯
	blinkIn4,
	//流水灯 
	flow,
	//LED灯指示开关状态
	showInput,
	//空闲状态
	p1Idle
}p1IOStatus_t;

void main(void)
{
	//状态指示变量
	p1IOStatus_t idata p1IOStatus = flow;
	while(1)
	{
		//每20ms循环一次
		DelayMs(20);
		
		switch(p1IOStatus)
		{
			//四个LED一组闪烁
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
	}
}
#endif

//定时器实验
#ifdef TIMER_EXP

//状态指示枚举变量类型
typedef enum
{
	timerExp1,
	timerExp2,
	timerExp3	
}timerStatus_t;

void main(void)
{
	//状态指示变量
	timerStatus_t idata timerStatus = timerExp3;
	
	//实验三是否触发指示变量
	unsigned char triggerFlag = 0;
	
	//实验三脉冲宽度变量
	unsigned short pulseWidth = 0;
	
	//定时器初始化结构体 
	timeMode_t timeMode ={0};
	
	//对结构体进行赋值
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = halfWordAutoReload;
	
	//初始化定时器
	TimeInit(TIM0 , timeMode ,200, TIMERUS);

	//对结构体进行赋值
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = counter;
	timeMode.timeTriggerMode = outerTrigger;
	timeMode.timerMode = byteAutoReload;
	//初始化定时器
	TimeInit(TIM1 , timeMode ,0, TIMERUS);
	TimerCmd(TIM1 , disable);
	TH1 = 0xfb;
	TL1 = 0xfb;
	TimerCmd(TIM1 ,enable);
	
	if(timerStatus==timerExp3)
	{
		//对结构体进行赋值	
		timeMode.isGateCrl = GateCrl;
		timeMode.timeWorkMode = timer;
		timeMode.timeTriggerMode = innerTrigger;
		timeMode.timerMode = halfWordNotReload;	
		//初始化定时器	
		TimeInit(TIM1 , timeMode ,65535, 1);
		TimerCmd(TIM1 , disable);
	}		
	while(1)
	{
		switch(timerStatus)
		{
			//在P1.0引脚上生成一个周期为400uS的方波
			case timerExp1:
				if(TimerGetOverFlowITFlag(TIM0))
				{
					P10=!P10;
					TimerClearOverFlowFlag(TIM0);
				}
			break;
			//通过定时器技术控制LED的亮灭
			case timerExp2:
				{
					if(TimerGetOverFlowITFlag(TIM1))
					{
						P10=!P10;
						TimerClearOverFlowFlag(TIM1);
					}							
				}
			break;
			//测量脉冲宽度
			case timerExp3:
			{
				//输入为高
				if(P33==1)
				{
					//失能定时器 
					TimerCmd(TIM1 , disable);
					//如果之前被触发计算脉冲宽度
					if(triggerFlag==1)
					{
						//从定时器寄存器中读出脉冲宽度
						pulseWidth = ((TH1<<8)|TL1);
						//在数码管上显示脉冲宽度
						LEDShowInt(pulseWidth);
						//复位标志位及寄存器
						triggerFlag = 0;
						TH1=0;
						TL1=0;
					}
				}
				//输入为低
				else if(P33==0)
				{
					//开始计时并对标志位进行置位
					TimerCmd(TIM1 , enable);
					triggerFlag = 1;
				}
			}
			break;
		}	
	}
}
#endif

//中断实验
#ifdef INTERRUPT_EXP

//中断实验状态指示枚举变量类型
typedef enum
{
	itExp1,
	itExp2,
	itExp3
}itStatus_t;

//LED状态知识标志位
unsigned char LedItStatus = 0;
unsigned char itTimes = 0;

void main(void)
{
	//中断状态指示枚举变量
	itStatus_t idata itStatus = itExp3;
	
	//定时器初始化结构体
	timeMode_t timeMode ={0};
	
	//初始化定时器
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = timer;
	timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = halfWordAutoReload;
	
	TimeInit(TIM0 , timeMode ,5000, TIMERUS);
	
	//使能定时器中断
	TimerOverFlowItInit(TIM0 , enable);
	
	//使能外部中断0
	IT0 = 1;
	

	while(1)
	{
		//每20ms循环一次
		DelayMs(20);
		//根据不同中断中的标志切换LED的状态
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

//数据储存器实验
#ifdef DATA_MEMORY_TEST
void main(void)
{
	//循环用计数变量
	unsigned char i = 0;
	//对P1IO的输出状态进行初始化
	P1 = 0x00;
	//延时20ms
	DelayMs(20);
	while(1)
	{
		//配置辅助寄存器
		AUXR = 0x8e;
		//对数据进行赋值和显示
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
		//配置辅助寄存器禁止片内扩展RAM区
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

#ifdef UART_EXP
unsigned char UART1Recieve = 0;

void main(void)
{
//	//对P1IO的输出状态进行初始化
	
	UARTMode_t UARTInitStruct = {0};
	
	P1 = 0x00;
	
	UARTInitStruct.UARTMode = UART_MODE_1;
	UARTInitStruct.UARTIsMulti = 0;
	UARTInitStruct.isUARTBaudrateDouble = UART_BAUDRATE_NORMAL;
	UARTInitStruct.itPriority = 0;
	
	UARTInit(UART1,UARTInitStruct,9600);
	
	while(1)
	{
		DelayMs(20);
		
		UARTSendByte(UART1,84);
		
		LEDShowInt(UART1Recieve);
		
	}
}
#endif

#ifdef IO8255_EXP

void main(void)
{
	IO8255Init_t IO8255InitStuct = {0};
	unsigned char pinNum = 0;
	
	IO8255InitStuct.portAInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portAInit.IOInOrOut = IO8255_INPUT;

	IO8255InitStuct.portBInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portBInit.IOInOrOut = IO8255_OUTPUT;
	
	IO8255InitStuct.portCUInit.IOInOrOut = IO8255_OUTPUT;
	IO8255InitStuct.portCLInit.IOInOrOut = IO8255_OUTPUT;

	IO8255Init(IO8255InitStuct);
	
	while(1)
	{
		for(pinNum=0 ; pinNum < 8 ; pinNum++)
		{
			IO8255SetBit(PortC , pinNum , IO8255ReadBit(PortA , pinNum));
		}

	}
}

#endif

#ifdef TIMER_8254_EXP

void main(void)
{
	
	CLK_DIV = (CLK_DIV&0x3f)|0x40;
	
	EA = 1;
	
	Timer8254CounterModeInit(timer8254Timer0, 10000);
	
	Timer8254PrescalerModeInit(timer8254Timer1, 500);
	
	StepMotorPinInit();

	ExternalITInit(exIT1 , EXIT_DOWN_TRIGGER);
	ExternalITCmd(exIT1, enable);

	
	while(1)
	{
	
//		LEDShowInt(Timer8254GetCounter(timer8254Timer0));
		DelayMs(20);
	}
}

#endif

#ifdef STEPMOTOR_EXP

extern float xdata actSpeed;
void main(void)
{
//	StepMotorPinInit();
//	while(1)
//	{
//		StepMotorSpeedControl(PI);
//	}
//	//定时器初始化结构体 
//	timeMode_t xdata timeMode ={0};
//	
//	//对结构体进行赋值
//	timeMode.isGateCrl = noGateCrl;
//	timeMode.timeWorkMode = timer;
//	timeMode.timeTriggerMode = innerTrigger;
//	timeMode.timerMode = halfWordAutoReload;
//	
//	//初始化定时器
//	TimeInit(TIM0 , timeMode ,100000, TIMERUS);
//	
//	TimerOverFlowItInit(TIM0 , enable);

//		//对结构体进行赋值
//	timeMode.isGateCrl = noGateCrl;
//	timeMode.timeWorkMode = counter;
//	timeMode.timeTriggerMode = innerTrigger;
//	timeMode.timerMode = halfWordAutoReload;
//	
//	//初始化定时器
//	TimeInit(TIM1 , timeMode ,0, TIMERUS);
//	
	PWM0Init();
	
	CCP1Init();
	
	PWM0SetCompare(0.5f);
	PWMCmd(enable);
//	
//	DelayMs(5000);

//unsigned long xdata adcGetValue  = 45;
//unsigned long xdata status = 0;
//float xdata adcFloat = 0.0f;

	CLK_DIV = (CLK_DIV&0x3f)|0x40;
	
//	CS5550WriteCmd(SOFT_RESET_CMD, 0xffffff);
//	DelayMs(1);
//	CS5550WriteCmd(SYNC1_CMD, 0xfffffe);
//	DelayMs(1);
//	CS5550WriteRes(CONFIG_RES, 0x000011);
//	DelayMs(1);
//	CS5550WriteCmd(START_CONTINUE_CONVER_CMD, 0xffffff);
//	DelayMs(1);	
//	CS5550WriteRes(CYCLE_COUNT_RES, 0x000138);
//	DelayMs(2);		

	
	while(1)
	{
//		DelayMs(100);
//		adcGetValue = CS5550ReadRes(FILT_AIN1_RES);
//		adcFloat = adcGetValue/(float)0x01000000;
//		status = CS5550ReadRes(STATUS_RES);
//		LEDShowFloat(adcFloat);
//		MotorVelCrl(50.0f,actSpeed);
//		LEDShowFloat(actSpeed);	
//		LedWrite(0x97,0x4F);
	}
}

#endif


#ifdef FINAL_EXAM

typedef enum
{
	readTemparature,
	readResister
}taskStatus_t;

typedef enum
{
	LEDShowAnalog,
	LEDShowSpeed
}LEDShowStatus_t;

//float xdata motorSpeed = 0.0f;
unsigned char xdata semapher = 0;
extern float xdata actSpeed;

void main(void)
{

//	unsigned long xdata tempraturADValue  = 0;
	unsigned long xdata voltageADValue = 0;
	unsigned char xdata valueSign = 0;
//	float xdata temprature = 0.0f;
	float xdata resisterValue = 0.0f;
	float xdata outputVoltage = 0.0f;
	taskStatus_t xdata taskStatus = readResister;
	LEDShowStatus_t xdata LEDShowStatus = LEDShowAnalog;
	unsigned char xdata keyState = 0;
	unsigned char xdata keyFlag = 0;
	union
    {
		unsigned char u8data[4];
		float floatData;
    }datatransform;
	
	//定时器初始化结构体 
	timeMode_t xdata timeMode ={0};
	
	//8255初始化结构体
	IO8255Init_t xdata IO8255InitStuct = {0};
	
	//串口初始化结构体
	UARTMode_t xdata UARTInitStruct = {0};

	//时钟输出1分频
	CLK_DIV = (CLK_DIV&0x3f)|0x40;
	
	//8255初始化
	IO8255InitStuct.portAInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portAInit.IOInOrOut = IO8255_OUTPUT;

	IO8255InitStuct.portBInit.IO8255Mode = IO8255_MODE0;
	IO8255InitStuct.portBInit.IOInOrOut = IO8255_INPUT;
	
	IO8255InitStuct.portCUInit.IOInOrOut = IO8255_OUTPUT;
	IO8255InitStuct.portCLInit.IOInOrOut = IO8255_OUTPUT;

	IO8255Init(IO8255InitStuct);
	
//	//8254初始化
	Timer8254PrescalerModeInit(timer8254Timer1, 500);
	
	//对结构体进行赋值
	timeMode.isGateCrl = noGateCrl;
	timeMode.timeWorkMode = counter;
	timeMode.timeTriggerMode = innerTrigger;
	timeMode.timerMode = halfWordAutoReload;
	
	//初始化定时器
	TimeInit(TIM0 , timeMode ,0, TIMERUS);
//	
	//串口初始化
	UARTInitStruct.UARTMode = UART_MODE_1;
	UARTInitStruct.UARTIsMulti = 0;
	UARTInitStruct.isUARTBaudrateDouble = UART_BAUDRATE_NORMAL;
	UARTInitStruct.itPriority = 0;
	
	UARTInit(UART1,UARTInitStruct,9600);
//	
	//CS5550初始化
	CS5550WriteCmd(SOFT_RESET_CMD, 0xffffff);
	DelayMs(1);
	CS5550WriteCmd(SYNC1_CMD, 0xfffffe);
	DelayMs(1);
	CS5550WriteRes(CONFIG_RES, 0x000011);
	DelayMs(1);
	CS5550WriteCmd(START_CONTINUE_CONVER_CMD, 0xffffff);
	DelayMs(1);	
	CS5550WriteRes(CYCLE_COUNT_RES, 0x000138);
	DelayMs(2);

	//PWM初始化
	PWM0Init();
	
	PWM0SetCompare(0.0f);
	PWMCmd(enable);		
	
	EA = 1;
//	
////	StepMotorPinInit();

	ExternalITInit(exIT1 , EXIT_DOWN_TRIGGER);
	ExternalITCmd(exIT1, enable);
	
	
	while(1)
	{
		while(semapher==0);
		
		//读取按键状态
		keyState = KeyRead();
		
		if(keyState==0xff)
		{
			keyFlag = 0;
		}		
		if(keyFlag==0&&keyState!=0xff)
		{
			if(keyState==KEY0)
			{
				if(LEDShowStatus)
				{
					LEDShowStatus = LEDShowAnalog;
				}
				else
				{
					LEDShowStatus = LEDShowSpeed;
				}
			}
			keyFlag = 1;
		}

				voltageADValue = CS5550ReadRes(FILT_AIN1_RES);
		
				resisterValue = voltageADValue/(float)0x01000000;

				resisterValue = resisterValue*322.4 + 0.3889;
		
				resisterValue = resisterValue/0.0213219;
		
				resisterValue = resisterValue/5000.0f*214.0;
		
				outputVoltage = resisterValue/214.0f * 4.0f + 1.0f;
		
				PWM0SetCompare((6.51f-outputVoltage)/6.231f);
				
				switch(LEDShowStatus)
				{
					case LEDShowAnalog:
						LEDShowFloat(resisterValue);
						LedWrite(0x97,0xe7);						
						datatransform.floatData = resisterValue;
						UARTSendByte(UART1,datatransform.u8data[0]);
						UARTSendByte(UART1,datatransform.u8data[1]);
						UARTSendByte(UART1,datatransform.u8data[2]);
						UARTSendByte(UART1,datatransform.u8data[3]);


					break;
					case LEDShowSpeed:
						LEDShowInt((unsigned long)(actSpeed/PI/2.0*60.0f));
						LedWrite(0x97,0x5b);						
						datatransform.floatData = actSpeed/PI/2.0*60.0f;					
						UARTSendByte(UART1,datatransform.u8data[0]);
						UARTSendByte(UART1,datatransform.u8data[1]);
						UARTSendByte(UART1,datatransform.u8data[2]);
						UARTSendByte(UART1,datatransform.u8data[3]);			
						
					break;
					default:
					break;
				}

		
		
	}
}

#endif

