#ifndef _SystemSleep_H_
#define _SystemSleep_H_

extern bit WakeupFlag;
extern bit FindIrFlag;

extern bit LowPowerFalshFlag;
extern unsigned char	LowPowerFlashTimer;
extern unsigned char	LowerFlashCounter;


#define IrWorkPin 	P00
#define IrCheckPin	P10
//#define Lm393PowerPin	P01

#define BatteryAdcChannel 	8
#define	IrAdcChannel 		0
//#define LowPowerValue		1000
//#define LowPowerValue		2072
#define LowPowerValue		2410				//低电压检测为4.6V ,使用680K分压，去掉103电容
//#define LowPowerValue		2650					//低电压检测为4.75V ,使用680K分压，去掉103电容


#define IrOverValue				1000
#define HandIsCloseNo1 		2000
#define HandIsCloseNo2 		1800
#define HandIsCloseNo3 		1500
//#define HandIsCloseNo4 		1200
#define HandIsCloseNo4 		1230

#define IrArroudValueNo1		3800
#define IrArroudValueNo2		3600
#define IrArroudValueNo3		3300
#define IrArroudValueNo4		2800







extern unsigned int 	MotorWorkTimer;
extern unsigned int 	MotorWokrKeepTimer;
extern unsigned int 	MotorRunLeftTimer;


void SleepProcess(void);



void 	ReadyToSleep(void);
void 	GotoSleep(void);
void 	WakeUpProcess(void);
void 	BtmInitial(void);
//void OpenMotor(void);
void OpenMotorRunRight(void);
void OpenMotorRunLeft(void);
void CloseMotor(void);
void OpenBackLight(void);
void CloseBackLight(void);

void DelayUs(unsigned char delayTimer);
void MotorWorkProcess(void);		

void ReadyToMotorWork(void);
void ReadyToLowpower(void);
void ConfirmWorkStatus(void);
void lowerPowerProcess(void);
void TurnOffWatchDog(void);
void TurnOnWatchDog(void);
void FeedToWatchDog(void);

void InitialIOPortForSleep(void);

#endif

