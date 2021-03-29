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
uint8  GPIO_ReadInputDataBit(uint16 GPIO_PIN);// Reads the specified input port pin
uint8  Check(void);
//uint8 read_byte();//读一个字节
//uint8 ACK(void);
void I2C_Check();
void  SendChar(unsigned char SendData);
void i2c_24c16 (void)
{
  
}

// //开始信号
////在时钟线为高电平时,数据线由高向低跳变. 
void StartI2C(void)
{   
    GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//SDA为输出
    SCK_1;
    SDA_1;
    arch_delay(150);// NOP;  200-4us  system clock --50Mhz  1000000--0.02s
    SDA_0;
    arch_delay(150);//NOP; 200-4us   250-5us
    SCK_0;
   // arch_delay(50000);   //NOP;
}
//停止信号
//在时钟线为高电平时,数据线由低向高跳变.
void StopI2C(void)
{  
    GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//SDA为输出
    SDA_0;
    arch_delay(150); //NOP;5us
    SCK_1;
    arch_delay(150); 
    SDA_1;
    arch_delay(150);//5us 
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功

uint8 IIC_Wait_Ack(void)
{ 
    uint8 ucErrTime=0;
    GPIO_Init(GPIOF, GPIO_INP_MODE, PIN6);//SDA设置为输入
    SDA_1;arch_delay(25);//延时1us  //这个时间可能不对要用示波器看下。。。
    SCK_1;arch_delay(25);//延时1us
      while(READ_SDA)
    {  
    ucErrTime++;
    if(ucErrTime>250)
    {
     StopI2C();
     return 1;
    }
   
    }
   SCK_0;//时钟输出0
   return 0;
}
/*****************************************************************
//函数名称：IIC_Ack(void)
//功能描述：产生ack应答
//designer: niub
//Data    :2017-3-3
*****************************************************************/
void IIC_Ack(void)
{
SCK_0;
GPIO_Init(GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//配置SDA输出
SDA_0;
arch_delay(60);//延时2us
SCK_1;
arch_delay(60);//延时2us
SCK_0;
}
/*****************************************************************
//函数名称：IIC_NAck(void)
//功能描述：不产生ack应答
//designer: niub
//Data    :2017-3-3
*****************************************************************/
void IIC_NAck(void)
{
SCK_0;
GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);
SDA_1;
arch_delay(60);//延时2us
SCK_1;
arch_delay(60);
SCK_0;
}

/*****************************************************************
//函数名称：write_add(uint8 address, uint8 data)
//功能描述：指定地址写入一个数据
//designer: niub
//Data    :2017-3-3
*****************************************************************/
  void write_add(uint16 address,uint8 date)//任意地址写一个字节  
  {  
     StartI2C();//开始信号 
     
    write_byte(0xA0+((address/256)<<1));//发送器件地址 写数据   /*高位 08的话---0xA0 a9 a8 
   // write_byte(0x55);
     IIC_Wait_Ack();//等待从设备的响应  
    write_byte(address%256);//发送低字节地址 
    IIC_Wait_Ack();//等待从设备的响应 
    write_byte(date);
     IIC_Wait_Ack();
    StopI2C();//停止 
    arch_delay(250000);//延时少于10ms
    
  }  

/*****************************************************************
//函数名称：read_add(uint8 data)
//功能描述：指定地址读入一个数据
//designer: niub
//Data    :2017-3-3
*****************************************************************/
uint8 read_add(uint16 address)
{
uint8 temp=0;
write_byte(0XA0+((address/256)<<1));// 发送器件地址，高地址
 //write_byte(0x55);
 IIC_Wait_Ack();
 write_byte(address%256); //低地址
 IIC_Wait_Ack();
 StartI2C();//开始信号
 write_byte(0xA1);//进入接收模式
  IIC_Wait_Ack();
  temp=read_byte(0);
  StopI2C();//产生一个停止信号
  return temp;
}


/*****************************************************************
//函数名称：write_byte(uint8 data)
//功能描述：发送一个字节 返回从机有无应答
/1,有应答 
/0 无应答
//designer: niub
//Data    :2017-3-3
*****************************************************************/

void write_byte(uint8 txd)//发送一个字节
{
uint8 t;
GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//配置SDA为输出
//temp=txd;
SCK_0;//拉低时钟开始数据传输
for(t=0;t<8;t++)
{
if((txd&0x80)>>7)//高位在前发送数据 (因为高位在前  所以高位有数据  就SDA置1)
   SDA_1;
else
   SDA_0;
   txd<<=1;
   arch_delay(60);//延时2us
   SCK_1;
   arch_delay(60);//延时2us
   SCK_0;
  arch_delay(60);
}
}

/*****************************************************************
//函数名称：read_byte()
//功能描述：读一个字节
/ack=1,发送ack 
/ack=0, 发送nack
//designer: niub
//Data    :2017-3-3
*****************************************************************/

uint8 read_byte(unsigned char ack1)//读一个字节
{
unsigned char i,receive=0;
GPIO_Init (GPIOF, GPIO_INP_MODE, PIN6);//SDA设置为输入  //输入输出模式配错
for(i=0;i<8;i++)
{
SCK_0;//
arch_delay(60);//延时2us
SCK_1;
receive=receive<<1;
  if(READ_SDA)receive++;
  arch_delay(25);//延时1us
}
if(!ack1)
  IIC_NAck();//发送nACK
else
  IIC_Ack(); //发送ACK  
return receive;

}

 






/*
*检测ACK应答
*/
/*  uint8 I2C_Check(void)
{
    uint8 result;  
    SDA_1;    //释放SDA数据总线  
    arch_delay(1);  
    SCK_1;  
    arch_delay(1);  
    result =GPIO_Get1(PIN6);  
    SCK_0;  
    return (result);   //低电平  ACk应答  
}*/




uint8  GPIO_ReadInputDataBit(uint16 GPIO_PIN)
{
  uint8 bitstatus = 0x00;
if((GPIOF_BASE_PTR->PDIR&0x40)!=(uint32)(Bit_RESET))
{
bitstatus=(uint8)Bit_SET;
}
else
{
 bitstatus=(uint8)Bit_RESET;
}  
return bitstatus;

}


/*****************************************************************
//函数名称：uint8 24C16_Check(void)
//功能描述：检测24c16是否正常
/检测失败返回1
/检测成功返回0
//designer: niub
//Data    :2017-3-3
*****************************************************************/
uint8   Check(void)
{
	uint8 tempc;
	tempc=read_add(2047);//			   
	if(tempc==0x55)return 0;		   
	//else//
	{
            write_add(2047,0x55);
	    tempc=read_add(2047);	  
		if(tempc==0X55)
                  return 0;
	}
	return 1;											  
}

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/