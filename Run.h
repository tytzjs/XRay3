#ifndef __Run_H__
#define __Run_H__

#define MCU_Reset 0
#define MCU_On 1
#define MCU_Off 2

typedef struct
{
	unsigned char MCUState;
	unsigned char PWMPower:1;
	unsigned char KVPWM:1;
	unsigned char FilamentPWM:1;
	unsigned char ExposureLED:1;
	unsigned char LED3:1;
	unsigned char LED4:1;
	unsigned char LED5:1;
	unsigned char LCDBackLight:1;
}STR_PartState;

typedef enum
{
	XRS_Off = (unsigned char)0,
	XRS_Music = (unsigned char)1,
	XRS_FilamentOn = (unsigned char)2,
	XRS_KVOn = (unsigned char)3
}Enum_XRayState;

#endif

#ifndef __Run__
	extern unsigned short TReset;
	extern unsigned short TXRayWork,TXRayStop;
	extern unsigned char BatteryResume;

	extern Enum_XRayState XRayState;
	extern STR_PartState PartState;

	extern void Int_XRayWork(void);
	extern void Run(void);
#endif

