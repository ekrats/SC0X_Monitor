/**
  *************************************************************************
  * This file is part of GBC01
  * COPYRIGHT (C) 1999-2013, TongYe Inverter Development Team
  * @file    ad.c
  * @brief   This file provides all the ad firmware functions.
  * Change Logs:
  * Date           Author       Notes
  * 2016/05/11     Coase        the first version
  *************************************************************************
  */

/* Includes -------------------------------------------------------------*/

#include "ad.h"
#include <rtthread.h>
#include "static_mem.h"
#include "math.h"

#define ADC_DR_OFFSET        ((uint32_t)0x4C)
#define ADC1_DR_ADRESS       ((uint32_t)(ADC1_BASE + ADC_DR_OFFSET))
#define ADC3_DR_ADRESS       ((uint32_t)(ADC3_BASE + ADC_DR_OFFSET))

#define ADC1_CHANNELS        (6)
#define ADC3_CHANNELS        (6)
#define ADC_FLT1_BUFFER_SIZE (10)
#define ADC1_BUF_LENGTH      ((uint32_t)(ADC1_CHANNELS * ADC_FLT1_BUFFER_SIZE))
#define ADC3_BUF_LENGTH      ((uint32_t)(ADC3_CHANNELS * ADC_FLT1_BUFFER_SIZE))

//---------------------------------------------------------------------
// AD采样原始值
//---------------------------------------------------------------------
rt_uint16_t ADC1_ValTemp[ADC1_BUF_LENGTH] = {0};
rt_uint16_t ADC3_ValTemp[ADC3_BUF_LENGTH] = {0};

static int * ad_buffer;
/*******************************************************************************
* Function Name  : ADC_GPIO_Config
* Description    : Initializes the ADC Input channal pins according to the 
*                  specified  parameters in the KT_InitStruct.
* Input          : - none.
* Output         : None
* Return         : None
*******************************************************************************/

static void ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure = {0};

	/* Enable the GPIO_A Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOB |RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 
		| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : ADC_Init
* Description    : Initializes the KT virtual peripheral according to the 
*                  specified  parameters in the KT_InitStruct.
* Input          :  .
* Output         : None
* Return         : None
*******************************************************************************/
int System_hw_ADC_Init(void)
{
	ADC_InitTypeDef           ADC_InitStructure       = {0};
	DMA_InitTypeDef           DMA_InitStructure       = {0};
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure   = {0};
	TIM_OCInitTypeDef         TIM_OCInitStructure     = {0};
	ADC_CommonInitTypeDef     ADC_CommonInitStructure = {0};
	
	ad_buffer = static_malloc(7 * 4);

	//--------------------------------------------------------------
	//
	// ADC模块所用到的GPIO管脚的初始化
	//
	//--------------------------------------------------------------
	ADC_GPIO_Config();

	//--------------------------------------------------------------
	// 开启ADC模块时钟，开启DMA1，DMA2时钟，开启TIM1时钟
	// 
	// [注] TIM1用于定时触发ADC采样
	//		DMA 用于传输ADC数据					    
	//--------------------------------------------------------------
	RCC_APB2PeriphClockCmd(ADC_MODULE1
		| ADC_MODULE2,
		ENABLE);

	RCC_AHB1PeriphClockCmd(ADC_DMA,
		ENABLE);

	RCC_APB2PeriphClockCmd(ADC_TIM_RCC, ENABLE);

	//--------------------------------------------------------------
	// 停止ADC工作
	//--------------------------------------------------------------
	ADC_Cmd(ADC1, DISABLE);
	ADC_Cmd(ADC3, DISABLE);

	//==============================================================
	//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	//--------------------------------------------------------------
	// TIM8 configuration 用于触发ADC1，ADC3 的规则转换组
	//--------------------------------------------------------------
	// 【注】APB2主频168MHz, TIM8 Clk = 168MHz
	//       TIM8的计数频率1MHz
	//
	//''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
	//==============================================================
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period        = 500;
	TIM_TimeBaseStructure.TIM_Prescaler     = 0x0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ADC_TIM, &TIM_TimeBaseStructure);

	TIM_PrescalerConfig(ADC_TIM, (168 - 1), TIM_PSCReloadMode_Immediate);

	/*-------- TIM8 channel1 configuration in PWM mode ------------*/
	TIM_OCInitStructure.TIM_OCMode          = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_OutputState     = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse           = 100; 
	TIM_OCInitStructure.TIM_OCPolarity      = TIM_OCPolarity_Low;
	TIM_OC1Init(ADC_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(ADC_TIM,TIM_OCPreload_Enable);

	//--------------------------------------------------------------
	// 配置DMA通道																 
	//--------------------------------------------------------------
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_Channel            = DMA_Channel_0;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (rt_uint32_t)ADC1_DR_ADRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr    = (rt_uint32_t)ADC1_ValTemp;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize         = ADC1_BUF_LENGTH;
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

	DMA_DeInit(DMA2_Stream1);
	DMA_InitStructure.DMA_Channel            = DMA_Channel_2; 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (rt_uint32_t)ADC3_DR_ADRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr    = (rt_uint32_t)ADC3_ValTemp;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize         = ADC3_BUF_LENGTH;
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);

	/* ADC Common Init **********************************************************/
	ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler        = ADC_Prescaler_Div4;
	ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//-------------------------------------------------------------------
	// ADC控制器的配置
	//-------------------------------------------------------------------
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Resolution           = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode         = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode   = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Falling;
	ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_T8_CC1;
	ADC_InitStructure.ADC_DataAlign            = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion      = ADC1_CHANNELS; 
	ADC_Init(ADC1, &ADC_InitStructure);

	//.......................................................................................
	/* ADC1 regular channel configuration                                                  */ 	
	/* ADC1 采样时间：SampleTime+12  个采样周期，ADC的时钟84/4 = 21MHz                     */ 	
	/* 例如         ：480 + 12 = 492个采样周期                                             */ 	
	/*  转换一个通道的时间 = 492 * 1 / 21 = 23.4 us                                        */
	//.......................................................................................
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4,  1, ADC_SampleTime_480Cycles);//tmp0(1#整流模块温度)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5,  2, ADC_SampleTime_480Cycles);//tmp1(2#整流模块温度)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6,  3, ADC_SampleTime_480Cycles);//tmp2(进风口温度)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7,  4, ADC_SampleTime_480Cycles);//tmp3(出风口温度)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8,  5, ADC_SampleTime_480Cycles);//tmp4(1#电容模块温度)
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9,  6, ADC_SampleTime_480Cycles);//tmp5(2#电容模块温度)

	/* ADC3 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Resolution           = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode         = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode   = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Falling;
	ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConv_T8_CC1;
	ADC_InitStructure.ADC_DataAlign            = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion      = ADC3_CHANNELS;	 
	ADC_Init(ADC3, &ADC_InitStructure);
	//.......................................................................................
	/* ADC3 regular channel configuration                                                  */ 	
	/* ADC3 采样时间：SampleTime+12  个采样周期，ADC的时钟84/4 = 21MHz                     */ 	
	/* 例如         ：480 + 12 = 492个采样周期                                             */ 	
	/*  转换一个通道的时间 = 492 * 1 / 21 = 23.4 us                                        */
	//.......................................................................................
	ADC_RegularChannelConfig(ADC3, ADC_Channel_1,  1, ADC_SampleTime_480Cycles);//iAD0(1#整流电流)
	ADC_RegularChannelConfig(ADC3, ADC_Channel_2,  2, ADC_SampleTime_480Cycles);//iAD1(2#整流电流)
	ADC_RegularChannelConfig(ADC3, ADC_Channel_3,  3, ADC_SampleTime_480Cycles);//iAD2(预留)
	ADC_RegularChannelConfig(ADC3, ADC_Channel_10, 4, ADC_SampleTime_480Cycles);//uAD0(1#交流输入电压)
	ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 5, ADC_SampleTime_480Cycles);//uAD1(2#交流输入电压)
	ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 6, ADC_SampleTime_480Cycles);//uAD2(母线电压)	
	
	/* Enable DMA request after last transfer (Single-ADC mode) */
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	/* Enable DMA request after last transfer (Single-ADC mode) */
	ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
	//----------------------------------------
	// 启动ADC1 和 与之挂钩的DMA2
	//----------------------------------------
	/* Enable DMA Stream0 */
	DMA_Cmd(DMA2_Stream0, ENABLE);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	//----------------------------------------
	// 启动ADC3 和 与之挂钩的DMA2
	//----------------------------------------
	/* Enable DMA Stream1 */
	DMA_Cmd(DMA2_Stream1, ENABLE);
	/* Enable ADC3 DMA */
	ADC_DMACmd(ADC3, ENABLE);
	/* Enable ADC3 */
	ADC_Cmd(ADC3, ENABLE);
	//-------------------------------------------------------------
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//             启动TIM8，触发ADC1，ADC3的规则组转换
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//-------------------------------------------------------------
	TIM_ARRPreloadConfig(ADC_TIM, ENABLE);
	/* TIM8 counter enable */
	TIM_Cmd(ADC_TIM, ENABLE);
	/* TIM8 main Output Enable */
	TIM_CtrlPWMOutputs(ADC_TIM, ENABLE); 

	return 0;
}

/*******************************************************************************
* Function Name  : adc_update 
* Description    : adc_update[ADC_INPUT_CHANEL_MAX][ADC_FLTBUFFER_SIZE] 
* Input          : - none.
* Output         : None
* Return         : None
*******************************************************************************/

static uint16_t ACcal(uint16_t vSrc)
{
	uint16_t  val;
	
	if (vSrc > 2048)
	{
		val = vSrc - 2048;
	}
	else
	{
		val = 2048 - vSrc;
	}
	return val*val;
}

static int ACFltAnalog(int sum, int lenth)
{
	double ss;
	
	ss = (double)sum / lenth;
	
	return (int)sqrt(ss);
}

void adc_update(void)
{
	rt_uint8_t i = 0;
	//ad_buffer;
	int sum0 = 0;
	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;
	int sum4 = 0;
	int sum5 = 0;
	int sum6 = 0;
	int sum7 = 0;
	int sum8 = 0;
	int sum9 = 0;
	int sum10 = 0;

	for(i = 0; i < ADC_FLT1_BUFFER_SIZE; i++)
	{
		sum0 += ADC1_ValTemp[i * ADC1_CHANNELS + 0]; 
		sum1 += ADC1_ValTemp[i * ADC1_CHANNELS + 1];
		sum2 += ADC1_ValTemp[i * ADC1_CHANNELS + 2];
		sum3 += ADC1_ValTemp[i * ADC1_CHANNELS + 3];
		sum4 += ADC1_ValTemp[i * ADC1_CHANNELS + 4];
		sum5 += ADC1_ValTemp[i * ADC1_CHANNELS + 5];

		sum6 += ADC3_ValTemp[i * ADC3_CHANNELS + 0];
		sum7 += ADC3_ValTemp[i * ADC3_CHANNELS + 1];
		sum8 += ACcal(ADC3_ValTemp[i * ADC3_CHANNELS + 3]);
		sum9 += ACcal(ADC3_ValTemp[i * ADC3_CHANNELS + 4]);
		sum10 += ADC3_ValTemp[i * ADC3_CHANNELS + 5];
	}
	ad_buffer[temp_module1_index] = sum0 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[temp_module2_index] = sum1 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[temp_in_index] = sum2 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[temp_out_index] = sum3 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[temp_cap1_index] = sum4 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[temp_cap2_index] = sum5 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[i_in1_index] = sum6 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[i_in2_index] = sum7 / ADC_FLT1_BUFFER_SIZE;
	ad_buffer[u_ac1_index] = ACFltAnalog(sum8, ADC_FLT1_BUFFER_SIZE);
	ad_buffer[u_ac2_index] = ACFltAnalog(sum9, ADC_FLT1_BUFFER_SIZE);
	ad_buffer[u_bus_index] = sum10 / ADC_FLT1_BUFFER_SIZE;
}

int * get_ad_data_buffer(void)
{
    return ad_buffer;
}

/******************* (C) COPYRIGHT 2013 TongYe **********END OF FILE****/

/*@}*/

