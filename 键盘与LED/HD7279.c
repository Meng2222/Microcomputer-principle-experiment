#include "HD7279.h"
#include "delay.h"

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

void LedWrite(unsigned char cmd , unsigned char dataSend)
{
	HD7279SendByte(cmd);
	
	HD7279SendByte(dataSend);	
}

unsigned char KeyRead(void)
{
	HD7279SendByte(CMD_READ);
	
	return (HD7279ReceiveByte());
}
