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
//  // while(SPI_TxCmpl(SPI0)==0x20); //判断发送寄存器数据有没有发送完   //true 和fause  待测试  false发送完跳出。
//   SPI_PutByte(SPI0,byte);//向发送寄存器写发送的数据
//    //while(SPI_RxFull(SPI0)==0);//判断接收寄存器有没有收到数据 0是代表没有接收到数据   1接收到数据后置1
//     return SPI_TxRxByte(SPI0,byte);//返回接收到的数据
//}



//读数据APi
 unsigned   char SST25_read(unsigned long addr)
{
 unsigned char i=0;
 uint32  max_addr=0x1fffff;
 
 if(addr>max_addr)  return(0);//
 SPI0_TxRxByte(0x03);//send read  commmand
 SPI0_TxRxByte(addr&0xffffff>>16);//先发送高8位
 SPI0_TxRxByte(addr&0xffff>>8);
 SPI0_TxRxByte(addr&0xff);//低8位
 i=SPI0_TxRxByte(0xff);//发送哑字节 以读取数据
 SPISS_1;
 return(i);
}

//写数据APi
void  SST25_write(unsigned long addr,unsigned char data)
{
  uint8 temp=0,statval=0;
  sect_clr(addr);//擦除页
  //SST25_E4K(0);
  wsr();//使能写状态
  wen();//写使能
 SPISS_0;
 temp=SPI0_TxRxByte(0x05);//Read-Status-Register   //0x05
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x50);//Enable-Write-Status-Registe
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x01);//Write-Status-Register 
 SPI0_TxRxByte(0);//Block Protection  使flash全区可写
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x06);//write enable
 SPISS_1;
 SPISS_0;
 SPI0_TxRxByte(0x02);//To Program One Data Byte   发送字节烧写
 SPI0_TxRxByte(addr&0xffffff>>16);//发送3字节的地址信息
 SPI0_TxRxByte(addr&0xffff>>8);
 SPI0_TxRxByte(addr&0xff);
 SPI0_TxRxByte(data);//发送要烧写的数据
 SPISS_1;
 do
 {
   SPISS_0;
  statval=SPI0_TxRxByte(0x05);//保存读到的状态寄存器的值
  SPISS_1;
  
 }while(statval==0x03);  //一直等待 直到芯片空闲
  SPISS_0;
  SPI0_TxRxByte(0x06);//发送写使能
  SPISS_1;
  SPISS_0;
  SPI0_TxRxByte(0x50);//Enable-Write-Status-Register 
  SPISS_1;
  SPISS_0;
  SPI0_TxRxByte(0x01);
  SPI0_TxRxByte(temp);//恢复状态寄存器的设置信息
  SPISS_1;
}
   





/*****************************************************************
//函数名称：SST25_ReadID
//功能描述：SST25VF016B的ID号--Jedec_ID
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
//SPI_CommByte(SPI0,spi_buff,1,NULL,0);//发送读设备ID命令 /* 1 Tx byte, no receiving  */
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
*名称：void sect_clr(unsigned long a1)
*功能：页擦除
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
*名称wsr(void)
* 功能：写状态
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
* 名称：void wip(void)
* 功能：忙检测

****************************************************************************/ 
void wip(void){
	unsigned char a=1;
	while((a&0x01)==1) a=rdsr();	

}
/****************************************************************************
* 名称：unsigned char rdsr(void)
* 功能： 读状态寄存器

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
* 名称：void wen(void)
* 功能：写使能
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
//函数名称：unsigned char SST25_E4k(unsigned short)
//功能描述：擦除指定的扇区号
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
temp_4k=SPI0_TxRxByte(0x05);//保存读的状态寄存器的值
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x50);//使状态寄存器可写
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x50);//发送写状态寄存器指令
SPI0_TxRxByte(0);//清0BPx位  使flash全区可写
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x06);//发送写使能命令
SPISS_1;
SechAddr=sec1*4096;//可能要改。。。
SPISS_0;
SPI0_TxRxByte(0x20);//发送擦除扇区指令
SPI0_TxRxByte(SechAddr&0xffffff>>16);
SPI0_TxRxByte(SechAddr&0xffff>>8);
SPI0_TxRxByte(SechAddr);
SPISS_1;
do
{
SPISS_0; 
SPI0_TxRxByte(0x05);//保存读的状态寄存器值
SPISS_1;
}while(StatRgVal==0x03); //等待芯片空闲

//擦除结束 恢复状态寄存器的值
SPISS_0; 
SPI0_TxRxByte(0x06);
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x05);//使状态寄存器可写
SPISS_1;
SPISS_0;
SPI0_TxRxByte(0x01);
SPI0_TxRxByte(temp_4k);
SPISS_1;
return 1;
}


/****************************************************************************
* 名称：void SST25_W_BLOCK(uint32_t addr, u8 *readbuff, uint16_t BlockSize)
* 功能页写
* 入口参数 uint32_t addr--页  uint8 *readbuff--数组  uint16_t BlockSize-- 长度  
* 
* 
* 
****************************************************************************/  
void SST25_W_BLOCK(uint32 addr, uint8 *readbuff, uint16 BlockSize){
	unsigned int i=0,a2;
	sect_clr(addr);   								  //é?3yò3		  
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
* 名称：void SST25_R_BLOCK(unsigned long addr, unsigned char *readbuff, unsigned int BlockSize)
* 功能：页读
*            unsigned long addr--页  unsigned char *readbuff--数组  unsigned int BlockSize--长度
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
* 名称：void wdis(void)
* 功能：写禁止
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

