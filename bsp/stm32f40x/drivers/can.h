/***********************************************************************************/
/* can.h                                                                    */
/*                                                                                 */
/***********************************************************************************/
#ifndef __CAN_H__
#define __CAN_H__
//-----------------------------------------------------------------------------------
#include "stm32f4xx.h"
//-----------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//定义使用can1还是can2(可两个都使用)
#define USE_CAN1
#define USE_CAN2 

//定义CAN1的IO口
#define CAN1_RX_PIN                 GPIO_Pin_8
#define CAN1_TX_PIN                 GPIO_Pin_9
#define CAN1_GPIO_PORT              GPIOB
#define CAN1_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define CAN1_RX_SOURCE              GPIO_PinSource8
#define CAN1_TX_SOURCE              GPIO_PinSource9  

//定义CAN2的IO口
#define CAN2_RX_PIN                 GPIO_Pin_5
#define CAN2_TX_PIN                 GPIO_Pin_6
#define CAN2_GPIO_PORT              GPIOB
#define CAN2_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define CAN2_RX_SOURCE              GPIO_PinSource5
#define CAN2_TX_SOURCE              GPIO_PinSource6
//-----------------------------------------------------------------------------------
void can_init(void);
void can_services_init(void);
uint32_t can_send_buffer(uint8_t port, CanTxMsg* msg);
uint32_t can_send_buffer_with_frame(uint32_t port, uint8_t * buffer, int length);

#ifdef __cplusplus
}
#endif

#endif 

/***********************END OF FILE****/
