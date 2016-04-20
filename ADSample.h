#ifndef __ADSample_H__
#define __ADSample_H__

typedef struct
{
	float BatteryVoltage;
	unsigned char BatteryVolume;
}STR_SampleValue;

#define CBatteryLowestVoltage 14.0
#define CBatteryLowVoltage 14.3
#define CBatteryMidVoltage 14.9
#define CBatteryFullVoltage 15.4

#endif

#ifndef __ADSample__
	extern STR_SampleValue SampleValue;

	extern unsigned char ADSample(void);
#endif

