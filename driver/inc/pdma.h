/********************************************************************************************************//**
 * @file    pdma.h	
 * @brief   The header file of the Pdma Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __PDMA_H
#define __PDMA_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
/* Includes ------------------------------------------------------------------------------------------------*/
#include "AM8813.h"
#include "user.h"

typedef uint8_t					FLAG_STATUS;
#define FLAG_SET				((uint8_t)0x01)
#define FLAG_NOTSET			((uint8_t)0x00)
/**
 * @brief Definition of PDMA channel Init Structure
 */
typedef struct
{
	uint8_t HardTrigSrc;
	uint8_t AutoReload;
	uint8_t AddrFix;
	uint8_t ChnPriority;
	uint8_t SrcAddrMode;
	uint8_t SrcAddrIncrement;
	uint8_t DestAddrMode;
	uint8_t DestAddrIncrement;
	uint8_t DataWidth;
	
	uint32_t AddrSrc;
	uint32_t AddrDest;
	uint16_t BlockCnt;
	uint16_t BlockLength;
}DMA_InitTypeDef;

/**
  * @}
  */

/** @defgroup PDMA_Exported_Constants PDMA exported constants
  * @{
  */
#define DMA_CH0								0
#define DMA_CH1								1
#define DMA_CH2								2
#define DMA_CH3								3
#define DMA_CH4								4
#define DMA_CH5								5
#define DMA_CH6								6
#define DMA_CH7								7

#define CHANNEL_PRI_LOW				0
#define CHANNEL_PRI_MIDDLE		1
#define CHANNEL_PRI_HIGH			2
#define CHANNEL_PRI_VERYHIGH	3
#define LINEAR								0
#define CIRCULAR							1
#define ADDR_INC							0
#define ADDR_DEC							1
#define DATA_WIDTH_8BIT				0
#define DATA_WIDTH_16BIT			1
#define DATA_WIDTH_32BIT			2
#define SW_TRIG								1
#define CH_EN									1

#define GLOBAL_INT						0
#define TRAN_BEND_INT					1
#define TRAN_HALF_INT					2
#define TRAN_CPLT_INT					3
#define TRAN_ERR_INT					4

#define DMA_HARDTRIG_SRC_ADC					0x00
#define DMA_HARDTRIG_SRC_SPI0_RX			0x01
#define DMA_HARDTRIG_SRC_SPI0_TX			0x02
#define DMA_HARDTRIG_SRC_I2C0_RX			0x03
#define DMA_HARDTRIG_SRC_I2C0_TX			0x04
#define DMA_HARDTRIG_SRC_GT0_CH0			0x05
#define DMA_HARDTRIG_SRC_GT0_CH1			0x06
#define DMA_HARDTRIG_SRC_GT0_CH2			0x07
#define DMA_HARDTRIG_SRC_GT0_CH3			0x08
#define DMA_HARDTRIG_SRC_GT0_TRIG			0x09
#define DMA_HARDTRIG_SRC_GT0_UEV			0x0a
#define DMA_HARDTRIG_SRC_GT1_CH0			0x0b
#define DMA_HARDTRIG_SRC_GT1_CH1			0x0c
#define DMA_HARDTRIG_SRC_GT1_CH2			0x0d
#define DMA_HARDTRIG_SRC_GT1_CH3			0x0e
#define DMA_HARDTRIG_SRC_GT1_TRIG			0x0f
#define DMA_HARDTRIG_SRC_GT1_UEV			0x10
#define DMA_HARDTRIG_SRC_GT2_CH0			0x11
#define DMA_HARDTRIG_SRC_GT2_CH1			0x12
#define DMA_HARDTRIG_SRC_GT2_CH2			0x13
#define DMA_HARDTRIG_SRC_GT2_CH3			0x14
#define DMA_HARDTRIG_SRC_GT2_TRIG			0x15
#define DMA_HARDTRIG_SRC_GT2_UEV	    0x16
#define DMA_HARDTRIG_SRC_GT3_CH0			0x17
#define DMA_HARDTRIG_SRC_GT3_CH1			0x18
#define DMA_HARDTRIG_SRC_GT3_CH2			0x19
#define DMA_HARDTRIG_SRC_GT3_CH3			0x1a
#define DMA_HARDTRIG_SRC_GT3_TRIG			0x1b
#define DMA_HARDTRIG_SRC_GT3_UEV	    0x1c
#define DMA_HARDTRIG_SRC_UR0_RX				0x1d
#define DMA_HARDTRIG_SRC_UR0_TX				0x1e
#define DMA_HARDTRIG_SRC_UR1_RX				0x1f
#define DMA_HARDTRIG_SRC_UR1_TX				0x20
#define DMA_HARDTRIG_SRC_UR2_RX				0x21
#define DMA_HARDTRIG_SRC_UR2_TX				0x22
#define DMA_HARDTRIG_SRC_UR3_RX				0x23
#define DMA_HARDTRIG_SRC_UR3_TX				0x24
#define DMA_HARDTRIG_SRC_UR4_RX				0x25
#define DMA_HARDTRIG_SRC_UR4_TX				0x26
#define DMA_HARDTRIG_SRC_UR5_RX				0x27
#define DMA_HARDTRIG_SRC_UR5_TX				0x28
#define DMA_HARDTRIG_SRC_SPI1_RX			0x29
#define DMA_HARDTRIG_SRC_SPI1_TX			0x2a

/**
  * @}
  */

/** @defgroup PDMA_Exported_Functions PDMA exported functions
  * @{
  */

void DMA_Init(DMA_InitTypeDef *pDmaInitStruct, uint8_t DmaChnx);
void DMA_EnaCmd(u32 PDMA_Ch, ControlStatus NewState);
void DMA_IntEnable(uint8_t IntType, uint8_t DmaChnx);
FLAG_STATUS DMA_GetStatus(uint8_t IntType,uint8_t DmaChnx);
FLAG_STATUS DMA_ClearStatus(uint8_t IntType,uint8_t DmaChnx);
void DMA_DeInit(uint8_t DmaChnx);
void DMA_SoftwareTrigEnable(uint8_t DmaChnx);

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
