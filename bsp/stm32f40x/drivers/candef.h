/**
  *************************************************************************
  * This file is part of platform
  * COPYRIGHT (C) 1999-2015, TongYe Inverter Development Team
  * @file    candef.h
  * @brief   This file contains all the functions prototypes for the   
  *          can definition firmware library.
  * Change Logs:
  * Date           Author       Notes
  * 2015/12/24     Íõ öÎ        the first version
  *************************************************************************
  */


#ifndef __CANDEF__H__
#define __CANDEF__H__
#include "stdint.h"
#include "stm32f4xx_can.h"

#ifdef __cplusplus
extern "C" {
#endif
#define CAN_SEND_RETRYTIMES (3)

typedef struct _Can_Ram_
{
	uint32_t  Tick;
	uint16_t  CanPort;
	uint16_t  BoardId;

}CAN_DATA_RAM, *PCAN_DATA_RAM;
	
typedef struct _Can_Rx_Ram_
{
	CAN_DATA_RAM parent;
	CanRxMsg     data;

}CAN_RX_DATA_RAM, *PCAN_RX_DATA_RAM;

typedef struct _Can_Tx_Ram_
{
	CAN_DATA_RAM parent;
	CanTxMsg     data;

}CAN_TX_DATA_RAM, *PCAN_TX_DATA_RAM;
	
    struct CAN_HEADER
    {
        uint32_t tick;
        uint16_t port;
        uint16_t res;
    };
    
    typedef struct
    {
        struct CAN_HEADER header;
        CAN_TypeDef* CANx;
        CanTxMsg data;
    }CAN_TX_TYPEDEF;

#ifdef __cplusplus
}
#endif

#endif


/******************* (C) COPYRIGHT 2015 TongYe **********END OF FILE****/




/*@}*/


