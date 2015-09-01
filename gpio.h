#ifndef _gpio_h_
#define _gpio_h_
#include "NUC1xx.h"
typedef enum
{
	PA=0,
	PB=1,
	PC=2,
	PD=3,
	PE=4
} Ports;
typedef enum 
{
    IO_IN=0,
    IO_OUT,
    IO_DRAIN,
    IO_QUASI
} IO_;
void delay(uint32_t us);
int32_t setpin(Ports p, uint8_t n, IO_ m);
int32_t clrpin(Ports p, uint8_t n);
int32_t setbit(Ports p, uint8_t n);
int32_t clrbit(Ports p, uint8_t n);
int32_t getbit(Ports p, uint8_t n);
#endif
