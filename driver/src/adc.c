/********************************************************************************************************//**
 * @file    adc.c	
 * @brief   The c file of the Adc Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/


#include "adc.h"
#include "rstcu.h"

/** @defgroup ADC_Private_Define ADC private definitions
  * @{
  */
#define ADC_SOFTWARE_RESET   (0x00000001)
#define LST_SEQ_SET          (0x0000001F)
#define TCR_SC_SET           (0x00000001)

#define HLST_SEQ_SET         (0x0000001F)
#define HTCR_SC_SET          (0x00000001)


/*********************************************************************************************************//**
 * @brief Deinitialize the ADCx peripheral registers to their default reset values.
 * @param None
 * @retval None
 ************************************************************************************************************/
void ADC_DeInit( )
{
  RSTCU_APBPerip0Reset(RSTCU_APBRST0_ADC, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Reset ADC.
 * @param ADCx: is the selected ADC from the ADC peripherals.
 * @retval None
 ************************************************************************************************************/
void ADC_Reset( )
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  pAM_ADC->CTL |= ADC_SOFTWARE_RESET;
}

/*********************************************************************************************************//**
 * @brief Configure conversion mode and length of list queue for regular group.
 * @param ADC_MODE: ADC Cyclic Conversion Mode
     This parameter can be one of the following values:
       @arg ONE_SHOT_MODE:
       @arg CONTINUOUS_MODE:
       @arg DISCONTIOUS_MODE:
 * @param Length: must between 1 ~ 18
 * @param SubLength: must between 1 ~ 18
 * @retval None
 ************************************************************************************************************/
void ADC_RegularGroupConfig(u8 ADC_MODE, u8 Length, u8 SubLength)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;

  /* Config cyclic conversion mode and length of list queue and sub length for regular group */
  pAM_ADC->CONV =  ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE;
}

/*********************************************************************************************************//**
 * @brief Configure conversion mode and length of list queue for high priority group.
 * @param ADCx: where ADCx is the selected ADC from the ADC peripherals.
 * @param ADC_MODE: ADC Cyclic Conversion Mode
     This parameter can be one of the following values:
       @arg ONE_SHOT_MODE:
       @arg CONTINUOUS_MODE:
       @arg DISCONTINUOUS_MODE:
 * @param Length: must between 1 ~ 4
 * @param SubLength: must between 1 ~ 4
 * @retval None
 ************************************************************************************************************/
void ADC_HPGroupConfig(u8 ADC_MODE, u8 Length, u8 SubLength)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  /* Config cyclic conversion mode and length of list queue and sub length for regular group */
  pAM_ADC->HCONV =  ((u32)(SubLength - 1) << 16) | ((u32)(Length - 1) << 8) | ADC_MODE;
}

/*********************************************************************************************************//**
 * @brief Configure the corresponding rank in the sequencer and the sample time for the regular channel of the selected ADC.
 * @param ADC_Channel: the ADC channel to configure
     This parameter can be one of the following values:
       @arg ADC_CH_x: ADC Channel x selected, x must between 0 ~ 17
       @arg ADC_CH_TEMP: ADC TEMP SENSOR selected
       @arg ADC_CH_VREF: ADC VREF selected
 * @param Rank: The rank in the regular group sequencer.
     This parameter must be between 0 to 17.
 * @param SampleClock: Number of sampling clocks.
     This parameter must be between 0x00 to 0xFF.
 * @retval None
 ************************************************************************************************************/
void ADC_RegularChannelConfig(u8 ADC_Channel, u8 Rank, u8 SampleClock)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
  u32 tmpreg1, tmpreg2;

  /* config sampling clock of correspond ADC input channel */
	if(ADC_Channel<16)
		pAM_ADC->CTL = ((pAM_ADC->CTL)&(~(0xff<<8)))|(SampleClock<<8);
	else
		pAM_ADC->CTL = ((pAM_ADC->CTL)&(~(0xff<<16)))|(SampleClock<<16);

  /* Config ADC Rank */

  /* Get the old register value */
  tmpreg1 = pAM_ADC->LST[Rank >> 2];
  /* Calculate the mask to clear */
  tmpreg2 = LST_SEQ_SET << (8 * (Rank & 0x3));
  /* Clear the old SEQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set */
  tmpreg2 = (u32)ADC_Channel << (8 * (Rank & 0x3));
  /* Set the SEQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  pAM_ADC->LST[Rank >> 2] = tmpreg1;
}

/*********************************************************************************************************//**
 * @brief Configure the corresponding rank in the sequencer and the sample time for the High Priority channel of the selected ADC.
 * @param ADC_Channel: the ADC channel to configure
     This parameter can be one of the following values:
       @arg ADC_CH_x: ADC Channel x selected, x must between 0 ~ 3
 * @param Rank: The rank in the high priority group sequencer.
     This parameter must be between 0 to 3.
 * @param SampleClock: Number of sampling clocks.
     This parameter must be between 0x00 to 0xFF.
 * @retval None
 ************************************************************************************************************/
void ADC_HPChannelConfig(u8 ADC_Channel, u8 Rank, u8 SampleClock)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
  u32 tmpreg1, tmpreg2;

  /* config sampling clock of correspond ADC input channel */
	pAM_ADC->CTL = ((pAM_ADC->CTL)&(~(0xff<<8)))|(SampleClock<<8);

  /* Config ADC Rank */

  /* Get the old register value */
  tmpreg1 = pAM_ADC->HLST;
  /* Calculate the mask to clear */
  tmpreg2 = HLST_SEQ_SET << (8 * (Rank & 0x3));
  /* Clear the old SEQx bits for the selected rank */
  tmpreg1 &= ~tmpreg2;
  /* Calculate the mask to set */
  tmpreg2 = (u32)ADC_Channel << (8 * (Rank & 0x3));
  /* Set the SEQx bits for the selected rank */
  tmpreg1 |= tmpreg2;
  /* Store the new register value */
  pAM_ADC->HLST = tmpreg1;
}

/*********************************************************************************************************//**
 * @brief Configure the ADCx trigger source for regular channels conversion.
 * @param ADC_RegularTrigCtrl:
     This parameter can be one of the following values:
       @arg ADC_TRIG_SOFTWARE   : S/W trigger
       @arg ADC_TRIG_GPTMx_MTO  : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH0O : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH1O : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH2O : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH3O : where x can be 0 ~ 3
       @arg ADC_TRIG_EXTI_x     : where x can be 0 ~ 15
 * @retval None
 ************************************************************************************************************/
void ADC_RegularTrigConfig(u32 ADC_RegularTrigCtrl)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  /* Config external trigger conversion source of regular group */
  pAM_ADC->TCR = (ADC_RegularTrigCtrl >> 28);
  pAM_ADC->TSR = ADC_RegularTrigCtrl;
}

/*********************************************************************************************************//**
 * @brief Configure the ADCx trigger source for high priority channels conversion.
 * @param ADC_RegularTrigCtrl:
     This parameter can be one of the following values:
       @arg ADC_TRIG_SOFTWARE   : S/W trigger
       @arg ADC_TRIG_GPTMx_MTO  : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH0O : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH1O : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH2O : where x can be 0 ~ 3
       @arg ADC_TRIG_GPTMx_CH3O : where x can be 0 ~ 3
       @arg ADC_TRIG_EXTI_x     : where x can be 0 ~ 15
 * @retval None
 ************************************************************************************************************/
void ADC_HPTrigConfig(u32 ADC_HPTrigCtrl)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  /* Config external trigger conversion source of regular group */
  pAM_ADC->HTCR = (ADC_HPTrigCtrl >> 28);
  pAM_ADC->HTSR = ADC_HPTrigCtrl;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the regular channel conversion.
 * @param NewState: new state of the selected ADC software start regular conversion.
     This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_SoftwareStartConvCmd(ControlStatus NewState)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;

  /* Start Conversion */
  if (NewState != DISABLE)
  {
    pAM_ADC->TSR |= TCR_SC_SET;
  }
  else
  {
    pAM_ADC->TSR &= ~TCR_SC_SET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable software start of the high priority channel conversion of the selected ADC .
 * @param NewState: new state of the selected ADC software start regular conversion.
     This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_HPSoftwareStartConvCmd(ControlStatus NewState)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;

  /* Start Conversion */
  if (NewState != DISABLE)
  {
    pAM_ADC->HTSR |= HTCR_SC_SET;
  }
  else
  {
    pAM_ADC->HTSR &= ~HTCR_SC_SET;
  }
}

/*********************************************************************************************************//**
 * @brief Return the result of ADC regular channel conversion.
 * @param ADC_REGULAR_DATAx: where x can be 0 ~ 17
 * @return The Value of data conversion.
 ************************************************************************************************************/
FlagStatus ADC_GetConversionData(u8 ADC_REGULAR_DATAx, u16 *adc_data)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	u32 reg_val;

	reg_val = pAM_ADC->DR[ADC_REGULAR_DATAx];
	if( (reg_val&0x80000000) == 0)
		return RESET;
	else
	{
		*adc_data = (uint16_t)reg_val;
		return SET;
	}
}

/*********************************************************************************************************//**
 * @brief Return the result of ADC high priority channel conversion.
 * @param ADC_HP_DATAx: where x can be 0 ~ 3
 * @return The Value of data conversion.
 ************************************************************************************************************/
FlagStatus ADC_GetHPConversionData(u8 ADC_HP_DATAx, u16 *adc_data)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	u32 reg_val;

	reg_val = pAM_ADC->HDR[ADC_HP_DATAx];
	if( (reg_val&0x80000000) == 0)
		return RESET;
	else
	{
		*adc_data = (uint16_t)reg_val;
		return SET;	
	}
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified ADC interrupts.
 * @param ADC_INT: Specify the ADC interrupt sources that is to be enabled or disabled.
     This parameter can be any combination of the following values:
       @arg ADC_INT_SINGLE_EOC:
       @arg ADC_INT_SUB_GROUP_EOC:
       @arg ADC_INT_CYCLE_EOC:
       @arg ADC_INT_HP_SINGLE_EOC
       @arg ADC_INT_HP_SUB_GROUP_EOC
       @arg ADC_INT_HP_CYCLE_EOC
       @arg ADC_INT_DATA_OVERWRITE:
       @arg ADC_INT_HP_DATA_OVERWRITE
       @arg ADC_INT_AWD_LOWER:
       @arg ADC_INT_AWD_UPPER:
 * @param NewState: new state of the specified ADC interrupts.
     This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_IntConfig(u32 ADC_INT, ControlStatus NewState)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;

  if(NewState != DISABLE)
  {
    pAM_ADC->IER |= ADC_INT;
  }
  else
  {
    pAM_ADC->IER &= ~ADC_INT;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC interrupt has occurred.
 * @param ADC_INT: Specify the interrupt status to check.
     This parameter can be any combination of the following values:
       @arg ADC_INT_SINGLE_EOC:
       @arg ADC_INT_SUB_GROUP_EOC:
       @arg ADC_INT_CYCLE_EOC:
       @arg ADC_INT_HP_SINGLE_EOC
       @arg ADC_INT_HP_SUB_GROUP_EOC
       @arg ADC_INT_HP_CYCLE_EOC
       @arg ADC_INT_DATA_OVERWRITE:
       @arg ADC_INT_HP_DATA_OVERWRITE
       @arg ADC_INT_AWD_LOWER:
       @arg ADC_INT_AWD_UPPER:
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus ADC_GetIntStatus(u32 ADC_INT)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
  FlagStatus Status;

  if((pAM_ADC->ISR & ADC_INT) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }

  return Status;
}

/*********************************************************************************************************//**
 * @brief Clear the ADCx interrupt pending bits.
 * @param ADC_INT: Specify the interrupt pending bits to be cleared.
     This parameter can be any combination of the following values:
       @arg ADC_INT_SINGLE_EOC:
       @arg ADC_INT_SUB_GROUP_EOC:
       @arg ADC_INT_CYCLE_EOC:
       @arg ADC_INT_HP_SINGLE_EOC
       @arg ADC_INT_HP_SUB_GROUP_EOC
       @arg ADC_INT_HP_CYCLE_EOC
       @arg ADC_INT_DATA_OVERWRITE:
       @arg ADC_INT_HP_DATA_OVERWRITE
       @arg ADC_INT_AWD_LOWER:
       @arg ADC_INT_AWD_UPPER:
 * @retval None
 ************************************************************************************************************/
void ADC_ClearIntPendingBit(u32 ADC_INT)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;

  pAM_ADC->ICLR = ADC_INT;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified ADC flag has been set.
 * @param ADC_FLAG: Specify the flag to check.
     This parameter can be any combination of the following values:
       @arg ADC_FLAG_SINGLE_EOC:
       @arg ADC_FLAG_SUB_GROUP_EOC:
       @arg ADC_FLAG_CYCLE_EOC:
       @arg ADC_FLAG_HP_SINGLE_EOC
       @arg ADC_FLAG_HP_SUB_GROUP_EOC
       @arg ADC_FLAG_HP_CYCLE_EOC
       @arg ADC_FLAG_DATA_OVERWRITE:
       @arg ADC_FLAG_HP_DATA_OVERWRITE
       @arg ADC_FLAG_AWD_LOWER:
       @arg ADC_FLAG_AWD_UPPER:
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus ADC_GetFlagStatus(u32 ADC_FLAG)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
  FlagStatus Status;

  if((pAM_ADC->IRAW & ADC_FLAG) != RESET)
  {
    Status = SET;
  }
  else
  {
    Status = RESET;
  }

  return Status;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable Lower/Upper threshold warning of the analog watchdog on single/all channels.
 * @param ADC_AWD:
     This parameter can be any combination of the following values:
       @arg ADC_AWD_DISABLE
       @arg ADC_AWD_ALL_LOWER
       @arg ADC_AWD_ALL_UPPER
       @arg ADC_AWD_ALL_LOWER_UPPER
       @arg ADC_AWD_SINGLE_LOWER
       @arg ADC_AWD_SINGLE_UPPER
       @arg ADC_AWD_SINGLE_LOWER_UPPER
 * @retval None
 ************************************************************************************************************/
void ADC_AWDConfig(u32 ADC_AWD)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  pAM_ADC->WCR = (pAM_ADC->WCR & 0xFFFFFFF8) | ADC_AWD;
}

/*********************************************************************************************************//**
 * @brief Configure the analog watchdog that guards single channel.
 * @param ADC_CH: ADC input channel
     This parameter can be one of the following values:
       @arg ADC_CH_x  where x must between 0 ~ 11
 * @retval None
 ************************************************************************************************************/
void ADC_AWDSingleChannelConfig(u8 ADC_CH)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  pAM_ADC->WCR = (pAM_ADC->WCR & 0xFFFFF0FF) | ((u32)ADC_CH << 8);
}

/*********************************************************************************************************//**
 * @brief Configure the high and low thresholds of the analog watchdog.
 * @param UPPER: must between 0x0000 ~ 0x0FFF
 * @param LOWER: must between 0x0000 ~ 0x0FFF
 * @retval None
 ************************************************************************************************************/
void ADC_AWDThresholdsConfig(u16 UPPER, u16 LOWER)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  pAM_ADC->LTR = LOWER;
  pAM_ADC->UTR = UPPER;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PDMA request.
 * @param ADC_PDMA: Specify the ADC PDMA request that is to be enabled or disabled.
     This parameter can be any combination of the following values:
       @arg ADC_PDMA_REGULAR_SINGLE:
       @arg ADC_PDMA_REGULAR_SUBGROUP:
       @arg ADC_PDMA_REGULAR_CYCLE:
       @arg ADC_PDMA_HP_SINGLE:
       @arg ADC_PDMA_HP_SUBGROUP:
       @arg ADC_PDMA_HP_CYCLE:
 * @param NewState new state of the specified ADC PDMA requests.
     This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void ADC_PDMAConfig(u32 ADC_PDMA, ControlStatus NewState)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
  if(NewState != DISABLE)
  {
    pAM_ADC->PDMAR |= ADC_PDMA;
  }
  else
  {
    pAM_ADC->PDMAR &= ~ADC_PDMA;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the align type and value for ADC.
 * @param Align: This parameter can be AlignRight or AlignLeft
 * @retval None
 ************************************************************************************************************/
void ADC_AlignConfig(u8 Align)
{
	AM_ADC_TypeDef *pAM_ADC = AM_ADC;
	
	pAM_ADC->CTL = ((pAM_ADC->CTL)&(~(1<<1)))|(Align<<1); 
}


/*********************************************************************************************************//**
 * @brief Enable or Disable the specified Current Source.
 * @param Cs_x    : Specify the Current Source x, which should be 0 or 1.
 * @param NewState: new state of the specified current source.
     This parameter can be: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CS_Cmd(CSx Cs_x, ControlStatus NewState)
{
  if(NewState != DISABLE)
  {
    AM_CS->CTL |= (1<<(0+Cs_x*8));
  }
  else
  {
    AM_CS->CTL &= (~(1<<(0+Cs_x*8)));
  }
}

/*********************************************************************************************************//**
 * @brief Select current of the specified Current Source.
 * @param Cs_x  : Specify the Current Source x, which should be 0 or 1.
 * @param Cs_cur: specify current.
     This parameter can be: CS_CUR_10UA, CS_CUR_100UA or CS_CUR_1MA.
 * @retval None
 ************************************************************************************************************/
void CS_CurrentSel(CSx Cs_x, CS_CUR Cs_cur)
{
  AM_CS->CTL = (AM_CS->CTL & (~(3<<(1+Cs_x*8)))) | (Cs_cur<<(1+Cs_x*8));
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
