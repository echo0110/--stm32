
#ifndef __modbus_H
#define __modbus_H



extern uint8 rececount;
extern uint8 receBuf[32];
extern uint16 voltage;
extern uint16 crcData;
extern uint8 sendPosi;
extern uint8 checkoutError;
extern uint8 sendCount;
extern uint8 byteCount;

extern uint8 sendBuf[120];



extern uint16 adcval[120];//={0.1,0.2,0.3,0.4};
//extern uint8 receCount;
//extern uint8 receCount;
//extern uint8 receBuf[32];
//extern uint8 sendCount;	 
//extern uint8 sendBuf[120];
//extern uint8 sendPosi;
//extern uint8 checkoutError;

extern void checkComm0Modbus(void);
extern void readRegisrers(void);
extern void beginSend(void);
//extern uint16 crc16(uint8 *puchMsg,uint16 usDataLen);

#endif
