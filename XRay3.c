/*
 * XRay3.c
 *晶振：4.032MHz
 *手持式牙医X光射线机
 * Created: 2015-07-02 15:14:51
 *  Author: 邰勇
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
	DDRA = 0x2F;			//PA4为蜂鸣器输出（未用，配置为浮空输入）

	PORTB = 0x00;
	DDRB = 0xBF;			//PB6充电输入端口为输入,PB1测试选择口

	PORTC = 0x00;
	DDRC = 0xFF;			//LCD 数据口

	PORTD = 0x00;
	DDRD = 0xF3;			//PD3:开关键、PD2:曝光键

	PORTE = 0x02;			//PE1:UART通讯输出，默认输出1
	DDRE = 0xFE;			//PE0:UART通讯输入，PE3蜂鸣器方波输出

	PORTF = 0x00;
	DDRF = 0xFE;			//PF0:电池电压
	
	PORTG = 0x00;
	DDRG = 0xFF;
}

int main(void)
{
	asm("cli");					//关闭全局中断
	
	PortInit();
	
	TCCR0 = 0x00;				//停止TIM0
	TCNT0 = 0;					//TIM0计数器清零
	OCR0 = F_CPU / 32000UL -1;	//TIM0中断周期为(125+1)*7.9365=1mS
	TIFR |= (1 << OCF0);		//清除TIM0比较中断标记
	TIMSK |= (1 << OCIE0);		//允许TIM0比较中断
	TCCR0 = 0x0B;				//CTC模式、4.032MHz / 32 = 7.9365uS

	TCNT3H = 0x00;				//TIM3计数器清零
	TCNT3L = 0x00;
	OCR3AH = (505 >> 8) & 0xFF;
	OCR3AL = 505 & 0xFF;
	TCCR3A = 0x00;				//OC3A为普通IO口模式
	TCCR3B = 0x09;				//CTC模式，4.032MHz / 1 = 0.248uS	

	ADMUX = 0x00;				//右对齐，选择ADC0通道
	ADCSRA = 0x84;				//开启ADC、ADC时钟=CPU时钟 / 16
	
	asm("sei");					//使能全局中断

	ResumeEEPROM();
	GUI_Init();
	LanguageInit();
	
	while (!ADSample());

	//允许看门狗，设置看门狗超时时间
  	wdt_enable(WDTO_1S);
	
    while(1)
    {
		wdt_reset();			//看门狗复位
		ADSample();
		KeyScan();
		Display();
		SaveEEPROM();
		Run();
		TimeScan();
    }
}
