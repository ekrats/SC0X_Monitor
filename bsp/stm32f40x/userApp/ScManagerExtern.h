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
void gbch_init(void);
void SendCan(uint8_t frame);					//CANÅ¼·¢Ö¡·¢ËÍº¯Êý
void CanApp_TriggerStream_Server(void);
void CanApp_CycleStream_Server(void);
void Bsp_can_send_trigger_event(void);
void Bsp_can_send_cycle_event(void);
void can_rx_interface(uint8_t port, CanRxMsg* msg);
void can_rx_thread_init(void);
void can_tx_thread_init(void);

#ifdef __cplusplus
}
#endif

#endif
