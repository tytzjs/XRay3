//Key.c
#define __Key__

#include "Iodefine.h"
#include "Buzzer.h"
#include "Run.h"
#include "Key.h"
#include "Display.h"
#include "EEPROM.h"
#include "ADSample.h"

#define CNoKey				0xFF
#define COnOffKey			0xFE
#define CExposureKey		0xFD
#define CAddKey				0xFB
#define CSubKey				0xF7
#define CMenuKey			0xFA
#define CStateKey			0xF6
#define CFactoryInit		0xF2

unsigned short TKeyAct = 0;					//按键动作后的时间 单位:秒
unsigned char TKeySame;
unsigned char TContinuePress;				//按键连续按的时间 单位:20毫秒

static void PressExposureKey(void)
{
	if ( (ExposureKey == CRemote) && !IO_RemoteInserting() )
	{
		XRayState = XRS_Off;
	}
	else if ( (PartState.MCUState == MCU_On) && (DispState == UI_Main) && BatteryResume )
	{
		XRayState = XRS_Music;

		ExposureNum++;
		BuzCmd = Buz_ExpKey;
	}
	else
		XRayState = XRS_Off;
}

static void AddTXRayRadiate(unsigned char Multiple)
{
	unsigned short time,step;
	unsigned short Max;

	if ( SensitizationMode == CFilm )
	{
		Max = 1350;
		step = 50 * Multiple;
	}
	else
	{
		Max = TMaxExposure;
		step = TExposureUnit * Multiple;
	}

	time = TXRayRadiate + step;
	if ( time <= Max )
		TXRayRadiate = time;
	else
		TXRayRadiate = Max;

	DispCmd = UICmd_Main;
}

static void FactoryInit()
{
	TXRayRadiate = 200;
	TMinExposure = 50;
	TMaxExposure = 1200;
	TExposureUnit = 50;
	SensitizationMode = CFilm;
//	UserLanguage = CChinese;
	TPowerSave = 300;
	TBackLight = 5;
	ExposureKey = CDual;
}

static void MenuItemEdit()
{
	if ( MenuItemNo == 0 )
	{
		if ( UserLanguage == CEnglish )
			UserLanguage = CChinese;
		else
			UserLanguage = CEnglish;
	}
	else if ( MenuItemNo == 1 )
	{
		if ( SensitizationMode == CFilm )
		{
			SensitizationMode = CDigitalSensor;
			TXRayRadiate = TMinExposure;
		}
		else
		{
			SensitizationMode = CFilm;
			TXRayRadiate = 200;
		}
	}
	else if ( MenuItemNo == 2 )
	{
		TPowerSave += 60;
		if ( TPowerSave > 600 )
			TPowerSave = 60;
	}
	else if ( MenuItemNo == 3 )
	{
		TBackLight++;
		if ( TBackLight > 10 )
			TBackLight = 1;
	}
	else if ( MenuItemNo == 4 )
	{
		if ( ExposureKey == CDual )
			ExposureKey = CRemote;
		else
			ExposureKey = CDual;
	}
	else if ( MenuItemNo == 5 )
	{
		TMaxExposure += 50;			//0.05S
		if ( TMaxExposure > 1200 )
			TMaxExposure = 1000;

		if ( (TXRayRadiate > TMaxExposure) && (SensitizationMode == CDigitalSensor) )
			TXRayRadiate = TMaxExposure;
	}
	else if ( MenuItemNo == 6 )
	{
		TMinExposure += 10;			//0.01S
		if ( TMinExposure > 200 )
			TMinExposure = 20;

		if ( (TXRayRadiate < TMinExposure) && (SensitizationMode == CDigitalSensor) )
			TXRayRadiate = TMinExposure;
	}
	else if ( MenuItemNo == 7 )
	{
		TExposureUnit += 10;			//0.01S
		if ( TExposureUnit > 100 )
			TExposureUnit = 10;
	}
	else
		FactoryInit();

}

static void PressAddKey()
{
	if ( DispState == UI_Main )
	{
		AddTXRayRadiate(1);
	}
	else if ( DispState == UI_Menu )
	{
		MenuItemEdit();
		DispCmd = UICmd_Menu;
	}

	BuzCmd = Buz_AddKey;
}

static void SubTXRayRadiate(unsigned char Multiple)
{
	unsigned short time,step;
	unsigned short Min;

	if ( SensitizationMode == CFilm )
	{
		Min = 200;
		step = 50 * Multiple;
	}
	else
	{
		Min = TMinExposure;
		step = TExposureUnit * Multiple;
	}

	if ( TXRayRadiate < step )
		time = Min;
	else
		time = TXRayRadiate - step;

	if ( time >= Min )
		TXRayRadiate = time;
	else
		TXRayRadiate = Min;
	
	DispCmd = UICmd_Main;
}

static void PressSubKey()
{
	if ( DispState == UI_Main )
	{
		SubTXRayRadiate(1);
	}
	else if ( DispState == UI_Menu )
	{
		MenuItemNo++;
		if ( MenuItemNo > 8 )
			MenuItemNo = 0;

		DispCmd = UICmd_Menu;
	}

	BuzCmd = Buz_SubKey;
}

static void KeyReceive(unsigned char key)
{
	if ( key != CExposureKey )
		XRayState = XRS_Off;

	switch (key)
	{
		case COnOffKey:
			break;
		case CExposureKey:
			PressExposureKey();
			break;
		case CAddKey:
			PressAddKey();
			break;
		case CSubKey:
			PressSubKey();
			break;
		case CNoKey:
			XRayState = XRS_Off;
			break;
		default:
			return;
	}

	TKeyAct = 0;				//键动作时间
}

void OffUnit()
{
	DispCmd = UICmd_ClrScreen;
	PartState.MCUState = MCU_Off;
	XRayState = XRS_Off;
}

static void OnOffUnit()
{
	if ( PartState.MCUState == MCU_On )
	{
		OffUnit();
	}
	else
	{
		if ( PartState.MCUState == MCU_Off )
		{
			TReset = 0;
			DispCmd = UICmd_Startup;
		}

		PartState.MCUState = MCU_On;
		XRayState = XRS_Off;
	}
}

static void ContinuePressOnOffKey(void)
{
	OnOffUnit();
	TContinuePress = 255;								//不再响应该按键

	if ( PartState.MCUState == MCU_On )
		BuzCmd = Buz_OnKey;
	else
		BuzCmd = Buz_OffKey;
}


static void ContinuePressAddKey(void)
{
	if ( DispState == UI_Main )
		AddTXRayRadiate(2);

	TContinuePress = 5;								//按键持续时间0.1秒
}

static void ContinuePressSubKey(void)
{
	if ( DispState == UI_Main )
		SubTXRayRadiate(2);

	TContinuePress = 5;								//按键持续时间0.1秒
}

static void ContinuePressKey(unsigned char key)
{
	if ( key != CExposureKey )
		XRayState = XRS_Off;

	switch (key)
	{
		case COnOffKey:
			ContinuePressOnOffKey();
			break;
		case CAddKey:
			ContinuePressAddKey();
			break;
		case CSubKey:
			ContinuePressSubKey();
			break;
		case CMenuKey:
			if ( DispState == UI_Menu )
				DispCmd = UICmd_Main;
			else
			{
				DispCmd = UICmd_Menu;
				XRayState = XRS_Off;
			}
			TContinuePress = 255;								//不再响应该按键

			BuzCmd = Buz_OtherKey;
			break;
		case CStateKey:
			if ( DispState == UI_State )
				DispCmd = UICmd_Main;
			else
			{
				DispCmd = UICmd_State;
				XRayState = XRS_Off;
			}
			TContinuePress = 255;								//不再响应该按键

			BuzCmd = Buz_OtherKey;
			break;
		case CFactoryInit:
			FactoryInit();
			ExposureNum = 0;

			if ( DispState == UI_State )
				DispCmd = UICmd_State;

			TContinuePress = 255;								//不再响应该按键

			BuzCmd = Buz_OtherKey;
			break;
		default:
			return;
	}

	TKeyAct = 0;				//键动作时间
}

void KeyScan(void)
{
	static unsigned char LastKey = CNoKey;
	static unsigned char KeyRelease = 1;
	static unsigned char CurKey;

	if ( TKeyAct > TPowerSave )
	{
		if ( PartState.MCUState == MCU_On )
			BuzCmd = Buz_OffKey;

		OffUnit();
		
		return;
	}
	
	CurKey = 0xF0;
	if ( !IO_OnOffKeyValue() )
		CurKey |= 0x01;
	if ( !IO_ExposureKeyValue() )
		CurKey |= 0x02;
	if ( IO_AddKeyValue() )
		CurKey |= 0x04;
	if ( IO_SubKeyValue() )
		CurKey |= 0x08;
	
	if ( CurKey == LastKey )
	{
		if ( TKeySame >= 2 )		//40ms
		{
			if ( CurKey == CNoKey )
			{
				if ( !KeyRelease )
				{
					KeyRelease = 1;
					KeyReceive(CurKey);

					if ( DispState == UI_Charge )
						DispCmd = UICmd_Main;
				}
			}
			else
			{
				if ( KeyRelease )
				{
					if ( (CurKey == CAddKey) || (CurKey == CSubKey) )
						TContinuePress = 5;					//首次按+、-键持续时间0.1秒
					else
						TContinuePress = 50;				//首次按键持续时间1秒
					KeyRelease = 0;
					KeyReceive(CurKey);
				}
				else
				{
					if ( TContinuePress == 0 )
						ContinuePressKey(CurKey);
				}
			}
		}
	}
	else
	{
		TKeySame = 0;
		LastKey = CurKey;
	}
	
}
#undef __Key__

