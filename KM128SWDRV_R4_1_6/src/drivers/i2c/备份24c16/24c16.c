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
uint8 IFACK;//ȷ��ACk ��û��Ӧ��
uint8 NO_ACK;

uint8 read_byte();//��һ���ֽ�
void I2C_Check();
void  SendChar(unsigned char SendData);
void i2c_24c16 (void)
{
  
}

// //��ʼ�ź�
////��ʱ����Ϊ�ߵ�ƽʱ,�������ɸ��������. 
void StartI2C(void)
{   SCK_1;
    SDA_1;
    delay5us();// NOP;  system clock --50Mhz  1000000--0.02s
    SDA_0;
    arch_delay(50000);//NOP;
    SCK_0;
    arch_delay(50000);   //NOP;
}
//ֹͣ�ź�
//��ʱ����Ϊ�ߵ�ƽʱ,�������ɵ��������.
void StopI2C(void)
{   SDA_0;
    delay5us();  //NOP;
    SCK_1;
    delay5us();// NOP;
    SDA_1;
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�

uint8 ACK(void)
{ 
    uint8 ucErrTime=0;
    SDA_1;arch_delay(50);//��ʱ1us
    SCK_1;arch_delay(50);//��ʱ1us
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
   SCK_0;//ʱ�����0
   return 0;
}


void write_byte(uint8 data)//дһ���ֽ�
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
SCK_1;//����SCL ��ʱSDA�ϵ������ȶ�
arch_delay(1);
}
SCK_0;//
arch_delay(1);
SDA_1;//�ͷ�SDA����  �ɴ��豸���ơ�SCL�� ����SDA��ΪӦ���źš�
arch_delay(1);
}

uint8 read_byte()//��һ���ֽ�
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
//void write_add(uint8 address,uint8 date)//�����ַдһ���ֽ�  
//{  
//    StartI2C();//����  
//    write_byte(0xa0);//���ʹ��豸��ַ  
//    uint8  I2C_Check();//�ȴ����豸����Ӧ  
//    write_byte(address);//����оƬ�ڵ�ַ  
//    I2C_Check();//�ȴ����豸����Ӧ  
//    write_byte(date);//��������  
//    I2C_Check();//�ȴ����豸����Ӧ  
//    StopI2C();//ֹͣ  
//}  
//***************************************************************************  
uint8 read_add(uint8 address)//��ȡһ���ֽ�  
{  
    uint8 date;  
    start();//����  
    write_byte(0xa0);//���ͷ��ʹ��豸��ַ д����  
    I2C_Check();//�ȴ����豸����Ӧ  
    write_byte(address);//����оƬ�ڵ�ַ  
    I2C_Check();//�ȴ����豸����Ӧ  
    start();//����  
    write_byte(0xa1);//���ͷ��ʹ��豸��ַ ������  
    I2C_Check();//�ȴ����豸����Ӧ  
    date=read_byte();//��ȡ����  
    StopI2C();//ֹͣ  
    return date;//��������  
}





/*
*���ACKӦ��
*/
  uint8 I2C_Check(void)
{
    uint8 result;  
    SDA_1;    //�ͷ�SDA��������  
    arch_delay(1);  
    SCK_1;  
    arch_delay(1);  
    result =GPIO_Get1(PIN6);  
    SCK_0;  
    return (result);   //�͵�ƽ  ACkӦ��  
}


/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/