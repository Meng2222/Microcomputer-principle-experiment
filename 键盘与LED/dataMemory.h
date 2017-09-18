#ifndef __DATAMEMORY_H
#define __DATAMEMORY_H

#define DIRECT_ACCESS_SIZE (32)
#define BIT_ACCESS_SIZE (14)
#define INDIRECT_ACCESS_SIZE (32)
#define PAGE_ACCESS_SIZE (32)
#define OUTER_MEM_IN_MCU_SIZE (256)
#define OUTER_EXTEND_MEM_SIZE (256)

extern unsigned char data directAccess[DIRECT_ACCESS_SIZE];
extern unsigned char bdata bitAccess[BIT_ACCESS_SIZE];
extern unsigned char idata indirectAccess[INDIRECT_ACCESS_SIZE];
extern unsigned char pdata pageAccess[PAGE_ACCESS_SIZE];
extern unsigned char xdata outerMemInMCU[OUTER_MEM_IN_MCU_SIZE];
extern unsigned char xdata outerExtendMem[OUTER_EXTEND_MEM_SIZE];

#endif