
#include "all.h"


bit WakeupFlag;
bit FindIrFlag;
bit LowPowerFalshFlag;
unsigned char	LowPowerFlashTimer;
unsigned char	LowerFlashCounter;

unsigned char 	MotorWorkTimer;
unsigned int 	MotorWokrKeepTimer;


void SleepProcess(void)
{
	CloseBackLight();
	printf("I will go to sleep!\n");
	ReadyToSleep();
	GotoSleep();
	DelayUs(100);
	if (WakeupFlag)
	{
		Uart0_Init();
		EnablePrintf();
		printf("I wake up from sleeep!\n");
	}
	WakeUpProcess();
	ConfirmWorkStatus();



}


void 	ReadyToSleep(void)
{
		PWMCON &= ~(0x80);//�ر�PWMģ���Դ
		ADCCON &= ~(0x80);//�ر�ADCģ���Դ
		TurnOffWatchDog();
		TR0 = 0; 
		WakeupFlag = 0;
		BtmInitial();

}
void 	GotoSleep(void)
{
	  /* half������֤ */
	  PCON = 0x02;  //half������֤
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
	  _nop_();
		BTMCON = 0x00; 										//�رյ�Ƶʱ��

}
void 	WakeUpProcess(void)
{
		unsigned int	IrRecVoltage1,IrRecVoltage2,IrRecVoltage;
		bit HandIsCloseFlag = 0;
		//WorkStatusValue = CheckIRStatus;
		FindIrFlag = 0;						//������û�к��ⷴ����־
		IrRecVoltage1 = AdcResult(IrAdcChannel);
		printf("Before IR LED WORK Voltage NO1 = %d \n", IrRecVoltage1);
	  DelayUs(80);
		IrRecVoltage1 = AdcResult(IrAdcChannel);
		printf("Before IR LED WORK Voltage NO2= %d \n", IrRecVoltage1);
		Lm393PowerPin = 0;					//�Ƚ����ϵ�
		DelayUs(10);
		if (IrCheckPin == 0)
			{
				printf("ATTEMTON,Find IR PIN is LOW !\n");
				Lm393PowerPin  = 1;
			}
		else
		{	
					
			IrWorkPin  = 0;
			DelayUs(10);
			//DelayUs(4);
			IrRecVoltage2 = AdcResult(IrAdcChannel);
			printf("After IR LED WORK Voltage = %d \n", IrRecVoltage2);
			if (IrRecVoltage1 > IrRecVoltage2 )
			{
				IrRecVoltage = IrRecVoltage1 - IrRecVoltage2;
				printf("IrRecValtage = %d \n", IrRecVoltage);
				if (IrRecVoltage1 > IrArroudValueNo1)
				{
					if (IrRecVoltage > HandIsCloseNo1)
						{
							HandIsCloseFlag = 1;
							printf("\n  IR NO1!");
						}
				}
				if (IrRecVoltage1 > IrArroudValueNo2)
				{
					if (IrRecVoltage > HandIsCloseNo2)
						{
							HandIsCloseFlag = 1;
							printf("\n IR NO2!");
						}
				}
				if (IrRecVoltage1 > IrArroudValueNo3)
				{
					if (IrRecVoltage > HandIsCloseNo3)
						{
							HandIsCloseFlag = 1;
							printf("\n IR NO3!");
						}
				}
				if (IrRecVoltage1 > IrArroudValueNo4)
				{
					if (IrRecVoltage > HandIsCloseNo4)
						{
							HandIsCloseFlag = 1;
							printf("\n IR NO4!");
						}
				}
				//if (IrCheckPin == 0)
				//if ((IrCheckPin == 0) && HandIsCloseFlag)
				if(HandIsCloseFlag)
				{
					//DelayUs(2);
					//DelayUs(1);
					IrWorkPin = 1;
					Lm393PowerPin = 1;
					FindIrFlag = 1;
					printf("\n Find IR imformation !\n");
					
	//				if (IrCheckPin == 0)
	//				{
	//					IrWorkPin = 1;
	//					Lm393PowerPin = 1;
	//					FindIrFlag = 1;
	//					printf("Find IR imformation !\n");
	//				}
				}
				else
				{
					CloseBackLight();
					IrWorkPin = 1;
					Lm393PowerPin = 1;
					printf("\n Can't find IR !\n");
				}
			}
			else
			{
					CloseBackLight();
					IrWorkPin = 1;
					Lm393PowerPin = 1;
					printf("Find error of check IR!\n");

			}
		}	
			
}


void OpenMotor(void)
{
	MotorControl = 1; 
	MotorWorkTimer = 0;
	MotorWokrKeepTimer = 0;
	MotorNeedWorkFlag = 1;
}


void CloseMotor(void)
{
	MotorControl = 0; 


}

void OpenBackLight(void)
{
	
	MotorWorkLed = 1;
	
	

}


void CloseBackLight(void)
{
	
	MotorWorkLed = 0;


}


/*****************************************************

*�������ƣ�void BtmInitial(void)
*�������ܣ�BTM��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void BtmInitial(void)
{
//	BTMCON = 0x00;  //������
//	BTMCON = 0x80;  //ÿ15.6ms����һ���ж�
//	BTMCON = 0x81;	//ÿ31.3ms����һ���ж�
//	BTMCON = 0x82;	//ÿ62.5ms����һ���ж�
//		BTMCON = 0x83;	//ÿ125ms����һ���ж�
	BTMCON = 0x84;	//ÿ0.25s����һ���ж�
//	BTMCON = 0x85;	//ÿ0.5s����һ���ж�
//	BTMCON = 0x86;	//ÿ1s����һ���ж�
//	BTMCON = 0x87;	//ÿ2s����һ���ж�
	//Pwm0Stop();
	//MotorWorkLed = 1;
	//CloseInt00();
	
	IE1 |= 0x04;       //����BTM�ж�
	EA = 1;           //�������ж�
}



/*****************************************************
*�������ƣ�void BTM_Int(void) interrupt 9
*�������ܣ��жϷ�����
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void BTM_Int(void) interrupt 9
{
	if(!(BTMCON&0X40))		//�жϱ�־λ�ж�
	{
		WakeupFlag = 1;
		//P04 = ~P04;
	}
}




void DelayUs(unsigned char delayTimer)
{

    unsigned char  n;

   	while(delayTimer>0)
	{
		for(n=0;n<30;++n)
 	 	{
			_nop_();
		}
		delayTimer--;
	}

}




void MotorWorkProcess()
{
	FeedToWatchDog();
	if (MotorTimerOverFlag)
	{
		
		CloseBackLight();
		WorkStatusValue  = SleepStatus;
		MotorTimerOverFlag = 0;
		Uart0_Init();
		EnablePrintf();
		printf("I from motor work status change sleep status!\n");
		TR0 = 0;
		ET0 = 0;
	}


}



void ReadyToMotorWork(void)
{
	//BTMCON = 0x00; 
	IrWorkPin = 1;
	OpenMotor();
	OpenBackLight();
	WorkStatusValue  = MotorWorkStatus;
	MotorTimerOverFlag = 0;
	MotorWorkTimer = 0;
	InitailTimer();

}



void ConfirmWorkStatus(void)
{
	unsigned int BatteryVoltage = 1000;
	
	if (FindIrFlag)
	{
		//TurnOnWatchDog();
		BTMCON = 0x00; 										//�رյ�Ƶʱ��
		TurnOnWatchDog();
		printf("ready to check Battery voltage!\n");
		//ReadyToMotorWork
		
		BatteryVoltage = AdcResult(BatteryAdcChannel);
		printf("BatteryValtage NO1 = %d \n", BatteryVoltage);
		DelayUs(30);
		
		BatteryVoltage = AdcResult(BatteryAdcChannel);
		//BatteryVoltage = 1000;
		printf("BatteryValtage NO2 = %d \n", BatteryVoltage);
		if (BatteryVoltage < LowPowerValue)
		{
			printf("It is low power!\n");
			ReadyToLowpower();
		}
		else
		{
			printf("power is ok and motor will work!\n");
			ReadyToMotorWork();
		}
		
	}
}



void ReadyToLowpower(void)
{
	WorkStatusValue  = LowPowerStatus;
	LowPowerFalshFlag	= 1;
	LowPowerFlashTimer = 0;
	LowerFlashCounter = 0;
	OpenBackLight();
	InitailTimer();
}



void lowerPowerProcess(void)
{
	FeedToWatchDog();
	if (!LowPowerFalshFlag)
	{
		
		CloseBackLight();
		WorkStatusValue  = SleepStatus;
		//MotorTimerOverFlag = 0;
		Uart0_Init();
		EnablePrintf();
		printf("I from lowpower status change sleep status!\n");
		TR0 = 0;
		ET0 = 0;
	}
}


void TurnOffWatchDog(void)
{
	bit TmpBit;
	TmpBit = EA;
	EA = 0;
	OPINX = 0xC1;
	OPREG &= ~(0x80); //�رտ��Ź�
	EA = TmpBit;
}

void TurnOnWatchDog(void)
{
	bit TmpBit;
	TmpBit = EA;
	EA = 0;
	OPINX = 0xC1;
	OPREG |= 0x80; //�򿪿��Ź�,Ĭ��500MS�ĸ�λʱ��
	EA = TmpBit;

}


void FeedToWatchDog(void)
{
	WDTCON |= 0x10;		

}
