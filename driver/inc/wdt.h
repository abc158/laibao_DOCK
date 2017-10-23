/********************************************************************************************************//**
 * @file    wdt.h	
 * @brief   The header file of the Wdt Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __WDT_H
#define __WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "AM8813.h"

/** @defgroup WDT_Exported_Constants WDT exported constants
  * @{
  */

/* WDT prescaler */
#define WDT_PRESCALER_1                           ((u16)0x0000)
#define WDT_PRESCALER_2                           ((u16)0x1000)
#define WDT_PRESCALER_4                           ((u16)0x2000)
#define WDT_PRESCALER_8                           ((u16)0x3000)
#define WDT_PRESCALER_16                          ((u16)0x4000)
#define WDT_PRESCALER_32                          ((u16)0x5000)
#define WDT_PRESCALER_64                          ((u16)0x6000)
#define WDT_PRESCALER_128                         ((u16)0x7000)

#define IS_WDT_PRESCALER(PRESCALER)               ((PRESCALER == WDT_PRESCALER_1) || \
                                                   (PRESCALER == WDT_PRESCALER_2) || \
                                                   (PRESCALER == WDT_PRESCALER_4) || \
                                                   (PRESCALER == WDT_PRESCALER_8) || \
                                                   (PRESCALER == WDT_PRESCALER_16) || \
                                                   (PRESCALER == WDT_PRESCALER_32) || \
                                                   (PRESCALER == WDT_PRESCALER_64) || \
                                                   (PRESCALER == WDT_PRESCALER_128))


/* WDT runs or halts in sleep and deep sleep1 mode  */
/* WDT WDTSHLT mask */
#define MODE0_WDTSHLT_BOTH     ((u32)0x00000000)
#define MODE0_WDTSHLT_SLEEP    ((u32)0x00004000)
#define MODE0_WDTSHLT_HALT     ((u32)0x00008000)

#define IS_WDT_WDTSHLT_MODE(WDT_Mode)              ((WDT_Mode == MODE0_WDTSHLT_BOTH) || \
                                                   (WDT_Mode == MODE0_WDTSHLT_SLEEP) || \
                                                   (WDT_Mode == MODE0_WDTSHLT_HALT))



/* WDT Flag */
#define WDT_FLAG_UNDERFLOW                        ((u32)0x00000001)
#define WDT_FLAG_ERROR                            ((u32)0x00000002)


#define IS_WDT_FLAG(WDT_FLAG)                     ((WDT_FLAG == WDT_FLAG_UNDERFLOW) || \
                                                   (WDT_FLAG == WDT_FLAG_ERROR))


#define IS_WDT_RELOAD(WDTV)                       ((WDTV <= 0xFFF))

#define IS_WDT_DELTA(WDTD)                        ((WDTD <= 0xFFF))

/* WDT Source Select */
#define WDT_SOURCE_LSI                            ((u32)0x00000000)
#define WDT_SOURCE_LSE                            ((u32)0x00000001)


#define IS_WDT_SOURCE_SELECT(WDT_SOURCE)           ((WDT_SOURCE == WDT_SOURCE_LSI) || \
                                                   (WDT_SOURCE == WDT_SOURCE_LSE))


/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup WDT_Exported_Functions WDT exported functions
  * @{
  */

void WDT_DeInit(void);
void WDT_Cmd(ControlStatus NewState);
void WDT_IntConfig(ControlStatus NewState);
void WDT_HaltConfig(u32 WDT_Mode);
void WDT_ResetCmd(ControlStatus NewState);
void WDT_ProtectCmd(ControlStatus NewState);
void WDT_SetReloadValue(u16 WDTV);
u16 WDT_GetReloadValue(void);
void WDT_SetDeltaValue(u16 WDTD);
u16 WDT_GetDeltaValue(void);
void WDT_SetPrescaler(u16 WDT_PRESCALER);
u8 WDT_GetPrescaler(void);
void WDT_Restart(void);
FlagStatus WDT_GetFlagStatus (u32 WDT_FLAG);
void WDT_LockCmd(ControlStatus NewState);
void WDT_SourceConfig( u32 WDT_SOURCE );

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
