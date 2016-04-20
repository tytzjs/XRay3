#define __EEPROM__

#include <avr/eeprom.h>
#include "EEPROM.h"
#include "Display.h"
#include "Run.h"

uint16_t BackupArray1[] __attribute__((section(".eeprom"))) = {
200,					//曝光时间
CFilm,					//感光模式
50,						//最小曝光时间 单位：毫秒
1200,					//最大曝光时间 单位：毫秒
50,						//曝光时间调节步长 单位：毫秒
CChinese,				//语言
300,					//自动关机时间 单位：秒
5,						//背光时间 单位：秒
CDual,					//曝光按键
0,						//曝光次数
1						//写结束
};

uint16_t BackupArray2[] __attribute__((section(".eeprom"))) = {
200,					//曝光时间
CFilm,					//感光模式
50,						//最小曝光时间 单位：毫秒
1200,					//最大曝光时间 单位：毫秒
50,						//曝光时间调节步长 单位：毫秒
CChinese,				//语言
300,					//自动关机时间 单位：秒
5,						//背光时间 单位：秒
CDual,					//曝光按键
0,						//曝光次数
1						//写结束
};

uint16_t *BackupArray;
unsigned short TXRayRadiate;								//单位:mS
unsigned short TMinExposure,TMaxExposure,TExposureUnit;		//单位:mS
unsigned short SensitizationMode;			//感光模式
unsigned short UserLanguage;				//用户语言
unsigned short TPowerSave,TBackLight;
unsigned short ExposureKey;
unsigned short ExposureNum;

static void InitEEPROM()
{
	unsigned short t;

	t = eeprom_read_word((const uint16_t *)&BackupArray[0]);
	if ( (t > 2000) || (t < 20) )
		eeprom_write_word((uint16_t *)&BackupArray[0],200);

	t = eeprom_read_word((const uint16_t *)&BackupArray[1]);
	if ( t > 1 )
		eeprom_write_word((uint16_t *)&BackupArray[1],CFilm);

	t = eeprom_read_word((const uint16_t *)&BackupArray[2]);
	if ( (t > 200) || (t < 20) )
		eeprom_write_word((uint16_t *)&BackupArray[2],50);

	t = eeprom_read_word((const uint16_t *)&BackupArray[3]);
	if ( (t > 1200) || (t < 1000) )
		eeprom_write_word((uint16_t *)&BackupArray[3],1200);

	t = eeprom_read_word((const uint16_t *)&BackupArray[4]);
	if ( (t > 100) || (t < 10) )
		eeprom_write_word((uint16_t *)&BackupArray[4],50);

	t = eeprom_read_word((const uint16_t *)&BackupArray[5]);
	if ( t > 1 )
		eeprom_write_word((uint16_t *)&BackupArray[5],CChinese);

	t = eeprom_read_word((const uint16_t *)&BackupArray[6]);
	if ( (t > 600) || (t < 60) )
		eeprom_write_word((uint16_t *)&BackupArray[6],300);
	
	t = eeprom_read_word((const uint16_t *)&BackupArray[7]);
	if ( (t > 10) || (t < 1) )
		eeprom_write_word((uint16_t *)&BackupArray[7],5);

	t = eeprom_read_word((const uint16_t *)&BackupArray[8]);
	if ( t > 1 )
		eeprom_write_word((uint16_t *)&BackupArray[8],CDual);

	t = eeprom_read_word((const uint16_t *)&BackupArray[9]);
	if ( t == 0xFFFF )
		eeprom_write_word((uint16_t *)&BackupArray[9],0);
	
	t = eeprom_read_word((const uint16_t *)&BackupArray[10]);
	if ( t == 0 )
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	
	
}

void ResumeEEPROM()
{
	unsigned short t;

	BackupArray = BackupArray1;

	t = eeprom_read_word((const uint16_t *)&BackupArray1[10]);
	if ( t == 0 )
	{
		t = eeprom_read_word((const uint16_t *)&BackupArray2[10]);
		if ( t )
			BackupArray = BackupArray2;
	}

	InitEEPROM();

	TXRayRadiate = eeprom_read_word((const uint16_t *)&BackupArray[0]);
	SensitizationMode = eeprom_read_word((const uint16_t *)&BackupArray[1]);
	TMinExposure = eeprom_read_word((const uint16_t *)&BackupArray[2]);
	TMaxExposure = eeprom_read_word((const uint16_t *)&BackupArray[3]);
	TExposureUnit = eeprom_read_word((const uint16_t *)&BackupArray[4]);
	UserLanguage = eeprom_read_word((const uint16_t *)&BackupArray[5]);
	TPowerSave = eeprom_read_word((const uint16_t *)&BackupArray[6]);
	TBackLight = eeprom_read_word((const uint16_t *)&BackupArray[7]);
	ExposureKey = eeprom_read_word((const uint16_t *)&BackupArray[8]);
	ExposureNum = eeprom_read_word((const uint16_t *)&BackupArray[9]);
}

void SaveArray()
{
	unsigned short t;

	t = eeprom_read_word((const uint16_t *)&BackupArray[0]);
	if ( TXRayRadiate != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[0],TXRayRadiate);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[1]);
	if ( SensitizationMode != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[1],(unsigned short)SensitizationMode);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[2]);
	if ( TMinExposure != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[2],TMinExposure);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[3]);
	if ( TMaxExposure != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[3],TMaxExposure);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[4]);
	if ( TExposureUnit != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[4],TExposureUnit);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[5]);
	if ( UserLanguage != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[5],UserLanguage);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[6]);
	if ( TPowerSave != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[6],TPowerSave);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[7]);
	if ( TBackLight != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[7],TBackLight);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[8]);
	if ( ExposureKey != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[8],ExposureKey);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[9]);
	if ( ExposureNum != t )
	{
		eeprom_write_word((uint16_t *)&BackupArray[10],0);
		eeprom_write_word((uint16_t *)&BackupArray[9],ExposureNum);
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
	}

	t = eeprom_read_word((const uint16_t *)&BackupArray[10]);
	if ( t == 0 )
		eeprom_write_word((uint16_t *)&BackupArray[10],1);
}

void SaveEEPROM()
{
	BackupArray = BackupArray1;
	SaveArray();

	BackupArray = BackupArray2;
	SaveArray();
}

#undef __EEPROM__
