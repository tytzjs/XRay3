#ifndef __Display_H__
#define __Display_H__

typedef enum
{
	UICmd_Startup = 0,
	UICmd_Main = 1,
	UICmd_Menu = 2,
	UICmd_State = 3,
	UICmd_ClrScreen = 4,
	UICmd_Charge = 5,
	UICmd_None = 6
}Enum_DisplayCmd;

typedef enum
{
	UI_Startup = 0,
	UI_Main = 1,
	UI_Menu = 2,
	UI_State = 3,
	UI_ClrScreen = 4,
	UI_Charge = 5
}Enum_DisplayState;


#endif

#ifndef __Display__
	extern unsigned char MenuItemNo;
	extern unsigned char TDisplayRefresh;
	extern unsigned char TChargeUI;
	extern Enum_DisplayState DispState;
	extern Enum_DisplayCmd DispCmd;

	extern void DisplayInit();
	extern void Display();
#endif
