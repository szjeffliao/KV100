#ifndef _Timer_H_
#define _Timer_H_

//#define motorWorkConst 250 
#define motorWorkConst 130 

//#define KeepTimerOK 1175


#define KeepTimerOK 705

#define FlashTimerConst 75
#define	LowerFlashTimer 4


extern bit CheckIrCounterFlag;
extern bit MotorNeedWorkFlag;
extern bit MotorTimerOverFlag;


void InitailTimer(void);



#endif

