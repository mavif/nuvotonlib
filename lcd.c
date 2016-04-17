#include "NUC1xx.h"
#include "lcd.h"

extern char Ascii[];

void lcd(void)
{
	SYSCLK->APBCLK.SPI3_EN = 1;
	SYS->IPRSTC2.SPI3_RST = 1;
	SYS->IPRSTC2.SPI3_RST = 0;
	SYS->GPDMFP.SPI3_SS0 = 1;
	SYS->GPDMFP.SPI3_CLK = 1;
	SYS->GPDMFP.SPI3_MOSI0 = 1;
	SPI3->CNTRL.CLKP = 1;
	SPI3->CNTRL.TX_BIT_LEN = 9;
	SPI3->CNTRL.TX_NEG = 1;
	SPI3->DIVIDER.DIVIDER = 0x03;

	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0xEB;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;

	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0x81;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->TX[0] = 0xA0;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;

	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0xC0;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;

	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0xAF;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;
}

void backlight(void)
{
	GPIOD->DOUT &= ~(1<<14);
}

void writelcd(unsigned char data)
{
	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0x100 | data;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;
}

void setpaca(unsigned char pa, unsigned char ca)
{
	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0xB0 | pa;
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;

	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0x10 | ((ca>>4)&0xF);
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;

	SPI3->SSR.SSR = 1;
	SPI3->TX[0] = 0x00 | (ca & 0xF);
	SPI3->CNTRL.GO_BUSY = 1;
	while(SPI3->CNTRL.GO_BUSY == 1);
	SPI3->SSR.SSR = 0;
}

void word(unsigned char x, unsigned char y, unsigned char asciiword)
{
	int i = 0, k = 0;
	unsigned char temp;
	k = (asciiword - 32) * 16;
	for(i=0; i<8; i++)
	{
		setpaca((x*2), (129-(y*8)-i));
		temp = Ascii[k+i];
		writelcd(temp);
	}
	for(i=0; i<8; i++)
	{
		setpaca((x*2)+1, (129-(y*8)-i));
		temp = Ascii[k+i+8];
		writelcd(temp);
	}
}

void text(unsigned char line, char *str)
{
	int i = 0;
	do {
		word(line, i, *str++);
		i++;
		if(i>15)
			break;
	} while(*str!='\0');
}

void clear(void)
{
	int i = 0;
	setpaca(0x00, 0x00);
	for(i=0; i<(132*8); i++)
	{
		writelcd(0x00);
	}
	writelcd(0x0F);
}
