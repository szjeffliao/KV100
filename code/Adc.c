
#include "all.h"


bit AdcFinishlag;



unsigned int AdcResultValue[10];

/*****************************************************
*函数名称：void ADC_Init(uint Channel)
*函数功能：ADC初始化
*入口参数：Channel
*出口参数：void
*****************************************************/
void ADC_Init(unsigned char Channel)
{
	
	ADCCON = 0X80|Channel;		//开启ADC，ADC采样频率为2M ,选择Channel位ADC采样口
	if(Channel<8)
	{
		ADCCFG0 = 1<<Channel;   //设置Channel作为采样口
	}
	else
	{
		ADCCFG1 = 1<<(Channel-8);   //设置Channel作为采样口
	}
	//ADCCON |= (0x80);
	IE |= 0X40;        //开启ADC中断
	EA = 1;
}


void ADC_Interrupt(void) interrupt 6
{
	ADCCON &= ~(0X10);  //清中断标志位
	AdcFinishlag = 1;
}


//读一次结果，需要做三次的ADC,取其平均值
unsigned int AdcResult(unsigned char AdcChannel)
{
	unsigned int ADCValue = 0;
	unsigned char i = 0;
	ADC_Init(AdcChannel);
	DelayUs(10);								//新转换通道，第一次采样，需要做一个延时
	for (i = 0; i < 10; i++)
	{
		ADCCON |= 0X40 ;   //开始ADC转换
		while(!AdcFinishlag);	         		 //等待 ADC转换完成;
			AdcFinishlag = 0;
		AdcResultValue[i] = (ADCVH<<4)+(ADCVL>>4);
	}
	for(i = 0; i < 8; i++)
	{
		ADCValue += AdcResultValue[i+2];
		
	}
	ADCValue = ADCValue / 8;
	//ADCValue = (AdcResultValue[2] + AdcResultValue[3] + AdcResultValue[4])/3;
	return ADCValue;
}


/*******************adc function*******************************************************/





