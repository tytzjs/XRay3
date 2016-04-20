#ifndef __Language_H__
#define __Language_H__

#include  "GUI.h"

typedef struct
{
	const prog_uchar *pUserLanguage;
	const prog_uchar *pReady,*pExposure,*pMenu,*pChange;
	const prog_uchar *pMode,*pFilm,*pDigital;
	const prog_uchar *pPowerSave,*pBackLight;
	const prog_uchar *pBattery,*pVer,*pDate,*pExposureNum;
	const prog_uchar *pFactorySet,*pExposureKeySet,*pDual,*pRemote;
	const prog_uchar *pMaxExpTime,*pMinExpTime,*pExpUnitTime;
	const prog_uchar *pMinute,*pSecond;
	const prog_uchar *pFactoryInit;
	const prog_uchar *pModel;
	const prog_uchar *pCharge;
}STR_Language;

#endif

#ifndef __Language__
	extern STR_Language English,Chinese;
	extern STR_Language *pLanguage;

	extern void LanguageInit();
	extern char *GetString(const prog_uchar string[]);

#endif
