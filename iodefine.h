//iodefine.h

#ifndef __IODefine_H__
#define __IODefine_H__

#include <avr/io.h>

#define F_CPU 4000000UL

//PORTA
#define IO_PWMPower_On() PORTA |= (1 << PA0)
#define IO_PWMPower_Off() PORTA &= ~(1 << PA0)

#define IO_FilamentPWM_On() PORTA |= (1 << PA1)
#define IO_FilamentPWM_Off() PORTA &= ~(1 << PA1)

#define IO_KVPWM_On() PORTA |= (1 << PA2)
#define IO_KVPWM_Off() PORTA &= ~(1 << PA2)

#define IO_MCUPower_On() PORTA |= (1 << PA3)
#define IO_MCUPower_Off() PORTA &= ~(1 << PA3)

#define IO_Buz_On() PORTA |= (1 << PA4)
#define IO_Buz_Off() PORTA &= ~(1 << PA4)

#define IO_ExposureLED_On() PORTA |= (1 << PA5)
#define IO_ExposureLED_Off() PORTA &= ~(1 << PA5)

#define IO_AddKeyValue() ((PINA >> PA6) & 0x01)
#define IO_SubKeyValue() ((PINA >> PA7) & 0x01)

//PORTB
#define IO_LCD_CS_Set() PORTB |= (1 << PB2)
#define IO_LCD_CS_Clr() PORTB &= ~(1 << PB2)

#define IO_LCD_RD_Set() PORTB |= (1 << PB3)
#define IO_LCD_RD_Clr() PORTB &= ~(1 << PB3)

#define IO_LCD_WR_Set() PORTB |= (1 << PB4)
#define IO_LCD_WR_Clr() PORTB &= ~(1 << PB4)

#define IO_LCD_CD_Set() PORTB |= (1 << PB5)
#define IO_LCD_CD_Clr() PORTB &= ~(1 << PB5)

#define IO_RemoteInserting() ((~PINB >> PB6) & 0x01)

//PORTD
#define IO_ExposureKeyValue() ((PIND >> PD2) & 0x01)
#define IO_OnOffKeyValue() ((PIND >> PD3) & 0x01)

#define IO_UnitPower_On() PORTD |= (1 << PD6)
#define IO_UnitPower_Off() PORTD &= ~(1 << PD6)

#define IO_BuzPower_On() PORTD |= (1 << PD7)
#define IO_BuzPower_Off() PORTD &= ~(1 << PD7)

//PORTE
#define IO_LCD_BackLight_On() PORTE |= (1 << PE4)
#define IO_LCD_BackLight_Off() PORTE &= ~(1 << PE4)

#define IO_LED3_On() PORTE |= (1 << PE5)
#define IO_LED3_Off() PORTE &= ~(1 << PE5)

#define IO_LED4_On() PORTE |= (1 << PE6)
#define IO_LED4_Off() PORTE &= ~(1 << PE6)

#define IO_LED5_On() PORTE |= (1 << PE7)
#define IO_LED5_Off() PORTE &= ~(1 << PE7)

#endif
