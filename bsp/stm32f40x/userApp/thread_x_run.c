#include "thread_x_run.h"
#include <rtthread.h>
#include "stm32f4xx.h"
#include "ScManagerExtern.h"
#include "Bsp_Board_Init.h"
#include "logicApp.h"

/*******************************************************************************
* Function Name  : rt_cycle_thread_entry
* Description    : 
* Input          :  .
* Output         : None
* Return         : None
*******************************************************************************/
__IO uint8_t enDog = 1;
static void rt_cycle_thread_entry(void* parameter)
{
	static uint8_t timeDelay = 0;
	//------------------------------------------------------
	// 系统指示灯初始化
	//------------------------------------------------------
	Bsp_led_init();
	while(1)
	{
		rt_thread_delay(RT_TICK_PER_SECOND/100);

#if IWDG_EN
		if(enDog)	IWDG_ReloadCounter();
#endif
		if(++timeDelay % 50 == 0)
		{
			timeDelay = 0;
			//------------------------------------------------------
			// 系统运行灯
			//------------------------------------------------------
			if(GPIOA->ODR & GPIO_Pin_12)
			{
				GPIOA->BSRRH = GPIO_Pin_12;
			}
			else
			{
				GPIOA->BSRRL = GPIO_Pin_12;
			}
		}
	}
}

static void cycle_thread_creat(uint8_t priority)
{
	rt_thread_t tid;
	
	//------- init thread
	tid = rt_thread_create("cycle",
		rt_cycle_thread_entry, RT_NULL,
		512, priority, 10);
	//------- start up thread
	if(tid != RT_NULL)
		rt_thread_startup(tid);
}

void rt_app_thread_x(void)
{
	logic_thread_creat(6);
	
	cycle_thread_creat(30);
	
	adio_thread_creat(1);
}
