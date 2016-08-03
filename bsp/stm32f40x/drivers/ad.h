/**
  *************************************************************************
  * This file is part of GBC01
  * COPYRIGHT (C) 1999-2013, TongYe Inverter Development Team
  * @file    ad.h
  * @brief   This file contains all the functions prototypes for the   
  *          ad firmware library.
  * Change Logs:
  * Date           Author       Notes
  * 2016/05/11     Coase        the first version
  *************************************************************************
  */

#ifndef __GBC01_AD__H__
#define __GBC01_AD__H__

#include "stm32f4xx_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_TIM            (TIM8)
#define ADC_TIM_RCC        (RCC_APB2Periph_TIM8)
#define ADC_MODULE1        (RCC_APB2Periph_ADC1)
#define ADC_MODULE2        (RCC_APB2Periph_ADC3)
#define ADC_DMA            (RCC_AHB1Periph_DMA2)

enum ad_data_buffer_index
{
	temp_module1_index,
	temp_module2_index,
	temp_in_index,
    temp_out_index,
	temp_cap1_index,
	temp_cap2_index,
	i_in1_index,
    i_in2_index,
    u_ac1_index,
	u_ac2_index,
	u_bus_index,
};

int System_hw_ADC_Init(void);
int * get_ad_data_buffer(void);
void adc_update(void);


#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT 2013 TongYe **********END OF FILE****/


/*@}*/

