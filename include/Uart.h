#ifndef _Uart_H_
#define _Uart_H_


void Uart0_Init(void);
void EnablePrintf(void);
void DisalbePrintf(void);

extern bit UartSendFlag; //�����жϱ�־λ
extern bit UartReceiveFlag; //�����жϱ�־λ
extern bit PrintfFlag;
extern bit PrintfFinishFlag;

extern unsigned char Counter_Value;
#endif

