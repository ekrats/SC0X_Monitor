/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "stm32f4xx.h"
#include "board.h"
#include "usart.h"
#include "fsmc.h"
#include "can.h"
#include "spi_flash.h"
#include "Bsp_systimer.h"

/**
 * @addtogroup STM32
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);
#endif

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

#if IWDG_EN
/*******************************************************************************
* Function Name  : IWDG_Init
* Description    : Init the IWDG
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IWDG_Init(rt_uint8_t ReloadTime)
{
	rt_uint16_t reload;

	if(26 <= ReloadTime)
	{
		reload = 0x0FFF;
	}
	else
	{
		reload = (156 * ReloadTime) & 0x0FFF;
	}

	/* IWDG timeout equal to 280 ms (the timeout may varies due to LSI frequency
	dispersion) */
	/* Enable write access to IWDG_PR and IWDG_RLR registers */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

	/* IWDG counter clock: 40KHz(LSI) / IWDG_Prescaler */
	IWDG_SetPrescaler(IWDG_Prescaler_256);

	/* Set counter reload value */
	IWDG_SetReload(reload);

	/* Reload IWDG counter */
	IWDG_ReloadCounter();

	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();
}
#endif

/*******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : Configures the SysTick for OS tick.
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void  SysTick_Configuration(void)
{
    RCC_ClocksTypeDef  rcc_clocks;
    rt_uint32_t         cnts;

    RCC_GetClocksFreq(&rcc_clocks);

    cnts = (rt_uint32_t)rcc_clocks.HCLK_Frequency / RT_TICK_PER_SECOND;
    cnts = cnts / 8;

    SysTick_Config(cnts);
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init()
{
#if IWDG_EN
	IWDG_Init(5);
#endif
    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Configuration();

    stm32_hw_usart_init();
    //stm32_hw_pin_init();
    
#ifdef RT_USING_CONSOLE
    rt_console_set_device(CONSOLE_DEVICE);
#endif
	
	logic_board_spi_init();
	
	System_fsmc_init();
	
	System_HW_Can_Init();
	
	System_hw_timerInit();
	
#if IWDG_EN
	IWDG_Init(1);
#endif
}

/*@}*/
