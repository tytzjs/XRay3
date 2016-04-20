#define __LCDrive__

#include "IODefine.h"

static unsigned char LCDRefreshed = 0;
static unsigned char DisplayRAM[8][132];

static void UC1601Write(unsigned char CD,unsigned char data)
{
	if ( CD )
		IO_LCD_CD_Set();
	else
		IO_LCD_CD_Clr();

	IO_LCD_RD_Set();
	IO_LCD_WR_Clr();
	DDRC = 0xFF;

	PORTC = data;

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	IO_LCD_WR_Set();

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
}

static unsigned char UC1601Read(unsigned char CD)
{
	unsigned char data;

	if ( CD )
		IO_LCD_CD_Set();
	else
		IO_LCD_CD_Clr();

	IO_LCD_WR_Set();
	IO_LCD_RD_Clr();
	PORTC = 0x00;
	DDRC = 0x00;

	IO_LCD_RD_Set();

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	data = PINC;

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	return data;
}

//设置像素值  原点在LCD的左下角
void LCD_SetPixel(unsigned short x,unsigned short y,unsigned short Color)
{
	unsigned short PageAddress;
	unsigned char BitAddress;

	LCDRefreshed = 0;

	PageAddress = y / 8;
	BitAddress = y % 8;

	if ( (x > 131) || (PageAddress > 64) )				//超出显示RAM范围
		return;
	
	if ( Color )
		DisplayRAM[PageAddress][x] |= (1 << BitAddress);
	else
		DisplayRAM[PageAddress][x] &= ~(1 << BitAddress);
}

void LCD_Refresh()
{
	unsigned char i,j;

	IO_LCD_CS_Clr();

	UC1601Write(0,0x00);		//Set Column Address LSB = 0
	UC1601Write(0,0x10);		//Set Column Address MSB = 0
	UC1601Write(0,0xB0);		//Set Page Address = 0

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 132; j++)
		{
			UC1601Write(1,DisplayRAM[i][j]);
		}
	}

	IO_LCD_CS_Set();

	LCDRefreshed = 1;
}

unsigned char LCD_IsRefreshed()
{
	return LCDRefreshed;
}

void LCD_SetScreen()
{
	unsigned char i,j;

	LCDRefreshed = 0;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 132; j++)
		{
			DisplayRAM[i][j] = 0xFF;
		}
	}
}

void LCD_ClrScreen()
{
	unsigned char i,j;

	LCDRefreshed = 0;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 132; j++)
		{
			DisplayRAM[i][j] = 0x00;
		}
	}
}

void LCD_Init()
{
	IO_LCD_CS_Clr();

	UC1601Write(0,0xE2);		//System Reset
	UC1601Write(0,0x2F);		//Set Power Control :Internal VLCD >15nF
	UC1601Write(0,0x27);		//温度补偿 11：-0.00%/℃
	UC1601Write(0,0xC0);		//LCD Maping Control MX=0，MY=0 
	UC1601Write(0,0xA0);		//Set Frame Rate = 80fps
	UC1601Write(0,0xEB);		//Set LCD Bias Ratio 1/9
	UC1601Write(0,0x81);		//Set VBIAS Potentiometer
	UC1601Write(0,161);			//VLCD = 10.2V
	UC1601Write(0,0x89);		//Set RAM Address Control 页、列地址自动增1，先增加列地址，在增加页地址

	UC1601Write(0,0xF1);		//Set COM END 
	UC1601Write(0,63);			//COM END = 63

	UC1601Write(0,0xAF);		//使能显示

	IO_LCD_CS_Set();

	LCD_ClrScreen();
}


#undef __LCDrive__
