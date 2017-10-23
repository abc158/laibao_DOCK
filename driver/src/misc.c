/********************************************************************************************************//**
 * @file    misc.c	
 * @brief   The c file of the miscellaneous firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#include "misc.h"

#define AIRCR_VECTKEY_MASK    ((u32)0x05FA0000)

#define CTRL_TICKINT_SET      ((u32)0x00000002)
#define CTRL_TICKINT_RESET    ((u32)0xFFFFFFFD)

/*********************************************************************************************************//**
  * @brief  Set the vector table location and Offset.
  * @param  NVIC_VectTable: Specify if the vector table is in FLASH or RAM.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VECTTABLE_RAM
  *     @arg NVIC_VECTTABLE_FLASH
  * @param  NVIC_Offset: Vector Table base offset field.
  *   This value must be a multiple of 0x100.
  * @retval None
  ***********************************************************************************************************/
void NVIC_SetVectorTable(u32 NVIC_VectTable, u32 NVIC_Offset)
{
//  SCB->VTOR = NVIC_VectTable | (NVIC_Offset & (u32)0x1FFFFF80);		
	  SCB->RESERVED0 = NVIC_VectTable | (NVIC_Offset & (u32)0x1FFFFF80);
}

/*********************************************************************************************************//**
  * @brief  Select which low power mode to execute to the system.
  * @param  NVIC_LowPowerMode:  Specify the new low power mode to execute to the system.
  *   This parameter can be one of the following values:
  *     @arg NVIC_LOWPOWER_SEVONPEND
  *     @arg NVIC_LOWPOWER_SLEEPDEEP
  *     @arg NVIC_LOWPOWER_SLEEPONEXIT
  * @param  NewState: new state of low power condition.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void NVIC_LowPowerConfig(u8 NVIC_LowPowerMode,  ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    SCB->SCR |= NVIC_LowPowerMode;
  }
  else
  {
    SCB->SCR &= (u32)(~(u32)NVIC_LowPowerMode);
  }
}

/*********************************************************************************************************//**
  * @brief  Generate a Core (Core + NVIC) reset.
  * @retval None
  ***********************************************************************************************************/
void NVIC_CoreReset(void)
{
  SCB->AIRCR = AIRCR_VECTKEY_MASK | (u32)0x04;
}
/*********************************************************************************************************//**
  * @brief  Set the pending bit for a system handler.
  * @param  SystemHandler: Specify the system handler pending bit to be set.
  *   This parameter can be one of the following values:
  *     @arg SYSTEMHANDLER_NMI
  *     @arg SYSTEMHANDLER_PSV
  *     @arg SYSTEMHANDLER_SYSTICK
  * @retval None
  ***********************************************************************************************************/
void NVIC_SetPendingSystemHandler(u32 SystemHandler)
{
  /* Set the corresponding System Handler pending bit */
  SCB->ICSR |= SystemHandler;
}

/*********************************************************************************************************//**
  * @brief  Configure the SysTick clock source.
  * @param  SysTick_ClockSource: Specify the SysTick clock source.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_SRC_FCLK   : AHB clock is selected as SysTick clock source.
  * @retval  None
  ***********************************************************************************************************/
void SYSTICK_ClockSourceConfig(u32 SysTick_ClockSource)
{
  if (SysTick_ClockSource == SYSTICK_SRC_FCLK)
  {
    SysTick->CTRL |= SYSTICK_SRC_FCLK;
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick counter.
  * @param  SysTick_Counter: new state of the SysTick counter.
  *   This parameter can be one of the following values:
  *     @arg SYSTICK_COUNTER_DISABLE  : Disable counter
  *     @arg SYSTICK_COUNTER_ENABLE   : Enable counter
  *     @arg SYSTICK_COUNTER_CLEAR    : Clear counter value to 0
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_CounterCmd(u32 SysTick_Counter)
{
  if (SysTick_Counter == SYSTICK_COUNTER_CLEAR)
  {
    SysTick->VAL = SYSTICK_COUNTER_CLEAR;
  }
  else
  {
    if (SysTick_Counter == SYSTICK_COUNTER_ENABLE)
    {
      SysTick->CTRL |= SYSTICK_COUNTER_ENABLE;
    }
    else
    {
      SysTick->CTRL &= SYSTICK_COUNTER_DISABLE;
    }
  }
}

/*********************************************************************************************************//**
  * @brief  Enable or Disable the SysTick Interrupt.
  * @param  NewState: new state of the SysTick Interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_IntConfig(ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    SysTick->CTRL |= CTRL_TICKINT_SET;
  }
  else
  {
    SysTick->CTRL &= CTRL_TICKINT_RESET;
  }
}

/*********************************************************************************************************//**
  * @brief  Set SysTick counter reload value.
  * @param  SysTick_Reload: SysTick reload new value.
  *   This parameter must be a number between 1 and 0xFFFFFF.
  * @retval None
  ***********************************************************************************************************/
void SYSTICK_SetReloadValue(u32 SysTick_Reload)
{
  SysTick->LOAD = SysTick_Reload;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
