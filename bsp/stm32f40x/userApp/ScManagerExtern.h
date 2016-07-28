#ifndef __ScManagerExtern__h__
#define __ScManagerExtern__h__

#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void sc_init(void);
void state_control(void);
void io_output(void);
void relays_refresh(void);
void data_refresh(void);
void status_updata(void);
void * GetShareDataPtr(void);
void CanApp_TriggerStream_Server(void);
void CanApp_CycleStream_Server(void);
void can_Rx_Msg(uint8_t port, CanRxMsg* msg);

#ifdef __cplusplus
}
#endif

#endif
