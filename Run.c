#define __Run__

#include "iodefine.h"
#include "Run.h"
#include "Buzzer.h"
#include "Display.h"
#include "EEPROM.h"
#include "Key.h"
#include "ADSample.h"

static unsigned short TFilamentHeating = 300;	//��λ:mS

unsigned short TReset;							//��λ��20mS
unsigned short TXRayWork;						//��λ:mS
unsigned short TXRayStop = 1000;				//�ع��Ļָ�ʱ�� ��λ:��
unsigned char BatteryResume = 0;				//��ػָ����

Enum_XRayState XRayState = XRS_Off;
STR_PartState PartState = {0,1,0,0,0,0,0,0,1};

//ÿ1ms����һ��
void Int_XRayWork(void)
{
	if ( TXRayWork < 2000 )
		TXRayWork++;
	else
	{
		if ( PartState.PWMPower || PartState.FilamentPWM || PartState.KVPWM )
			XRayState = 255;
	}


	switch (XRayState)
	{
	case XRS_Music:
		TXRayStop = 0;
		TXRayWork = 0;

		if ( (BuzCmd == Buz_None) && (Buzzing == Buz_None) )
			XRayState = XRS_FilamentOn;
		
		PartState.PWMPower = 0;
		PartState.FilamentPWM = 0;
		PartState.KVPWM = 0;
		break;
	case XRS_FilamentOn:
		TXRayStop = 0;

		if ( TXRayWork < TFilamentHeating )
		{
			PartState.PWMPower = 1;
			PartState.FilamentPWM = 1;
			PartState.KVPWM = 0;
		}
		else
		{
			XRayState = XRS_KVOn;
		}
		break;
	case XRS_KVOn:
		TXRayStop = 0;

		if ( TXRayWork < (TFilamentHeating + TXRayRadiate + 38) )
		{
			if ( !PartState.KVPWM )
				DispCmd = UICmd_Main;

			PartState.PWMPower = 1;
			PartState.FilamentPWM = 1;
			PartState.KVPWM = 1;
		}
		else
		{
			XRayState = XRS_Off;
			DispCmd = UICmd_Main;
		}
		break;
	default:
		TXRayWork = 0;
		PartState.PWMPower = 0;
		PartState.FilamentPWM = 0;
		PartState.KVPWM = 0;
		break;
	}

	if ( PartState.PWMPower )
		IO_PWMPower_On();
	else
		IO_PWMPower_Off();
	
	if ( PartState.FilamentPWM )
		IO_FilamentPWM_On();
	else
		IO_FilamentPWM_Off();
		
	if ( PartState.KVPWM )
		IO_KVPWM_On();
	else
		IO_KVPWM_Off();
}

void BatteryRest(void)
{
	if ( TXRayStop >= 5 )
	{
		if ( !BatteryResume )
		{
			BatteryResume = 1;
			if ( DispState == UI_Main )
				DispCmd = UICmd_Main;
		}
	}
	else if ( XRayState == XRS_Off )
	{
		if ( BatteryResume )
		{
			BatteryResume = 0;
			if ( DispState == UI_Main )
				DispCmd = UICmd_Main;
		}
	}
}

void PartDrive(void)
{
	if ( PartState.MCUState == MCU_On )
		IO_UnitPower_On();
	else
		IO_UnitPower_Off();

	if ( PartState.MCUState == MCU_Reset )
		IO_MCUPower_Off();
	else if ( PartState.MCUState == MCU_On )
		IO_MCUPower_On();
	else
	{
		if ( (BuzCmd == Buz_None) && (Buzzing == Buz_None) )
			IO_MCUPower_Off();
	}

	if ( PartState.ExposureLED)
		IO_ExposureLED_On();
	else
		IO_ExposureLED_Off();
		
	if ( PartState.LED3)
		IO_LED3_On();
	else
		IO_LED3_Off();
		
	if ( PartState.LED4)
		IO_LED4_On();
	else
		IO_LED4_Off();
		
	if ( PartState.LED5)
		IO_LED5_On();
	else
		IO_LED5_Off();
		
	if ( PartState.LCDBackLight )
		IO_LCD_BackLight_On();
	else
		IO_LCD_BackLight_Off();
		
}

void LEDWork(void)
{
	if ( XRayState > XRS_Music )
		PartState.ExposureLED = 1;
	else
		PartState.ExposureLED = 0;
	
	if ( PartState.MCUState == MCU_Off )
		PartState.LCDBackLight = 0;
	else if ( TKeyAct < TBackLight )
		PartState.LCDBackLight = 1;
	else
		PartState.LCDBackLight = 0;

	if ( (TReset < 250) || ((XRayState == XRS_Off) && (TXRayStop < 5)) || (XRayState > XRS_Music) || (PartState.MCUState == MCU_Off) || (SampleValue.BatteryVoltage > CBatteryLowVoltage) )
	{
		PartState.LED3 = 0;
		PartState.LED4 = 0;
		PartState.LED5 = 0;
	}
	else if ( SampleValue.BatteryVoltage < (CBatteryLowVoltage - 0.1) )
	{
		PartState.LED3 = 1;
		PartState.LED4 = 1;
		PartState.LED5 = 1;
	}
}

void Run(void)
{
	LEDWork();
	BatteryRest();
	PartDrive();
}

#undef	__Run__

