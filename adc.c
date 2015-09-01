#include <inttypes.h>
#include "NUC1xx.h"
#include "adc.h"

void setadc(void)
{
	GPIOA->PMD.PMD0 = 0;
	GPIOA->PMD.PMD1 = 0;
	GPIOA->PMD.PMD2 = 0;
	GPIOA->PMD.PMD3 = 0;
	GPIOA->OFFD = 1;
	SYS->GPAMFP.ADC0 = 1;
	SYS->GPAMFP.ADC1_AD12 = 1;
	SYS->GPAMFP.ADC2_AD11 = 1;
	SYS->GPAMFP.ADC3_AD10 = 1;
	SYS->GPAMFP.ADC7_SS21_AD6 = 1;
	SYS->IPRSTC2.ADC_RST = 1;
	SYS->IPRSTC2.ADC_RST = 0;
	SYSCLK->CLKSEL1.ADC_S = 2;
	SYSCLK->CLKDIV.ADC_N = 1;
	SYSCLK->APBCLK.ADC_EN = 1;
	ADC->ADCR.ADEN = 1;
	ADC->ADCR.DIFFEN = 0;
	ADC->ADCR.ADMD = 3;
	ADC->ADCHER.CHEN = 0xFF;
	ADC->ADSR.ADF = 1;
	ADC->ADCR.ADIE = 1;
	ADC->ADCR.ADST = 1;
}
uint16_t getadc(uint8_t channel)
{
	while(ADC->ADSR.ADF==0);
	ADC->ADSR.ADF = 1;
	return ADC->ADDR[channel].RSLT;
	ADC->ADCR.ADST = 1;
}
