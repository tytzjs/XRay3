#define __GUI__

#include "GUI.h"
#include "Font38x37.h"

STR_FontLibrary *pCurFontLibrary = &FontLibrary38x37;

static unsigned short GUI_GetFontIndex(unsigned short gbkCode)
{
	unsigned short Index;

	for ( Index = 0; Index < pCurFontLibrary->Num; Index++)
	{
		if ( pgm_read_word(&(pCurFontLibrary->pGBKCode[Index])) == gbkCode )
			return Index;
	}

	return 0xFFFF;
}

static unsigned short GUI_GetFontWidth(unsigned short GBKCode)
{
	unsigned short Width;

	if ( GBKCode >= 0x81 )
		Width = pCurFontLibrary->Width;
	else
	{
		if ( GBKCode == 46 )
			Width = pCurFontLibrary->Width / 4;
		else
			Width = pCurFontLibrary->Width / 2;

		Width++;
	}

	return Width;
}

static unsigned short GUI_GetByteWidth(unsigned short DotWidth)
{
	unsigned short ByteWidth;

	ByteWidth = DotWidth / 8;
	if ( DotWidth % 8 != 0 )
		ByteWidth++;

	return ByteWidth;
}

void GUI_DrawDotArray(const prog_uchar *pDot,unsigned short StartX,unsigned short StartY,unsigned short Width,unsigned short Height,unsigned short ByteWidth,unsigned char InvertColor)
{
	unsigned short i,j;
	unsigned short CurX,CurY;
	unsigned char byte;
	const prog_uchar *pDotArray;

	for (i = 0; i < Height; i++)
	{
		CurX = StartX;
		CurY = StartY + Height - i - 1;
		pDotArray = pDot + i * ByteWidth;
		byte = pgm_read_byte(pDotArray);
		if ( InvertColor )
			byte = ~byte;
		j = 0;
		
		do
	 	{
			LCD_SetPixel(CurX++,CurY,(byte & 0x80));
			byte <<= 1;
			j++;
			if ( (j % 8) == 0 )
			{
				pDotArray++;
				byte = pgm_read_byte(pDotArray);
				if ( InvertColor )
					byte = ~byte;
			}

	 	}while (j < Width);
	}
}

static void GUI_DrawAChar(unsigned short GBKCode,unsigned short StartX,unsigned short StartY,unsigned char InvertColor)
{
	unsigned short index;
	unsigned short Height,Width,ByteWidth;
	const prog_uchar *pDotArray;

	index = GUI_GetFontIndex(GBKCode);
	if ( index == 0xFFFF )
		return;

	Height = pCurFontLibrary->Height;
	Width = GUI_GetFontWidth(GBKCode);

	ByteWidth = GUI_GetByteWidth(pCurFontLibrary->Width);

	pDotArray = pCurFontLibrary->pDotArray + ByteWidth * Height * index;

	GUI_DrawDotArray(pDotArray,StartX,StartY,Width,Height,ByteWidth,InvertColor);
}

void GUI_DrawString(char string[],unsigned short StartX,unsigned short StartY,unsigned char InvertColor)
{
	unsigned short X,Y,i = 0;
	unsigned short gbkCode;
	
	X = StartX;
	Y = StartY;
	while (string[i] != 0)
	{
		if ( (unsigned char)string[i] < 0x81 )
		{
			gbkCode = (unsigned short)string[i];
			i++;
		}
		else
		{
			gbkCode = ((unsigned short)string[i] << 8) | ((unsigned short)string[i+1]);
			i += 2;
		}
		GUI_DrawAChar(gbkCode,X,Y,InvertColor);

		X += GUI_GetFontWidth(gbkCode);
	}
}

void GUI_DrawPicture(STR_Picture *pPicture,unsigned short StartX,unsigned short StartY,unsigned char InvertColor)
{
	unsigned short ByteWidth;

	ByteWidth = pPicture->Width / 8;
	if ( pPicture->Width % 8 != 0 )
		ByteWidth++;

	GUI_DrawDotArray(pPicture->pDotArray,StartX,StartY,pPicture->Width,pPicture->Height,ByteWidth,InvertColor);
}

/****************************************************************************
* 功    能：在指定座标画直线
* 入口参数：xs     起点行座标
*           ys     起点列座标
*           xe     终点行座标
*           ye     终点列座标
*           color  线颜色
* 出口参数：无
* 说    明:
****************************************************************************/
void GUI_DrawLine(unsigned short xs, unsigned short ys, unsigned short xe, unsigned short ye,unsigned short color)
{
	unsigned short i;
	
	if ( xs == xe )					//垂直直线
	{
		if ( ys > ye )
		{
			i = ys;
			ys = ye;
			ye = i;
		}
		
		for (i = ys; i <= ye; i++)
			LCD_SetPixel(xs,i,color);
	}
	else if ( ys == ye )				//水平直线
	{
		if ( xs > xe )
		{
			i = xs;
			xs = xe;
			xe = i;
		}
		
		for (i = xs; i <= xe; i++)
			LCD_SetPixel(i,ys,color);
	}
	else							//任意直线
	{
		//直线的方程为y=ax+b
		float a,b;
		unsigned short y0,y1;
		unsigned short j;

		if ( xs > xe )				//坐标更改为起点X坐标小
		{
			j = xs;
			xs = xe;
			xe = j;

			j = ys;
			ys = ye;
			ye = j;
		}

		a = (float)(ys-ye) / (float)(xs-xe);
		b = (float)ys - a * (float)xs;

		y0 = ys;
		for ( i = xs; i <= xe; i++)
		{
			y1 = (unsigned short)(a * i + b);

			if ( y1 > y0 )
			{
				for ( j = y0; j <= y1; j++)
				{
					LCD_SetPixel(i,j,color);
				}
			}
			else
			{
				for ( j = y1; j <= y0; j++)
				{
					LCD_SetPixel(i,j,color);
				}
			}
			
			y0 = y1;
		}
	}
}

/****************************************************************************
* 功    能：在指定座标画矩形
* 入口参数：pRect 矩形坐标结构指针
*           color  线颜色
* 出口参数：无
* 说    明:
****************************************************************************/
void GUI_DrawRectangle(STR_Rectangle *pRect,unsigned short color)
{
	GUI_DrawLine(pRect->StartPoint.X,
				  pRect->StartPoint.Y,
				  pRect->StartPoint.X,
				  pRect->EndPoint.Y,color);
				  
	GUI_DrawLine(pRect->StartPoint.X,
				  pRect->StartPoint.Y,
				  pRect->EndPoint.X,
				  pRect->StartPoint.Y,color);

	GUI_DrawLine(pRect->EndPoint.X,
				  pRect->EndPoint.Y,
				  pRect->EndPoint.X,
				  pRect->StartPoint.Y,color);

	GUI_DrawLine(pRect->EndPoint.X,
				  pRect->EndPoint.Y,
				  pRect->StartPoint.X,
				  pRect->EndPoint.Y,color);
}

/****************************************************************************
* 功    能：在指定座标填充矩形
* 入口参数：pRect 矩形坐标结构指针
*           color  线颜色
* 出口参数：无
* 说    明:
****************************************************************************/
void GUI_FillRectangle(STR_Rectangle *pRect,unsigned short color)
{
	unsigned short x;
	unsigned short MinX,MaxX;

	if ( pRect->StartPoint.X < pRect->EndPoint.X )
	{
		MinX = pRect->StartPoint.X;
		MaxX = pRect->EndPoint.X;
	}
	else
	{
		MinX = pRect->EndPoint.X;
		MaxX = pRect->StartPoint.X;
	}

	for ( x = MinX; x <= MaxX; x++)
	{
		GUI_DrawLine(x,pRect->StartPoint.Y,x,pRect->EndPoint.Y,color);
	}
}

void GUI_Refresh()
{
	if ( !LCD_IsRefreshed() )
		LCD_Refresh();
}

void GUI_Init()
{
	LCD_Init();
}

#undef __GUI__
