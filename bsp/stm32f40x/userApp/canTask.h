#ifndef _can_task_h_
#define _can_task_h_

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------
// Event
//------------------------------------------------------------------
#define CanTask_Event_Cycle        ((uint32_t)0x01)
#define CanTask_Event_Trigger      ((uint32_t)0x02)
	
#define CAN_TX_THREAD_STACK 1024
#define CAN_TX_THREAD_PRI   9//10
#define CAN_TX_THREAD_SLICE 15
#define CAN_TX_THREAD_DELAY 10//10ms
#define CAN_RX_THREAD_STACK 1024
#define CAN_RX_THREAD_PRI   3
#define CAN_RX_THREAD_SLICE 15
#define CAN_RX_THREAD_DELAY 10//10ms
//----------------------------------------
#define CAN_RX_TIMEOUT  100000
	
void can_rx_thread_init(void);
void can_tx_thread_init(void);
void Bsp_can_send_trigger_event(void);
	
#ifdef __cplusplus
}
#endif

#endif

