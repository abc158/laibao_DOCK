/********************************************************************************************************//**
 * @file    crc.h	
 * @brief   The header file of the Clock Control Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#ifndef __CRC_H
#define __CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

/** @defgroup CRC_Exported_Constants CRC exported constants
  * @{
  */

#define CRC_CCITT_POLY            (0)           // 0x1021
#define CRC_16_POLY               (1UL << 0)    // 0x8005
#define CRC_32_POLY               (1UL << 1)    // 0x04C11DB7

#define IS_CRC_POLY(POLY)         ((POLY == CRC_CCITT_POLY) || \
                                   (POLY == CRC_16_POLY) || \
                                   (POLY == CRC_32_POLY))

#define CRC_NORMAL_WR             (0)
#define CRC_BIT_RVS_WR            (1UL << 2)
#define CRC_BYTE_RVS_WR           (1UL << 3)
#define CRC_CMPL_WR               (1UL << 4)

#define CRC_NORMAL_SUM            (0)
#define CRC_BIT_RVS_SUM           (1UL << 5)
#define CRC_BYTE_RVS_SUM          (1UL << 6)
#define CRC_CMPL_SUM              (1UL << 7)

#define IS_CRC_MOD(MOD)           ((MOD & 0xFFFFFF00) == 0)


/** @defgroup CRC_Exported_Functions CRC exported functions
  * @{
  */

void CRC_DeInit(void);
u16 CRC_CCITT(u16 seed, u8 *buffer, u32 length);
u16 CRC_16(u16 seed, u8 *buffer, u32 length);
u32 CRC_32(u32 seed, u8 *buffer, u32 length);

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
