#include "HD7279.h"
#include "delay.h"

//HD7279显示内容对应数码
unsigned char code realCode[] = \
	{0x7e , 0x30 , 0x6d , 0x79 , 0x33 , 0x5b , 0x5f , 0x70 , 0x7f , 0x7b , 0x01 , 0x80 , 0x00 , 0x6f};
//	0		1		2		3		4		5	6		7		8	9		-		.		blank	error

//向HD7279发送一个字节
void HD7279SendByte(unsigned char sendData)
{
#define SEND_DATA_LENGTH (8)
	unsigned char sendCounter = 0;
	cs = 0;
	Delay10Us(12);
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
		clk = 1;
		Delay10Us(2);
		clk = 0;
		Delay10Us(2);
		sendData<<=1;
	}
	dat = 0;
}

//从HD7279接收一个字节
unsigned char HD7279ReceiveByte(void)
{
#define RECEIVE_DATA_LENGTH (8)
	unsigned char receiveCounter  = 0;
	unsigned char receiveData = 0;
	dat = 1;
	Delay10Us(12);
	for(receiveCounter = 0 ; receiveCounter < RECEIVE_DATA_LENGTH ; receiveCounter++)
	{
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
void LedWrite(unsigned char cmd , unsigned char dataSend)
{
	HD7279SendByte(cmd);
	
	HD7279SendByte(dataSend);	
}

//读取按键状态
unsigned char KeyRead(void)
{
	HD7279SendByte(CMD_READ);
	
	return (HD7279ReceiveByte());
}
