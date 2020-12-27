#ifndef _Uart_H_
#define _Uart_H_


void Uart0_Init(void);
void EnablePrintf(void);
void DisalbePrintf(void);

extern bit UartSendFlag; //发送中断标志位
extern bit UartReceiveFlag; //接收中断标志位
extern bit PrintfFlag;
extern bit PrintfFinishFlag;

extern unsigned char Counter_Value;
#endif

