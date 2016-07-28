#include "logicApp.h"
#include <rtthread.h>
#include "stm32f4xx.h"
#include "ScManagerExtern.h"
#include "static_mem.h"
#include "ad.h"
#include "pcmaster.h"
#include "fsmc.h"

ALIGN(RT_ALIGN_SIZE)
struct rt_semaphore sem_ad_task;
struct rt_thread thread_logic;

static void rt_thread_entry_logic(void* parameter)
{
	rt_thread_delay(2000);
    while(1)
    {
        relays_refresh();
		status_updata();
		state_control();
		rt_thread_delay(10);
    }
}

ALIGN(RT_ALIGN_SIZE)
static rt_uint32_t thread_ad_stack[1024];
struct rt_thread thread_ad;
static void rt_thread_entry_ad(void* parameter)
{
    rt_sem_init(&sem_ad_task, "ad", 1, 1);
	System_hw_ADC_Init();
    rt_thread_delay(1000);
	sc_init();
    
    while(1)
    {
        if(-RT_ETIMEOUT == rt_sem_take(&sem_ad_task, 5))
        {
            ADC_SoftwareStartConv(ADC1);
            //adc_i_update();
        }
        adc_update();
		io_update();
        data_refresh();
		io_output();
        pcmaster_record();
    }
}

void logic_thread_creat(uint8_t priority)
{
	 //------- init ad thread
    rt_thread_init(&thread_logic,
        "logic",
        rt_thread_entry_logic,
        RT_NULL,
        static_malloc(0x800),
        0x800, priority, 10);
    rt_thread_startup(&thread_logic);
}

void adio_thread_creat(uint8_t priority)
{
	//------- init ad thread
    rt_thread_init(&thread_ad,
        "ad",
        rt_thread_entry_ad,
        RT_NULL,
        thread_ad_stack,//static_malloc(0x800)
        1024 * 4, priority, 10);
    rt_thread_startup(&thread_ad);
}
