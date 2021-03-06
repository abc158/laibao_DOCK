/********************************************************************************************************//**
 * @file    misc.h	
 * @brief   The header file of the miscellaneous firmware library..
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#ifndef __MISC_H
#define __MISC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

/* Vector Table Base */
#define NVIC_VECTTABLE_RAM                          ((u32)0x20000000)
#define NVIC_VECTTABLE_FLASH                        ((u32)0x00000000)

#define IS_NVIC_VECTTABLE(VECTTABLE)                ((VECTTABLE == NVIC_VECTTABLE_RAM) || \
                                                     (VECTTABLE == NVIC_VECTTABLE_FLASH))

#define IS_NVIC_OFFSET(OFFSET)                      (OFFSET < 0x0001FFFF)

/* System Low Power */
#define NVIC_LOWPOWER_SEVONPEND                     ((u8)0x10)
#define NVIC_LOWPOWER_SLEEPDEEP                     ((u8)0x04)
#define NVIC_LOWPOWER_SLEEPONEXIT                   ((u8)0x02)

#define IS_NVIC_LOWPOWER(LOWPOWER)                  ((LOWPOWER == NVIC_LOWPOWER_SEVONPEND) || \
                                                     (LOWPOWER == NVIC_LOWPOWER_SLEEPDEEP) || \
                                                     (LOWPOWER == NVIC_LOWPOWER_SLEEPONEXIT))

/* System Handler */
#define SYSTEMHANDLER_NMI                           ((u32)0x80000000)
#define SYSTEMHANDLER_PSV                           ((u32)0x10000000)
#define SYSTEMHANDLER_SYSTICK                       ((u32)0x04000000)
#define SYSTEMHANDLER_ALL                           ((u32)0x94000000)

#define IS_NVIC_SYSTEMHANDLER(HANDLER)              ((HANDLER == SYSTEMHANDLER_NMI)     || \
                                                     (HANDLER == SYSTEMHANDLER_PSV)     || \
                                                     (HANDLER == SYSTEMHANDLER_SYSTICK) ||\
                                                     (HANDLER == SYSTEMHANDLER_ALL))

/* SysTick clock source */
#define SYSTICK_SRC_FCLK                            ((u32)0x00000004)

#define IS_SYSTICK_CLOCK_SOURCE(SOURCE)             ((SOURCE == SYSTICK_SRC_STCLK) || \
                                                     (SOURCE == SYSTICK_SRC_FCLK) )

/* SysTick counter state  */
#define SYSTICK_COUNTER_DISABLE                     ((u32)0xFFFFFFFE)
#define SYSTICK_COUNTER_ENABLE                      ((u32)0x00000001)
#define SYSTICK_COUNTER_CLEAR                       ((u32)0x00000000)

#define IS_SYSTICK_COUNTER(COUNTER)                 ((COUNTER == SYSTICK_COUNTER_DISABLE) || \
                                                     (COUNTER == SYSTICK_COUNTER_ENABLE)  || \
                                                     (COUNTER == SYSTICK_COUNTER_CLEAR))

#define IS_SYSTICK_RELOAD(RELOAD)                   ((RELOAD  > 0) && (RELOAD <= 0xFFFFFF))

/**
  * @}
  */



/** @defgroup MISC_Exported_Functions MISC exported functions
  * @{
  */

void NVIC_SetVectorTable(u32 NVIC_VectTable, u32 NVIC_Offset);
void NVIC_LowPowerConfig(u8 NVIC_LowPowerMode, ControlStatus NewState);
void NVIC_CoreReset(void);
void NVIC_SetPendingSystemHandler(u32 SystemHandler);
void SYSTICK_ClockSourceConfig(u32 SysTick_ClockSource);
void SYSTICK_CounterCmd(u32 SysTick_Counter);
void SYSTICK_IntConfig(ControlStatus NewState);
void SYSTICK_SetReloadValue(u32 SysTick_Reload);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif 
