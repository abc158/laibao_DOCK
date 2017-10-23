/********************************************************************************************************//**
 * @file    system.c
 * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer Source File
 * @version V1.00
 * @date:   2017-3-11
 * @note
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "system.h"

static __IO u32 TimingDelay;

/*********************************************************************************************************//**
 * @brief  Setup the microcontroller system.
 *         Initializes the system clocks and the embedded Flash.
 * @note   This function should be used after reset.
 * @param  None
 * @retval None
 ************************************************************************************************************/
void SystemInit(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 100000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   us��ʱ����,10usΪһ����λ
  * @param  
  *	@arg nTime: Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 10us = 10us
  * @retval  ��
  */
void Delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	
	while(TimingDelay != 0);
}

void Delay_ms(__IO u32 nTime)
{ 
	__IO u32 i;
	for(i=0;i<nTime;i++)
	{
		Delay_us(100);
	}
}
/*********************************************************************************************************//**
 * @brief  Update SystemCoreClock
 * @note   This function should be used after reset.
 * @param  None
 * @retval None
 ************************************************************************************************************/
void SystemCoreClockUpdate(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

