#include "89C51_it.h"
extern unsigned char LedItStatus;
void interint0()interrupt 0
{
	if(LedItStatus)
	{
		LedItStatus = 0;
	}
	else
	{
		LedItStatus = 1;
	}
}