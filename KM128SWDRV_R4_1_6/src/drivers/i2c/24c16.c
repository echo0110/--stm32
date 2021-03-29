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
uint8  GPIO_ReadInputDataBit(uint16 GPIO_PIN);// Reads the specified input port pin
uint8  Check(void);
//uint8 read_byte();//��һ���ֽ�
//uint8 ACK(void);
void I2C_Check();
void  SendChar(unsigned char SendData);
void i2c_24c16 (void)
{
  
}

// //��ʼ�ź�
////��ʱ����Ϊ�ߵ�ƽʱ,�������ɸ��������. 
void StartI2C(void)
{   
    GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//SDAΪ���
    SCK_1;
    SDA_1;
    arch_delay(150);// NOP;  200-4us  system clock --50Mhz  1000000--0.02s
    SDA_0;
    arch_delay(150);//NOP; 200-4us   250-5us
    SCK_0;
   // arch_delay(50000);   //NOP;
}
//ֹͣ�ź�
//��ʱ����Ϊ�ߵ�ƽʱ,�������ɵ��������.
void StopI2C(void)
{  
    GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//SDAΪ���
    SDA_0;
    arch_delay(150); //NOP;5us
    SCK_1;
    arch_delay(150); 
    SDA_1;
    arch_delay(150);//5us 
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�

uint8 IIC_Wait_Ack(void)
{ 
    uint8 ucErrTime=0;
    GPIO_Init(GPIOF, GPIO_INP_MODE, PIN6);//SDA����Ϊ����
    SDA_1;arch_delay(25);//��ʱ1us  //���ʱ����ܲ���Ҫ��ʾ�������¡�����
    SCK_1;arch_delay(25);//��ʱ1us
      while(READ_SDA)
    {  
    ucErrTime++;
    if(ucErrTime>250)
    {
     StopI2C();
     return 1;
    }
   
    }
   SCK_0;//ʱ�����0
   return 0;
}
/*****************************************************************
//�������ƣ�IIC_Ack(void)
//��������������ackӦ��
//designer: niub
//Data    :2017-3-3
*****************************************************************/
void IIC_Ack(void)
{
SCK_0;
GPIO_Init(GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//����SDA���
SDA_0;
arch_delay(60);//��ʱ2us
SCK_1;
arch_delay(60);//��ʱ2us
SCK_0;
}
/*****************************************************************
//�������ƣ�IIC_NAck(void)
//����������������ackӦ��
//designer: niub
//Data    :2017-3-3
*****************************************************************/
void IIC_NAck(void)
{
SCK_0;
GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);
SDA_1;
arch_delay(60);//��ʱ2us
SCK_1;
arch_delay(60);
SCK_0;
}

/*****************************************************************
//�������ƣ�write_add(uint8 address, uint8 data)
//����������ָ����ַд��һ������
//designer: niub
//Data    :2017-3-3
*****************************************************************/
  void write_add(uint16 address,uint8 date)//�����ַдһ���ֽ�  
  {  
     StartI2C();//��ʼ�ź� 
     
    write_byte(0xA0+((address/256)<<1));//����������ַ д����   /*��λ 08�Ļ�---0xA0 a9 a8 
   // write_byte(0x55);
     IIC_Wait_Ack();//�ȴ����豸����Ӧ  
    write_byte(address%256);//���͵��ֽڵ�ַ 
    IIC_Wait_Ack();//�ȴ����豸����Ӧ 
    write_byte(date);
     IIC_Wait_Ack();
    StopI2C();//ֹͣ 
    arch_delay(250000);//��ʱ����10ms
    
  }  

/*****************************************************************
//�������ƣ�read_add(uint8 data)
//����������ָ����ַ����һ������
//designer: niub
//Data    :2017-3-3
*****************************************************************/
uint8 read_add(uint16 address)
{
uint8 temp=0;
write_byte(0XA0+((address/256)<<1));// ����������ַ���ߵ�ַ
 //write_byte(0x55);
 IIC_Wait_Ack();
 write_byte(address%256); //�͵�ַ
 IIC_Wait_Ack();
 StartI2C();//��ʼ�ź�
 write_byte(0xA1);//�������ģʽ
  IIC_Wait_Ack();
  temp=read_byte(0);
  StopI2C();//����һ��ֹͣ�ź�
  return temp;
}


/*****************************************************************
//�������ƣ�write_byte(uint8 data)
//��������������һ���ֽ� ���شӻ�����Ӧ��
/1,��Ӧ�� 
/0 ��Ӧ��
//designer: niub
//Data    :2017-3-3
*****************************************************************/

void write_byte(uint8 txd)//����һ���ֽ�
{
uint8 t;
GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6);//����SDAΪ���
//temp=txd;
SCK_0;//����ʱ�ӿ�ʼ���ݴ���
for(t=0;t<8;t++)
{
if((txd&0x80)>>7)//��λ��ǰ�������� (��Ϊ��λ��ǰ  ���Ը�λ������  ��SDA��1)
   SDA_1;
else
   SDA_0;
   txd<<=1;
   arch_delay(60);//��ʱ2us
   SCK_1;
   arch_delay(60);//��ʱ2us
   SCK_0;
  arch_delay(60);
}
}

/*****************************************************************
//�������ƣ�read_byte()
//������������һ���ֽ�
/ack=1,����ack 
/ack=0, ����nack
//designer: niub
//Data    :2017-3-3
*****************************************************************/

uint8 read_byte(unsigned char ack1)//��һ���ֽ�
{
unsigned char i,receive=0;
GPIO_Init (GPIOF, GPIO_INP_MODE, PIN6);//SDA����Ϊ����  //�������ģʽ���
for(i=0;i<8;i++)
{
SCK_0;//
arch_delay(60);//��ʱ2us
SCK_1;
receive=receive<<1;
  if(READ_SDA)receive++;
  arch_delay(25);//��ʱ1us
}
if(!ack1)
  IIC_NAck();//����nACK
else
  IIC_Ack(); //����ACK  
return receive;

}

 






/*
*���ACKӦ��
*/
/*  uint8 I2C_Check(void)
{
    uint8 result;  
    SDA_1;    //�ͷ�SDA��������  
    arch_delay(1);  
    SCK_1;  
    arch_delay(1);  
    result =GPIO_Get1(PIN6);  
    SCK_0;  
    return (result);   //�͵�ƽ  ACkӦ��  
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
//�������ƣ�uint8 24C16_Check(void)
//�������������24c16�Ƿ�����
/���ʧ�ܷ���1
/���ɹ�����0
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