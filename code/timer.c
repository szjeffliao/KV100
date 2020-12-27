#include "all.h"

//11月23日增加电机反转前，停止一下再开始反转
bit CheckIrCounterFlag;
bit MotorNeedWorkFlag;
bit MotorTimerOverFlag;
bit MotorRunLeftFlag;
bit MotorPauseFlag;
unsigned char MotorPauseValue;

void InitailTimer(void)
{
	
		TMCON = 0X07;	 //------111 ;Timer0、Tiemr1和Tiemr2选择时钟Fsys
		
		//T0设置
		TMOD |= 0x01;				  //0000 0001;Timer0设置工作方式1
		TL0 = (65536 - 48000)%256;	  //溢出时间：时钟为Fsys，则24000*（1/Fsys）=1ms;
		TH0 = (65536 - 48000)/256;
		TR0 = 0;
		ET0 = 1;//定时器0允许
		TR0 = 1;//打开定时器0
	

}


void timer0() interrupt 1
{
    TL0 = (65536 - 48000)%256;
		TH0 = (65536 - 48000)/256;
		//P04 = ~P04;
		
		
		if (WorkStatusValue == MotorWorkStatus)
		{
			if (MotorNeedWorkFlag)
				{
					MotorWorkTimer ++;
					if (MotorWorkTimer > motorWorkConst)
					{
						CloseMotor();
						MotorNeedWorkFlag = 0;
						MotorPauseFlag = 1;
						MotorPauseValue = 0;
						//OpenMotorRunLeft();
					}
				}
				if(MotorPauseFlag)
				{
						MotorPauseValue++;
						if(MotorPauseValue >= motorPauseConst)
						{
							MotorPauseFlag = 0;
							OpenMotorRunLeft();
							//MotorRunLeftFlag = 1;
						}
				}
				if (MotorRunLeftFlag)
					{
						MotorRunLeftTimer ++;
						if (MotorRunLeftTimer > motorComebackConst)
							{
									MotorRunLeftFlag = 0;
									CloseMotor();
									
							}
					}
			MotorWokrKeepTimer ++ ;
			if (MotorWokrKeepTimer > KeepTimerOK)
			{
				MotorTimerOverFlag = 1; 
				CloseMotor();
			}
	
		}
		if (LowPowerFalshFlag)
		{
			LowerFlashCounter ++;
			if(LowerFlashCounter > FlashTimerConst)
			{
				LowerFlashCounter = 0;
				LowPowerFlashTimer ++;
				MotorWorkLed = ~MotorWorkLed;
				if (LowPowerFlashTimer > LowerFlashTimer)
				{
					LowPowerFalshFlag  = 0;					//lowerPower闪动结束
					
				}
			}
		}

		

}





