#ifndef _initilSystem_H_
#define _initilSystem_H_


#define MotorControlInB    	P01
#define MotorControlInA   	P03
#define MotorWorkLed		P02	


extern unsigned char WorkStatusValue;


#define SleepStatus 	0x01
#define	CheckIRStatus	0x02
#define	MotorWorkStatus 0x03
#define LowPowerStatus 	0x04
#define ChangeCheckLength 0x05

void InitialSystem(void);

void InitialIOPort(void);


void InitialChangeValue(void);

#endif

