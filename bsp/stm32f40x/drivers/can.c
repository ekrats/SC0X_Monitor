/***********************************************************************************/
/*can_driver.c                                                                     */
/*                                                                                 */
/***********************************************************************************/
#include "can.h"
//-----------------------------------------------------------------------------------
void can_init(void);


static void gpio_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    //---------------------------------------------------------------
    // 
    //---------------------------------------------------------------
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);

    //---------------------------------------------------------------
    // 
    //---------------------------------------------------------------
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_CAN1);
    //---------------------------------------------------------------
    // 
    //---------------------------------------------------------------
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2);
}

void can_config(void)
{
    CAN_InitTypeDef CAN_InitStructure = { 0 };

    //---------------------------------------------------------------
    // DeInit CAN1,CAN2
    //---------------------------------------------------------------
    CAN_DeInit(CAN1);
    CAN_DeInit(CAN2);
    
    //---------------------------------------------------------------
    // ??????????
    //---------------------------------------------------------------
    CAN_StructInit(&CAN_InitStructure);
    //---------------------------------------------------------------
    // ???CAN1,CAN2, ??????,
    //---------------------------------------------------------------
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStructure.CAN_Prescaler = 6;  //42M/6*(1+3+3)
    
    CAN_Init(CAN1, &CAN_InitStructure);
    CAN_Init(CAN2, &CAN_InitStructure);
}

void can_nvic_config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    //-------------------------------------------------------------
    // ??CAN1?????	
    //-------------------------------------------------------------
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    //-------------------------------------------------------------
    // ??CAN2?????	
    //-------------------------------------------------------------
    NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//===================================================================================
//can硬件初始化
//
//===================================================================================
void can_init(void)
{
    gpio_config();
    can_config();
    can_nvic_config();
}


#include "rtthread.h"
#include "static_mem.h"

struct rt_mailbox mb_can1_rx;
struct rt_mailbox mb_can2_rx;
char can1_rx_mb_pool[256];
char can2_rx_mb_pool[256];

#include "candef.h"

struct rt_mailbox mb_can_tx;
char can_tx_mb_pool[1024];
int send_cnt = 0;
static void can_tx_services_entry( void* parameter)
{
    CAN_TX_TYPEDEF * tx_info;
    uint8_t transmit_mailbox;
    while(1)
    {
        if(RT_EOK == rt_mb_recv(&mb_can_tx, (rt_uint32_t * )&tx_info, RT_WAITING_FOREVER))
        {
            int retry_times = CAN_SEND_RETRYTIMES;
            
            if((tx_info->CANx != NULL) && (CAN_GetFlagStatus(tx_info->CANx, CAN_FLAG_BOF) == SET))
            {
                return;
            }
            
            while(retry_times--)
            {
                tx_info->data.ExtId = 0;
                tx_info->data.IDE = CAN_ID_STD;
                tx_info->data.RTR = CAN_RTR_DATA;
                send_cnt++;
                transmit_mailbox = CAN_Transmit(tx_info->CANx, &tx_info->data);
                if(CAN_TxStatus_NoMailBox == transmit_mailbox)//发送队列已满
                {
                    rt_thread_delay(1); 
                }
                else
                {
                    break;
                }
            }
        }
        
        rt_free(tx_info);
    }
}

void can_services_init()
{
    struct rt_thread * can_services_thread;
    rt_mb_init(&mb_can_tx, "mbct", &can_tx_mb_pool, 
                sizeof(can_tx_mb_pool) / 4, RT_IPC_FLAG_FIFO);
    
    rt_mb_init(&mb_can1_rx, "mbcr1", &can1_rx_mb_pool, 
                sizeof(can1_rx_mb_pool) / 4, RT_IPC_FLAG_FIFO);
    
    rt_mb_init(&mb_can2_rx, "mbcr2", &can2_rx_mb_pool, 
                sizeof(can2_rx_mb_pool) / 4, RT_IPC_FLAG_FIFO);
    
    can_services_thread = rt_thread_create("can_tx",
                                    can_tx_services_entry, RT_NULL,
                                    1024, 15, 10);
    if (can_services_thread != RT_NULL)
    {
        rt_thread_startup(can_services_thread);
    }

    //rt_sem_init(&sem_serial_rx, "usart_rx", 0, 1);
}

static CanRxMsg can1_rx_msgs[64];
static CanRxMsg can2_rx_msgs[64];
static int can1_rx_msgs_index = 0;
static int can2_rx_msgs_index = 0;

/*****************************************************************
can1  FIFO0接收中断
*****************************************************************/
void CAN1_RX0_IRQHandler(void)
{
    CAN_Receive(CAN1, CAN_FIFO0, &can1_rx_msgs[can1_rx_msgs_index]);//can使用FIFO0中断接收;
    if(-RT_EFULL == rt_mb_send(&mb_can1_rx, (rt_uint32_t)&can1_rx_msgs[can1_rx_msgs_index]))
    {
    }
    /*若有需要可插入接收队列*/
    if(++can1_rx_msgs_index == 64)
    {
        can1_rx_msgs_index = 0;
    }
}

void CAN2_RX0_IRQHandler(void)
{
    if(CAN_GetITStatus(CAN2, CAN_IT_FF0)) 
    { 
        CAN_ClearITPendingBit(CAN2, CAN_IT_FF0); 
    } 
    else if(CAN_GetITStatus(CAN2, CAN_IT_FOV0)) 
    { 
        CAN_ClearITPendingBit(CAN2, CAN_IT_FOV0); 
    } 
    else
    { 
        CAN_Receive(CAN2, CAN_FIFO0, &can2_rx_msgs[can2_rx_msgs_index]);//can使用FIFO0中断接收;
        /*若有需要可插入接收队列*/
        rt_mb_send(&mb_can2_rx, (rt_uint32_t)&can2_rx_msgs[can2_rx_msgs_index]);
        if(++can2_rx_msgs_index == 64)
        {
            can2_rx_msgs_index = 0;
        }
    }  
}


uint32_t can_send_buffer(uint8_t port, CanTxMsg* msg)
{
    CAN_TX_DATA_RAM * tx_buffer = RT_NULL;
    uint8_t * tmp = msg->Data;
    
    while(tmp != RT_NULL)
    {
        tx_buffer = rt_malloc(sizeof(CAN_TX_DATA_RAM));
        if(tx_buffer != RT_NULL)
        {
            tx_buffer->parent.CanPort = port;
			tx_buffer->data.StdId = msg->StdId;
			tx_buffer->data.ExtId = msg->ExtId;
			tx_buffer->data.IDE = msg->IDE;
			tx_buffer->data.RTR = msg->RTR;
			tx_buffer->data.DLC = msg->DLC;
            tx_buffer->data.Data[0] = tmp[0];
            tx_buffer->data.Data[1] = tmp[1];
            tx_buffer->data.Data[2] = tmp[2];
            tx_buffer->data.Data[3] = tmp[3];
            tx_buffer->data.Data[4] = tmp[4];
            tx_buffer->data.Data[5] = tmp[5];
            tx_buffer->data.Data[6] = tmp[6];
            tx_buffer->data.Data[7] = tmp[7];
            rt_mb_send(&mb_can_tx, (rt_uint32_t)tx_buffer);
        }
        else
        {
            return 1;
        }
    }
    
    return 0;
}

uint32_t can_send_buffer_with_frame(uint32_t port, uint8_t * buffer, int length)
{
    CAN_TX_TYPEDEF * tx_buffer = RT_NULL;
    uint8_t * tmp = buffer;
    
    tx_buffer = rt_malloc(sizeof(CAN_TX_TYPEDEF));
    if(tx_buffer != RT_NULL)
    {
        tx_buffer->data.StdId = port;
        tx_buffer->data.Data[0] = *tmp++;
        tx_buffer->data.Data[1] = *tmp++;
        tx_buffer->data.Data[2] = *tmp++;
        tx_buffer->data.Data[3] = *tmp++;
        tx_buffer->data.Data[4] = *tmp++;
        tx_buffer->data.Data[5] = *tmp++;
        tx_buffer->data.Data[6] = *tmp++;
        tx_buffer->data.Data[7] = *tmp++;
        tx_buffer->data.DLC = length;
        rt_mb_send(&mb_can_tx, (rt_uint32_t)tx_buffer);
    }
    else
    {
        return 1;
    }
    
    return 0;
}


/*********************end of file******************************/
