#include "delay.h"

void DelayMs(unsigned int timeMs)
{
#define TIME_1_MS (355)
	unsigned int nMsCounter = 0;
	unsigned short msCounter = 0;
	unsigned char  i = 0;
	for(nMsCounter = 0 ; nMsCounter < timeMs ; nMsCounter++)
	{
		for(msCounter = 0 ; msCounter < TIME_1_MS ; msCounter++)
		{
			i = 1;
		}
	}
}

void Delay10Us(unsigned int timeUs)
{
#define TIME_10_US (4)
	unsigned int nUsCounter = 0;
	unsigned char usCounter = 0;
	for(nUsCounter = 0 ; nUsCounter < timeUs ; nUsCounter++)
	{
		for(usCounter = 0 ; usCounter < TIME_10_US ; usCounter++)
		{
		
		}
	}
}

