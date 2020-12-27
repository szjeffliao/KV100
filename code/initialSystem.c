



#include "all.h"



unsigned char WorkStatusValue;


void InitialSystem(void)
{
	unsigned char i;
	unsigned int BatteryVoltage;
	InitialIOPort();
	InitialChangeValue();
	Uart0_Init();
	DisalbePrintf();
	BatteryVoltage = AdcResult(BatteryAdcChannel);
		//BatteryVoltage = 1000;
	EnablePrintf();
	printf("BatteryValtage = %d \n", BatteryVoltage);
	//DelayUs(200);

	DelayUs(200);
	for (i = 0; i < 50; ++i)
	{
		DelayUs(200);
	}
	MotorWorkLed = 0;
	EA = 1;

}



void InitialChangeValue(void)
{
	WorkStatusValue = SleepStatus;
	MotorWorkTimer = 0;
}



void InitialIOPort(void)
{
	P0CON = 0xFF;  //设置P0为强推挽模式
	P0PH  = 0x00;
	P1CON = 0xFF;  //设置P1为强推挽模式
	P1PH  = 0x00;
	P2CON = 0xFF;  //设置P2为强推挽模式
	P2PH  = 0x00;
	
	//P1CON = 0x00;  //设置P1为高阻输入模式
	//P1PH  = 0x00;
	//P2CON = 0x00;  //设置P2为高阻带上拉模式
	//P2PH  = 0xFF;
	SC92F7251_NIO_Init(); //未引出IO口配置
	MotorControlInA = 0; 
	MotorControlInB = 0;
	MotorWorkLed = 1;
	//Lm393PowerPin = 1; 
	//MotorWorkLed = 0;
	IrWorkPin = 1;
	P1CON &= 0XFE;     //中断IO INT00口设置为高阻输入
	P1PH  |= 0x01;     //中断IO口设置为高阻带上拉
	

}

