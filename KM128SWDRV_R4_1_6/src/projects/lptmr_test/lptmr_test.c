/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 * lptmr_test.c
 ******************************************************************************/
#include "drivers.h"
int t=0;
static volatile uint16 counter;
/* PIT callback declarations                                                  */
void pit_callback (PIT_CALLBACK_TYPE type);

void main (void)
{
  /* enable clocks to all on chip peripherals                                 */
  SIM_Init(SIM_MODULE_ALL_PERIPH_ON_CONFIG);

  /* initialize LPTMR in freerun Timer mode                                   */
  LPTMR_Init(LPTMR_MODULE_TMR_FREERUN_MODE_CONFIG(0,LPTMR_LPOCLK),0);
  LPTMR_Enable();
  PIT_InstallCallback (PRI_LVL1,pit_callback);
  PIT_Init(PIT0, CH0, PIT_CH_TMR_EN_CONFIG,25000);//1ms
 // LPTMR_CNR=100;
  EnableInterrupts();//是不是引脚接的不对
  while (1)
  {
    //counter = LPTMR_CNR;//LPTMR_ReadCnt();
    //LPTMR_CNR=0;
    //LPTMR_BASE_PTR->CSR&=~(1<<0);//清计数器复位
    
  }
}
/* PIT callback definition                                                    */
void pit_callback (PIT_CALLBACK_TYPE type)
{
  
    counter = LPTMR_ReadCnt();//读之前要先写
    LPTMR_BASE_PTR->CSR&=~LPTMR_CSR_TEN_MASK;//清计数器复位
    LPTMR_BASE_PTR->CSR|=LPTMR_CSR_TEN_MASK;
    
//  if (type == PIT0CH0_CALLBACK)
//  { 
//    if(t<20)
//    {
//   counter = LPTMR_ReadCnt();
//   //LPTMR_CNR=0;
//    t++;
//    }
//    if(t==20)
//    {
//     t=0;
//     
//    }
//  }
}
