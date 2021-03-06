#include "stepMotor.h"
#include "delay.h"
#include "8255.h"

void StepMotorPinInit(void)
{
	GPIOInit(PHASE_A_PORT, PHASE_A_PIN, GPIO_PUSHPULL);
	GPIOInit(PHASE_B_PORT, PHASE_B_PIN, GPIO_PUSHPULL);
	GPIOInit(PHASE_C_PORT, PHASE_C_PIN, GPIO_PUSHPULL);
	GPIOInit(PHASE_D_PORT, PHASE_D_PIN, GPIO_PUSHPULL);	
}

void StepMotorSpeedControl(float vel)
{
	static unsigned char xdata state = 0x00;
	static unsigned long xdata counter = 0;
	
	switch(state)
	{
		case 0:
			IO8255SetBit(PortA , 0 , 1);
			IO8255SetBit(PortA , 1 , 0);
			IO8255SetBit(PortA , 2 , 0);
			IO8255SetBit(PortA , 3 , 0);		
//			GPIOSetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 1:
			IO8255SetBit(PortA , 0 , 1);
			IO8255SetBit(PortA , 1 , 1);
			IO8255SetBit(PortA , 2 , 0);
			IO8255SetBit(PortA , 3 , 0);	
//			GPIOSetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOSetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 2:
			IO8255SetBit(PortA , 0 , 0);
			IO8255SetBit(PortA , 1 , 1);
			IO8255SetBit(PortA , 2 , 0);
			IO8255SetBit(PortA , 3 , 0);	
//			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOSetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 3:
			IO8255SetBit(PortA , 0 , 0);
			IO8255SetBit(PortA , 1 , 1);
			IO8255SetBit(PortA , 2 , 1);
			IO8255SetBit(PortA , 3 , 0);
//			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOSetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOSetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 4:
			IO8255SetBit(PortA , 0 , 0);
			IO8255SetBit(PortA , 1 , 0);
			IO8255SetBit(PortA , 2 , 1);
			IO8255SetBit(PortA , 3 , 0);
//			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOSetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOResetBit(PHASE_D_PORT,PHASE_D_PIN);			
		break;
		case 5:
			IO8255SetBit(PortA , 0 , 0);
			IO8255SetBit(PortA , 1 , 0);
			IO8255SetBit(PortA , 2 , 1);
			IO8255SetBit(PortA , 3 , 1);
//			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOSetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOSetBit(PHASE_D_PORT,PHASE_D_PIN);
		break;
		case 6:
			IO8255SetBit(PortA , 0 , 0);
			IO8255SetBit(PortA , 1 , 0);
			IO8255SetBit(PortA , 2 , 0);
			IO8255SetBit(PortA , 3 , 1);
//			GPIOResetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOSetBit(PHASE_D_PORT,PHASE_D_PIN);
		break;
		case 7:
			IO8255SetBit(PortA , 0 , 1);
			IO8255SetBit(PortA , 1 , 0);
			IO8255SetBit(PortA , 2 , 0);
			IO8255SetBit(PortA , 3 , 1);
//			GPIOSetBit(PHASE_A_PORT, PHASE_A_PIN);
//			GPIOResetBit(PHASE_B_PORT,PHASE_B_PIN);
//			GPIOResetBit(PHASE_C_PORT,PHASE_C_PIN);
//			GPIOSetBit(PHASE_D_PORT,PHASE_D_PIN);
		break;
		default:
		break;
	}
	
	counter++;
 	
	if(counter==((unsigned long)((STEP_RESOLUTION/(vel))*1000.0f)))
	{
		counter=0;
		if(vel>0)
		{
	//		DelayMs((int)((STEP_RESOLUTION/vel)*1000));
			state++;
			state%=8;
		}
		else if(vel<0)
		{
	//		DelayMs((int)((STEP_RESOLUTION/(-vel))*1000));
			if(state==0)
			{
				state=8;
			}
			state--;	
		}
	}
}

