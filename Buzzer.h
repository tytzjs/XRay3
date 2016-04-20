#ifndef __Buzzer_H__
#define __Buzzer_H__

typedef enum
{
	Buz_OnKey = 0,
	Buz_OffKey = 1,
	Buz_AddKey = 2,
	Buz_SubKey = 3,
	Buz_ExpKey = 4,
	Buz_OtherKey = 5,
	Buz_None = 6
}Enum_BuzCmd;

#endif

#ifndef __Buzzer__
	extern Enum_BuzCmd BuzCmd;
	extern Enum_BuzCmd Buzzing;

	extern void Int_Buzzer(void);
#endif

