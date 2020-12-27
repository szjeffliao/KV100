/*
使用1.5版本主板
使用最6V的马达，兼容到4.5V的工作电压
使用两个软件版本，主要是针对碱性电池与镍氢电池时候不同的低电压的状况进行判读
增加一个2CM与5CM的距离修改，这个需要配合，如果上电时候，直接按住红外头不放，2S后进入到修改状态
修改的状态将写入到EEPROM,以后工作起来后将按照这个距离在处理
*/


#include "all.h"



void main (void)
{

	InitialSystem();
	EnablePrintf();
	printf("Begin to work,MCU go into main loop!\n");
	while(1)
	{
		FeedToWatchDog();
		switch (WorkStatusValue)
		{
			case SleepStatus:
				SleepProcess();
				break;
			//case CheckIRStatus:
			//	CheckIrProcess();		//WorkStatusValue = SleepStatus;
			//	break;
			case MotorWorkStatus:
				MotorWorkProcess();		
				break;
			case LowPowerStatus:
				lowerPowerProcess();
				break;
			
			
			default:
				break;
		}
	}
}