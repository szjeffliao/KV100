



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
	P0CON = 0xFF;  //����P0Ϊǿ����ģʽ
	P0PH  = 0x00;
	P1CON = 0xFF;  //����P1Ϊǿ����ģʽ
	P1PH  = 0x00;
	P2CON = 0xFF;  //����P2Ϊǿ����ģʽ
	P2PH  = 0x00;
	
	//P1CON = 0x00;  //����P1Ϊ��������ģʽ
	//P1PH  = 0x00;
	//P2CON = 0x00;  //����P2Ϊ���������ģʽ
	//P2PH  = 0xFF;
	SC92F7251_NIO_Init(); //δ����IO������
	MotorControlInA = 0; 
	MotorControlInB = 0;
	MotorWorkLed = 1;
	//Lm393PowerPin = 1; 
	//MotorWorkLed = 0;
	IrWorkPin = 1;
	P1CON &= 0XFE;     //�ж�IO INT00������Ϊ��������
	P1PH  |= 0x01;     //�ж�IO������Ϊ���������
	

}

