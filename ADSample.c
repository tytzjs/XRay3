//ADSample.c
#define __ADSample__

#include "iodefine.h"
#include "ADSample.h"
#include "Display.h"
#include "Run.h"
#include "Buzzer.h"
#include "math.h"

#define Ch_BatteryVoltage 1

STR_SampleValue SampleValue;

/*
��ADPort��Ӧ�Ķ˿ڿ�ʼAD����
*/
static void SelectADPort( unsigned char ADPort )
{
	switch (ADPort)
	{
	case Ch_BatteryVoltage:
		ADMUX = 0x00;				//�Ҷ��룬ADC0(��ص�ѹ)
		break;
	}
	ADCSRA |= (1 << ADSC);			//��ʼADת��
}

/*
����34�κ�ȥ��������Сֵ������ADֵ,���򷵻�0xFFFF;
*/
static unsigned short ADFilter( void )
{
	static unsigned short Min = 0xFFFF;
	static unsigned short Max = 0;
	static unsigned short ADValue = 0;
	static unsigned char SampleNum = 0;
	unsigned short temp;

	if ( !(ADCSRA & (1 << ADSC)) )								//ADת�����
	{
//		temp = (unsigned short)ADCL;							//�ȶ���8λ
//		temp |= ((unsigned short)(ADCH & 0x03) << 8);			//�ٶ���2λ
		temp = ADC;
		ADValue += temp;
		
		Min = temp < Min ? temp : Min;
		Max = temp > Max ? temp : Max;
			
		SampleNum++;
		if (SampleNum >= 34)
		{
			temp = ADValue - Min - Max;
			Min = 0xFFFF;
			Max = 0;
			ADValue = 0;
			SampleNum = 0;
			return temp;
		}
		
		ADCSRA |= (1 << ADSC);			//��ʼADת��
	}
	
	return 0xFFFF;
}

static void ChargeBattery(void)
{
	if ( (XRayState == XRS_Off) && (TReset > 250) && (TXRayStop >= 5) )			//�ϵ�5������ع�5���
	{
		if ( SampleValue.BatteryVoltage < CBatteryLowestVoltage )
		{
			if ( (DispState != UI_Charge) && (DispState != UI_ClrScreen) )
			{
				DispCmd = UICmd_Charge;
			}
		}
	}
}

static void CalBatteryVolume(float voltage)
{
	unsigned char bv;

	if ( voltage < CBatteryLowVoltage )
		bv = 0;
	else if ( voltage < CBatteryMidVoltage )
		bv = 1;
	else if ( voltage < CBatteryFullVoltage )
		bv = 2;
	else
		bv = 3;

	if ( bv != SampleValue.BatteryVolume )
	{
		SampleValue.BatteryVolume = bv;
		if ( DispState == UI_Main )
			DispCmd = UICmd_Main;
	}
}

/*
�ɼ�����������ADֵ��������ֵת��Ϊ��Ӧ���¶�ֵ
*/
unsigned char ADSample(void)
{
	static unsigned char ADPort = 0;
	static unsigned char Inited = 0;
	static float batvol;
	static unsigned short advalue;

	if ( ADPort == 0 )
	{
		ADPort = 1;
		SelectADPort(ADPort);
	}
	else
	{
		advalue = ADFilter();
		if ( advalue != 0xFFFF )
		{
			switch ( ADPort )
			{
				case Ch_BatteryVoltage:
					if ( (XRayState == XRS_Off) && (TXRayStop >= 3) )			//�ع�3��������ѹ
						SampleValue.BatteryVoltage =0.8 + 5.0 * 199.9 / 49.9 *(float)advalue / 32768.0;

					ChargeBattery();

					if ( fabs(SampleValue.BatteryVoltage - batvol) > 0.1 )
					{
						batvol = SampleValue.BatteryVoltage;
						if ( DispState == UI_State )
							DispCmd = UICmd_State;
					}

					CalBatteryVolume(SampleValue.BatteryVoltage);
					Inited = 1;
				default:
					ADPort = 0;
			}
			
			ADPort++;
			if ( ADPort > 1 )
				ADPort = 1;
			SelectADPort(ADPort);
		}
	}
	
	return Inited;
}

#undef __ADSample__


