
#include "all.h"


bit AdcFinishlag;



unsigned int AdcResultValue[10];

/*****************************************************
*�������ƣ�void ADC_Init(uint Channel)
*�������ܣ�ADC��ʼ��
*��ڲ�����Channel
*���ڲ�����void
*****************************************************/
void ADC_Init(unsigned char Channel)
{
	
	ADCCON = 0X80|Channel;		//����ADC��ADC����Ƶ��Ϊ2M ,ѡ��ChannelλADC������
	if(Channel<8)
	{
		ADCCFG0 = 1<<Channel;   //����Channel��Ϊ������
	}
	else
	{
		ADCCFG1 = 1<<(Channel-8);   //����Channel��Ϊ������
	}
	//ADCCON |= (0x80);
	IE |= 0X40;        //����ADC�ж�
	EA = 1;
}


void ADC_Interrupt(void) interrupt 6
{
	ADCCON &= ~(0X10);  //���жϱ�־λ
	AdcFinishlag = 1;
}


//��һ�ν������Ҫ�����ε�ADC,ȡ��ƽ��ֵ
unsigned int AdcResult(unsigned char AdcChannel)
{
	unsigned int ADCValue = 0;
	unsigned char i = 0;
	ADC_Init(AdcChannel);
	DelayUs(10);								//��ת��ͨ������һ�β�������Ҫ��һ����ʱ
	for (i = 0; i < 10; i++)
	{
		ADCCON |= 0X40 ;   //��ʼADCת��
		while(!AdcFinishlag);	         		 //�ȴ� ADCת�����;
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





