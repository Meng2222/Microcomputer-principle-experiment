#ifndef __CS5550_H
#define __CS5550_H

#include "main.h"

#define START_SINGLE_CONVER_CMD (0xe0)
#define START_CONTINUE_CONVER_CMD (0xe8)
#define SYNC0_CMD (0xfe)
#define SYNC1_CMD (0xff)
#define POWER_UP_CMD (0xa0)
#define SOFT_RESET_CMD (0x80)
#define STANDBY_CMD (0x88)
#define SLEEP_CMD (0x90)
#define AIN1_GAIN_CMD (0xca)
#define AIN1_OFFSET_CMD (0xc9)
#define AIN2_GAIN_CMD (0xd2)
#define AIN2_OFFSET_CMD (0xd1)
#define AIN12_GAIN_CMD (0xda)
#define AIN12_OFFSET_CMD (0xd9)

#define CONFIG_RES (0x00<<1)
#define AIN1_OFFSET_RES (0x01<<1)
#define AIN1_GAIN_RES (0x02<<1)
#define AIN2_OFFSET_RES (0x03<<1)
#define AIN2_GAIN_RES (0x04<<1)
#define CYCLE_COUNT_RES (0x05<<1)
#define AIN1_OUTPUT_RES (0x07<<1)
#define AIN2_OUTPUT_RES (0x08<<1)
#define FILT_AIN1_RES (0x0b<<1)
#define FILT_AIN2_RES (0x0c<<1)
#define STATUS_RES (0x0f<<1)
#define MASK_RES (0x1a<<1)
#define CONTROL_RES (0x1c<<1)

sbit CS5550_SDO = P1^0;
sbit CS5550_SDI = P1^7;
sbit CS5550_CS = P1^6;
sbit CS5550_SCLK = P3^2;

void CS5550WriteByte(unsigned char message);

void CS5550WriteCmd(unsigned char cmd, unsigned long value);

unsigned char CS5550RecieveByte(void);

void CS5550WriteRes(unsigned char cmd, unsigned long value);

unsigned long CS5550ReadRes(unsigned char cmd);


#endif