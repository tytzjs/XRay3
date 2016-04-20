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
对ADPort对应的端口开始AD采样
*/
static void SelectADPort( unsigned char ADPort )
{
	switch (ADPort)
	{
	case Ch_BatteryVoltage:
		ADMUX = 0x00;				//右对齐，ADC0(电池电压)
		break;
	}
	ADCSRA |= (1 << ADSC);			//开始AD转换
}

/*
采样34次后去除最大和最小值，返回AD值,否则返回0xFFFF;
*/
static unsigned short ADFilter( void )
{
	static unsigned short Min = 0xFFFF;
	static unsigned short Max = 0;
	static unsigned short ADValue = 0;
	static unsigned char SampleNum = 0;
	unsigned short temp;

	if ( !(ADCSRA & (1 << ADSC)) )								//AD转换完成
	{
//		temp = (unsigned short)ADCL;							//先读低8位
//		temp |= ((unsigned short)(ADCH & 0x03) << 8);			//再读高2位
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
		
		ADCSRA |= (1 << ADSC);			//开始AD转换
	}
	
	return 0xFFFF;
}

static void ChargeBattery(void)
{
	if ( (XRayState == XRS_Off) && (TReset > 250) && (TXRayStop >= 5) )			//上电5秒后且曝光5秒后
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
采集各传感器的AD值，并将该值转换为相应的温度值
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
					if ( (XRayState == XRS_Off) && (TXRayStop >= 3) )			//曝光3秒后采样电压
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


