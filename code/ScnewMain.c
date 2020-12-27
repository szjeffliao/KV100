












#include "all.h"




void main (void)
{
//	unsigned char i;
//	unsigned int BatteryVoltage1,BatteryVoltage2,BatteryVoltage;
	InitialSystem();
	EnablePrintf();
	printf("it is not easy to use sc mcu!\n");
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
//==========================================================================================
//			for (i = 0; i < 50; ++i)
//			{
//				DelayUs(200);
//			}
//			
//			BatteryVoltage1 = AdcResult(BatteryAdcChannel);
//			printf("Turn off the ir LED  IR RECEIVE Valtage = %d \n", BatteryVoltage1);
//			IrWorkPin  = 0;
//			DelayUs(4);
//			BatteryVoltage2 = AdcResult(BatteryAdcChannel);
//			EnablePrintf();
//			IrWorkPin  = 1;
//			printf(" AT ONCE Turn ON the ir LED  IR RECEIVE Valtage = %d \n", BatteryVoltage2);
//			BatteryVoltage = BatteryVoltage1 -BatteryVoltage2;
//			printf("Check Valtage = %d \n", BatteryVoltage);
//=============================================================================================
	}
}
/*****************************************************/



