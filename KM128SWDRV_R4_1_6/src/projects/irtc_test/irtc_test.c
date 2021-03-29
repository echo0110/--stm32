/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 * irtc_test.c
 ******************************************************************************/
#include <string.h>
#include "drivers.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/* Initialize time variable for 20.10.2012 Saturday 23:59:58                  */
static tTIME  wtime = {0,54,13,15,WEDNESDAY,MARCH ,2017}, rtime;
static tALARM atime = {35, 0, 0,21,OCTOBER,2012};
static tTAMPER_LOG log;
static void irtc_callback (IRTC_CALLBACK_TYPE type, void *data);
uint8 miao;
uint8 fen;
int i=0;
int b=2;




uint8 a[10]={0};

//volatile unsigned long *reg=(volatile unsigned long*)(RTC_BASE_PTR->SECONDS);
void main (void)
{
  /* initialize SIM module                                                    */
  SIM_Init  (SIM_MODULE_ALL_PERIPH_ON_CONFIG);
  SIM_SetClkMode (SYSCLK_MODE1);
  SIM_SetClkDiv  (SYSCLK_DIV1);
  SIM_EnableModule(PORTF);
  FLL_Init(FLL_MODULE_FEE_48MHZ_CONFIG);
  
  IRTC_Init(IRTC_MODULE_COMP_OFF_CONFIG(LFSR_CLK_64HZ,10),
             IRTC_TAMPER_PIN_DI_CONFIG,
             IRTC_TAMPER_PIN_PASSIVE_POL_HIGH_CONFIG(LFSR_CLK_64HZ,10),
             IRTC_TAMPER_PIN_DI_CONFIG,
             IRTC_TAMPER1_MASK|IRTC_ALM_MASK|IRTC_1HZ_MASK);
   /* UART0 init 9600bd                                                        */
    PORT_Init (PORTF, PORT_MODULE_ALT4_MODE, PIN3|PIN4);
    UART_Init (UART0, UART_MODULE_POLLMODE_CONFIG(9600,24e6));
      //  PTD4初始化用于拉高485 
    PORT_Init (PORTD, PORT_MODULE_LED_MODE, PIN4);
    GPIO_Init (GPIOD, GPIO_OUT_LOGIC0_MODE, PIN4);
    GPIO_Set(GPIOD,PIN4);//拉高485引脚
   
  //IRTC_GetClock (tTIME *ptr);
  //RTC_SECONDS = RTC_SECONDS_SEC_CNT(ptr->sec);
   
 
    IRTC_InstallCallback (PRI_LVL3,irtc_callback);
    IRTC_SetClock (&wtime);
    IRTC_GetClock(&rtime);
   // IRTC_GetClock (&tTIME);
  // IRTC_SetDST(14,14,MARCH,3,28,OCTOBER);
//  IRTC_SetAlarm(ALM_MATCH_SMH,&atime);
    EnableInterrupts();
    

 // RTC_BASE_PTR->SECONDS;
  //RTC_SECONDS;
 
  // RTC_SECONDS=0;//秒
  // RTC_HOURMIN=0;  //分
   // for(i=0;i<sizeof(rtime);i++)
//    rtime.sec=0;
//    rtime.min=0;
  
   while(1);
  // {
     
     // UART_PutChar(UART0, hs);
//     for(i=0;i<sizeof(rtime);i++)
//     UART_PutChar (UART0,*(uint8*)&rtime+i);
     
 //   IRTC_RdRam((uint8*)&rtime, sizeof(rtime));
   //  UART0_BASE_PTR->D=rtime.sec;
    // a[0]=UART0_BASE_PTR->D;
    //UART_PutStr (UART0,‘当前时间’);
//    //arch_delay(9000);
 // UART_PutChar(UART0, 2); 
 // printf("0x01");
 //  UART_PutChar(UART0, rtime.min);
     
   // printf("(int)20");
     
  // }
 // {
    
  
//   if(RTC_SECONDS==59)
//   fen=1;//分钟
//   if(RTC_HOURMIN==59)
//     //hour=hour+1;
//  
//   UART_PutChar(UART0, fen);
 // UART_PutChar(UART0,rtime.sec);
  // }
}

static void irtc_callback (IRTC_CALLBACK_TYPE type, void *data)
{
  
  if(type == IRTC_1HZ_CALLBACK    ) { memcpy (&rtime,data,sizeof(tTIME));     }
  if(type == IRTC_ALM_CALLBACK    ) { IRTC_SetClock(&wtime);                  }
  if(type == IRTC_TAMPER1_CALLBACK) { memcpy (&log,data,sizeof(tTAMPER_LOG)); }
}




