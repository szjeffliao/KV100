
#include "all.h"

//#define IapROM  0x00	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
//#define IapEPPROM  0x02	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
unsigned char code *IapAddr = 0x00;


/*****************************************************
*函数名称：void IAPWrite(unsigned char  Addr,unsigned char Value,unsigned char IAPArea)
*函数功能：IAP写初始化
*入口参数：Addr,Value,IAPArea
*出口参数：void
*****************************************************/
//IAP写操作
void IAPWrite(unsigned char  Addr,unsigned char Value,unsigned char IAPArea)
{	
	EA = 0;
	IAPDAT = Value;      //写入数据Data
	IAPADH = ((Addr>>8)&0X7F);   //写入地址的高5位
	IAPADL = Addr;               //写入地址的低8位
	
	IAPADE = IAPArea;  //IAPArea=0x00：选择ROM区操作  IAPArea=0x02：选择EEPROM区操作
	IAPKEY = 240;		   //IAP开启保护控制时间
	IAPCTL = 0x06;     //CPU hold time为2ms，写入操作命令
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	IAPADE = 0x00;      //MOVC指向ROM
	EA = 1;
}
/*****************************************************
*函数名称：unsigned char IAPRead(unsigned char Addr,unsigned char IAPArea);
*函数功能：IAP读初始化
*入口参数：Addr,IAPArea
*出口参数：void
*****************************************************/
unsigned char IAPRead(unsigned char Addr,unsigned char IAPArea)
{
	unsigned char ReadValue = 0x00;
	EA = 0;
	IAPADE = IAPArea;
	ReadValue = *(IapAddr+Addr); //读取的数据
	IAPADE = 0x00;               //MOVC指向ROM
	EA = 1;
	return ReadValue;
}

