#include "common.h"
#include "gpio/gpio.h"
#include  "i2c/modbus.h"
#include  "usart.h"
#include "uart/uart.h"
#include "adc/adc.h"
#include "math.h"
#include "stdio.h"
#define  K 20
double data[120];
float voltage3;




int t=0;

#define HIFI_CONST 65523
struct Hifi_filter_s
{
uint32 ynLast;
uint16 wDataLast;
};

/*
 * 函数名： AC
 * 描述  ：采集交流电压
 * 输入  ：无
 * 输出  ：无
 * 调用  ：  
 */
void AC(void)                
{
  //y.f=3.14;
 // for(int t=0;i<t;i++)
 // {
  if(t<64)
  {
     if (ADC_Ready(CHA))
     {
      data[t]=(ADC_Read(CHA)-1.925943089315270844E+4);//-1.8788E+4);//-1.8585E+4);//这里减去一个值 了所以AD变了
      ADC_Start(CHA,AD10);
      t++;
     }
  }

   if(t==64)
  {
     double rms=calc(data,64);
     voltage3=rms*(3.357/65535);//3.354//3.357//3.28 //3.323
//     voltage3=voltage3*1000;
  //     adcval[0]=voltage3&0xff;//adcval[0]=(uint16)voltage3/1000;//最左边一位
//     adcval[1]=(uint16)voltage3%1000/100;
//     adcval[2]=(uint16)voltage3%1000%100/10;//%100/10;
//     adcval[3]=(uint16)voltage3%1000%100%10;//个位，最右边一位
     
     t=0;
  }
  //}    
}
/*
 * 函数名： calc
 * 描述  ：计算均方根
 * 输入  ：无
 * 输出  ：无
 * 调用  ：  
 */
double calc(double*pData,int nNum)
{
 //平方和
  double fSum=0;
  for(int i=0;i<nNum;i++)
  {
   fSum+=pData[i]*pData[i];
  }
  //平均 开方
  return sqrt(fSum/nNum);
}

/*
 * 函数名： Hifi_filter_s
 * 描述  ：高通滤波
 * 输入  ：无
 * 输出  ：无
 * 调用  ：  
 */
//static struct  Hifi_filter_s filters[ADC_CHANNEL_NUMBER];
//static void Hifi_filter_init(struct Hifi_filter_s *filter)
//{
//filter->ynLast=0;
//filter->wDataLast=0;
//}
////高通滤波
//static uint16 Hifi_filter(uint16 wData,struct Hifi_filter_s *filter)
//{
//uint64  mul=(uint64)HIFI_CONST*filter->ynLast;
//filter->ynLast=mul>>16;
//filter->ynLast-=(uint32)filter->wDataLast<<16;
//filter->ynLast+=(uint32)wData<<16;
//filter->wDataLast=wData;
//return filter->ynLast>>16;
//}

