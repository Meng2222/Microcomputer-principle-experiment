#include "dataMemory.h"
unsigned char data directAccess[DIRECT_ACCESS_SIZE] = {0};
unsigned char bdata bitAccess[BIT_ACCESS_SIZE] = {0};
unsigned char idata indirectAccess[INDIRECT_ACCESS_SIZE] = {0};
unsigned char pdata pageAccess[PAGE_ACCESS_SIZE] = {0};
unsigned char xdata outerMemInMCU[OUTER_MEM_IN_MCU_SIZE] _at_ 0x100;
unsigned char xdata outerExtendMem[OUTER_EXTEND_MEM_SIZE] _at_ 0x500;