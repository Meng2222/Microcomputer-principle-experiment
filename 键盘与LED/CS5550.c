#include "CS5550.h"
#include "delay.h"
#include "8255.h"

void CS5550WriteByte(unsigned char message)
{
	unsigned char xdata i = 0;
	for(i = 0;i<8;i++)
	{
		CS5550_SCLK = 0;

		if(message&0x80)
		{
			CS5550_SDI = 1;
		}
		else
		{
			CS5550_SDI = 0;
		}
		Delay10Us(2);
		CS5550_SCLK = 1;
		Delay10Us(2);
		message<<=1;

	}
	CS5550_SCLK = 0;
}

unsigned char CS5550RecieveByte(void)
{
	unsigned char xdata recieveData = 0;
	unsigned char xdata i = 0;
	
	for(i = 0;i<8;i++)
	{
		if(i==7)
		{
			CS5550_SDI = 0;
		}
		else
		{
			CS5550_SDI = 1;
		}

		CS5550_SCLK = 0;	
		recieveData<<=1;
		Delay10Us(2);
		CS5550_SCLK = 1;
		Delay10Us(2);
		if(CS5550_SDO)
		{
			recieveData|=0x01;
		}
		else
		{
			recieveData&=(~0x01);
		}

	}
	return recieveData;
}

void CS5550WriteCmd(unsigned char cmd, unsigned long value)
{
	CS5550_CS = 0;
	CS5550WriteByte(cmd);
	CS5550WriteByte((value>>16)&0xff);
	CS5550WriteByte((value>>8)&0xff);
	CS5550WriteByte(value&0xff);
	CS5550_CS = 1;
}

void CS5550WriteRes(unsigned char cmd, unsigned long value)
{
	CS5550_CS = 0;
	CS5550WriteByte(cmd+0x40);
	CS5550WriteByte((value>>16)&0xff);
	CS5550WriteByte((value>>8)&0xff);
	CS5550WriteByte(value&0xff);
	CS5550_CS = 1;
}

unsigned long CS5550ReadRes(unsigned char cmd)
{
	unsigned long xdata recieveData = 0;
	CS5550_CS = 0;
	CS5550WriteByte(cmd);
	recieveData|=((unsigned long)CS5550RecieveByte()<<16);
	recieveData|=((unsigned long)CS5550RecieveByte()<<8);
	recieveData|=CS5550RecieveByte();
	CS5550_CS = 1;
	return recieveData;
}

