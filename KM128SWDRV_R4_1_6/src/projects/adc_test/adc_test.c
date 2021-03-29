/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 * adc_test.c
 ******************************************************************************/
#include "drivers.h"
//#include "modbus.h"

static volatile float tmp16;
 float voltage3;

void main (void)
{
  SIM_Init (SIM_MODULE_ALL_PERIPH_ON_CONFIG);
  ADC_Init (ADC_MODULE_16B_SWTRG_XREF_CONFIG,
            HWAVG_32,
            ADC_CH_SE_POLL_CONFIG(AD3),
            ADC_CH_DISABLE_CONFIG,
            ADC_CH_DISABLE_CONFIG,
            ADC_CH_DISABLE_CONFIG,
            PRI_LVL0, NULL);
  while (1)
  {
    if (ADC_Ready(CHA))
    {
      tmp16 = ADC_Read(CHA);
      ADC_Start(CHA,AD3);
      voltage3=tmp16*(3.323/65535);
      //voltage=voltage/10;
    }
   
  }
}
