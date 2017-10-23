/********************************************************************************************************//**
 * @file    pdma.c	
 * @brief   The c file of the Pdma Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/


#include "pdma.h"

/*********************************************************************************************************//**
  * @brief  Init specific PDMA channel
  * @param  DmaChnx: DMA_CH0 ~ DMA_CH7
  * @param  pDmaInitStruct: pointer to a DMA_InitTypeDef structure that contains the configuration
  * @retval None
  ***********************************************************************************************************/
void DMA_Init(DMA_InitTypeDef *pDmaInitStruct, uint8_t DmaChnx)
{
	AM_PDMACH_TypeDef *pAM_PDMACH = (AM_PDMACH_TypeDef *)AM_PDMA;
	
	(pAM_PDMACH + DmaChnx)->CR = (pDmaInitStruct->HardTrigSrc << 16) \
	| (pDmaInitStruct->AutoReload << 11) \
	| (pDmaInitStruct->AddrFix << 10) \
	| (pDmaInitStruct->ChnPriority << 8) \
	| (pDmaInitStruct->SrcAddrMode << 7) \
	| (pDmaInitStruct->SrcAddrIncrement << 6) \
	| (pDmaInitStruct->DestAddrMode << 5) \
	| (pDmaInitStruct->DestAddrIncrement << 4) \
	| (pDmaInitStruct->DataWidth << 2);
	
	(pAM_PDMACH + DmaChnx)->SADR = pDmaInitStruct->AddrSrc;
	(pAM_PDMACH + DmaChnx)->DADR = pDmaInitStruct->AddrDest;
	(pAM_PDMACH + DmaChnx)->TSR = (pDmaInitStruct->BlockCnt << 16) | (pDmaInitStruct->BlockLength << 0);
	
//	(pAM_PDMACH + DmaChnx)->CR = (pAM_PDMACH + DmaChnx)->CR | (1<<0);
}

/*********************************************************************************************************//**
  * @brief  Enable a specific PDMA channel
  * @param  PDMA_Ch: DMA_CH0 ~ DMA_CH7
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  ***********************************************************************************************************/
void DMA_EnaCmd(u32 PDMA_Ch, ControlStatus NewState)
{
	AM_PDMACH_TypeDef *PDMACHx = (AM_PDMACH_TypeDef *)(AM_PDMA_BASE + PDMA_Ch*6*4);

  if (NewState != DISABLE)
  {
    SetBit_BB((u32)(&PDMACHx->CR), 0);
  }
  else
  {
    ResetBit_BB((u32)(&PDMACHx->CR), 0);
  }
}
/*********************************************************************************************************//**
  * @brief  Enable the specific PDMA channel interrupts
  * @param  DmaChnx: DMA_CH0 ~ DMA_CH7
  * @param  IntType: GLOBAL_INT, TRAN_BEND_INT, TRAN_HALF_INT, TRAN_CPLT_INT, TRAN_ERR_INT
  * @retval None
  ***********************************************************************************************************/
void DMA_IntEnable(uint8_t IntType, uint8_t DmaChnx)
{
	AM_PDMA_TypeDef *pAM_PDMA = AM_PDMA;
	
	if(DmaChnx<6)
	{
		pAM_PDMA->IER0 |= (ENABLE<<(IntType+5*DmaChnx));
	}
	else
	{
		pAM_PDMA->IER1 |= (ENABLE<<(IntType+5*(DmaChnx-6)));
	}
}

/*********************************************************************************************************//**
  * @brief  Get the specific PDMA channel interrupt flag
  * @param  DmaChnx: DMA_CH0 ~ DMA_CH7
  * @param  IntType: GLOBAL_INT, TRAN_BEND_INT, TRAN_HALF_INT, TRAN_CPLT_INT, TRAN_ERR_INT
  * @retval FLAG_SET or FLAG_NOTSET
  ***********************************************************************************************************/
FLAG_STATUS DMA_GetStatus(uint8_t IntType,uint8_t DmaChnx)
{
	AM_PDMA_TypeDef *pAM_PDMA = AM_PDMA;
	uint32_t reg_val,mask_val;

	if(DmaChnx<6)
	{
		mask_val = 1<<(IntType+5*DmaChnx);
		reg_val = pAM_PDMA->ISR0 & mask_val;
	}
	else
	{
		mask_val = 1<<(IntType+5*(DmaChnx-6));
		reg_val = pAM_PDMA->ISR1 & mask_val;
	}
	
	if( reg_val == 0)
		return FLAG_NOTSET;
	else
	{
		return FLAG_SET;
	}
}

/*********************************************************************************************************//**
  * @brief  Clear the specific PDMA channel interrupt flag
  * @param  DmaChnx: DMA_CH0 ~ DMA_CH7
  * @param  IntType: GLOBAL_INT, TRAN_BEND_INT, TRAN_HALF_INT, TRAN_CPLT_INT, TRAN_ERR_INT
  * @retval FLAG_SET(not clear) or FLAG_NOTSET(clear)
  ***********************************************************************************************************/
FLAG_STATUS DMA_ClearStatus(uint8_t IntType,uint8_t DmaChnx)
{
	AM_PDMA_TypeDef *pAM_PDMA = AM_PDMA;
	uint32_t reg_val,mask_val;

	if(DmaChnx<6)
	{
		mask_val = 1<<(IntType+5*DmaChnx);
		pAM_PDMA->ISCR0 = mask_val;
		reg_val = pAM_PDMA->ISR0 & mask_val;
	}
	else
	{
		mask_val = 1<<(IntType+5*(DmaChnx-6));
		pAM_PDMA->ISCR1 = mask_val;
		reg_val = pAM_PDMA->ISR1 & mask_val;
	}
	
	if(reg_val == 0)
		return FLAG_NOTSET;
	else
		return FLAG_SET;
}

/*********************************************************************************************************//**
  * @brief  DeInit specific PDMA channel
  * @param  DmaChnx: DMA_CH0 ~ DMA_CH7
  * @retval None
  ***********************************************************************************************************/
void DMA_DeInit(uint8_t DmaChnx)
{
	AM_PDMACH_TypeDef *pAM_PDMACH = (AM_PDMACH_TypeDef *)AM_PDMA;
	AM_PDMA_TypeDef *pAM_PDMA = AM_PDMA;
	
	(pAM_PDMACH + DmaChnx)->CR = 0;
	(pAM_PDMACH + DmaChnx)->SADR = 0;
	(pAM_PDMACH + DmaChnx)->DADR = 0;
	(pAM_PDMACH + DmaChnx)->TSR = 0;
	if(DmaChnx<6)
	{
		pAM_PDMA->IER0 &= (~(0x1f<<(0+5*DmaChnx)));
	}
	else
	{
		pAM_PDMA->IER1 &= (~(0x1f<<(0+5*(DmaChnx-6))));
	}	
}

/*********************************************************************************************************//**
  * @brief  PDMA channel software trig
  * @param  DmaChnx: DMA_CH0 ~ DMA_CH7
  * @retval None
  ***********************************************************************************************************/
void DMA_SoftwareTrigEnable(uint8_t DmaChnx)
{
	AM_PDMACH_TypeDef *pAM_PDMACH = (AM_PDMACH_TypeDef *)AM_PDMA;
	
	(pAM_PDMACH + DmaChnx)->CR |= (1<<1);
}

