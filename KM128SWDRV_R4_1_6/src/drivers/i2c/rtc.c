/******************************************************************************
 * (c) Copyright 2010-2014, Freescale Semiconductor Inc.
 * ALL RIGHTS RESERVED.
 ***************************************************************************//*!
 * @file      irtc.c
 * @version   1.0.7.0
 * @date      Apr-20-2014
 * @brief     IRTC Real Time Clock (IRTC) driver source code.
 ******************************************************************************/
#include "common.h"
#include "rtc.h"

typedef struct
{
  uint8  sec1;           ///< Second after the minute [0, 59]
  uint8  min1;           ///< Minute after the hour [0, 59]
  uint8  hour1;          ///< Hour since midnight [0, 23]
  uint8  day1;           ///< Day of the month [1, 31]
  uint8  wday1;          ///< @ref irtc_wday since Sunday [0, 6]
  uint8  mon1;           ///< @ref irtc_mon since January [1, 12]
  uint16 year1;          ///< Year [1984, 2239]
} tTIME;

/******************************************************************************
 * public function definitions                                                *
 ******************************************************************************/

/******************************************************************************
 * End of module                                                              *
 ******************************************************************************/