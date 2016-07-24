#include "canTask.h"
#include "stm32f4xx_can.h"
#include "rtthread.h"
#include "ScManagerExtern.h"

static u32 s_rx_timeout_flag = 0;
//-----------------------静态信号量及线程空间------------------------------------
//ALIGN(RT_ALIGN_SIZE)
static struct rt_thread can_tx_thread;
static rt_uint8_t can_tx_thread_stack[CAN_TX_THREAD_STACK];
static struct rt_thread can1_rx_thread;
static rt_uint8_t can1_rx_thread_stack[CAN_RX_THREAD_STACK];
static struct rt_thread can2_rx_thread;
static rt_uint8_t can2_rx_thread_stack[CAN_RX_THREAD_STACK];

//================================================================
//Function Name: 
//Description  :can发送线程入口程序
//Input        : 
//Output       : 
//Return       : 
//================================================================
static void can_tx_thread_entry(void* parameter)
{
    static uint8_t cnt = 0;
	while (1)
    {
//        if (++cnt >=10)
//		{
//			CanTxDataUpdate(&can);
//			cnt = 0;
//		}
//		
//        CanBurstACK(&can);

        rt_thread_delay(CAN_TX_THREAD_DELAY);
    }
}

//================================================================
//Function Name: 
//Description  :发送线程初始化
//Input        : 
//Output       : 
//Return       : 
//================================================================
void can_tx_thread_init(void)
{
    rt_err_t result;
    result = rt_thread_init(&can_tx_thread, "can_s_tx", can_tx_thread_entry,
        RT_NULL, &can_tx_thread_stack[0],
        sizeof(can_tx_thread_stack), CAN_TX_THREAD_PRI, CAN_TX_THREAD_SLICE);
    if (result == RT_EOK)
    {
        rt_thread_startup(&can_tx_thread);//启动线程
    }
    else
    {
#ifdef CAN_ERR_PRINT    
        rt_kprintf("can_tx_thread init fail\n");
#endif
    }
}

//================================================================
//Function Name: 
//Description  :can接收线程入口程序
//Input        : 
//Output       : 
//Return       : 
//================================================================
static void can1_rx_thread_entry(void* parameter)
{
    rt_err_t result;
    extern struct rt_mailbox mb_can1_rx;
    CanRxMsg * msg;
    while (1)
    {
        result = rt_mb_recv(&mb_can1_rx, (rt_uint32_t *)&msg, CAN_RX_TIMEOUT);
        //超时未收到CAN数据
        if (result == -RT_ETIMEOUT)
        {
            s_rx_timeout_flag = 1;
#ifdef CAN_ERR_PRINT    
            rt_kprintf("NO CAN1. CAN1 connect error\n");
#endif                    
        }
        //收到CAN数据,进行处理
        else
        {
            s_rx_timeout_flag = 0;
			can_Rx_Msg(1, msg);
        }
    }
}

//================================================================
//Function Name: 
//Description  :can接收线程入口程序
//Input        : 
//Output       : 
//Return       : 
//================================================================
static void can2_rx_thread_entry(void* parameter)
{
    rt_err_t result;
    extern struct rt_mailbox mb_can2_rx;
    CanRxMsg * msg;
    while (1)
    {
        result = rt_mb_recv(&mb_can2_rx, (rt_uint32_t *)&msg, CAN_RX_TIMEOUT);
        //超时未收到CAN数据
        if (result == -RT_ETIMEOUT)
        {
            s_rx_timeout_flag = 1;
#ifdef CAN_ERR_PRINT    
            rt_kprintf("NO CAN2. CAN2 connect error\n");
#endif                    
        }
        //收到CAN数据,进行处理
        else
        {
            s_rx_timeout_flag = 0;
			can_Rx_Msg(2, msg);
        }
    }
}

//================================================================
//Function Name: 
//Description  :接收线程初始化
//Input        : 
//Output       : 
//Return       : 
//================================================================
void can_rx_thread_init(void)
{
    rt_err_t result;
    result = rt_thread_init(&can1_rx_thread, "can1_s_rx", can1_rx_thread_entry,
        RT_NULL, &can1_rx_thread_stack[0],
        sizeof(can1_rx_thread_stack), CAN_RX_THREAD_PRI, CAN_RX_THREAD_SLICE);
    if (result == RT_EOK)
    {
        rt_thread_startup(&can1_rx_thread);//启动线程
    }
    else
    {
#ifdef CAN_ERR_PRINT    
        rt_kprintf("can1_rx_thread init fail\n");
#endif
    }

    result = rt_thread_init(&can2_rx_thread, "can2_s_rx", can2_rx_thread_entry,
        RT_NULL, &can2_rx_thread_stack[0],
        sizeof(can2_rx_thread_stack), CAN_RX_THREAD_PRI, CAN_RX_THREAD_SLICE);
    if (result == RT_EOK)
    {
        rt_thread_startup(&can2_rx_thread);//启动线程
    }
    else
    {
#ifdef CAN_ERR_PRINT    
        rt_kprintf("can2_rx_thread init fail\n");
#endif
    }

}

