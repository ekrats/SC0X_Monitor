#ifndef __ScManagerExtern__h__
#define __ScManagerExtern__h__

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif
	
void ad_init(void);
void io_init(void);
void io_output(void);
void relays_refresh(void);
void data_deal(void);
void slow_check(void);
void * GetShareDataPtr(void);
void CanApp_TriggerStream_Server(void);
void CanApp_CycleStream_Server(void);
void can_Rx_Msg(uint8_t port, CanRxMsg* msg);

#ifdef __cplusplus
}
#endif

#endif
