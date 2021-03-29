/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      i2c.h
 * @version   1.0.4.0
 * @date      Feb-02-2015
 * @brief     I2C bus comtroller (I2C) driver header file.
 ******************************************************************************/
#ifndef __flash_H
#define __flash_H

/* SPi  signal defines */

#define SPI0_SCK        PIN3/*PTG3*/
#define SPI0_MOSI       PIN4/*PTG4*/
#define SPI0_MISO       PIN5 /*PTG5 */
#define SPI0_SS         PIN2
//#define SPI0_SS         PIN1/*PTD1*/

#define    SPISS_1     GPIO_Set(GPIOG,PIN2)     
#define    SPISS_0     GPIO_Clr(GPIOG,PIN2)
#define    Dummy_Byte   0
#define SPI0_MISO_0    GPIO_Clr(GPIOG,PIN5)
#define SPI0_MISO_1    GPIO_Set(GPIOG,PIN5)
#define SPI0_MOSI_1    GPIO_Set(GPIOG,PIN4)
#define SPI0_MOSI_0    GPIO_Clr(GPIOG,PIN4)





/******************************************************************************
 * Configuration structure definition                                         *
 ******************************************************************************/

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
//extern void 24c16_Init(void);

extern  unsigned  char SST25_read(unsigned long addr);
extern  unsigned char SendByte(unsigned char byte);
extern  void SST25_write(unsigned long addr,unsigned char data);//FlashÐ´Êý¾Ý
extern unsigned long SST25_ReadID(void);
extern void wsr(void);
extern void wen(void);
extern void wip(void);
extern unsigned char rdsr(void);
extern void sect_clr(unsigned long a1);
extern uint8 SPI_Flash_ReadByte(void);
extern uint8 spi_buff[16];//={0x00,0x09,0x9f};
extern uint32 temp_id,temp_id1;
extern uint32 Temp,Temp1,Temp2,Temp3;
extern unsigned char SST25_E4K(unsigned short sec1);
extern void SST25_W_BLOCK(uint32 addr, uint8 *readbuff, uint16 BlockSize);//flash Ð´Ò»Ò³
extern void SST25_R_BLOCK(unsigned long addr,unsigned char *readbuff,unsigned int BlockSize);
extern void wdis(void);//Ð´½ûÖ¹
extern unsigned char SST25_buffer[4096];

//extern uint8  GPIO_Get1(gpio,mask);
//extern void i2cx_isr (void);
//extern void bit SendChar(unsigned char SendData);//send  a  byte data



#endif /* __flash_H */
