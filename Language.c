//Language.c
#define __Language__

#include "Language.h"

//Ӣ�ĵ��ʶ���
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


//���Ķ���
static const prog_uchar SH_UserLanguage[] = "����:����";
static const prog_uchar SH_Ready[] = "����";
static const prog_uchar SH_Exposure[] = "�ع�";
static const prog_uchar SH_Menu[] = "�˵�:";
static const prog_uchar SH_Change[] = "�޸�:";
static const prog_uchar SH_Mode[] = "�й�ģʽ:";
static const prog_uchar SH_Film[] = "��Ƭ";
static const prog_uchar SH_Digital[] = "����";
static const prog_uchar SH_PowerSave[] = "�Զ��ػ�ʱ��:";
static const prog_uchar SH_BackLight[] = "����ʱ��:";
static const prog_uchar SH_Minute[] = "����";
static const prog_uchar SH_Second[] = "��";
static const prog_uchar SH_Battery[] = "��ص�ѹ:";
static const prog_uchar SH_Ver[] = "�汾:";
static const prog_uchar SH_ExposureNum[] = "�ع����:";
static const prog_uchar SH_FactorySet[] = "��������";
static const prog_uchar SH_ExposureKeySet[] = "�ع��:";
static const prog_uchar SH_Dual[] = "�ֶ�+ң��";
static const prog_uchar SH_Remote[] = "ң��";
static const prog_uchar SH_MaxExpTime[] = "����ع�ʱ��:";
static const prog_uchar SH_MinExpTime[] = "��С�ع�ʱ��:";
static const prog_uchar SH_ExpUnitTime[] = "�ع���ڲ���:";
static const prog_uchar SH_FactoryInit[] = "������ʼ��";
static const prog_uchar SH_Model[] = "����ͺ�:";
static const prog_uchar SH_Charge[] = "����!";

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
