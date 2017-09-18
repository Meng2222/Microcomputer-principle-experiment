#ifndef __P1IO_H
#define __P1IO_H


#define P1_INPUT  (0x0f)

void BlinkIn4(unsigned short period);
void Flow(unsigned short flowPeriod);
void ShowInput(void);

#endif