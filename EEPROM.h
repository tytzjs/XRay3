#ifndef __EEPROM_H__
#define __EEPROM_H__

#define CDigitalSensor 0
#define CFilm 1

#define	CEnglish 0
#define CChinese 1

#define CDual	0
#define CRemote	1

#endif

#ifndef __EEPROM__
	extern unsigned short TXRayRadiate;
	extern unsigned short TMinExposure,TMaxExposure,TExposureUnit;
	extern unsigned short SensitizationMode;
	extern unsigned short UserLanguage;
	extern unsigned short TPowerSave,TBackLight;
	extern unsigned short ExposureKey;
	extern unsigned short ExposureNum;

	extern void ResumeEEPROM();
	extern void SaveEEPROM();

#endif
