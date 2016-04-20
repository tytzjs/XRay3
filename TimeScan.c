#define	__TimeScan__

#include <avr/interrupt.h>
#include "iodefine.h"
#include "Run.h"
#include "Buzzer.h"
#include "key.h"
#include "Display.h"

#define CTIMEBASE 1000
#define CTIME20MS 20000
static unsigned char Num1ms = 0;

//1mS定时中断
ISR(TIMER0_COMP_vect)
{
	Num1ms++;

	Int_Buzzer();
	Int_XRayWork();
}

static void Visit20ms(void)
{
	if ( TReset < 10000 )
		TReset++;

	if ( TKeySame < 251 )
		TKeySame++;

	if ( TContinuePress != 255 )
	{
		if ( TContinuePress )
			TContinuePress--;
	}

	if ( TDisplayRefresh )
		TDisplayRefresh--;
}

static void Visit1s(void)
{
	if ( TKeyAct < 1000 )
		TKeyAct++;

	if ( TXRayStop < 1000 )
		TXRayStop++;

	if ( TChargeUI < 250 )
		TChargeUI++;
}

void TimeScan( void )
{
	static unsigned long TBase = 0;
	static unsigned char Num20ms = 0;
	
	while ( Num1ms != 0 )
	{
		TBase += CTIMEBASE;
		if ( TBase >= CTIME20MS )
		{
			TBase -= CTIME20MS;
			Visit20ms();
			
			Num20ms++;
			if ( Num20ms >= 50 )
			{
				Num20ms -= 50;
				Visit1s();
			}
		}
		TIMSK &= ~(1 << OCIE0);			//禁止TIM0比较中断		
		Num1ms--;
		TIMSK |= (1 << OCIE0);			//允许TIM0比较中断
	}
}


#undef __TimeScan__
