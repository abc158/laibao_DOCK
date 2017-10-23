/*********************************************************************************************************//**
 * @file    AM38x_exti.h
 * @version V1.0
 * @date    10/01/2013
 * @brief   The header file of the EXTI library.
 *************************************************************************************************************
 *
 * <h2><center>Copyright (C) 2013 Amicro Semiconductor Inc. All rights reserved</center></h2>
 *
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __EXTI_H
#define __EXTI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "AM8813.h"

/** @addtogroup AM38x_Peripheral_Driver
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/* Exported types ------------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Types EXTI exported types
  * @{
  */

/* Definitions of EXTI interrupt line */
typedef enum
{
  EXTI_CHANNEL_0 = 0,
  EXTI_CHANNEL_1,
  EXTI_CHANNEL_2,
  EXTI_CHANNEL_3,
  EXTI_CHANNEL_4,
  EXTI_CHANNEL_5,
  EXTI_CHANNEL_6,
  EXTI_CHANNEL_7,
  EXTI_CHANNEL_8,
  EXTI_CHANNEL_9,
  EXTI_CHANNEL_10,
  EXTI_CHANNEL_11,
  EXTI_CHANNEL_12,
  EXTI_CHANNEL_13,
  EXTI_CHANNEL_14,
  EXTI_CHANNEL_15
}EXTI_Channel_TypeDef;

#define IS_EXTI_CHANNEL(CHANNEL)                    ((CHANNEL == EXTI_CHANNEL_0) || \
                                                     (CHANNEL == EXTI_CHANNEL_1) || \
                                                     (CHANNEL == EXTI_CHANNEL_2) || \
                                                     (CHANNEL == EXTI_CHANNEL_3) || \
                                                     (CHANNEL == EXTI_CHANNEL_4) || \
                                                     (CHANNEL == EXTI_CHANNEL_5) || \
                                                     (CHANNEL == EXTI_CHANNEL_6) || \
                                                     (CHANNEL == EXTI_CHANNEL_7) || \
                                                     (CHANNEL == EXTI_CHANNEL_8) || \
                                                     (CHANNEL == EXTI_CHANNEL_9) || \
                                                     (CHANNEL == EXTI_CHANNEL_10) || \
                                                     (CHANNEL == EXTI_CHANNEL_11) || \
                                                     (CHANNEL == EXTI_CHANNEL_12) || \
                                                     (CHANNEL == EXTI_CHANNEL_13) || \
                                                     (CHANNEL == EXTI_CHANNEL_14) || \
                                                     (CHANNEL == EXTI_CHANNEL_15))

/* Definitions of EXTI init structure */
typedef enum
{
  EXTI_LOW_LEVEL     = 0x0,
  EXTI_HIGH_LEVEL    = 0x1,
  EXTI_NEGATIVE_EDGE = 0x2,
  EXTI_POSITIVE_EDGE = 0x3,
  EXTI_BOTH_EDGE     = 0x4
}EXTIInterrupt_TypeDef;

#define IS_EXTI_INT_TYPE(TYPE)                      ((TYPE == EXTI_LOW_LEVEL) || \
                                                     (TYPE == EXTI_HIGH_LEVEL) || \
                                                     (TYPE == EXTI_NEGATIVE_EDGE) || \
                                                     (TYPE == EXTI_POSITIVE_EDGE) || \
                                                     (TYPE == EXTI_BOTH_EDGE))

typedef enum
{
  EXTI_DEBOUNCE_DISABLE = 0x0,
  EXTI_DEBOUNCE_ENABLE  = 0x1
}EXTIDeb_TypeDef;

#define IS_EXTI_DEBOUNCE_TYPE(TYPE)                 ((TYPE == EXTI_DEBOUNCE_DISABLE) || \
                                                     (TYPE == EXTI_DEBOUNCE_ENABLE))

typedef struct
{
  u32 EXTI_Channel;
  EXTIDeb_TypeDef EXTI_Debounce;
  u32 EXTI_DebounceCnt;
  EXTIInterrupt_TypeDef EXTI_IntType;
}EXTI_InitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Constants EXTI exported constants
  * @{
  */

/* Definitions of EXTI wake up polarity */
#define EXTI_WAKEUP_HIGH_LEVEL                      ((u8)0x0)
#define EXTI_WAKEUP_LOW_LEVEL                       ((u8)0x1)

#define IS_EXTI_WAKEUP_TYPE(TYPE)                   ((TYPE == EXTI_WAKEUP_HIGH_LEVEL) || \
                                                     (TYPE == EXTI_WAKEUP_LOW_LEVEL))


#define EXTI_EDGE_POSITIVE                          ((u8)0x0)
#define EXTI_EDGE_NEGATIVE                          ((u8)0x1)

#define IS_EXTI_EDGE(EDGE)                          ((EDGE == EXTI_EDGE_POSITIVE) || \
                                                     (EDGE == EXTI_EDGE_NEGATIVE))


#define IS_EXTI_DEBOUNCE_SIZE(SIZE)                 (SIZE <= 0xFFFFFFF)

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Macro EXTI exported macro
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/

/** @defgroup EXTI_Exported_Functions EXTI exported functions
  * @{
  */

void EXTI_DeInit(u32 EXTI_Channel);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_IntConfig(u32 EXTI_Channel, ControlStatus NewState);
void EXTI_WakeupEventConfig(u32 EXTI_Channel, u8 EXTI_WakeUpType, ControlStatus NewState);
void EXTI_WakeupEventIntConfig(ControlStatus NewState);
void EXTI_ClearEdgeFlag(u32 EXTI_Channel);
void EXTI_ClearWakeupFlag(u32 EXTI_Channel);
FlagStatus EXTI_GetEdgeStatus(u32 EXTI_Channel, u32 EXTI_Edge);
FlagStatus EXTI_GetWakeupFlagStatus(u32 EXTI_Channel);
void EXTI_SWIntCmd(u32 EXTI_Channel, ControlStatus NewState);
u32 EXTI_GetSWCmdStatus(u32 EXTI_Channel);

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

#endif /* __AM38x_EXTI_H ----------------------------------------------------------------------------*/
