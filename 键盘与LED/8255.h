/***********************8255.h******************************/
#ifndef __8255_H
#define __8255_H

//8255工作模式宏定义
#define IO8255_MODE0 (0)
#define IO8255_MODE1 (1)
#define IO8255_MODE2 (2)

//8255输入输出宏定义
#define IO8255_OUTPUT (0)
#define IO8255_INPUT (1)

//8255端口号枚举类型定义
typedef enum
{
	PortA,
	PortB,
	PortC
}IO8255PortDef_t;

//8255端口 初始化结构体类型定义
typedef struct
{
	unsigned char IO8255Mode;
	unsigned char IOInOrOut;
}IO8255PortInit_t;

//8255初始化结构体定义
typedef struct
{
	IO8255PortInit_t portAInit;
	IO8255PortInit_t portBInit;
	IO8255PortInit_t portCUInit;
	IO8255PortInit_t portCLInit;	
}IO8255Init_t;

void IO8255Init(IO8255Init_t IO8255InitStuction);

void IO8255SetBit(IO8255PortDef_t IOPort , unsigned char IOBit , unsigned char state);

unsigned char IO8255ReadBit(IO8255PortDef_t IOPort , unsigned char IOBit);

#endif
