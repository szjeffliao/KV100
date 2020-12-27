
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
		PWMCON &= ~(0x80);//关闭PWM模组电源
		ADCCON &= ~(0x80);//关闭ADC模组电源
		TurnOffWatchDog();
		TR0 = 0; 
		WakeupFlag = 0;
		BtmInitial();

}
void 	GotoSleep(void)
{
	  /* half唤醒验证 */
	  PCON = 0x02;  //half唤醒验证
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
		BTMCON = 0x00; 										//关闭低频时钟

}
void 	WakeUpProcess(void)
{
		unsigned int	IrRecVoltage1,IrRecVoltage2,IrRecVoltage;
		bit HandIsCloseFlag = 0;
		//WorkStatusValue = CheckIRStatus;
		FindIrFlag = 0;						//发现有没有红外反馈标志
		IrRecVoltage1 = AdcResult(IrAdcChannel);
		printf("Before IR LED WORK Voltage NO1 = %d \n", IrRecVoltage1);
	  DelayUs(80);
		IrRecVoltage1 = AdcResult(IrAdcChannel);
		printf("Before IR LED WORK Voltage NO2= %d \n", IrRecVoltage1);
		Lm393PowerPin = 0;					//比较器上电
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

*函数名称：void BtmInitial(void)
*函数功能：BTM初始化
*入口参数：void
*出口参数：void
*****************************************************/
void BtmInitial(void)
{
//	BTMCON = 0x00;  //不开启
//	BTMCON = 0x80;  //每15.6ms产生一个中断
//	BTMCON = 0x81;	//每31.3ms产生一个中断
//	BTMCON = 0x82;	//每62.5ms产生一个中断
//		BTMCON = 0x83;	//每125ms产生一个中断
	BTMCON = 0x84;	//每0.25s产生一个中断
//	BTMCON = 0x85;	//每0.5s产生一个中断
//	BTMCON = 0x86;	//每1s产生一个中断
//	BTMCON = 0x87;	//每2s产生一个中断
	//Pwm0Stop();
	//MotorWorkLed = 1;
	//CloseInt00();
	
	IE1 |= 0x04;       //开启BTM中断
	EA = 1;           //开启总中断
}



/*****************************************************
*函数名称：void BTM_Int(void) interrupt 9
*函数功能：中断服务函数
*入口参数：void
*出口参数：void
*****************************************************/
void BTM_Int(void) interrupt 9
{
	if(!(BTMCON&0X40))		//中断标志位判断
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
		BTMCON = 0x00; 										//关闭低频时钟
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
	OPREG &= ~(0x80); //关闭看门狗
	EA = TmpBit;
}

void TurnOnWatchDog(void)
{
	bit TmpBit;
	TmpBit = EA;
	EA = 0;
	OPINX = 0xC1;
	OPREG |= 0x80; //打开看门狗,默认500MS的复位时间
	EA = TmpBit;

}


void FeedToWatchDog(void)
{
	WDTCON |= 0x10;		

}
