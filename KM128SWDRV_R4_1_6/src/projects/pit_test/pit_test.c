/******************************************************************************
 * (c) Copyright 2010-2015, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ******************************************************************************
 //   //modbus调试通过 2017-3-23--晚上19:30/  modbus上位机软件刷新时间10ms
 ******************************************************************************/
#include "drivers.h"
#include "types.h"   
#include "i2c/modbus.h"




/* PIT callback declarations                                                  */
void pit_callback (PIT_CALLBACK_TYPE type);
/* uart callback function prototype                                           */
static void uart_callback (UART_CALLBACK_SRC module, UART_CALLBACK_TYPE type,
                           int32 status);
//AD define
static volatile float tmp16;
//static volatile float voltage3;
float buffer[20];
double rms;//均方差
int s;
//extern float voltage;
void main(void)
{
  SIM_Init (SIM_MODULE_ALL_PERIPH_ON_CONFIG);
  ADC_Init (ADC_MODULE_16B_SWTRG_XREF_CONFIG,
            HWAVG_32,
            ADC_CH_SE_POLL_CONFIG(AD3),
            ADC_CH_DISABLE_CONFIG,
            ADC_CH_DISABLE_CONFIG,
            ADC_CH_DISABLE_CONFIG,
            PRI_LVL0, NULL);
//  /* route core clock to PTF7                                                 */
  SIM_SelClkout (CLKOUT_SRC2);
  PORT_Init (PORTF,PORT_MODULE_ALT3_MODE,PIN7);
  /* clock mode 1:1:1, 24MHz                                                  */
  SIM_SetClkMode (SYSCLK_MODE0);
  SIM_SetClkDiv  (SYSCLK_DIV1);
  FLL_Init  (FLL_MODULE_FEE_24MHZ_CONFIG);
//
  /* UART0 init 9600bd                                                        */
  PORT_Init(PORTF, PORT_MODULE_ALT4_MODE, PIN3|PIN4);
  UART_Init(UART0, UART_MODULE_INTRMODE_CONFIG(115200,24e6));//1/115200*10*1000=0.08ms
  UART_InstallCallback (UART0_UART1, PRI_LVL0, uart_callback);//38400--0.26ms
    //  PTD4初始化用于拉高485 
   PORT_Init (PORTD, PORT_MODULE_LED_MODE, PIN4);
   GPIO_Init (GPIOD, GPIO_OUT_LOGIC0_MODE, PIN4);
   PIT_InstallCallback (PRI_LVL1,pit_callback);
   PIT_Init(PIT0, CH0, PIT_CH_TMR_EN_CONFIG,7500);//1250000);//25000);//7500);//25000);//;//7500);//0.3ms//25000);//40000--这个是modbus发送招10个数据也没问题的时间);//2000);//2000);//1250000)对的;//12500000--500ms//25000--1ms//5000-200us//500000);//1500000);// 1000000这个时间是没问题的 //过多长时间进入一次中断  这个时间要小于 上位机刷新的时间  // 1000000
   EnableInterrupts();//
   while(1)
  { 
    
    
//    if (ADC_Ready(CHA))
//    {
//      tmp16 = ADC_Read(CHA);
//      ADC_Start(CHA,AD3);
//      voltage3=tmp16*(3.357/65535);//3.317
//      //voltage=voltage/10;
//    }
//    if(t==20)
//    {
//    double rms=calc(data,20);
//    voltage3=rms*(3.2541/65535);
//    }
//       voltage3=voltage3*1000;
//       adcval[0]=(uint16)voltage3/1000;//最左边一位
//       adcval[1]=(uint16)voltage3%1000/100;
//       adcval[2]=(uint16)voltage3%1000%100/10;//%100/10;
//       adcval[3]=(uint16)voltage3%1000%100%10;//个位，最右边一位
   }
  }

/* PIT callback definition                                                    */
void pit_callback (PIT_CALLBACK_TYPE type)
{
  if (type == PIT0CH0_CALLBACK)
  { 
       // s++;
     // GPIO_Tgl(GPIOD,PIN4);
         AC();
   
    
        checkComm0Modbus();
  }
}

/* uart callback function definition                                          */
static void uart_callback (UART_CALLBACK_SRC module, UART_CALLBACK_TYPE type,
                           int32 status)
{
  if (module == UART0_CALLBACK)
  {
    if(type == UART_TX_CALLBACK)
    {
   //   UART0_BASE_PTR->S1&=~(1<<6);//清中断  TC位
//      if(sendPosi <=sendCount)
//      {
//        sendPosi++;
//        while(!UART_TxIdle(UART0))
//        UART_PutChar(UART0,sendBuf[sendPosi]);
//      }
//      else
//      {
//       GPIO_Clr(GPIOD,PIN4);   //485置于接收
//       receCount = 0;   //清地址偏移寄存器
//       checkoutError = 0;
//      } 
      
 
    }
   if (type == UART_RX_CALLBACK)
    {
        while(!UART_RxFull(UART0));  
      	receBuf[receCount]= UART_GetChar(UART0);
        receCount++; 
    }
       
  }
}
/***************************************************************************
 * END OF MODULE
 ****************************************************************************/
