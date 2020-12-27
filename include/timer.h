#ifndef _Timer_H_
#define _Timer_H_

//#define motorWorkConst 250 
//#define motorWorkConst 130 
//#define motorWorkConst 200    0.86S
#define motorWorkConst  372
#define motorComebackConst 28
#define motorPauseConst 73
//#define KeepTimerOK 1175


//#define KeepTimerOK 705

#define KeepTimerOK 800

#define FlashTimerConst 75
#define	LowerFlashTimer 4


extern bit CheckIrCounterFlag;
extern bit MotorNeedWorkFlag;
extern bit MotorTimerOverFlag;
extern bit MotorRunLeftFlag;

extern bit MotorPauseFlag;
extern unsigned char MotorPauseValue;

void InitailTimer(void);



#endif

