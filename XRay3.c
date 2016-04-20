/*
 * XRay3.c
 *����4.032MHz
 *�ֳ�ʽ��ҽX�����߻�
 * Created: 2015-07-02 15:14:51
 *  Author: ۢ��
 */ 

#include <avr/wdt.h>
#include "IODefine.h"
#include "TimeScan.h"
#include "Run.h"
#include "ADSample.h"
#include "Key.h"
#include "Display.h"
#include "GUI.h"
#include "EEPROM.h"
#include "Language.h"

void PortInit(void)
{
	PORTA = 0x00;
	DDRA = 0x2F;			//PA4Ϊ�����������δ�ã�����Ϊ�������룩

	PORTB = 0x00;
	DDRB = 0xBF;			//PB6�������˿�Ϊ����,PB1����ѡ���

	PORTC = 0x00;
	DDRC = 0xFF;			//LCD ���ݿ�

	PORTD = 0x00;
	DDRD = 0xF3;			//PD3:���ؼ���PD2:�ع��

	PORTE = 0x02;			//PE1:UARTͨѶ�����Ĭ�����1
	DDRE = 0xFE;			//PE0:UARTͨѶ���룬PE3�������������

	PORTF = 0x00;
	DDRF = 0xFE;			//PF0:��ص�ѹ
	
	PORTG = 0x00;
	DDRG = 0xFF;
}

int main(void)
{
	asm("cli");					//�ر�ȫ���ж�
	
	PortInit();
	
	TCCR0 = 0x00;				//ֹͣTIM0
	TCNT0 = 0;					//TIM0����������
	OCR0 = F_CPU / 32000UL -1;	//TIM0�ж�����Ϊ(125+1)*7.9365=1mS
	TIFR |= (1 << OCF0);		//���TIM0�Ƚ��жϱ��
	TIMSK |= (1 << OCIE0);		//����TIM0�Ƚ��ж�
	TCCR0 = 0x0B;				//CTCģʽ��4.032MHz / 32 = 7.9365uS

	TCNT3H = 0x00;				//TIM3����������
	TCNT3L = 0x00;
	OCR3AH = (505 >> 8) & 0xFF;
	OCR3AL = 505 & 0xFF;
	TCCR3A = 0x00;				//OC3AΪ��ͨIO��ģʽ
	TCCR3B = 0x09;				//CTCģʽ��4.032MHz / 1 = 0.248uS	

	ADMUX = 0x00;				//�Ҷ��룬ѡ��ADC0ͨ��
	ADCSRA = 0x84;				//����ADC��ADCʱ��=CPUʱ�� / 16
	
	asm("sei");					//ʹ��ȫ���ж�

	ResumeEEPROM();
	GUI_Init();
	LanguageInit();
	
	while (!ADSample());

	//�����Ź������ÿ��Ź���ʱʱ��
  	wdt_enable(WDTO_1S);
	
    while(1)
    {
		wdt_reset();			//���Ź���λ
		ADSample();
		KeyScan();
		Display();
		SaveEEPROM();
		Run();
		TimeScan();
    }
}
