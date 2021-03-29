/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      i2c.h
 * @version   1.0.4.0
 * @date      Feb-02-2015
 * @brief     I2C bus comtroller (I2C) driver header file.
 ******************************************************************************/
#ifndef __24C16_H
#define __24C16_H

typedef enum
{
Bit_RESET=0,
Bit_SET
}BitAction;

#define    SCK_1       GPIO_Set(GPIOF,PIN5)  
#define    SCK_0       GPIO_Clr(GPIOF,PIN5)
#define    SDA_1       GPIO_Set(GPIOF,PIN6)
#define    SDA_0       GPIO_Clr(GPIOF,PIN6)
#define    READ_SDA    GPIO_ReadInputDataBit(uint16 GPIO_PIN);
//#define 



#define    delay5us()      arch_delay(50000)

//写指令   0xA0----10100000
//读指令   0xA1----10100001

/******************************************************************************
 * Configuration structure definition                                         *
 ******************************************************************************/

/******************************************************************************
 * interrupt function prototypes                                              *
 ******************************************************************************/
//extern void 24c16_Init(void);
extern void init();  //总线初始化
extern void i2c_24c16 (void);
extern void i2cx_isr (void);
extern void StartI2C(void);//I2c  start signal
extern void StopI2C(void);//i2c stop sigal


extern void ACK(void);
extern void NAK(void);
//extern void write_add(uint8 address,uint8 date);
extern void write_byte(uint8 data);
extern  uint8 read_byte();//读一个字节
extern  uint8 read_add(uint8 address);//读取一个字节 
extern  void I2C_Check();

//extern  write_add(uint8 address,uint8 date);//任意地址写一个字节


 

#endif /* __24c16_H */
