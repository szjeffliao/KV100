#include "all.h" 

bit PrintfFlag;
bit PrintfFinishFlag;
bit UartSendFlag = 0; //�����жϱ�־λ
bit UartReceiveFlag = 0; //�����жϱ�־λ

unsigned char Counter_Value;
/*
*�������ƣ�void Uart0_Init(void)
*�������ܣ�Uart0�жϳ�ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void Uart0_Init(void)    //ѡ��Timer1��Ϊ�������źŷ�����
{
	P1CON &= 0XF3;
	P1PH |= 0X0C;	 //TX/RXΪ����������
	SCON = 0X50;     //��ʽ1�������������
	PCON |= 0X80; 
	T2CON = 0x00;    //ʹ�ö�ʱ��1��UARTʱ��
	TMOD = 0X20;     //��ʱ��1  8λ�Զ�����
	TMCON = 0X02;    //��ʱ��1   Fsys��
	TL1 = 217;		
	TH1 = 217;		 //UART ������24M�����=38400��
	TR1 = 1;		 //����Timer0
	EUART = 1;	     //����UART�ж�
	EA = 1;		     //�����ж�
}





void EnablePrintf(void)
{
	PrintfFlag = 1;
	TI = 1;


}


void DisalbePrintf(void)
{
	PrintfFlag  = 0;

}



char putchar (char c)  {

  while (!PrintfFinishFlag);

  PrintfFinishFlag = 0;

  return (SBUF = c);

}


void UartInt(void) interrupt 4
{
	if(TI)
	{
		if(PrintfFlag == 0)
		{
			TI = 0;	
			UartSendFlag = 1;	
		}			
		else
		{
				TI = 0;
				PrintfFinishFlag  = 1;
		
		}
	}
	if(RI)
	{
		RI = 0;	
		UartReceiveFlag = 1;
	}	
}

