#include "all.h"

//11��23�����ӵ����תǰ��ֹͣһ���ٿ�ʼ��ת
bit CheckIrCounterFlag;
bit MotorNeedWorkFlag;
bit MotorTimerOverFlag;
bit MotorRunLeftFlag;
bit MotorPauseFlag;
unsigned char MotorPauseValue;

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
					LowPowerFalshFlag  = 0;					//lowerPower��������
					
				}
			}
		}

		

}





