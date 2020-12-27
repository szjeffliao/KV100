#ifndef _Adc_H_
#define _Adc_H_






extern bit AdcFinishlag;

extern unsigned int AdcResultValue[10];

void ADC_Init(unsigned char  Channel);
//void AdcResult(unsigned char AdcChannel);
unsigned int AdcResult(unsigned char AdcChannel);



#endif

