/****************************HD7279.c***********************/
#include "HD7279.h"
#include "delay.h"
#include "stdio.h"

//HD7279显示内容对应数码
unsigned char xdata realCode[] = \
	{0x7e , 0x30 , 0x6d , 0x79 , 0x33 , 0x5b , 0x5f , 0x70 , 0x7f , 0x7b , 0x01 , 0x80 , 0x00 , 0x6f};
//	0		1		2		3		4		5	6		7		8	9		-		.		blank	error

/**
  * @brief	HD7279发送一个字节
  * @note
  * @param	sendData：要发送的数据
  *     @arg
  * @param
  * @retval none
  */
void HD7279SendByte(unsigned char sendData)
{
#define SEND_DATA_LENGTH (8)
	unsigned char xdata sendCounter = 0;
	//片选端拉低
	cs=0;
	Delay10Us(12);
	//生成时钟信号并将八位数字依次发送
	for(sendCounter = 0 ; sendCounter < SEND_DATA_LENGTH ; sendCounter++)
	{
		if(sendData & 0x80)
		{
			dat = 1;
		}
		else
		{
			dat = 0;
		}
		//产生一个上升沿
		clk = 1;
		Delay10Us(2);
		//产生一个下降沿
		clk = 0;
		Delay10Us(2);
		sendData<<=1;
	}
	dat = 0;
}

/**
  * @brief	HD7279接收数据
  * @note
  * @param none
  *     @arg
  * @param none
  * @retval ：接受到的一个字节数据
  */
unsigned char HD7279ReceiveByte(void)
{
#define RECEIVE_DATA_LENGTH (8)
	unsigned char xdata receiveCounter  = 0;
	unsigned char xdata receiveData = 0;
	//数据端拉高准备接收数据
	dat = 1;
	Delay10Us(12);
	//生成时钟信号并将八位数字一次接收
	for(receiveCounter = 0 ; receiveCounter < RECEIVE_DATA_LENGTH ; receiveCounter++)
	{
		//产生一个上升沿
		clk = 1;
		Delay10Us(2);
		receiveData*=2;
		if(dat)
		{
			receiveData|=0x01;
		}
		else
		{
		
		}
		clk = 0;
		Delay10Us(2);
	}
	dat = 0;
	return receiveData;
}

//通过HD7279让数码管显示对应内容
/**
  * @brief	数码管显示函数
  * @note
  * @param cmd：命令字
  *     @arg
* @param dataSend:数据字
  * @retval
  */
void LedWrite(unsigned char cmd , unsigned char dataSend)
{
	HD7279SendByte(cmd);
	
	HD7279SendByte(dataSend);	
}

/**
  * @brief	读取按键状态
  * @note
  * @param
  *     @arg
  * @param
  * @retval ：返回的按键状态
  */
unsigned char KeyRead(void)
{
	HD7279SendByte(CMD_READ);
	
	return (HD7279ReceiveByte());
}

/**
  * @brief	数码管显示整数
  * @note
  * @param	showData：要显示的整形数
  *     @arg
  * @param
  * @retval
  */
void LEDShowInt(long int showData)
{
	//要发送的八个数据
	unsigned char xdata LedData[8] = {0x00};
	//循环技术变量
	unsigned char xdata i = 0;
	//存放字符串用临时数组
	signed char xdata tempBuff[8] = {0};
	//数据长度记录变量
	unsigned char xdata dataLength = 0;
	
	//检验输入数据是否在显示范围内
	if(showData<=99999999&&showData>=-9999999)
	{
	
		//将输入的整数转换为字符串
		sprintf((char *)tempBuff,"%Ld",(long int)showData);
		
		//记录数字长度
		for(i = 0; i< 8; i++)
		{
			if(tempBuff[i]!=0x00)
			{
				dataLength++;
			}
		}
		
		//将字符串转换为对应编码
		for(i = dataLength;i > 0;i--)
		{
			if(tempBuff[i-1]!='-')
			{
				LedData[7 - (dataLength - i)]=tempBuff[i-1] - 0x30;
				LedData[7 - (dataLength - i)] = realCode[LedData[7 - (dataLength - i)]];
			}
			else
			{
				LedData[7 - (dataLength - i)] = realCode[10];			
			}
		}
		
		//显示对应编码
		for(i = 0;i<8;i++)
		{
			LedWrite(0x97 - i , LedData[i]);
		}
	}
	else
	{
		//超出范围时全部显示e
		for(i = 0;i<8;i++)
		{
			LedWrite(0x97 - i , 0x6f);
		}
	}
}
/**
  * @brief	显示浮点数
  * @note
* @param showData:要显示的浮点数
  *     @arg
  * @param
  * @retval
  */
void LEDShowFloat(float showData)
{
	//要发送的8个数据
	unsigned char xdata LedData[8] = {0x00};
	//循环技术变量
	unsigned char xdata i = 0;
	//储存字符串用临时变量
	signed char xdata tempBuff[8] = {0};
	//数据长度记录变量
	unsigned char xdata dataLength = 0;
	
	//检验是否在显示范围内
	if(showData<=9999.99&&showData>=-999.99)
	{
	
		//将输入的整数转换为字符串
		sprintf((char *)tempBuff,"%.2f",(float)showData);
		
		//记录数字长度
		for(i = 0; i< 8; i++)
		{
			if(tempBuff[i]!=0x00)
			{
				dataLength++;
			}
		}
		
		//将字符串转换为对应编码
		for(i = dataLength;i > 0;i--)
		{
			if(tempBuff[i-1]!='-'&&tempBuff[i-1]!='.')
			{
				LedData[7 - (dataLength - i)]=tempBuff[i-1] - 0x30;
				LedData[7 - (dataLength - i)] = realCode[LedData[7 - (dataLength - i)]];
			}
			else if(tempBuff[i-1]=='.')
			{
				LedData[7 - (dataLength - i)]=0x80;
			}
			else if(tempBuff[i-1]=='-')
			{
				LedData[7 - (dataLength - i)] = realCode[10];			
			}
		}
		
		//显示对应编码
		for(i = 0;i<8;i++)
		{
			LedWrite(0x97 - i, LedData[i]);				
		}
	}
	else
	{
		//超出范围时全部显示e
		for(i = 0;i<8;i++)
		{
			LedWrite(0x97 - i , 0x6f);
		}
	}
}
