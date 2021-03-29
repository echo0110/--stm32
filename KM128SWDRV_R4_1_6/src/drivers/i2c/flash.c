/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      i2c.c
 * @version   1.0.4.0
 * @date      Apr-20-2014
 * @brief     I2C bus controller (I2C) driver source code.
******************************************************************************/
#include "common.h"
#include "flash.h"
#include "spi/spi.h"
#include "gpio/gpio.h"
#include "headers/MKM34ZA5.h"
#include "i2c/24c16.h"
//#include "spi.h"
//PTF5---SCL
//PTF6---SDA
void  SST25_write(unsigned long addr,unsigned char data);

uint8 spi_buff[16];//={0x00,0x09,0x9f};
uint32 temp_id=0,temp_id1=0;
uint32 Temp=0,Temp1=0,Temp2=0,Temp3=0;
unsigned char SST25_buffer[4096];

//  unsigned char  SendByte(unsigned char byte)
//{
// 
//
//  // while(SPI_TxCmpl(SPI0)==0x20); //�жϷ��ͼĴ���������û�з�����   //true ��fause  ������  false������������
//   SPI_PutByte(SPI0,byte);//���ͼĴ���д���͵�����
//    //while(SPI_RxFull(SPI0)==0);//�жϽ��ռĴ�����û���յ����� 0�Ǵ���û�н��յ�����   1���յ����ݺ���1
//     return SPI_TxRxByte(SPI0,byte);//���ؽ��յ�������
//}



//������APi
 unsigned   char SST25_read(unsigned long addr)
{
 unsigned char i=0;
 uint32  max_addr=0x1fffff;
 
 if(addr>max_addr)  return(0);//
 SPI0_TxRxByte(0x03);//send read  commmand
 SPI0_TxRxByte(addr&0xffffff>>16);//�ȷ��͸�8λ
 SPI0_TxRxByte(addr&0xffff>>8);
 SPI0_TxRxByte(addr&0xff);//��8λ
 i=SPI0_TxRxByte(0xff);//�������ֽ� �Զ�ȡ����
 SPISS_1;
 return(i);
}

//д����APi
void  SST25_write(unsigned long addr,unsigned char data)
{
  uint8 temp=0,statval=0;
  sect_clr(addr);//����ҳ
  //SST25_E4K(0);
  wsr();//ʹ��д״̬
  wen();//дʹ��
 SPISS_0;
 temp=SPI0_TxRxByte(0x05);//Read-Status-Register   //0x05
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x50);//Enable-Write-Status-Registe
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x01);//Write-Status-Register 
 SPI0_TxRxByte(0);//Block Protection  ʹflashȫ����д
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x06);//write enable
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x02);//To Program One Data Byte   �����ֽ���д
 SPI0_TxRxByte(addr&0xffffff>>16);//����3�ֽڵĵ�ַ��Ϣ
 SPI0_TxRxByte(addr&0xffff>>8);
 SPI0_TxRxByte(addr&0xff);
 SPI0_TxRxByte(data);//����Ҫ��д������
 SPISS_1;
 do
 {
   SPISS_0;
  statval=SPI0_TxRxByte(0x05);//���������״̬�Ĵ�����ֵ
  SPISS_1;
  
 }while(statval==0x03);  //һֱ�ȴ� ֱ��оƬ����
  SPISS_0;
  SPI0_TxRxByte(0x06);//����дʹ��
  SPISS_1;
  SPISS_0;
  SPI0_TxRxByte(0x50);//Enable-Write-Status-Register 
  SPISS_1;
  SPISS_0;
  SPI0_TxRxByte(0x01);
  SPI0_TxRxByte(temp);//�ָ�״̬�Ĵ�����������Ϣ
  SPISS_1;
}
   





/*****************************************************************
//�������ƣ�SST25_ReadID
//����������SST25VF016B��ID��--Jedec_ID
//designer: niub
//Data    :2017-2-10
*****************************************************************/
unsigned long SST25_ReadID(void)
{

//unsigned long temp_id=0;
SPISS_0;
//SPI0_MISO_0;
//SPI0_MOSI_0;
//spi_buff[0]=0x90;
//SPI0_BASE_PTR->S=0x03;
//SPI0_BASE_PTR->DL=0x01;
//SPI0_BASE_PTR->DL=0x01;
//SPI0_BASE_PTR->DL=0x01;
//SPI0_BASE_PTR->DL=0x01;
//SPI0_BASE_PTR->BR=0x04;
//SPI0_BASE_PTR->BR=0x04;
//SPI0_BASE_PTR->BR=0x04;
//SPI0_BASE_PTR->C1=0x05;
//SPI_CommByte(SPI0,spi_buff,1,NULL,0);//���Ͷ��豸ID���� /* 1 Tx byte, no receiving  */
//spi_buff[0]=0x00;
//SPI_CommByte(SPI0,spi_buff,1,NULL,0);
//SPI_CommByte(SPI0,spi_buff,1,NULL,0);
//SPI_CommByte(SPI0,spi_buff,1,NULL,0);
SPI0_TxRxByte(0x90);
Temp1=SPI0_TxRxByte(0x00);
Temp2=SPI0_TxRxByte(0x00);
Temp3=SPI0_TxRxByte(0x00);
temp_id=SPI0_TxRxByte(0);//BF
temp_id1=SPI0_TxRxByte(0);//41
//temp_id|=SPI0_TxRxByte(0xff)<<8;
//temp_id|=SPI0_TxRxByte(0xff);
//temp_id=(temp_id|SPI_GetByte(SPI0))<<8;  
////temp_id=(temp_id|SPI_GetByte(SPI0))<<8;
//temp_id=(temp_id|SPI_GetByte(SPI0));

SPISS_1;
Temp= (Temp1<< 16)|(Temp2<<8)|Temp3;
return Temp;
}
/******************************
*���ƣ�void sect_clr(unsigned long a1)
*���ܣ�ҳ����
*********************************/
void sect_clr(unsigned long a1)
{
wsr();
wen();
SPISS_0;	  
SPI0_TxRxByte(0x20);
SPI0_TxRxByte((a1&0xffffff)>>16);          //addh
SPI0_TxRxByte((a1&0xffff)>>8);          //addl 
SPI0_TxRxByte(a1&0xff);                 //wtt
SPISS_1;;
wip();
}
/****************************************************************************
*����wsr(void)
* ���ܣ�д״̬
****************************************************************************/ 
void wsr(void){	
SPISS_0;
SPI0_TxRxByte(0x50);
SPISS_1; 
SPISS_0;
SPI0_TxRxByte(0x01);
SPI0_TxRxByte(0x00); 
SPISS_1;
wip();
}
/****************************************************************************
* ���ƣ�void wip(void)
* ���ܣ�æ���

****************************************************************************/ 
void wip(void){
	unsigned char a=1;
	while((a&0x01)==1) a=rdsr();	

}
/****************************************************************************
* ���ƣ�unsigned char rdsr(void)
* ���ܣ� ��״̬�Ĵ���

****************************************************************************/ 
unsigned char rdsr(void){
	unsigned char busy=0;
	SPISS_0;
        SPI0_TxRxByte(0x05);
     //busy=5;
        //busy=SPI0_TxRxByte(0);
	busy = SPI_Flash_ReadByte();
	SPISS_1;
	return(busy);
	
}
/****************************************************************************
* ���ƣ�void wen(void)
* ���ܣ�дʹ��
*
*
****************************************************************************/ 
void wen(void)
{
SPISS_0;
SPI0_TxRxByte(0x06);
SPISS_1;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
uint8 SPI_Flash_ReadByte(void)
{
  return (SPI0_TxRxByte(Dummy_Byte));
}



/*****************************************************************
//�������ƣ�unsigned char SST25_E4k(unsigned short)
//��������������ָ����������
//designer: niub
//Data    :2017-3-2
*****************************************************************/

unsigned char SST25_E4K(unsigned short sec1)
{
unsigned long temp_4k=0,StatRgVal=0;
uint32  SechAddr=0;
if(sec1>511)
{
return(0);
}
SPISS_0;
temp_4k=SPI0_TxRxByte(0x05);//�������״̬�Ĵ�����ֵ
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x50);//ʹ״̬�Ĵ�����д
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x50);//����д״̬�Ĵ���ָ��
SPI0_TxRxByte(0);//��0BPxλ  ʹflashȫ����д
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x06);//����дʹ������
SPISS_1;
SechAddr=sec1*4096;//����Ҫ�ġ�����
SPISS_0;
SPI0_TxRxByte(0x20);//���Ͳ�������ָ��
SPI0_TxRxByte(SechAddr&0xffffff>>16);
SPI0_TxRxByte(SechAddr&0xffff>>8);
SPI0_TxRxByte(SechAddr);
SPISS_1;
do
{
SPISS_0; 
SPI0_TxRxByte(0x05);//�������״̬�Ĵ���ֵ
SPISS_1;
}while(StatRgVal==0x03); //�ȴ�оƬ����

//�������� �ָ�״̬�Ĵ�����ֵ
SPISS_0; 
SPI0_TxRxByte(0x06);
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x05);//ʹ״̬�Ĵ�����д
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x01);
SPI0_TxRxByte(temp_4k);
SPISS_1;
return 1;
}


/****************************************************************************
* ���ƣ�void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize)
* ����ҳд
* ��ڲ��� uint32_t addr--ҳ  uint8 *readbuff--����  uint16_t BlockSize-- ����  
* 
* 
* 
****************************************************************************/  
void SST25_W_BLOCK(uint32 addr, uint8 *readbuff, uint16 BlockSize){
	unsigned int i=0,a2;
	sect_clr(addr);   								  //��?3y��3		  
	wsr();
  	wen();	
	SPISS_0;   
	SPI0_TxRxByte(0xad);
	SPI0_TxRxByte((addr&0xffffff)>>16);
	SPI0_TxRxByte((addr&0xffff)>>8);
	SPI0_TxRxByte(addr&0xff);
  	SPI0_TxRxByte(readbuff[0]);
	SPI0_TxRxByte(readbuff[1]);
        SPISS_1; 
	i=2;
	while(i<BlockSize){
		a2=120;
		while(a2>0) a2--;
		SPISS_0; 
		SPI0_TxRxByte(0xad);
		SPI0_TxRxByte(readbuff[i++]);
		SPI0_TxRxByte(readbuff[i++]);
		SPISS_1; 
	}
	
	a2=100;
	while(a2>0) a2--;
	wdis();	
        SPISS_0; 	
	wip();
}


/****************************************************************************
* ���ƣ�void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize)
* ���ܣ�ҳ��
*            unsigned long addr--ҳ  unsigned char *readbuff--����  unsigned int BlockSize--����
* 
* 
* 
****************************************************************************/  
void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize){
	unsigned int i=0; 	
	SPISS_0; 
	SPI0_TxRxByte(0x0b);
	SPI0_TxRxByte((addr&0xffffff)>>16);
	SPI0_TxRxByte((addr&0xffff)>>8);
	SPI0_TxRxByte(addr&0xff);
	SPI0_TxRxByte(0);
	//while(i<BlockSize){	
		readbuff[4]=SPI_Flash_ReadByte();
		
		//i++;
	//}
	SPISS_1; 	 	
}

/****************************************************************************
* ���ƣ�void wdis(void)
* ���ܣ�д��ֹ
* 
****************************************************************************/ 
void wdis(void){

	SPISS_0;  
	SPI0_TxRxByte(0x04); 
	SPISS_1;  
	wip();
	
}	

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/

