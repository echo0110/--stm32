/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 * uart_test.c
 ******************************************************************************/
#include "drivers.h"

void main (void)
{
 char c;
 uint8 i=1;

  SIM_Init  (SIM_MODULE_ALL_PERIPH_ON_CONFIG);

  /* route core clock to PTF7                                                 */
  SIM_SelClkout (CLKOUT_SRC2);
  PORT_Init (PORTF,PORT_MODULE_ALT3_MODE,PIN7);

  /* clock mode 1:1:1, 24MHz                                                  */
  SIM_SetClkMode (SYSCLK_MODE0);
  SIM_SetClkDiv  (SYSCLK_DIV1);
  FLL_Init(FLL_MODULE_FEE_24MHZ_CONFIG);

//  /* UART1 init 9600bd                                                        */
//  PORT_Init (PORTF, PORT_MODULE_ALT4_MODE, PIN3|PIN4);
//  UART_Init (UART0, UART_MODULE_POLLMODE_CONFIG(9600,24e6));
  
   //  PTD4初始化用于拉高485 
    PORT_Init (PORTD, PORT_MODULE_LED_MODE, PIN4);
    GPIO_Init (GPIOD, GPIO_OUT_LOGIC0_MODE, PIN4);
    GPIO_Set(GPIOD,PIN4);//拉高485的那个引脚

 //UART_PutStr (UART1,"\n\rCharacters will be echoed on the screen:\n");
  // UART_PutChar(UART0,'y');
  while(1)
  {
 //  UART_PutStr (UART0,"\n\rCharacters will be echoed on the screen:\n");
    //UART_PutChar(UART0,1);
//   UART_PutStr (UART0,"\n\rCharacters will be echoed on the screen:\n");
//    /* read and echo character                                                */
       while (!UART_RxFull(UART0));
        c=UART_GetChar(UART0);
//    while (!UART_TxIdle(UART0));
     // UART_PutChar(UART0,0x01);
//     //UART_PutChar (UART0,'c');
//     GPIO_Set(FGPIOF, PIN5);
   }
}