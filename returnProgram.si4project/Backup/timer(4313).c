#include "all.h"


bit CheckIrCounterFlag;
bit MotorNeedWorkFlag;
bit MotorTimerOverFlag;

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
					}
				}
			MotorWokrKeepTimer ++ ;
			if (MotorWokrKeepTimer > KeepTimerOK)
			{
				MotorTimerOverFlag = 1; 
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





