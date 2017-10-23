/********************************************************************************************************//**
 * @file    crc.c	
 * @brief   The c file of the Crc Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
#include "crc.h"
#include "rstcu.h"


/** @defgroup CRC_Private_Function CRC private functions
  * @{
  */

/*********************************************************************************************************//**
  * @brief  Deinitialize the CRC peripheral registers to their default reset values.
  * @retval None
  ***********************************************************************************************************/
void CRC_DeInit(void)
{
  RSTCU_AHBPeripReset(RSTCU_AHBRST_CRC, ENABLE);
}

/*********************************************************************************************************//**
  * @brief  Get the CRC-CCITT checksum from the given data
  * @param  seed: CRC initial data
  * @param  buffer: pointer to the given data to be calculated
  * @param  length: data length in byte
  * @return The checksum value
  ***********************************************************************************************************/
u16 CRC_CCITT(u16 seed, u8 *buffer, u32 length)
{
  /* CRC-CCITT poly: 0x1021 */
  AM_CRC->SDR = seed;
  AM_CRC->CR = CRC_CCITT_POLY | CRC_NORMAL_WR | CRC_NORMAL_SUM;

  while (length--)
  {
    wb(&AM_CRC->DR, *buffer++); // byte write
  }

  return (u16)(AM_CRC->CSR);
}

/*********************************************************************************************************//**
  * @brief  Get the CRC-16 checksum from the given data
  * @param  seed: CRC initial data
  * @param  buffer: pointer to the given data to be calculated
  * @param  length: data length in byte
  * @return The checksum value
  ***********************************************************************************************************/
u16 CRC_16(u16 seed, u8 *buffer, u32 length)
{
  /* CRC-16 poly: 0x8005 */
  AM_CRC->SDR = seed;
  AM_CRC->CR = CRC_16_POLY | CRC_BIT_RVS_WR | CRC_BIT_RVS_SUM | CRC_BYTE_RVS_SUM;

  while (length--)
  {
    wb(&AM_CRC->DR, *buffer++); // byte write
  }

  return (u16)(AM_CRC->CSR);
}

/*********************************************************************************************************//**
  * @brief  Get the CRC-32 checksum from the given data
  * @param  seed: CRC initial data
  * @param  buffer: pointer to the given data to be calculated
  * @param  length: data length in byte
  * @return The checksum value
  ***********************************************************************************************************/
u32 CRC_32(u32 seed, u8 *buffer, u32 length)
{
  /* CRC-32 poly: 0x04C11DB7 */
  AM_CRC->SDR = seed;
  AM_CRC->CR = CRC_32_POLY | CRC_BIT_RVS_WR | CRC_BIT_RVS_SUM | CRC_BYTE_RVS_SUM | CRC_CMPL_SUM;

  while (length--)
  {
    wb(&AM_CRC->DR, *buffer++); // byte write
  }

  return (AM_CRC->CSR);
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

