#define __Display__

#include "GUI.h"
#include "stdio.h"
#include "string.h"
#include "Run.h"
#include "Picture.h"
#include "ADSample.h"
#include "Display.h"
#include "EEPROM.h"
#include "Language.h"
#include "Key.h"
#include "Buzzer.h"
#include "iodefine.h"

#include "Font38x37.h"
#include "FontB14x13.h"
#include "Font12x12.h"

unsigned char MenuItemNo = 0;
unsigned char TDisplayRefresh;
unsigned char TChargeUI;

Enum_DisplayState DispState = UI_Startup;
Enum_DisplayCmd DispCmd = UICmd_Startup;

static void ToothDisplay(unsigned short min,unsigned short max)
{
	unsigned short step;

	step = (unsigned short)((float)(max - min) / 23.0);

	if ( TXRayRadiate <= min )
	{
		GUI_DrawPicture(&Tooth1,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step) )
	{
		GUI_DrawPicture(&Tooth1,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 2) )
	{
		GUI_DrawPicture(&Tooth1,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 3) )
	{
		GUI_DrawPicture(&Tooth2,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 4) )
	{
		GUI_DrawPicture(&Tooth2,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 5) )
	{
		GUI_DrawPicture(&Tooth2,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 6) )
	{
		GUI_DrawPicture(&Tooth3,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 7) )
	{
		GUI_DrawPicture(&Tooth3,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 8) )
	{
		GUI_DrawPicture(&Tooth3,19,0,0);
		GUI_DrawPicture(&Tooth1,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 9) )
	{
		GUI_DrawPicture(&Tooth4,19,0,0);
		GUI_DrawPicture(&Tooth2,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 10) )
	{
		GUI_DrawPicture(&Tooth4,19,0,0);
		GUI_DrawPicture(&Tooth2,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 11) )
	{
		GUI_DrawPicture(&Tooth4,19,0,0);
		GUI_DrawPicture(&Tooth2,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 12) )
	{
		GUI_DrawPicture(&Tooth5,19,0,0);
		GUI_DrawPicture(&Tooth3,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 13) )
	{
		GUI_DrawPicture(&Tooth5,19,0,0);
		GUI_DrawPicture(&Tooth3,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 14) )
	{
		GUI_DrawPicture(&Tooth5,19,0,0);
		GUI_DrawPicture(&Tooth3,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 15) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth4,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 16) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth4,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 17) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth4,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 18) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth5,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 19) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth5,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 20) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth5,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 21) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth6,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step1,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else if ( TXRayRadiate <= (min + step * 22) )
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth6,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step2,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
	else
	{
		GUI_DrawPicture(&Tooth6,19,0,0);
		GUI_DrawPicture(&Tooth6,19,32,0);
		if ( SensitizationMode == CFilm )
			GUI_DrawPicture(&Step3,57,0,0);
		else
			GUI_DrawPicture(&Step3,57,0,0);
	}
}

static void DispSensitizationMode()
{
	if ( SensitizationMode == CDigitalSensor )
	{
		pCurFontLibrary = &FontLibraryB14x13;

		GUI_DrawString("D",121,40,1);
		GUI_DrawLine(120,40,120,52,1);
		GUI_DrawLine(128,40,128,52,1);

		ToothDisplay(TMinExposure,TMaxExposure);
	}
	else
		ToothDisplay(200,1350);
}

static void DispBatteryVolume(unsigned char BatteryVolume)
{
	STR_Picture *pPicture;

	switch (BatteryVolume)
	{
	case 0:
		pPicture = &BatteryNone;
		break;
	case 1:
		pPicture = &BatteryLow;
		break;
	case 2:
		pPicture = &BatteryMid;
		break;
	case 3:
		pPicture = &BatteryHigh;
		break;
	default:
		break;
	}

	GUI_DrawPicture(pPicture,117,56,0);
}

//显示主界面
static void DispMainUI()
{
	char s[20];

	DispState = UI_Main;
	DispCmd = UICmd_None;

	LCD_ClrScreen();

	GUI_DrawPicture(&Adult,2,32,0);
	GUI_DrawPicture(&Children,4,3,0);

	pCurFontLibrary = &FontLibrary38x37;
	sprintf(s,"%3.2f",(double)TXRayRadiate / 1000.0);
	GUI_DrawString(s,50,11,0);

	if ( BatteryResume )
	{
		GUI_DrawPicture(&RightArrow,52,53,0);

		if ( UserLanguage == CEnglish )
			pCurFontLibrary = &FontLibrary12x12;
		else
			pCurFontLibrary = &FontLibraryB14x13;

		if ( PartState.KVPWM )
			GUI_DrawString(GetString(pLanguage->pExposure),57,50,0);
		else
			GUI_DrawString(GetString(pLanguage->pReady),57,50,0);
	}

	pCurFontLibrary = &FontLibraryB14x13;
	GUI_DrawString("S",122,17,0);
	
	DispSensitizationMode();
	DispBatteryVolume(SampleValue.BatteryVolume);
}

//启动界面显示
static void DispStartupUI()
{
	DispState = UI_Startup;
	DispCmd = UICmd_None;

	LCD_ClrScreen();

	pCurFontLibrary = &FontLibrary38x37;
	GUI_DrawString("Resun",15,10,0);

	GUI_DrawPicture(&TradeMark,100,35,0);
}

//显示菜单界面
static void DispMenuUI()
{
	char s[30],s1[30];

	DispState = UI_Menu;
	DispCmd = UICmd_None;

	LCD_ClrScreen();

	pCurFontLibrary = &FontLibrary12x12;
	
	GUI_DrawString(GetString(pLanguage->pMenu),20,52,0);
	GUI_DrawString(GetString(pLanguage->pChange),70,52,0);

	if ( UserLanguage == CEnglish )
	{
		GUI_DrawPicture(&DownArrow,54,56,0);
		GUI_DrawPicture(&UpArrow,118,56,0);
	}
	else
	{
		GUI_DrawPicture(&DownArrow,51,56,0);
		GUI_DrawPicture(&UpArrow,101,56,0);
	}

	GUI_DrawLine(2,51,130,51,1);

	if ( MenuItemNo <= 3 )
	{
		strcpy(s,GetString(pLanguage->pUserLanguage));
		GUI_DrawString(s,5,38,MenuItemNo == 0 ? 1:0);

		strcpy(s,GetString(pLanguage->pMode));
		strcat(s,SensitizationMode == CFilm ? GetString(pLanguage->pFilm) : GetString(pLanguage->pDigital) );
		GUI_DrawString(s,5,25,MenuItemNo == 1 ? 1:0);

		strcpy(s,GetString(pLanguage->pPowerSave));
		sprintf(s1,"%d%s",TPowerSave / 60,GetString(pLanguage->pMinute));
		strcat(s,s1);
		GUI_DrawString(s,5,12,MenuItemNo == 2 ? 1:0);

		strcpy(s,GetString(pLanguage->pBackLight));
		sprintf(s1,"%d%s",TBackLight,GetString(pLanguage->pSecond));
		strcat(s,s1);
		GUI_DrawString(s,5,0,MenuItemNo == 3 ? 1:0);
	}
	else if ( MenuItemNo <= 7 )
	{
		strcpy(s,GetString(pLanguage->pExposureKeySet));
		strcat(s,ExposureKey == CDual ? GetString(pLanguage->pDual) : GetString(pLanguage->pRemote) );
		GUI_DrawString(s,5,38,MenuItemNo == 4 ? 1:0);

		strcpy(s,GetString(pLanguage->pMaxExpTime));
		sprintf(s1,"%3.2f%s",(float)TMaxExposure / 1000.0,GetString(pLanguage->pSecond));
		strcat(s,s1);
		GUI_DrawString(s,5,25,MenuItemNo == 5 ? 1:0);

		strcpy(s,GetString(pLanguage->pMinExpTime));
		sprintf(s1,"%3.2f%s",(float)TMinExposure / 1000.0,GetString(pLanguage->pSecond));
		strcat(s,s1);
		GUI_DrawString(s,5,12,MenuItemNo == 6 ? 1:0);

		strcpy(s,GetString(pLanguage->pExpUnitTime));
		sprintf(s1,"%3.2f%s",(float)TExposureUnit / 1000.0,GetString(pLanguage->pSecond));
		strcat(s,s1);
		GUI_DrawString(s,5,0,MenuItemNo == 7 ? 1:0);
	}
	else
	{
		strcpy(s,GetString(pLanguage->pFactoryInit));
		GUI_DrawString(s,5,38,MenuItemNo == 8 ? 1:0);
	}
}

static void DispStateUI()
{
	char s[30],s1[30];

	DispState = UI_State;
	DispCmd = UICmd_None;

	LCD_ClrScreen();

	pCurFontLibrary = &FontLibrary12x12;

	strcpy(s,GetString(pLanguage->pBattery));
	sprintf(s1,"% 4.1fV",(double)SampleValue.BatteryVoltage);
	strcat(s,s1);
	GUI_DrawString(s,20,45,0);

	strcpy(s,GetString(pLanguage->pVer));
	strcat(s,"1.0 ");
	strcat(s,GetString(pLanguage->pDate));
	GUI_DrawString(s,20,32,0);

	strcpy(s,GetString(pLanguage->pExposureNum));
	sprintf(s1,"%u",ExposureNum);
	strcat(s,s1);
	GUI_DrawString(s,20,19,0);

	strcpy(s,GetString(pLanguage->pModel));
	strcat(s,"D-045");
	GUI_DrawString(s,20,6,0);
	
}

static void DispChargeUI()
{
	char s[30];

	DispState = UI_Charge;
	DispCmd = UICmd_None;

	LCD_ClrScreen();

	GUI_DrawPicture(&Caution,48,27,0);

	pCurFontLibrary = &FontLibraryB14x13;

	strcpy(s,GetString(pLanguage->pCharge));

	if ( UserLanguage == CEnglish )
		GUI_DrawString(s,12,10,0);
	else
		GUI_DrawString(s,42,10,0);

	TChargeUI = 0;
}

static void ClrScreen()
{
	DispState = UI_ClrScreen;
	DispCmd = UICmd_None;

	LCD_ClrScreen();
}

void Display()
{
	if ( UserLanguage == CEnglish )
		pLanguage = &English;
	else
		pLanguage = &Chinese;
	
	switch (DispCmd)
	{
	case UICmd_Startup:
		DispStartupUI();
		break;
	case UICmd_Main:
		DispMainUI();
		break;
	case UICmd_Menu:
		DispMenuUI();
		break;
	case UICmd_State:
		DispStateUI();
		break;
	case UICmd_ClrScreen:
		ClrScreen();
		break;
	case UICmd_Charge:
		DispChargeUI();
		break;
	default:
		break;
	}

	if ( DispState == UI_Charge )
	{
		if ( (TChargeUI > 5) || (SampleValue.BatteryVoltage < (CBatteryLowestVoltage-1)) )		//提示充电后5秒，或电池电压低于13V时自动关机
		{
			if ( PartState.MCUState == MCU_On )
				BuzCmd = Buz_OffKey;

			OffUnit();
		}
	}
	else if ( (TReset > 75) && (DispState == UI_Startup) )
		DispCmd = UICmd_Main;

	GUI_Refresh();
}

#undef __Display__
