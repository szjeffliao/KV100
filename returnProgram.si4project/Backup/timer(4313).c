#include "all.h"


bit CheckIrCounterFlag;
bit MotorNeedWorkFlag;
bit MotorTimerOverFlag;

void InitailTimer(void)
{
	
		TMCON = 0X07;	 //------111 ;Timer0��Tiemr1��Tiemr2ѡ��ʱ��Fsys
		
		//T0����
		TMOD |= 0x01;				  //0000 0001;Timer0���ù�����ʽ1
		TL0 = (65536 - 48000)%256;	  //���ʱ�䣺ʱ��ΪFsys����24000*��1/Fsys��=1ms;
		TH0 = (65536 - 48000)/256;
		TR0 = 0;
		ET0 = 1;//��ʱ��0����
		TR0 = 1;//�򿪶�ʱ��0
	

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
					LowPowerFalshFlag  = 0;					//lowerPower��������
					
				}
			}
		}

		

}





