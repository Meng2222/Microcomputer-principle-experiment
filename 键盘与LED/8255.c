#include "8255.h"

unsigned char xdata IO8255PortA _at_ 0xF800;
unsigned char xdata IO8255PortB _at_ 0xF801;
unsigned char xdata IO8255PortC _at_ 0xF802;
unsigned char xdata IO8255PortCtl _at_ 0xF803;

void IO8255Init(IO8255Init_t IO8255InitStuction)
{
	unsigned char initData = 0x80;
	
	initData|=(IO8255InitStuction.portAInit.IO8255Mode<<5);
	initData|=(IO8255InitStuction.portAInit.IOInOrOut<<4);
	
	initData|=(IO8255InitStuction.portBInit.IO8255Mode<<2);
	initData|=(IO8255InitStuction.portBInit.IOInOrOut<<1);
	
	initData|=(IO8255InitStuction.portCUInit.IOInOrOut<<3);
	
	initData|=(IO8255InitStuction.portCLInit.IOInOrOut);
	
	IO8255PortCtl = initData;
	
}

void IO8255SetBit(IO8255PortDef_t IOPort , unsigned char IOBit , unsigned char state)
{
	if(state)
	{
		switch(IOPort)
		{
			case PortA:
				IO8255PortA = IO8255PortA|(0x01<<IOBit);
			break;
			case PortB:
				IO8255PortB = IO8255PortB|(0x01<<IOBit);
			break;
			case PortC:
				IO8255PortCtl = 0x01|(IOBit<<1);
			break;
			default:
			break;
		}
	}
	else
	{
		switch(IOPort)
		{
			case PortA:
				IO8255PortA = IO8255PortA&(~(0x01<<IOBit));
			break;
			case PortB:
				IO8255PortB = IO8255PortB&(~(0x01<<IOBit));
			break;
			case PortC:
				IO8255PortCtl = 0x00|(IOBit<<1);
			break;
			default:
			break;
		}	
	}
}


unsigned char IO8255ReadBit(IO8255PortDef_t IOPort , unsigned char IOBit)
{
	switch(IOPort)
	{
		case PortA:
			return (IO8255PortA&(0x01<<IOBit))!=0;
		break;
		case PortB:
			return (IO8255PortB&(0x01<<IOBit))!=0;
		break;
		case PortC:
			return (IO8255PortC&(0x01<<IOBit))!=0;
		break;
		default:
		break;
	}
}