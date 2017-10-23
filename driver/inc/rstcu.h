/********************************************************************************************************//**
 * @file    rstcu.h	
 * @brief   The header file of the Reset Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/


#ifndef __RSTCU_H
#define __RSTCU_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

/** @addtogroup RSTCU
  * @{
  */

/**
 * @brief Enumeration of Global reset status.
 */
typedef enum
{
  RSTCU_FLAG_SYSRST = 0,
  RSTCU_FLAG_EXTRST,
  RSTCU_FLAG_WDTRST,
  RSTCU_FLAG_PORST
} RSTCU_RSTF_TypeDef;

/** @defgroup RSTCU_Exported_Constants RSTCU exported constants
  * @{
  */
/*  Definitions of AHB peripheral reset */
#define RSTCU_AHBRST_PDMA         ((u32)0x1 << 4)
#define RSTCU_AHBRST_CRC          ((u32)0x1 << 13)
#define RSTCU_AHBRST_PA           ((u32)0x1 << 16)
#define RSTCU_AHBRST_PB           ((u32)0x1 << 17)
#define RSTCU_AHBRST_PC           ((u32)0x1 << 18)
#define RSTCU_AHBRST_PD           ((u32)0x1 << 19)
#define RSTCU_AHBRST_PE           ((u32)0x1 << 20)
#define RSTCU_AHBRST_CAN          ((u32)0x1 << 15)
#define RSTCU_AHBRST_CAN1         ((u32)0x1 << 14)

/*  Definitions of APB peripheral 0 reset */
#define RSTCU_APBRST0_AFIO         ((u32)0x1 << 14)
#define RSTCU_APBRST0_EXTI         ((u32)0x1 << 15)
#define RSTCU_APBRST0_ADC          ((u32)0x1 << 24)
#define RSTCU_APBRST0_SPI0         ((u32)0x1 << 4)
#define RSTCU_APBRST0_SPI1         ((u32)0x1 << 6)
#define RSTCU_APBRST0_UART0        ((u32)0x1 << 8)
#define RSTCU_APBRST0_UART2        ((u32)0x1 << 10)
#define RSTCU_APBRST0_UART4        ((u32)0x1 << 12)
#define RSTCU_APBRST0_UART5        ((u32)0x1 << 13)
#define RSTCU_APBRST0_TRNG         ((u32)0x1 << 5)

/* Definitions of APB peripheral 1 reset */
#define RSTCU_APBRST1_GPTM0        ((u32)0x1 << 8)
#define RSTCU_APBRST1_GPTM1        ((u32)0x1 << 9)
#define RSTCU_APBRST1_GPTM2        ((u32)0x1 << 10)
#define RSTCU_APBRST1_GPTM3        ((u32)0x1 << 11)
#define RSTCU_APBRST1_UART1        ((u32)0x1 << 2)
#define RSTCU_APBRST1_UART3        ((u32)0x1 << 3)
#define RSTCU_APBRST1_I2C0         ((u32)0x1 << 0)
#define RSTCU_APBRST1_WDT					 ((u32)0x1 << 4)
#define RSTCU_APBRST1_COMP				 ((u32)0x1 << 12)

/** @defgroup RSTCU_Exported_Functions RSTCU exported functions
  * @{
  */
FlagStatus RSTCU_GetResetFlagStatus(RSTCU_RSTF_TypeDef RSTCU_RSTF);
void RSTCU_ClearResetFlag(RSTCU_RSTF_TypeDef RSTCU_RSTF);
void RSTCU_ClearAllResetFlag(void);
void RSTCU_AHBPeripReset(u32 RSTCU_AHBP, ControlStatus Cmd);
void RSTCU_APBPerip0Reset(u32 RSTCU_APBP, ControlStatus Cmd);
void RSTCU_APBPerip1Reset(u32 RSTCU_APBP, ControlStatus Cmd);
bool RSTCU_IS_AHBPeripResetEnd(u32 RSTCU_AHBP);
bool RSTCU_IS_APBPerip0ResetEnd(u32 RSTCU_APBP);
bool RSTCU_IS_APBPerip1ResetEnd(u32 RSTCU_APBP);

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
