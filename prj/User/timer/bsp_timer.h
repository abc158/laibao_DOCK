/********************************************************************************************************//**
 * @file    bsp_timer.h	
 * @brief   The header file of the bsp_timer.
 * @author  Amicro
 * @version V1.00
 * @date:   2017-3-27
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
#ifndef __BSP_TIMER_H
#define __BSP_TIMER_H
#include "AM8813.h"
#include "gptm.h"
#include "AM8813_misc.h"
#include "gpio.h"

#define TIMx			AM_GPTM0
#define TIMx_INT 	GPTM_INT_CH0CC
#define TIMx_Flag	GPTM_FLAG_CH0CC

#define TIM1			AM_GPTM1
#define TIM1_INT 	GPTM_INT_CH1CC
#define TIM1_Flag	GPTM_FLAG_CH1CC

static void TIMx_NVIC_Configuration(void);
void TIM_Mode_Config(void);

#endif
