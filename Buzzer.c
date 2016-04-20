#define __Buzzer__

#include  <avr/pgmspace.h>
#include "iodefine.h"
#include "Buzzer.h"
#include "Run.h"

#define L_do ((unsigned short)((float)F_CPU / (2.0 * 261.625565300599) + 0.5) -1)
#define L_re ((unsigned short)((float)F_CPU / (2.0 * 293.664767917407) + 0.5) -1)
#define L_mi ((unsigned short)((float)F_CPU / (2.0 * 329.62755691287) + 0.5) -1)
#define L_fa ((unsigned short)((float)F_CPU / (2.0 * 349.228231433004) + 0.5) -1)
#define L_so ((unsigned short)((float)F_CPU / (2.0 * 391.995435981749) + 0.5) -1)
#define L_la ((unsigned short)((float)F_CPU / (2.0 * 440.0) + 0.5) -1)
#define L_si ((unsigned short)((float)F_CPU / (2.0 * 493.883301256124) + 0.5) -1)

#define M_do ((unsigned short)((float)F_CPU / (2.0 * 523.251130601197) + 0.5) -1)
#define M_re ((unsigned short)((float)F_CPU / (2.0 * 587.329535834815) + 0.5) -1)
#define M_mi ((unsigned short)((float)F_CPU / (2.0 * 659.25511382574) + 0.5) -1)
#define M_fa ((unsigned short)((float)F_CPU / (2.0 * 698.456462866008) + 0.5) -1)
#define M_so ((unsigned short)((float)F_CPU / (2.0 * 783.990871963499) + 0.5) -1)
#define M_la ((unsigned short)((float)F_CPU / (2.0 * 880.0) + 0.5) -1)
#define M_si ((unsigned short)((float)F_CPU / (2.0 * 987.766602512249) + 0.5) -1)

#define H_do ((unsigned short)((float)F_CPU / (2.0 * 1046.50226120239) + 0.5) -1)
#define H_re ((unsigned short)((float)F_CPU / (2.0 * 1174.65907166963) + 0.5) -1)
#define H_mi ((unsigned short)((float)F_CPU / (2.0 * 1318.51022765148) + 0.5) -1)
#define H_fa ((unsigned short)((float)F_CPU / (2.0 * 1396.91292573202) + 0.5) -1)
#define H_so ((unsigned short)((float)F_CPU / (2.0 * 1567.981743927) + 0.5) -1)
#define H_la ((unsigned short)((float)F_CPU / (2.0 * 1760.0) + 0.5) -1)
#define H_si ((unsigned short)((float)F_CPU / (2.0 * 1975.5332050245) + 0.5) -1)

#define SH_do ((unsigned short)((float)F_CPU / (2.0 * 2093.00452240479) + 0.5) -1)
#define SH_re ((unsigned short)((float)F_CPU / (2.0 * 2349.31814333926) + 0.5) -1)
#define SH_mi ((unsigned short)((float)F_CPU / (2.0 * 2637.02045530296) + 0.5) -1)
#define SH_fa ((unsigned short)((float)F_CPU / (2.0 * 2793.82585146403) + 0.5) -1)
#define SH_so ((unsigned short)((float)F_CPU / (2.0 * 3135.963487854) + 0.5) -1)
#define SH_la ((unsigned short)((float)F_CPU / (2.0 * 3520.0) + 0.5) -1)
#define SH_si ((unsigned short)((float)F_CPU / (2.0 * 3951.066410049) + 0.5) -1)

typedef struct
{
	unsigned short Freq;
	unsigned short Time;				//频率持续时间 单位：1mS
}STR_BuzSound;

static STR_BuzSound PROGMEM BuzSound[7][5] ={{{H_so,100},{H_la,100},{H_si,100},{0,500},{0,0}},			//开机音 高音  5 6 7
										     {{H_si,100},{H_la,100},{H_so,100},{0,500},{0,0}},			//关机音 高音  7 6 5
										     {{H_so,100},{H_la,100},{0,500},{0,0},{0,0}},				//上升音 高音  5 6
										     {{H_la,100},{H_so,100},{0,500},{0,0},{0,0}},				//下降音 高音  6 5
										     {{H_re,160},{H_mi,160},{H_fa,160},{H_so,160},{H_la,160}},	//曝光键音 高音  2 3 4 5 6
										     {{H_si,100},{0,500},{0,0},{0,0},{0,0}}};					//曝光 高音    7


Enum_BuzCmd BuzCmd = Buz_None;
Enum_BuzCmd Buzzing = Buz_None;

void Int_Buzzer()
{
	static unsigned char BuzStep = 0,Exposuring = 0;
	static unsigned short TBuzMoo;
	unsigned short freq;
	unsigned short time;

	if ( PartState.KVPWM )
	{
		if ( !Exposuring )
		{
			Exposuring = 1;

			IO_BuzPower_On();				//打开蜂鸣器电源

			freq = H_si;

			OCR3AH = (freq >> 8) & 0xFF;	//高音 7
			OCR3AL = freq & 0xFF;
			TCCR3A = 0x40;					//比较匹配时OC3A电平取反，CTC模式，输出PWM
			
			Buzzing = Buz_None;
			BuzCmd = Buz_None;
		}

		return;
	}

	Exposuring = 0;

	if ( Buzzing == Buz_None )
	{
		IO_BuzPower_Off();				//关闭蜂鸣器电源
		TCCR3A = 0x00;					//OC3A为普通IO口模式，CTC模式，关闭蜂鸣器方波输出

		if ( BuzCmd != Buz_None )
		{
			Buzzing = BuzCmd;
			BuzCmd = Buz_None;
			BuzStep = 0;
			TBuzMoo =0;
		}
	}
	else
	{
		if ( TBuzMoo == 0 )
		{
			freq = pgm_read_word(&BuzSound[Buzzing][BuzStep].Freq);
			time = pgm_read_word(&BuzSound[Buzzing][BuzStep].Time);

			if ( (BuzStep >= 5) || ((freq == 0) && (time == 0)) )
			{
				Buzzing = Buz_None;
			}
			else
			{
				if ( freq == 0 )
				{
					IO_BuzPower_Off();		//关闭蜂鸣器电源
					TCCR3A = 0x00;			//OC3A为普通IO口模式，CTC模式，关闭蜂鸣器方波输出
				}
				else
				{		
					IO_BuzPower_On();		//打开蜂鸣器电源

					OCR3AH = (freq >> 8) & 0xFF;
					OCR3AL = freq & 0xFF;
					TCCR3A = 0x40;			//比较匹配时OC3A电平取反，CTC模式，输出PWM
				}

				TBuzMoo = time;
				BuzStep++;
			}
		}
		else
			TBuzMoo--;
	}
}

#undef	__Buzzer__

