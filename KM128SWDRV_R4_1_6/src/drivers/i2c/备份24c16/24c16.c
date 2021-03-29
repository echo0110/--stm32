/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      24c16.c
 * @version   1.0.4.0
 * @date      Apr-30-2016
 * @brief     I2C bus controller (I2C) driver source code.
******************************************************************************/
#include "common.h"
#include "24c16.h"
#include "gpio/gpio.h"
#include "flash.h"
uint8 IFACK;//确定ACk 有没有应答
uint8 NO_ACK;

uint8 read_byte();//读一个字节
void I2C_Check();
void  SendChar(unsigned char SendData);
void i2c_24c16 (void)
{
  
}

// //开始信号
////在时钟线为高电平时,数据线由高向低跳变. 
void StartI2C(void)
{   SCK_1;
    SDA_1;
    delay5us();// NOP;  system clock --50Mhz  1000000--0.02s
    SDA_0;
    arch_delay(50000);//NOP;
    SCK_0;
    arch_delay(50000);   //NOP;
}
//停止信号
//在时钟线为高电平时,数据线由低向高跳变.
void StopI2C(void)
{   SDA_0;
    delay5us();  //NOP;
    SCK_1;
    delay5us();// NOP;
    SDA_1;
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功

uint8 ACK(void)
{ 
    uint8 ucErrTime=0;
    SDA_1;arch_delay(50);//延时1us
    SCK_1;arch_delay(50);//延时1us
//   while(READ_SDA)
//   {
//    ucErrTime++;
//    if(ucErrTime>250)
//    {
//     StopI2C();
//     return 1;
//    }
//   
//   }
   SCK_0;//时钟输出0
   return 0;
}


void write_byte(uint8 data)//写一个字节
{
uint8 i,temp;
temp=data;
for(i=0;i<8;i++)
{
temp=temp<<1;
SCK_0;//
arch_delay(1);
if(temp&0x80) SDA_1;
else SDA_0;
arch_delay(1);
SCK_1;//拉高SCL 此时SDA上的数据稳定
arch_delay(1);
}
SCK_0;//
arch_delay(1);
SDA_1;//释放SDA总线  由从设备控制。SCL高 拉低SDA作为应答信号。
arch_delay(1);
}

uint8 read_byte()//读一个字节
{
uint8 i,k;
SCK_0;
arch_delay(1);
SDA_1;
arch_delay(1);
for(i=0;i<8;i++)
{
SCK_1;//
arch_delay(1);
k=(k<<1)|GPIO_ReadInputDataBit(PIN5); //SDA;
SCK_0;//
arch_delay(1);
}
return k;

}

//***************************************************************************  
//void write_add(uint8 address,uint8 date)//任意地址写一个字节  
//{  
//    StartI2C();//启动  
//    write_byte(0xa0);//发送从设备地址  
//    uint8  I2C_Check();//等待从设备的响应  
//    write_byte(address);//发出芯片内地址  
//    I2C_Check();//等待从设备的响应  
//    write_byte(date);//发送数据  
//    I2C_Check();//等待从设备的响应  
//    StopI2C();//停止  
//}  
//***************************************************************************  
uint8 read_add(uint8 address)//读取一个字节  
{  
    uint8 date;  
    start();//启动  
    write_byte(0xa0);//发送发送从设备地址 写操作  
    I2C_Check();//等待从设备的响应  
    write_byte(address);//发送芯片内地址  
    I2C_Check();//等待从设备的响应  
    start();//启动  
    write_byte(0xa1);//发送发送从设备地址 读操作  
    I2C_Check();//等待从设备的响应  
    date=read_byte();//获取数据  
    StopI2C();//停止  
    return date;//返回数据  
}





/*
*检测ACK应答
*/
  uint8 I2C_Check(void)
{
    uint8 result;  
    SDA_1;    //释放SDA数据总线  
    arch_delay(1);  
    SCK_1;  
    arch_delay(1);  
    result =GPIO_Get1(PIN6);  
    SCK_0;  
    return (result);   //低电平  ACk应答  
}


/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/