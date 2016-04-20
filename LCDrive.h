#ifndef __LCDrive_H__
#define __LCDrive_H__

#include "LCDrive.h"

#endif

#ifndef __LCDrive__
	extern void LCD_Init();
	extern void LCD_SetPixel(unsigned short x,unsigned short y,unsigned char Color);
	extern unsigned char LCD_IsRefreshed();
	extern void LCD_Refresh();
	extern void LCD_ClrScreen();
	extern void LCD_SetScreen();
#endif
