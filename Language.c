//Language.c
#define __Language__

#include "Language.h"

//英文单词定义
static const prog_uchar SE_UserLanguage[] = "Language:English";
static const prog_uchar SE_Ready[] = "READY";
static const prog_uchar SE_Exposure[] = "EXPOSURE";
static const prog_uchar SE_Menu[] = "MENU:";
static const prog_uchar SE_Change[] = "CHANGE:";
static const prog_uchar SE_Mode[] = "Mode:";
static const prog_uchar SE_Film[] = "Film";
static const prog_uchar SE_Digital[] = "Digital";
static const prog_uchar SE_PowerSave[] = "Power-save:";
static const prog_uchar SE_BackLight[] = "Back-light:";
static const prog_uchar SE_Minute[] = "M";
static const prog_uchar SE_Second[] = "S";
static const prog_uchar SE_Battery[] = "Bat Vol:";
static const prog_uchar SE_Ver[] = "Ver:";
static const prog_uchar SE_ExposureNum[] = "Exp Num:";
static const prog_uchar SE_FactorySet[] = "Factory Setting";
static const prog_uchar SE_ExposureKeySet[] = "Expkey Set:";
static const prog_uchar SE_Dual[] = "Dual";
static const prog_uchar SE_Remote[] = "Remote";
static const prog_uchar SE_MaxExpTime[] = "MaxExp Time:";
static const prog_uchar SE_MinExpTime[] = "MinExp Time:";
static const prog_uchar SE_ExpUnitTime[] = "ExpUnit Time:";
static const prog_uchar SE_FactoryInit[] = "Factory Init";
static const prog_uchar SE_Model[] = "Model:";
static const prog_uchar SE_Charge[] = "Please Charge!";


//中文定义
static const prog_uchar SH_UserLanguage[] = "语言:中文";
static const prog_uchar SH_Ready[] = "就绪";
static const prog_uchar SH_Exposure[] = "曝光";
static const prog_uchar SH_Menu[] = "菜单:";
static const prog_uchar SH_Change[] = "修改:";
static const prog_uchar SH_Mode[] = "感光模式:";
static const prog_uchar SH_Film[] = "胶片";
static const prog_uchar SH_Digital[] = "数字";
static const prog_uchar SH_PowerSave[] = "自动关机时间:";
static const prog_uchar SH_BackLight[] = "背光时间:";
static const prog_uchar SH_Minute[] = "分钟";
static const prog_uchar SH_Second[] = "秒";
static const prog_uchar SH_Battery[] = "电池电压:";
static const prog_uchar SH_Ver[] = "版本:";
static const prog_uchar SH_ExposureNum[] = "曝光次数:";
static const prog_uchar SH_FactorySet[] = "工厂设置";
static const prog_uchar SH_ExposureKeySet[] = "曝光键:";
static const prog_uchar SH_Dual[] = "手动+遥控";
static const prog_uchar SH_Remote[] = "遥控";
static const prog_uchar SH_MaxExpTime[] = "最大曝光时间:";
static const prog_uchar SH_MinExpTime[] = "最小曝光时间:";
static const prog_uchar SH_ExpUnitTime[] = "曝光调节步长:";
static const prog_uchar SH_FactoryInit[] = "工厂初始化";
static const prog_uchar SH_Model[] = "球管型号:";
static const prog_uchar SH_Charge[] = "请充电!";

static const prog_uchar S_Date[] = "15-10-25";

STR_Language English,Chinese;
STR_Language *pLanguage;

void LanguageInit()
{
	English.pUserLanguage = SE_UserLanguage;
	English.pReady = SE_Ready;
	English.pExposure = SE_Exposure;
	English.pMenu = SE_Menu;
	English.pChange = SE_Change;
	English.pMode = SE_Mode;
	English.pFilm = SE_Film;
	English.pDigital = SE_Digital;
	English.pPowerSave = SE_PowerSave;
	English.pBackLight = SE_BackLight;
	English.pMinute = SE_Minute;
	English.pSecond = SE_Second;
	English.pBattery = SE_Battery;
	English.pVer = SE_Ver;
	English.pDate = S_Date;
	English.pExposureNum = SE_ExposureNum;
	English.pFactorySet = SE_FactorySet;
	English.pExposureKeySet = SE_ExposureKeySet;
	English.pDual = SE_Dual;
	English.pRemote = SE_Remote;
	English.pMaxExpTime = SE_MaxExpTime;
	English.pMinExpTime = SE_MinExpTime;
	English.pExpUnitTime = SE_ExpUnitTime;
	English.pFactoryInit = SE_FactoryInit;
	English.pModel = SE_Model;
	English.pCharge = SE_Charge;

	Chinese.pUserLanguage = SH_UserLanguage;
	Chinese.pReady = SH_Ready;
	Chinese.pExposure = SH_Exposure;
	Chinese.pMenu = SH_Menu;
	Chinese.pChange = SH_Change;
	Chinese.pMode = SH_Mode;
	Chinese.pFilm = SH_Film;
	Chinese.pDigital = SH_Digital;
	Chinese.pPowerSave = SH_PowerSave;
	Chinese.pBackLight = SH_BackLight;
	Chinese.pMinute = SH_Minute;
	Chinese.pSecond = SH_Second;
	Chinese.pBattery = SH_Battery;
	Chinese.pVer = SH_Ver;
	Chinese.pDate = S_Date;
	Chinese.pExposureNum = SH_ExposureNum;
	Chinese.pFactorySet = SH_FactorySet;
	Chinese.pExposureKeySet = SH_ExposureKeySet;
	Chinese.pDual = SH_Dual;
	Chinese.pRemote = SH_Remote;
	Chinese.pMaxExpTime = SH_MaxExpTime;
	Chinese.pMinExpTime = SH_MinExpTime;
	Chinese.pExpUnitTime = SH_ExpUnitTime;
	Chinese.pFactoryInit = SH_FactoryInit;
	Chinese.pModel = SH_Model;
	Chinese.pCharge = SH_Charge;
}

char *GetString(const prog_uchar string[])
{
	static char s[20];
	unsigned char i;
	char t;

	for (i = 0; i < 20; i++)
	{
		t = pgm_read_byte(&string[i]);
		s[i] = t;
		if ( t == 0 )
			break;
	}

	if ( i == 20 )
		s[19] = 0;

	return s;
}

#undef __Language__
