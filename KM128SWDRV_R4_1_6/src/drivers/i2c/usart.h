#ifndef __USART_H
#define __USART_H
//#include "stdio.h"

typedef enum
{
RESET=0,
SET=!RESET
}FlagStatus;

extern uint8 receCount;
extern double data[120];
extern  void USART0_IRQHandler(void);
extern double calc(double*pData,int nNum);
extern void AC(void);
extern int t;
extern float voltage3;

extern  uint8 f;
#endif
