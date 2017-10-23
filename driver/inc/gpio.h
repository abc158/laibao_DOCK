/********************************************************************************************************//**
 * @file    gpio.h	
 * @brief   The header file of the Gpio Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

/**
 * @brief  Enumeration of GPIO pull resistor.
 */
typedef enum
{
  GPIO_PR_UP = 0,   /*!< weak pull-up resistor */
  GPIO_PR_DOWN,     /*!< weak pull-down resistor */
  GPIO_PR_DISABLE   /*!< Tri-state */
}GPIO_PR_Enum ;
/**
 * @brief  Enumeration of GPIO output drive current.
 */
typedef enum
{
  GPIO_DV_3MA = 0,   /*!< 3mA source/sink current */
  GPIO_DV_6MA        /*!< 6mA source/sink current */
}GPIO_DV_Enum ;
/**
 * @brief  Enumeration of GPIO direction.
 */
typedef enum
{
  GPIO_DIR_IN = 0,    /*!< input mode */
  GPIO_DIR_OUT        /*!< output mode */
}GPIO_DIR_Enum ;
/**
 * @brief  Enumeration of GPIO port source for EXTI channel.
 */
typedef enum
{
  AFIO_ESS_PA = 0,  /*!< EXTI channel x source come from GPIO Port A */
  AFIO_ESS_PB,      /*!< EXTI channel x source come from GPIO Port B */
  AFIO_ESS_PC,      /*!< EXTI channel x source come from GPIO Port C */
  AFIO_ESS_PD,      /*!< EXTI channel x source come from GPIO Port D */
  AFIO_ESS_PE       /*!< EXTI channel x source come from GPIO Port E */
}AFIO_ESS_Enum ;
/**
 * @brief  Enumeration of AFIO for EXTI channel.
 */
typedef enum
{
  AFIO_EXTI_CH_0 = 0x00,     /*!< EXTI channel 0 */
  AFIO_EXTI_CH_1 = 0x04,     /*!< EXTI channel 1 */
  AFIO_EXTI_CH_2 = 0x08,     /*!< EXTI channel 2 */
  AFIO_EXTI_CH_3 = 0x0C,     /*!< EXTI channel 3 */
  AFIO_EXTI_CH_4 = 0x10,     /*!< EXTI channel 4 */
  AFIO_EXTI_CH_5 = 0x14,     /*!< EXTI channel 5 */
  AFIO_EXTI_CH_6 = 0x18,     /*!< EXTI channel 6 */
  AFIO_EXTI_CH_7 = 0x1C,     /*!< EXTI channel 7 */
  AFIO_EXTI_CH_8 = 0x20,     /*!< EXTI channel 8 */
  AFIO_EXTI_CH_9 = 0x24,     /*!< EXTI channel 9 */
  AFIO_EXTI_CH_10 = 0x28,    /*!< EXTI channel 10 */
  AFIO_EXTI_CH_11 = 0x2C,    /*!< EXTI channel 11 */
  AFIO_EXTI_CH_12 = 0x30,    /*!< EXTI channel 12 */
  AFIO_EXTI_CH_13 = 0x34,    /*!< EXTI channel 13 */
  AFIO_EXTI_CH_14 = 0x38,    /*!< EXTI channel 14 */
  AFIO_EXTI_CH_15 = 0x3C     /*!< EXTI channel 15 */
}AFIO_EXTI_CH_Enum ;
/**
 * @brief Enumeration of AFIO_MODE.
 */
typedef enum
{
 AFIO_MODE_DEFAULT = 0,   /*!< Default AFIO mode */
 AFIO_MODE_1,             /*!< AFIO mode 1 */
 AFIO_MODE_2,             /*!< AFIO mode 2 */
 AFIO_MODE_3,             /*!< AFIO mode 3 */
 AFIO_MODE_4,             /*!< AFIO mode 4 */
 AFIO_MODE_5,             /*!< AFIO mode 5 */
 AFIO_MODE_6,             /*!< AFIO mode 6 */
 AFIO_MODE_7,             /*!< AFIO mode 7 */
 AFIO_MODE_8,             /*!< AFIO mode 8 */
 AFIO_MODE_9,             /*!< AFIO mode 9 */
 AFIO_MODE_10,            /*!< AFIO mode 10 */
 AFIO_MODE_11,            /*!< AFIO mode 11 */
 AFIO_MODE_12,            /*!< AFIO mode 12 */
 AFIO_MODE_13,            /*!< AFIO mode 13 */
 AFIO_MODE_14,            /*!< AFIO mode 14 */
 AFIO_MODE_15             /*!< AFIO mode 15 */
}AFIO_MODE_Enum ;
/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants GPIO exported constants
  * @{
  */

/* Definitions of GPIO_PIN */
#define GPIO_PIN_0    0x0001   /*!< GPIO pin 0 selected */
#define GPIO_PIN_1    0x0002   /*!< GPIO pin 1 selected */
#define GPIO_PIN_2    0x0004   /*!< GPIO pin 2 selected */
#define GPIO_PIN_3    0x0008   /*!< GPIO pin 3 selected */
#define GPIO_PIN_4    0x0010   /*!< GPIO pin 4 selected */
#define GPIO_PIN_5    0x0020   /*!< GPIO pin 5 selected */
#define GPIO_PIN_6    0x0040   /*!< GPIO pin 6 selected */
#define GPIO_PIN_7    0x0080   /*!< GPIO pin 7 selected */
#define GPIO_PIN_8    0x0100   /*!< GPIO pin 8 selected */
#define GPIO_PIN_9    0x0200   /*!< GPIO pin 9 selected */
#define GPIO_PIN_10   0x0400   /*!< GPIO pin 10 selected */
#define GPIO_PIN_11   0x0800   /*!< GPIO pin 11 selected */
#define GPIO_PIN_12   0x1000   /*!< GPIO pin 12 selected */
#define GPIO_PIN_13   0x2000   /*!< GPIO pin 13 selected */
#define GPIO_PIN_14   0x4000   /*!< GPIO pin 14 selected */
#define GPIO_PIN_15   0x8000   /*!< GPIO pin 15 selected */
#define GPIO_PIN_ALL  0xFFFF   /*!< GPIO all pins selected */

/* Definitions of AFIO_PIN */
#define AFIO_PIN_0   (u32)0x00000001 /*!< AFIO pin 0 selected */
#define AFIO_PIN_1   (u32)0x00000002 /*!< AFIO pin 1 selected */
#define AFIO_PIN_2   (u32)0x00000004 /*!< AFIO pin 2 selected */
#define AFIO_PIN_3   (u32)0x00000008 /*!< AFIO pin 3 selected */
#define AFIO_PIN_4   (u32)0x00000010 /*!< AFIO pin 4 selected */
#define AFIO_PIN_5   (u32)0x00000020 /*!< AFIO pin 5 selected */
#define AFIO_PIN_6   (u32)0x00000040 /*!< AFIO pin 6 selected */
#define AFIO_PIN_7   (u32)0x00000080 /*!< AFIO pin 7 selected */
#define AFIO_PIN_8   (u32)0x00000100 /*!< AFIO pin 8 selected */
#define AFIO_PIN_9   (u32)0x00000200 /*!< AFIO pin 9 selected */
#define AFIO_PIN_10  (u32)0x00000400 /*!< AFIO pin 10 selected */
#define AFIO_PIN_11  (u32)0x00000800 /*!< AFIO pin 11 selected */
#define AFIO_PIN_12  (u32)0x00001000 /*!< AFIO pin 12 selected */
#define AFIO_PIN_13  (u32)0x00002000 /*!< AFIO pin 13 selected */
#define AFIO_PIN_14  (u32)0x00004000 /*!< AFIO pin 14 selected */
#define AFIO_PIN_15  (u32)0x00008000 /*!< AFIO pin 15 selected */
#define AFIO_PIN_ALL (u32)0x0000FFFF /*!< All AFIO pins selected */

/* check parameter of the GPIOx */
#define IS_GPIO(x)          ((x == AM_GPIOA) || (x == AM_GPIOB) || (x == AM_GPIOC) || (x == AM_GPIOD) || \
                             (x == AM_GPIOE))

/* check parameter of the GPIOx pull resistor */
#define IS_GPIO_PR(x)       (((x) == GPIO_PR_UP) || ((x) == GPIO_PR_DOWN) || ((x) == GPIO_PR_DISABLE))

/* check parameter of the GPIOx driving current */
#define IS_GPIO_DV(x)       (((x) == GPIO_DV_4MA) || ((x) == GPIO_DV_8MA) )

/* check parameter of the GPIOx input/output direction */
#define IS_GPIO_DIR(x)      (((x) == GPIO_DIR_IN) || ((x) == GPIO_DIR_OUT) )

/* check parameter of the EXTI source port */
#define IS_AFIO_ESS(x)      ((x == AFIO_ESS_PA) || (x == AFIO_ESS_PB) || (x == AFIO_ESS_PC) || (x == AFIO_ESS_PD)\
                             || (x == AFIO_ESS_PE))

/* check parameter of the EXTI channel */
#define IS_AFIO_EXTI_CH(x)  ((x == AFIO_EXTI_CH_0) || (x == AFIO_EXTI_CH_1) || \
                             (x == AFIO_EXTI_CH_2) || (x == AFIO_EXTI_CH_3) || \
                             (x == AFIO_EXTI_CH_4) || (x == AFIO_EXTI_CH_5) || \
                             (x == AFIO_EXTI_CH_6) || (x == AFIO_EXTI_CH_7) || \
                             (x == AFIO_EXTI_CH_8) || (x == AFIO_EXTI_CH_9) || \
                             (x == AFIO_EXTI_CH_10) || (x == AFIO_EXTI_CH_11) || \
                             (x == AFIO_EXTI_CH_12) || (x == AFIO_EXTI_CH_13) || \
                             (x == AFIO_EXTI_CH_14) || (x == AFIO_EXTI_CH_15))

/* check parameter of the AFIO mode */
#define IS_AFIO_MODE(x)     ((x == AFIO_MODE_DEFAULT) || (x == AFIO_MODE_1) || \
                             (x == AFIO_MODE_2) || (x == AFIO_MODE_3) || \
                             (x == AFIO_MODE_4) || (x == AFIO_MODE_5) || \
                             (x == AFIO_MODE_6) || (x == AFIO_MODE_7) || \
                             (x == AFIO_MODE_8) || (x == AFIO_MODE_9) || \
                             (x == AFIO_MODE_10) || (x == AFIO_MODE_11) || \
                             (x == AFIO_MODE_12) || (x == AFIO_MODE_13) || \
                             (x == AFIO_MODE_14) || (x == AFIO_MODE_15))

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions GPIO exported functions
  * @{
  */

/* Prototype of related GPIO function */
void GPIO_DeInit(AM_GPIO_TypeDef* GPIOx) ;
void GPIO_DirectionConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DIR_Enum Direction) ;
void GPIO_PullResistorConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_PR_Enum PR) ;
void GPIO_InputConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd) ;
void GPIO_DriveConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DV_Enum Drive) ;
void GPIO_OpenDrainConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd) ;
FlagStatus GPIO_ReadInBit(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
FlagStatus GPIO_ReadOutBit(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
u16 GPIO_ReadInData(AM_GPIO_TypeDef* GPIOx);
u16 GPIO_ReadOutData(AM_GPIO_TypeDef* GPIOx);
void GPIO_SetOutBits(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
void GPIO_ClearOutBits(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
void GPIO_WriteOutBits(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, FlagStatus Status);
void GPIO_WriteOutData(AM_GPIO_TypeDef* GPIOx, u16 Data);
void GPIO_PinLock(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN);
bool GPIO_IsPortLocked(AM_GPIO_TypeDef* GPIOx);
bool GPIO_IsPinLocked(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN);

/* Prototype of related AFIO function */
void AFIO_DeInit(void) ;
void AFIO_GPAConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_GPBConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_GPCConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_GPDConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_GPEConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_GPFConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_GPGConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE);
void AFIO_EXTISourceConfig(AFIO_EXTI_CH_Enum Channel, AFIO_ESS_Enum Source);

FlagStatus exti_clear_edge_flag(AFIO_EXTI_CH_Enum exti_line_x);
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
