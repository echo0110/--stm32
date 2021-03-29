/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 * i2c_test.c
 ******************************************************************************/
#include "drivers.h"
#include "i2c/flash.h"
#include "stdio.h"
#include "i2c/24c16.h"

#define BYTES (uint8)5                    /* number of bytes to read or write */
/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))
static uint8 volatile ui8_data[BYTES];
static uint8 i;
uint32 temp_read;
uint8  temp_read1;
uint8  TXBuffer1[]="this is SPI TEST";

const uint8 TxBuffer1[]={"9"};//要写入到SPI FLASH的字符串数组
static void spi0_ss_callback (SS_CONTROL ss_pin); /* SS pin callback          */



/* data type definitions                                                      */
volatile char c;
 
void main (void)
{
  /*************************** INITIALIZING SECTION ***************************/
  /* initialize SIM module                                                    */
  SIM_Init  (SIM_MODULE_ALL_PERIPH_ON_CONFIG);
// /* route core clock to PTF7                                                 */
//  SIM_SelClkout (CLKOUT_SRC2);
//  PORT_Init (PORTF,PORT_MODULE_ALT3_MODE,PIN7);
//  /* clock mode 2:1:1, 48MHz                                                  */
  SIM_SetClkMode (SYSCLK_MODE1);
  SIM_SetClkDiv  (SYSCLK_DIV1);
  SIM_EnableModule(PORTF);
  FLL_Init(FLL_MODULE_FEE_48MHZ_CONFIG);
   
  /* PORTs initialize, PTD7_SCL, PTE0_SDA                                     */
  // PORT_Init (PORTF, PORT_MODULE_ALT3_MODE, PIN6|PIN5);
 // PORT_Init (PORTF, PORT_MODULE_ALT3_MODE, PIN5);
   PORT_Init (PORTF, PORT_MODULE_LED_MODE, PIN6|PIN5);//配置SCL   SDA为输出
   GPIO_Init (GPIOF, GPIO_OUT_LOGIC0_MODE, PIN6|PIN5);//配置SCL   SDA为输出

    /* I2C module initialization (100 kBps @24MHz)                              */
    I2C_Init(I2C1, I2C_MODULE_IRQ_DI_CONFIG(0x1f));
     SCK_1;
     SDA_1;
  
    /* UART0 init 9600bd                                                        */
    PORT_Init (PORTF, PORT_MODULE_ALT4_MODE, PIN3|PIN4);
    UART_Init (UART0, UART_MODULE_POLLMODE_CONFIG(9600,24e6));
    
    
     //  PTD4初始化用于拉高485 
    PORT_Init (PORTD, PORT_MODULE_LED_MODE, PIN4);
    GPIO_Init (GPIOD, GPIO_OUT_LOGIC0_MODE, PIN4);
  /* SPI0 initialization                                                      */
 //   PORT_Init (PORTG, PORT_MODULE_ALT2_MODE, SPI0_MOSI | SPI0_MISO | SPI0_SCK );
 //   SPI_Init (SPI0, SPI_MODULE_DIV12_8B_POLL_CONFIG,spi0_ss_callback,PRI_LVL0,NULL);
      /* 将测试用的数组写到缓存区里 */
//   for(i=0; i<TxBufferSize1;i++) SST25_buffer[i]=TxBuffer1[i]; 
 while(1)
 {
   /************flash  test programm***********/
 /*   uint8 a=0;
    SST25_ReadID();
   // SST25_write(0x00,2);//向地址0写入1数据 
    SST25_W_BLOCK(0, SST25_buffer,4096);	  
    arch_delay(50000);//1ms
     //temp_read=SST25_read(0);
   SST25_R_BLOCK(0, SST25_buffer,4096);*/
   
   /************i2c  test programm***********/
   //  StartI2C();
    //Check();
 //     write_add(0,0x88);
    //  arch_delay(50000);//1ms
   //  temp_read1=read_add(0);
 // SCK_1;
 // arch_delay(250000);//150--5us  25--1us  60-2us
 // SCK_0;
 // arch_delay(250000);
  //  arch_delay(250);
   
     
   //  spi_buff[1]=(uint8)SST25_read(1);
   // spi_buffer[0]=SST25_ReadID();
    //  arch_delay(50000);//1ms  
       //spi_buffer[0]=SST25_read(0); 
 //UART_PutChar(UART0,temp_id);
  // NOP;  system clock --50Mhz  1000000--0.0002s
   //  arch_delay(2000000);//1s
 //  GPIO_Set(GPIOD,PIN4);
 UART_PutChar(UART0,'b');
  //GPIO_Set (FGPIOF, PIN3);
    
    
 //   while (!UART_RxFull(UART0));
 //       c=UART_GetChar(UART0);

   //GPIO_Clr (FGPIOF, PIN3);
  //c = UART_GetChar (UART0);
 //printf("c=%d\n",c);
 // printf("b\n");
 }
  
  
  
  
  
  
} 
  
/* callback function implementation for manual driving of slave select pin    */
static void spi0_ss_callback (SS_CONTROL ss_pin)
{
  if      (ss_pin == SS_SET  ) { GPIO_Set (GPIOG,SPI0_SS); }
  else if (ss_pin == SS_CLEAR) { GPIO_Clr (GPIOG,SPI0_SS); }
  else if (ss_pin == SS_INIT )
  {
    PORT_Init (PORTG, PORT_MODULE_LED_MODE, SPI0_SS);
    GPIO_Init (GPIOG, GPIO_OUT_LOGIC0_MODE, SPI0_SS);
    GPIO_Set  (GPIOG, SPI0_SS);
  }
}  
  
  
  
  
  
  
  
  
  
  
  
  
  /****************************** WRITING SECTION *****************************/
//  I2C_SetTxMode(I2C0);                 /* Set TX mode                         */
//  I2C_StartSignal(I2C0);               /* Generate START on I2C bus           */
//
//  I2CWRITE(0xA0);                      /* 0xA0= device (EEPROM) select byte   */
//  I2CWRITE(0x00);                      /* 0x00= device starting address       */
//
//  for (i=0; i<BYTES; i++)              /* Writing i-bytes to the memory       */
//    I2CWRITE(2*i);                     /* Writing byte = address * 2          */
//
//  I2C_StopSignal(I2C0);                /* Generate STOP signal on I2C bus     */
//  arch_delay(1000000);                 /* Bus recovering between write/read   */
//
//  /****************************** READING SECTION *****************************/
//  I2C_SetTxMode(I2C0);                 /* Set TX mode                         */
//  I2C_StartSignal(I2C0);               /* Generate START on I2C bus           */
//
//  I2CWRITE(0xA0);                      /* 0xA0= device (EEPROM) select byte   */
//  I2CWRITE(0x00);                      /* 0x00= device starting address       */
//
//  I2C_RepeatStartSignal(I2C0);         /* Generate Repeat START on I2C bus    */
//  while(!(I2C_GetTcFlag(I2C0)));       /* Waiting for bus releasing           */
//
//  I2CWRITE(0xA1);                      /* 0xA1= activate device reading mode  */
//
//  I2C_SetRxMode(I2C0);                 /* Set to RX Mode                      */
//  (void) I2C_RdData(I2C0);             /* Dummy reading                       */
//
//  for (i=0; i<BYTES; i++)              /* Reading i-bytes from the memory     */
//  {
//    if (i == (BYTES-1))                /* Last byte?                          */
//    {
//      I2C_SetNackMode(I2C0);           /* No acknowledge is needed now        */
//      while(I2C_GetIsrFlag(I2C0) == 0);
//      I2C_StopSignal(I2C0);            /* Generate STOP signal on I2C bus     */
//      ui8_data[i] = I2C_RdData(I2C0);  /* Reading the last byte               */
//      I2C_ClrIsrFlag(I2C0);
//      I2C_ClrNackMode(I2C0);           /* next acknowledge is allowed         */
//    }
//    else
//    {
//      I2CREAD(ui8_data[i]);            /* Reading the i-th byte               */
//    }
//  }

  /* main loop - check the results                                            */
  //while(1);

