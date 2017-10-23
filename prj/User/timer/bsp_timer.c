/********************************************************************************************************//**
 * @file    bsp_timer.c
 * @brief   Timer Driver
 * @author  Amicro
 * @version V1.00
 * @date:   2017-3-27
 * @note		1.计时器满进中断；2.进中断Toggle LED1的引脚；
 * @Pin
 *********************************************
 *TIMx | CHx | PIN | PIN | PIN | AFx *
 *********************************************
 *TIM0 | CH0 | PA6 | PD10| *** | AF7 *->T0_CH0
 *TIM0 | CH1 | PA7 | PD11| *** | AF7 *->T0_CH1
 *TIM0 | CH2 | PA8 | PD12| PA3 | AF7 *->T0_CH2
 *TIM0 | CH3 | PA14| PD13| *** | AF7 *->T0_CH3
 *TIM0 | ETI | PA0 | PB7 | *** | AF7 *->T0_ETI
 *********************************************
 *TIM1 | CH0 | PA15| PD14| *** | AF7 *->T1_CH0
 *TIM1 | CH1 | PB6 | PD15| *** | AF7 *->T1_CH1
 *TIM1 | CH2 | PB8 | PE0 | *** | AF7 *->T1_CH2
 *TIM1 | CH3 | PB11| PE1 | *** | AF7 *->T1_CH3
 *TIM1 | ETI | PA1 | *** | *** | AF7 *->T1_ETI
 *********************************************
 *TIM2 | CH0 | PB13| PC8 | *** | AF7 *->T2_CH0
 *TIM2 | CH1 | PB15| PD6 | *** | AF7 *->T2_CH1
 *TIM2 | CH2 | PC0 | PC9 | *** | AF7 *->T2_CH2
 *TIM2 | CH3 | PD0 | PD7 | *** | AF7 *->T2_CH3
 *TIM2 | ETI | PA2 | *** | *** | AF7 *->T2_ETI
 *********************************************
 *TIM3 | CH0 | PD2 | *** | *** | AF7 *->T3_CH0
 *TIM3 | CH1 | PD3 | *** | *** | AF7 *->T3_CH1
 *TIM3 | CH2 | PD4 | *** | *** | AF7 *->T3_CH2
 *TIM3 | CH3 | PD5 | *** | *** | AF7 *->T3_CH3
 *TIM3 | ETI | PA13| *** | *** | AF7 *->T3_ETI
 *********************************************
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#include "bsp_timer.h"

static void TIMx_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannel = GPTM0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

static void TIM1_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannel = GPTM1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}
void TIM_Mode_Config(void)
{
	GPTM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
			
	GPTM_DeInit(TIMx);
	TIM_TimeBaseStructure.CounterMode = GPTM_CNT_MODE_UP;
	TIM_TimeBaseStructure.Prescaler = 4-1;// 高级控制定时器时钟源TIMxCLK = HCLK = 24MHz；设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=6000000Hz
	TIM_TimeBaseStructure.CounterReload = 1500-1; //当定时器从0计数到5999，即为6000次，为一个定时周期；进中断的频率为=6000000/6000=1000Hz
	TIM_TimeBaseStructure.PSCReloadTime = GPTM_PSC_RLD_IMMEDIATE;
	GPTM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
	
	TIMx_NVIC_Configuration();
	GPTM_ClearFlag(TIMx, TIMx_Flag);
	GPTM_IntConfig(TIMx,TIMx_INT,ENABLE);
	GPTM_Cmd(TIMx, ENABLE);
	
  GPTM_DeInit(TIM1);
	TIM_TimeBaseStructure.CounterMode = GPTM_CNT_MODE_UP;
	TIM_TimeBaseStructure.Prescaler = 4-1;// 高级控制定时器时钟源TIMxCLK = HCLK = 24MHz；设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=6000000Hz
	TIM_TimeBaseStructure.CounterReload = 60000-1; //当定时器从0计数到5999，即为6000次，为一个定时周期；进中断的频率为=6000000/6000=1000Hz
	TIM_TimeBaseStructure.PSCReloadTime = GPTM_PSC_RLD_IMMEDIATE;
	GPTM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	TIM1_NVIC_Configuration();
	GPTM_ClearFlag(TIM1, TIM1_Flag);
	GPTM_IntConfig(TIM1,TIM1_INT,ENABLE);
	GPTM_Cmd(TIM1, ENABLE);
}




