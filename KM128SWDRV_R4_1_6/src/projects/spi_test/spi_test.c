/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 * spi_test.c
 ******************************************************************************/
#include "drivers.h"

/* SPI signal defines                                                         */
#define SPI0_SS         PIN2            /* PTD1 */
#define SPI0_SCK        PIN3            /* PTD2 */
#define SPI0_MOSI       PIN4            /* PTD3 */
#define SPI0_MISO       PIN5           /* PTD4 */

static void spi0_ss_callback (SS_CONTROL ss_pin); /* SS pin callback          */
uint8 spi_buff[16];                               /* Tx/Rx buffer             */
uint16 temp;
void main (void)
{
  /* SIM initialization                                                       */
  SIM_Init (SIM_MODULE_ALL_PERIPH_ON_CONFIG);
  GPIO_Init (GPIOG, GPIO_OUT_LOGIC0_MODE, SPI0_MOSI | SPI0_MISO | SPI0_SCK);
  /* SPI0 initialization                                                      */
  PORT_Init (PORTG, PORT_MODULE_ALT2_MODE, SPI0_MOSI | SPI0_MISO | SPI0_SCK);
  SPI_Init (SPI0, SPI_MODULE_DIV12_8B_POLL_CONFIG,spi0_ss_callback,PRI_LVL0,NULL);

  // GPIO_Set(GPIOG,PIN5);
 // SPI0_MISO_0;
  //uint8 temp_id=0;
  
   SPI_TxRxByte(SPI0,0x90) ;
   SPI0_TxRxByte(0x00);
   SPI0_TxRxByte(0x00);
   SPI0_TxRxByte(0x00);
   temp=(temp|SPI_GetByte(SPI0))<<8;  
//temp_id=(temp_id|SPI_GetByte(SPI0))<<8;
   temp=(temp|SPI_GetByte(SPI0));

   SPISS_1;
   
  
  spi_buff[0] = 0x90;                             /* fill Tx buffer           */
  SPI_CommByte (SPI0,spi_buff,1,NULL,0);          /* 1 Tx byte, no receiving  */
  
  spi_buff[0] = 0x05;                             /* fill Tx buffer           */
  SPI_CommByte (SPI0,spi_buff,1,spi_buff,1);      /* 1 Tx byte, 1 Rx byte     */

  spi_buff[0] = 0x03; spi_buff[1] = 0x00;         /* fill Tx buffer           */

  SPI_CommByte (SPI0,spi_buff,2,spi_buff,8);      /* 2 Tx bytes, 8 Rx bytes   */

  while(1);
}

/* callback function implementation for manual driving of slave select pin    */
static void spi0_ss_callback (SS_CONTROL ss_pin)
{
  if      (ss_pin == SS_SET  ) { GPIO_Set (GPIOD,SPI0_SS); }
  else if (ss_pin == SS_CLEAR) { GPIO_Clr (GPIOD,SPI0_SS); }
  else if (ss_pin == SS_INIT )
  {
    PORT_Init (PORTG, PORT_MODULE_LED_MODE, SPI0_SS);
    GPIO_Init (GPIOG, GPIO_OUT_LOGIC0_MODE, SPI0_SS);
    GPIO_Set  (GPIOG, SPI0_MOSI);
  }
}
