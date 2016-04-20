#ifndef __GUI_H__
#define __GUI_H__

#include  <avr/pgmspace.h>
#include "LCDrive.h"

typedef struct
{
	unsigned short X,Y;
}STR_Point;

typedef struct
{
	STR_Point StartPoint,EndPoint;
}STR_Rectangle;

typedef struct
{
	const prog_uchar *pDotArray;
	const prog_uint16_t *pGBKCode;
	unsigned short Width,Height;
	unsigned short Num;				//字库共有多少字
}STR_FontLibrary;

typedef struct
{
	const prog_uchar *pDotArray;
	unsigned short Width,Height;
}STR_Picture;


#endif

#ifndef __GUI__
	extern STR_FontLibrary *pCurFontLibrary;

	extern void GUI_Init();
	extern void GUI_Refresh();
	extern void GUI_DrawString(char string[],unsigned short StartX,unsigned short StartY,unsigned char InvertColor);
	extern void GUI_DrawPicture(STR_Picture *pPicture,unsigned short StartX,unsigned short StartY,unsigned char InvertColor);
	extern void GUI_DrawLine(unsigned short xs, unsigned short ys, unsigned short xe, unsigned short ye,unsigned short color);
	extern void GUI_DrawRectangle(STR_Rectangle *pRect,unsigned short color);

#endif
