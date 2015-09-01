#include "NUC1xx.h"
#include "gpio.h"
#define P_OFFSET 0x40
void delay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  = (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
    while((SysTick->CTRL & (1 << 16)) == 0);
}
int32_t setpin(Ports p, uint8_t n, IO_ m)
{
	volatile uint32_t val;
	val=(uint32_t)&GPIOA->PMD + (p*P_OFFSET);
	if((m==IO_IN)||(m==IO_OUT)||(m==IO_DRAIN))
	{
		outpw(val, inpw(val) & ~(0x3<<(n*2)));
		if(m==IO_OUT)
		{
			outpw(val, inpw(val) | (0x1<<(n*2)));
		} 
		else if(m==IO_DRAIN)
		{
			outpw(val, inpw(val) | (0x2<<(n*2)));
		}
	}
	else if(m==IO_QUASI)
	{
		outpw(val, inpw(val) | (0x3<<(n*2)));
	}
	return 0;
}
int32_t clrpin(Ports p, uint8_t n)
{
	volatile uint32_t val;
	val = (uint32_t)&GPIOA->PMD + (p*P_OFFSET);    
	outpw(val, inpw(val) | (0x3<<(n*2)));
	GPIO_DBNCECON->DBNCECON.ICLK_ON = 0; 
	return 0;
}
int32_t setbit(Ports p, uint8_t n)
{
	GPIO_T * tGPIO;
	tGPIO=(GPIO_T *)((uint32_t)GPIOA + (p*P_OFFSET));  
	tGPIO->DOUT|=(1<<n);
	return 0;
}
int32_t clrbit(Ports p, uint8_t n)
{
	GPIO_T * tGPIO;
	tGPIO=(GPIO_T *)((uint32_t)GPIOA + (p*P_OFFSET));  
	tGPIO->DOUT &=~(1<<n);
	return 0;  
}
int32_t getbit(Ports p, uint8_t n)
{
	volatile uint32_t val;
	val=(uint32_t)&GPIOA->PIN + (p*P_OFFSET);
	return ((inpw(val)>>n) & 0x1);
}
