#include "gpio.h"

void GPIOInit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin, unsigned char GPIOMode)
{
	switch(GPIOPort)
	{
		case GPIOPort0:
			if(GPIOMode&0x02)
			{
				P0M1|=GPIOPin;
			}
			else
			{
				P0M1&=(~GPIOPin);
			}
			if(GPIOMode&0x01)
			{
				P0M0|=GPIOPin;
			}
			else
			{
				P0M0&=(~GPIOPin);
			}
		break;
		case GPIOPort1:
			if(GPIOMode&0x02)
			{
				P1M1|=GPIOPin;
			}
			else
			{
				P1M1&=(~GPIOPin);
			}
			if(GPIOMode&0x01)
			{
				P1M0|=GPIOPin;
			}
			else
			{
				P1M0&=(~GPIOPin);
			}
		break;
		case GPIOPort2:
			if(GPIOMode&0x02)
			{
				P2M1|=GPIOPin;
			}
			else
			{
				P2M1&=(~GPIOPin);
			}
			if(GPIOMode&0x01)
			{
				P2M0|=GPIOPin;
			}
			else
			{
				P2M0&=(~GPIOPin);
			}
		break;
		case GPIOPort3:
			if(GPIOMode&0x02)
			{
				P3M1|=GPIOPin;
			}
			else
			{
				P3M1&=(~GPIOPin);
			}
			if(GPIOMode&0x01)
			{
				P3M0|=GPIOPin;
			}
			else
			{
				P3M0&=(~GPIOPin);
			}
		break;
		default:
		break;
	}

}

void GPIOSetBit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin)
{
	switch(GPIOPort)
	{
		case GPIOPort0:
			P0|=GPIOPin;
		break;
		case GPIOPort1:
			P1|=GPIOPin;
		break;
		case GPIOPort2:
			P2|=GPIOPin;
		break;
		case GPIOPort3:
			P3|=GPIOPin;
		break;
		default:
		break;
	}

}

void GPIOResetBit(GPIOTypeDef_t GPIOPort, unsigned char GPIOPin)
{
	switch(GPIOPort)
	{
		case GPIOPort0:
			P0&=(~GPIOPin);
		break;
		case GPIOPort1:
			P1&=(~GPIOPin);
		break;
		case GPIOPort2:
			P2&=(~GPIOPin);
		break;
		case GPIOPort3:
			P3&=(~GPIOPin);
		break;
		default:
		break;
	}
}

unsigned char GPIOReadBit(unsigned char GPIOPort, unsigned char GPIOPin)
{
	switch(GPIOPort)
	{
		case GPIOPort0:
			P0|=GPIOPin;
			return ((P0&GPIOPin)!=0x00);
		break;
		case GPIOPort1:
			P1|=GPIOPin;
			return ((P1&GPIOPin)!=0x00);
		break;
		case GPIOPort2:
			P2|=GPIOPin;
			return ((P2&GPIOPin)!=0x00);
		break;
		case GPIOPort3:
			P3|=GPIOPin;
			return ((P3&GPIOPin)!=0x00);
		break;
		default:
			return RETURN_ERROR;
		break;
	}
}
