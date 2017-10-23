/********************************************************************************************************//**
 * @file    gptm.c	
 * @brief   The c file of the Gptm Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/


#include "gptm.h"
#include "rstcu.h"

/** @defgroup GPTM_Private_Define GPTM private definitions
  * @{
  */
#define CNTCFR_UEVDIS       0x00000001ul
#define CNTCFR_UGDIS        0x00000002ul
#define CNTCFR_DIR          0x01000000ul
#define CNTCFR_CMSEL_MASK   ~0x00030000ul
#define CNTCFR_CKDIV_MASK   ~0x00000300ul

#define MDCFR_SPMSET        0x01000000ul
#define MDCFR_TSE           0x00000001ul
#define MDCFR_SMSEL_MASK    ~0x00000700ul
#define MDCFR_MMSEL_MASK    ~0x00070000ul

#define TRCFR_ECME          0x01000000ul
#define TRCFR_ETI_POL       0x00010000ul
#define TRCFR_ETI_PSC_MASK  ~0x00003000ul
#define TRCFR_ETIF_MASK     ~0x00000F00ul
#define TRCFR_TRSEL_MASK    ~0x0000000Ful
#define TRCFR_ETI_CONF_MASK ~0x00013F00ul

#define CTR_TME             0x00000001ul
#define CTR_CRBE            0x00000002ul
#define CTR_CHCCDS          0x00010000ul

#define CH0ICFR_CH0SRC      0x80000000ul
#define CHICFR_CHF_MASK     ~0x0000000Ful
#define CHICFR_CHCCS_MASK   ~0x00030000ul
#define CHICFR_CHPSC_MASK   ~0x000C0000ul

#define CHOCFR_REFCE        0x00000008ul
#define CHOCFR_CHPRE        0x00000010ul
#define CHOCFR_IMAE         0x00000020ul
#define CHOCFR_CHOM_MASK    ~0x00000107ul

#define CHPOLR_CH0P         0x00000001ul
#define CHPOLR_CH1P         0x00000004ul
/**
  * @}
  */

/** @defgroup GPTM_Private_Function_Prototype GPTM private function prototypes
  * @{
  */
static void
gptm_CHx_Config(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Ch, GPTM_CHP_Enum Pol, GPTM_CHCCS_Enum Sel, u8 Filter);
/**
  * @}
  */

/** @defgroup GPTM_Private_Function GPTM private functions
  * @{
  */

/*********************************************************************************************************//**
 * @brief Deinitialize the GPTMx peripheral registers to their default reset values.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0 ~ 3.
 * @retval None
 ************************************************************************************************************/
void GPTM_DeInit(AM_GPTM_TypeDef* GPTMx)
{
  if(GPTMx == AM_GPTM0)
  {
    RSTCU_APBPerip1Reset(RSTCU_APBRST1_GPTM0, ENABLE);
  }
  else if(GPTMx == AM_GPTM1)
  {
    RSTCU_APBPerip1Reset(RSTCU_APBRST1_GPTM1, ENABLE);
  }
	else if(GPTMx == AM_GPTM2)
  {
    RSTCU_APBPerip1Reset(RSTCU_APBRST1_GPTM2, ENABLE);
  }
	else if(GPTMx == AM_GPTM3)
  {
    RSTCU_APBPerip1Reset(RSTCU_APBRST1_GPTM3, ENABLE);
  }
}

/*********************************************************************************************************//**
 * @brief Initialize the GPTMx counter to reload, prescaler and counter mode.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param TimeBaseInit: Point to a \ref GPTM_TimeBaseInitTypeDef that contains the configuration information.
 * @retval None
 ************************************************************************************************************/
void GPTM_TimeBaseInit(AM_GPTM_TypeDef* GPTMx, GPTM_TimeBaseInitTypeDef* TimeBaseInit)
{
  /* Set the counter reload value */
  GPTMx->CRR = TimeBaseInit->CounterReload;

  /* Set the Prescaler value */
  GPTMx->PSCR = TimeBaseInit->Prescaler;

  /* Select the Counter Mode */
  GPTMx->CNTCFR &= CNTCFR_CMSEL_MASK;
  GPTMx->CNTCFR &= ~CNTCFR_DIR;
  GPTMx->CNTCFR |= TimeBaseInit->CounterMode;

  /* To reload the Prescaler value immediatly or next update event */
  GPTMx->EVGR = TimeBaseInit->PSCReloadTime;
}

/*********************************************************************************************************//**
 * @brief Initialize the GPTMx channel N output.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param OutInit: Point to a \ref GPTM_OutputInitTypeDef structure that contains
                   the configuration information.
 * @retval None
 ************************************************************************************************************/
void GPTM_OutputInit(AM_GPTM_TypeDef* GPTMx, GPTM_OutputInitTypeDef* OutInit)
{
  vu32 *pOcfr = (vu32*)&GPTMx->CH0OCFR + OutInit->Channel;
  vu32 *pCcr = (vu32*)&GPTMx->CH0CCR + OutInit->Channel;
  vu32 *pAcr = (vu32*)&GPTMx->CH0ACR + OutInit->Channel;
  u8 bChPos = OutInit->Channel << 1;
  u32 wTmpMask = ~(0x1ul << bChPos);

  /* Disable the Channel */
  GPTMx->CHCTR &= wTmpMask;

  /* Set the Output Compare Polarity */
  GPTMx->CHPOLR &= wTmpMask;
  GPTMx->CHPOLR |= (u32)OutInit->Polarity << bChPos;

  /* Select the Output Compare Mode */
  *pOcfr &= CHOCFR_CHOM_MASK;
  *pOcfr |= OutInit->OutputMode;

  /* Set the Capture Compare Register value */
  *pCcr = OutInit->Compare;

  /* Set the Asymmetric Compare Register value */
  *pAcr = OutInit->AsymmetricCompare;

  /* Set the channel state */
  GPTMx->CHCTR |= (u32)OutInit->Control << bChPos;
}

/*********************************************************************************************************//**
 * @brief Initialize input capture of the GPTMx channel.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param CapInit: Point to a \ref GPTM_CaptureInitTypeDef structure that contains the configuration
 *                information.
 * @retval None
 ************************************************************************************************************/
void GPTM_CaptureInit(AM_GPTM_TypeDef* GPTMx, GPTM_CaptureInitTypeDef* CapInit)
{
  gptm_CHx_Config(GPTMx, CapInit->Channel, CapInit->Polarity, CapInit->Selection, CapInit->Filter);

  /* Set the Input Capture Prescaler value */
  GPTM_CHPSCConfig(GPTMx, CapInit->Channel, CapInit->Prescaler);
}

/*********************************************************************************************************//**
 * @brief Configure the GPTMx to measure an external PWM signal.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param CapInit: Point to a \ref GPTM_CaptureInitTypeDef structure that contains the configuration
 *                information.
 * @retval None
 ************************************************************************************************************/
void GPTM_PwmInputInit(AM_GPTM_TypeDef* GPTMx, GPTM_CaptureInitTypeDef* CapInit)
{
  GPTM_CHP_Enum OppositePol = GPTM_CHP_NONINVERTED;
  GPTM_CHCCS_Enum OppositeSel = GPTM_CHCCS_DIRECT;

  /* Select the Opposite Input Polarity */
  if (CapInit->Polarity == GPTM_CHP_NONINVERTED)
  {
    OppositePol = GPTM_CHP_INVERTED;
  }
  else
  {
    OppositePol = GPTM_CHP_NONINVERTED;
  }

  /* Select the Opposite Input */
  if (CapInit->Selection == GPTM_CHCCS_DIRECT)
  {
    OppositeSel = GPTM_CHCCS_INDIRECT;
  }
  else
  {
    OppositeSel = GPTM_CHCCS_DIRECT;
  }

  if (CapInit->Channel == GPTM_CH_0)
  {
    /* CH0 Configuration */
    gptm_CHx_Config(GPTMx, GPTM_CH_0, CapInit->Polarity, CapInit->Selection, CapInit->Filter);

    /* Set the Input Capture Prescaler value */
    GPTM_CHPSCConfig(GPTMx, GPTM_CH_0, CapInit->Prescaler);

    /* CH1 Configuration */
    gptm_CHx_Config(GPTMx, GPTM_CH_1, OppositePol, OppositeSel, CapInit->Filter);

    /* Set the Input Capture Prescaler value */
    GPTM_CHPSCConfig(GPTMx, GPTM_CH_1, CapInit->Prescaler);
  }
  else
  {
    /* CH1 Configuration */
    gptm_CHx_Config(GPTMx, GPTM_CH_1, CapInit->Polarity, CapInit->Selection, CapInit->Filter);

    /* Set the Input Capture Prescaler value */
    GPTM_CHPSCConfig(GPTMx, GPTM_CH_1, CapInit->Prescaler);

    /* CH0 Configuration */
    gptm_CHx_Config(GPTMx, GPTM_CH_0, OppositePol, OppositeSel, CapInit->Filter);

    /* Set the Input Capture Prescaler value */
    GPTM_CHPSCConfig(GPTMx, GPTM_CH_0, CapInit->Prescaler);
  }
}

/*********************************************************************************************************//**
 * @brief Fill each TimeBaseInit member with its default value.
 * @param TimeBaseInit: Point to a \ref GPTM_TimeBaseInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void GPTM_TimeBaseStructInit(GPTM_TimeBaseInitTypeDef* TimeBaseInit)
{
  /* Set the default configuration */
  TimeBaseInit->CounterMode = GPTM_CNT_MODE_UP;
  TimeBaseInit->CounterReload = 0xFFFF;
  TimeBaseInit->Prescaler = 0x0000;
  TimeBaseInit->PSCReloadTime = GPTM_PSC_RLD_IMMEDIATE;
}

/*********************************************************************************************************//**
 * @brief Fill each OutInit member with its default value.
 * @param OutInit: Point to a \ref GPTM_OutputInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void GPTM_OutputStructInit(GPTM_OutputInitTypeDef* OutInit)
{
  /* Set the default configuration */
  OutInit->Channel = GPTM_CH_0;
  OutInit->OutputMode = GPTM_OM_MATCH_NOCHANGE;
  OutInit->Control = GPTM_CHCTL_DISABLE;
  OutInit->Polarity = GPTM_CHP_NONINVERTED;
  OutInit->Compare = 0x0000;
  OutInit->AsymmetricCompare = 0x0000;
}

/*********************************************************************************************************//**
 * @brief Fill each CapInit member with its default value.
 * @param CapInit: Point to a \ref GPTM_CaptureInitTypeDef structure.
 * @retval None
 ************************************************************************************************************/
void GPTM_CaptureStructInit(GPTM_CaptureInitTypeDef* CapInit)
{
  /* Set the default configuration */
  CapInit->Channel = GPTM_CH_0;
  CapInit->Polarity = GPTM_CHP_NONINVERTED;
  CapInit->Selection = GPTM_CHCCS_DIRECT;
  CapInit->Prescaler = GPTM_CHPSC_OFF;
  CapInit->Filter = 0x00;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable GPTMx counter.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_Cmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the GPTM Counter */
    GPTMx->CTR |= CTR_TME;
  }
  else
  {
    /* Disable the GPTM Counter */
    GPTMx->CTR &= ~CTR_TME;
  }
}

/*********************************************************************************************************//**
 * @brief Configure external clock mode of the GPTMx. Used ITIx as the clock source.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Iti: Trigger source.
 *        This parameter can be one of the following values:
 *        @arg GPTM_TRSEL_ITI0: Internal trigger 0
 *        @arg GPTM_TRSEL_ITI1: Internal trigger 1
 *        @arg GPTM_TRSEL_ITI2: Internal trigger 2
 * @retval None
 ************************************************************************************************************/
void GPTM_ItiExternalClockConfig(AM_GPTM_TypeDef* GPTMx, GPTM_TRSEL_Enum Iti)
{
  /* Select the Internal Trigger. Slave mode will be disable in this function*/
  GPTM_StiConfig(GPTMx, Iti);

  /* Select the STIED as external clock source */
  GPTMx->MDCFR |= GPTM_SMSEL_STIED;
}

/*********************************************************************************************************//**
 * @brief Configure external clock mode of the GPTMx. Used CHx as the clock source.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Sel: Specify the channel source.
 *        This parameter can be one of the following values:
 *        @arg GPTM_TRSEL_TI0BED : TI0 both edge detector
 *        @arg GPTM_TRSEL_TI0S0 : Filtered timer input 0
 *        @arg GPTM_TRSEL_TI1S1 : Filtered timer input 1
 * @param Pol: Specify the CHx Polarity.
 *        This parameter can be one of the following values:
 *        @arg GPTM_CHP_NONINVERTED : active high.
 *        @arg GPTM_CHP_INVERTED    : active low.
 * @param Filter: Specify the filter value.
 *        This parameter must be a value between 0x0 and 0xF.
 * @retval None
 ************************************************************************************************************/
void GPTM_ChExternalClockConfig(AM_GPTM_TypeDef* GPTMx, GPTM_TRSEL_Enum Sel, GPTM_CHP_Enum Pol, u8 Filter)
{
  /* Configure the Timer Input Clock Source */
  if (Sel == GPTM_TRSEL_TI1S1)
  {
    gptm_CHx_Config(GPTMx, GPTM_CH_1, Pol, GPTM_CHCCS_DIRECT, Filter);
  }
  else
  {
    gptm_CHx_Config(GPTMx, GPTM_CH_0, Pol, GPTM_CHCCS_DIRECT, Filter);
  }

  /* Select the external clock source. Slave mode will be disable in this function */
  GPTM_StiConfig(GPTMx, Sel);

  /* Select the STIED as external clock source */
  GPTMx->MDCFR |= GPTM_SMSEL_STIED;
}

/*********************************************************************************************************//**
 * @brief Configure external clock mode of the GPTMx. Used ETI as the clock source.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Psc: The external Trigger Prescaler.
 *        It can be one of the following values:
 *        @arg GPTM_ETIPSC_OFF : ETI prescaler off
 *        @arg GPTM_ETIPSC_2   : ETIP frequency divided by 2
 *        @arg GPTM_ETIPSC_4   : ETIP frequency divided by 4
 *        @arg GPTM_ETIPSC_8   : ETIP frequency divided by 8
 * @param Pol: The external trigger input polarity.
 *        It can be one of the following values:
 *        @arg GPTM_ETIPOL_NONINVERTED : Active high level or rising edge
 *        @arg GPTM_ETIPOL_INVERTED    : Active low level or falling edge
 * @param Filter: Filter for ETI input.
 *        This parameter must be a value between 0x00 and 0x0F
 * @retval None
 ************************************************************************************************************/
void GPTM_EtiExternalClockConfig(AM_GPTM_TypeDef* GPTMx, GPTM_ETIPSC_Enum Psc, GPTM_ETIPOL_Enum Pol, u8 Filter)
{
  /* Configure the ETI Clock source */
  GPTM_EtiConfig(GPTMx, Psc, Pol, Filter);

  /* Enable the external clock mode */
  GPTMx->TRCFR |= TRCFR_ECME;
}

/*********************************************************************************************************//**
 * @brief Configure external trigger input (ETI) of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Psc: The external Trigger Prescaler.
 *        It can be one of the following values:
 *        @arg GPTM_ETIPSC_OFF : ETI prescaler off
 *        @arg GPTM_ETIPSC_2   : ETIP frequency divided by 2
 *        @arg GPTM_ETIPSC_4   : ETIP frequency divided by 4
 *        @arg GPTM_ETIPSC_8   : ETIP frequency divided by 8
 * @param Pol: The external trigger input polarity.
 *        It can be one of the following values:
 *        @arg GPTM_ETIPOL_NONINVERTED : Active high level or rising edge
 *        @arg GPTM_ETIPOL_INVERTED    : Active low level or falling edge
 * @param Filter: Filter for ETI input.
 *        This parameter must be a value between 0x00 and 0x0F
 * @retval None
 ************************************************************************************************************/
void GPTM_EtiConfig(AM_GPTM_TypeDef* GPTMx, GPTM_ETIPSC_Enum Psc, GPTM_ETIPOL_Enum Pol, u8 Filter)
{
  u32 wTrcfr;

  /* Get TRCFR value with cleared ETI configuration bits */
  wTrcfr = GPTMx->TRCFR & TRCFR_ETI_CONF_MASK;

  /* Set the prescaler, filter and polarity for ETI inpit */
  wTrcfr |= (u32)Psc | Pol | ((u32)Filter << 8);

  /* Write to GPTMx TRCFR */
  GPTMx->TRCFR = wTrcfr;
}

/*********************************************************************************************************//**
 * @brief Configure prescaler of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Psc: Specify the prescaler value.
 * @param PscReloadTime: Specify the GPTM prescaler reload time.
 *        This parameter can be one of the following values:
 *        @arg GPTM_PSC_RLD_UPDATE    : The prescaler is loaded at the next update event.
 *        @arg GPTM_PSC_RLD_IMMEDIATE : The prescaler is loaded immediatly.
 * @retval None
 ************************************************************************************************************/
void GPTM_PrescalerConfig(AM_GPTM_TypeDef* GPTMx, u16 Psc, GPTM_PSC_RLD_Enum PscReloadTime)
{
  /* Set the prescaler value */
  GPTMx->PSCR = Psc;

  /* Set the UEVG bit or not */
  GPTMx->EVGR = PscReloadTime;
}

/*********************************************************************************************************//**
 * @brief Configure counter mode of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Mod: Specify the counter mode to be used.
 *        This parameter can be one of the following values:
 *        @arg GPTM_CNT_MODE_UP   : GPTM up counting mode.
 *        @arg GPTM_CNT_MODE_DOWN : GPTM down counting mode.
 *        @arg GPTM_CNT_MODE_CA1  : GPTM center aligned mode 1.
 *        @arg GPTM_CNT_MODE_CA2  : GPTM center aligned mode 2.
 *        @arg GPTM_CNT_MODE_CA3  : GPTM center aligned mode 3.
 * @retval None
 ************************************************************************************************************/
void GPTM_CounterModeConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CNT_MODE_Enum Mod)
{
  /* Reset the CMSEL and DIR Bits */
  GPTMx->CNTCFR &= CNTCFR_CMSEL_MASK;
  GPTMx->CNTCFR &= ~CNTCFR_DIR;

  /* Set the Counter Mode */
  GPTMx->CNTCFR |= Mod;
}

/*********************************************************************************************************//**
 * @brief Select the STI source.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Sel: Store the STI source.
 *        This parameter can be one of the following:
 *        @arg GPTM_TRSEL_ITI0  : Internal trigger 0.
 *        @arg GPTM_TRSEL_ITI1  : Internal trigger 1.
 *        @arg GPTM_TRSEL_ITI2  : Internal trigger 2.
 *        @arg GPTM_TRSEL_TI0BED : TI0 both edge detector.
 *        @arg GPTM_TRSEL_TI0S0 : Filtered channel 0 input.
 *        @arg GPTM_TRSEL_TI1S1 : Filtered channel 1 input.
 *        @arg GPTM_TRSEL_ETIF  : External trigger input.
 *        @arg GPTM_TRSEL_UEVG  : Trigger by setting UEVG bit.
 * @retval None
 ************************************************************************************************************/
void GPTM_StiConfig(AM_GPTM_TypeDef* GPTMx, GPTM_TRSEL_Enum Sel)
{
  u32 wTrcfr;

  /* Disable slave mode */
  GPTMx->MDCFR &= MDCFR_SMSEL_MASK;

  /* Get the TRCFR value with cleared TRSEL */
  wTrcfr = GPTMx->TRCFR & TRCFR_TRSEL_MASK;

  /* Set the STI source */
  GPTMx->TRCFR |= wTrcfr | Sel;
}

/*********************************************************************************************************//**
 * @brief Configure encoder interface of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param DecoderMod: Specify the GPTMx decoder mode.
 *        This parameter can be one of the following values:
 *        @arg GPTM_SMSEL_DECODER1 : Counter counts on CH0 edge depending on CH1 level.
 *        @arg GPTM_SMSEL_DECODER2 : Counter counts on CH1 edge depending on CH0 level.
 *        @arg GPTM_SMSEL_DECODER3 : Counter counts on both CH0 and CH1 edges depending on
 *             the level of the other input.
 * @param CH0P: Specify the CH0 polarity.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CHP_NONINVERTED : Active high level or rising edge
 *        @arg GPTM_CHP_INVERTED    : Active low level or falling edge
 * @param CH1P: Specify the CH1 polarity.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CHP_NONINVERTED : Active high level or rising edge
 *        @arg GPTM_CHP_INVERTED    : Active low level or falling edge
 * @retval None
 ************************************************************************************************************/
void GPTM_DecoderConfig(AM_GPTM_TypeDef* GPTMx, GPTM_SMSEL_Enum DecoderMod,
                        GPTM_CHP_Enum CH0P, GPTM_CHP_Enum CH1P)
{
  u32 wMdcfr, wCh0Icfr, wCh1Icfr, wChpolr;

  /* Get the GPTMx MDCFR register value */
  wMdcfr = GPTMx->MDCFR;

  /* Get the GPTMx CH0ICFR & CH1ICFR register value */
  wCh0Icfr = GPTMx->CH0ICFR;
  wCh1Icfr = GPTMx->CH1ICFR;

  /* Get the GPTMx CHPOLR register value */
  wChpolr = GPTMx->CHPOLR;

  /* Set the decoder mode */
  wMdcfr &= MDCFR_SMSEL_MASK;
  wMdcfr |= DecoderMod;

  /* Select the channel 0 and the channel 1 as input and clear CH0SRC */
  wCh0Icfr &= CHICFR_CHCCS_MASK & (~CH0ICFR_CH0SRC);
  wCh1Icfr &= CHICFR_CHCCS_MASK;
  wCh0Icfr |= GPTM_CHCCS_DIRECT;
  wCh1Icfr |= GPTM_CHCCS_DIRECT;

  /* Set the CH0 and the CH1 polarities */
  wChpolr &= ~(CHPOLR_CH0P | CHPOLR_CH1P);
  wChpolr |= (CH0P | (CH1P << 2));

  /* Write to GPTMx MDCFR */
  GPTMx->MDCFR = wMdcfr;

  /* Write to GPTMx CH0ICFR & CH1ICFR */
  GPTMx->CH0ICFR = wCh0Icfr;
  GPTMx->CH1ICFR = wCh1Icfr;

  /* Write to GPTMx CHPOLR */
  GPTMx->CHPOLR = wChpolr;
}

/*********************************************************************************************************//**
 * @brief Force the GPTMx CH0OREF waveform to active or inactive level.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param ForcedAction: Specify the forced action to be set to the output waveform.
 *        This parameter can be one of the following values:
 *        @arg GPTM_OM_FORCED_ACTIVE   : Forced active level on CH0OREF
 *        @arg GPTM_OM_FORCED_INACTIVE : Forced inactive level on CH0OREF.
 * @retval None
 ************************************************************************************************************/
void GPTM_ForcedOREF0(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction)
{
  /* Configure The forced output mode */
  GPTMx->CH0OCFR = (GPTMx->CH0OCFR & CHOCFR_CHOM_MASK) | ForcedAction;
}

/*********************************************************************************************************//**
 * @brief Force the GPTMx CH1OREF waveform to active or inactive level.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param ForcedAction: Specify the forced action to be set to the output waveform.
 *        This parameter can be one of the following values:
 *        @arg GPTM_OM_FORCED_ACTIVE   : Force active level on CH1OREF
 *        @arg GPTM_OM_FORCED_INACTIVE : Force inactive level on CH1OREF.
 * @retval None
 ************************************************************************************************************/
void GPTM_ForcedOREF1(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction)
{
  /* Configure The forced output mode */
  GPTMx->CH1OCFR = (GPTMx->CH1OCFR & CHOCFR_CHOM_MASK) | ForcedAction;
}

/*********************************************************************************************************//**
 * @brief Force the GPTMx CH2OREF waveform to active or inactive level.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param ForcedAction: Specify the forced action to be set to the output waveform.
 *        This parameter can be one of the following values:
 *        @arg GPTM_OM_FORCED_ACTIVE   : Force active level on CH2OREF
 *        @arg GPTM_OM_FORCED_INACTIVE : Force inactive level on CH2OREF.
 * @retval None
 ************************************************************************************************************/
void GPTM_ForcedOREF2(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction)
{
  /* Configure The forced output mode */
  GPTMx->CH2OCFR = (GPTMx->CH2OCFR & CHOCFR_CHOM_MASK) | ForcedAction;
}

/*********************************************************************************************************//**
 * @brief Force the GPTMx CH3OREF waveform to active or inactive level.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param ForcedAction: Specify the forced action to be set to the output waveform.
 *        This parameter can be one of the following values:
 *        @arg GPTM_OM_FORCED_ACTIVE   : Force active level on CH3OREF
 *        @arg GPTM_OM_FORCED_INACTIVE : Force inactive level on CH3OREF.
 * @retval None
 ************************************************************************************************************/
void GPTM_ForcedOREF3(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction)
{
  /* Configure The forced output mode */
  GPTMx->CH3OCFR = (GPTMx->CH3OCFR & CHOCFR_CHOM_MASK) | ForcedAction;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the GPTMx CRR preload function.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_CRRPreloadCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    /* Set the CRR preload control bit */
    GPTMx->CTR |= CTR_CRBE;
  }
  else
  {
    /* Reset the CRR preload control bit */
    GPTMx->CTR &= ~CTR_CRBE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the GPTMx CHxCCR preload function.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param NewState This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_CHCCRPreloadConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, ControlStatus NewState)
{
  vu32 *pOcfr = (vu32*)&GPTMx->CH0OCFR + Channel;

  /* Enable or disable the channel N CCR preload feature */
  if(NewState != DISABLE)
  {
    *pOcfr |= CHOCFR_CHPRE;
  }
  else
  {
    *pOcfr &= ~CHOCFR_CHPRE;
  }
}

/*********************************************************************************************************//**
 * @brief Clear or Safeguard the CHxOREF signal when ETI is active.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param NewState This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_ClearOREFConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, ControlStatus NewState)
{
  vu32 *pOcfr = (vu32*)&GPTMx->CH0OCFR + Channel;

  /* Enable or Disable the channel N clear Oref at ETI active function */
  if(NewState != DISABLE)
  {
    *pOcfr |= CHOCFR_REFCE;
  }
  else
  {
    *pOcfr &= ~CHOCFR_REFCE;
  }
}

/*********************************************************************************************************//**
 * @brief Configure polarity of the GPTMx channel N.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param Pol: Specify the polarity of channel N.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CHP_NONINVERTED : active high
 *        @arg GPTM_CHP_INVERTED    : active low
 * @retval None
 ************************************************************************************************************/
void GPTM_ChPolarityConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, GPTM_CHP_Enum Pol)
{
  u32 wChpolr;

  /* Set or reset the CHx polarity */
  wChpolr = GPTMx->CHPOLR & (~(u32)(0x1 << (Channel << 1)));
  GPTMx->CHPOLR = wChpolr | (Pol << (Channel << 1));
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the single pulse immediate active function.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 * @note Must configurs output mode to PWM1 or PWM2 before invok this function.
 ************************************************************************************************************/
void GPTM_ImmActiveConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, ControlStatus NewState)
{
  vu32 *pOcfr = (vu32*)&GPTMx->CH0OCFR + Channel;

  /* Enable or disable the channel N clear CHxOREF at ETI active function */
  if(NewState != DISABLE)
  {
    *pOcfr |= CHOCFR_IMAE;
  }
  else
  {
    *pOcfr &= ~CHOCFR_IMAE;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the GPTMx channel N.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param Control: This parameter can be GPTM_CHCTL_ENABLE or GPTM_CHCTL_DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_ChannelConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, GPTM_CHCTL_Enum Control)
{
  /* Reset the CHxE Bit */
  GPTMx->CHCTR &= ~(u32)(0x1 << (Channel << 1));

  /* Set or reset the CHxE Bit */
  GPTMx->CHCTR |= (u32)Control << (Channel << 1);
}

/*********************************************************************************************************//**
 * @brief Configure output mode of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param Mod: Specify the GPTM output mode.
 *        This paramter can be one of the following values:
 *        @arg GPTM_OM_MATCH_NOCHANGE  : Output dont change on match
 *        @arg GPTM_OM_MATCH_INACTIVE  : Output inactive on compare match
 *        @arg GPTM_OM_MATCH_ACTIVE    : Output active on compare match
 *        @arg GPTM_OM_MATCH_TOGGLE    : Output toggle on compare match
 *        @arg GPTM_OM_FORCED_INACTIVE : Output forced inactive
 *        @arg GPTM_OM_FORCED_ACTIVE   : Output forced active
 *        @arg GPTM_OM_PWM1            : PWM1 mode
 *        @arg GPTM_OM_PWM2            : PWM2 mode
 * @retval None
 * @note This function disables the selected channel before changing the output mode.
 ************************************************************************************************************/
void GPTM_OutputModeConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, u32 Mod)
{
  vu32 *pOcfr = (vu32*)&GPTMx->CH0OCFR + Channel;

  /* Disable the channel: Reset the CHxE Bit */
  GPTMx->CHCTR &= ~(u32)(0x1 << (Channel << 1));

  /* Selects the GPTM output mode */
  *pOcfr = (*pOcfr & CHOCFR_CHOM_MASK) | Mod;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable update event of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be ENABLE(default) or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_UpdateCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if (NewState == DISABLE)
  {
    /* Set the update disable bit */
    GPTMx->CNTCFR |= CNTCFR_UEVDIS;
  }
  else
  {
    /* Reset the update disable bit */
    GPTMx->CNTCFR &= ~CNTCFR_UEVDIS;
  }
}

/*********************************************************************************************************//**
 * @brief Configure UEVG interrupt function of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be one of the following value:
 *    @arg ENABLE  : Default value. Any of the following events will generate an update event interrupt:
 *                   - Counter overflow/underflow
 *                   - Setting the UEVG bit
 *                   - Update generation through the slave restart mode
 *    @arg DISABLE : Only counter overflow/underflow generations an update event interrupt.
 * @retval None
 ************************************************************************************************************/
void GPTM_UEVG_IntConfig(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if (NewState == DISABLE)
  {
    /* Set the UEVG interrupt disable bit */
    GPTMx->CNTCFR |= CNTCFR_UGDIS;
  }
  else
  {
    /* Reset the UEVG interrupt disable bit */
    GPTMx->CNTCFR &= ~CNTCFR_UGDIS;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable hall sensor interface of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_HallInterfaceCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    /* Set the CH0SRC Bit */
    GPTMx->CH0ICFR |= CH0ICFR_CH0SRC;
  }
  else
  {
    /* Reset the CH0SRC Bit */
    GPTMx->CH0ICFR &= ~CH0ICFR_CH0SRC;
  }
}

/*********************************************************************************************************//**
 * @brief Select single pulse mode of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_SinglePulseModeCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if(NewState != DISABLE)
  {
    GPTMx->MDCFR |= MDCFR_SPMSET;
  }
  else
  {
    GPTMx->MDCFR &= ~MDCFR_SPMSET;
  }
}

/*********************************************************************************************************//**
 * @brief Select master trigger output source of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Sel: Specify the master trigger output source.
 *        This paramter can be as follow:
 *        @arg GPTM_MMSEL_RESET   : Send trigger signal when S/W setting UEVG or slave restart
 *        @arg GPTM_MMSEL_ENABLE  : The counter enable signal is used as trigger output.
 *        @arg GPTM_MMSEL_UPDATE  : The update event is used as trigger output.
 *        @arg GPTM_MMSEL_CH0CC   : Channel 0 capture or compare match occurred as trigger output.
 *        @arg GPTM_MMSEL_CH0OREF : The CH0OREF signal is used as trigger output.
 *        @arg GPTM_MMSEL_CH1OREF : The CH1OREF signal is used as trigger output.
 *        @arg GPTM_MMSEL_CH2OREF : The CH2OREF signal is used as trigger output.
 *        @arg GPTM_MMSEL_CH3OREF : The CH3OREF signal is used as trigger output.
 * @retval None
 ************************************************************************************************************/
void GPTM_MMSELConfig(AM_GPTM_TypeDef* GPTMx, GPTM_MMSEL_Enum Sel)
{
  /* Select the MTO source */
  GPTMx->MDCFR = (GPTMx->MDCFR & MDCFR_MMSEL_MASK) | Sel;
}

/*********************************************************************************************************//**
 * @brief Select slave mode of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Sel: Specify the timer slave mode.
 *        This paramter can be one of the following values:
 *        @arg GPTM_SMSEL_RESTART : Slave restart counter mode.
 *        @arg GPTM_SMSEL_PAUSE   : Slave pause counter mode.
 *        @arg GPTM_SMSEL_TRIGGER : Slave trigger counter start mode.
 *        @arg GPTM_SMSEL_STIED   : Used rising edge of STI as prescaler clock source.
 * @retval None
 ************************************************************************************************************/
void GPTM_SlaveModeConfig(AM_GPTM_TypeDef* GPTMx, GPTM_SMSEL_Enum Sel)
{
  /* Select the slave mode */
  GPTMx->MDCFR = (GPTMx->MDCFR & MDCFR_SMSEL_MASK) | Sel;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the master & slave GPTMx synchronous function.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_TimSyncCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    /* Set the TSE Bit */
    GPTMx->MDCFR |= MDCFR_TSE;
  }
  else
  {
    /* Reset the TSE Bit */
    GPTMx->MDCFR &= ~MDCFR_TSE;
  }
}

/*********************************************************************************************************//**
 * @brief Set counter register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Counter: Specify the counter register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetCounter(AM_GPTM_TypeDef* GPTMx, u16 Counter)
{
  /* Set the Counter Register value */
  GPTMx->CNTR = Counter;
}

/*********************************************************************************************************//**
 * @brief Set counter reload register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Reload: Specify the counter reload register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetCounterReload(AM_GPTM_TypeDef* GPTMx, u16 Reload)
{
  /* Set the counter reload register value */
  GPTMx->CRR = Reload;
}

/*********************************************************************************************************//**
 * @brief Set channel 0 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH0CCR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetCaptureCompare0(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH0CCR register new value */
  GPTMx->CH0CCR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 1 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH1CCR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetCaptureCompare1(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH1CCR register new value */
  GPTMx->CH1CCR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 2 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH2CCR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetCaptureCompare2(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH2CCR register new value */
  GPTMx->CH2CCR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 3 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH3CCR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetCaptureCompare3(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH3CCR register new value */
  GPTMx->CH3CCR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 0 asymmetric compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH0ACR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetAsymmetricCompare0(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH0ACR register new value */
  GPTMx->CH0ACR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 1 asymmetric compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH1ACR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetAsymmetricCompare1(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH1ACR register new value */
  GPTMx->CH1ACR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 2 asymmetric compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH2ACR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetAsymmetricCompare2(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH2ACR register new value */
  GPTMx->CH2ACR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Set channel 3 asymmetric compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Cmp: Specify the CH3CCR register new value.
 * @retval None
 ************************************************************************************************************/
void GPTM_SetAsymmetricCompare3(AM_GPTM_TypeDef* GPTMx, u16 Cmp)
{
  /* Set the CH3ACR register new value */
  GPTMx->CH3ACR = Cmp;
}

/*********************************************************************************************************//**
 * @brief Configure input capture prescaler.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Channel: Specify the GPTM channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param Psc: Specify the input capture prescaler new value.
 *        This parameter can be one of the following values:
 *        @arg GPTM_CHPSC_OFF : No prescaler
 *        @arg GPTM_CHPSC_2   : Capture is done once every 2 events
 *        @arg GPTM_CHPSC_4   : Capture is done once every 4 events
 *        @arg GPTM_CHPSC_8   : Capture is done once every 8 events
 * @retval None
 ************************************************************************************************************/
void GPTM_CHPSCConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, GPTM_CHPSC_Enum Psc)
{
  vu32 *pIcfr = (vu32*)&GPTMx->CH0ICFR + Channel;

  /* Reset the CHxPSC bits */
  *pIcfr &= CHICFR_CHPSC_MASK;

  /* Set the capture input prescaler value */
  *pIcfr |= Psc;
}

/*********************************************************************************************************//**
 * @brief Set clock division value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Div: Specify the clock division value.
 *        This parameter can be one of the following value:
 *        @arg GPTM_CKDIV_OFF : fDTS = fCLKIN
 *        @arg GPTM_CKDIV_2   : fDTS = fCLKIN / 2
 *        @arg GPTM_CKDIV_4   : fDTS = fCLKIN / 4
 * @retval None
 ************************************************************************************************************/
void GPTM_CKDIVConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CKDIV_Enum Div)
{
  /* Reset the CKDIV Bits */
  GPTMx->CNTCFR &= CNTCFR_CKDIV_MASK;

  /* Set the CKDIV value */
  GPTMx->CNTCFR |= Div;
}

/*********************************************************************************************************//**
 * @brief Get channel 0 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @return Value of CH0CCR register
 ************************************************************************************************************/
u32 GPTM_GetCaptureCompare0(AM_GPTM_TypeDef* GPTMx)
{
  /* Get the CH0CCR register value */
  return GPTMx->CH0CCR;
}

/*********************************************************************************************************//**
 * @brief Get channel 1 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @return Value of CH1CCR register
 ************************************************************************************************************/
u32 GPTM_GetCaptureCompare1(AM_GPTM_TypeDef* GPTMx)
{
  /* Get the CH1CCR register value */
  return GPTMx->CH1CCR;
}

/*********************************************************************************************************//**
 * @brief Get channel 2 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @return Value of CH2CCR register
 ************************************************************************************************************/
u32 GPTM_GetCaptureCompare2(AM_GPTM_TypeDef* GPTMx)
{
  /* Get the CH2CCR register value */
  return GPTMx->CH2CCR;
}

/*********************************************************************************************************//**
 * @brief Get channel 3 capture/compare register value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @return Value of CH3CCR register
 ************************************************************************************************************/
u32 GPTM_GetCaptureCompare3(AM_GPTM_TypeDef* GPTMx)
{
  /* Get the CH3CCR register value */
  return GPTMx->CH3CCR;
}

/*********************************************************************************************************//**
 * @brief Get counter value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @return Value of Counter register
 ************************************************************************************************************/
u32 GPTM_GetCounter(AM_GPTM_TypeDef* GPTMx)
{
  /* Get the Counter Register value */
  return GPTMx->CNTR;
}

/*********************************************************************************************************//**
 * @brief Get prescaler value of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @return Value of Prescaler register
 ************************************************************************************************************/
u32 GPTM_GetPrescaler(AM_GPTM_TypeDef* GPTMx)
{
  /* Get the Prescaler Register value */
  return GPTMx->PSCR;
}

/*********************************************************************************************************//**
 * @brief Generate GPTMx events.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_EVENT: Stores the event source.
 *        This parameter can be any combination of following:
 *        @arg GPTM_EVENT_CH0CC     : Timer Capture/compare 0 event
 *        @arg GPTM_EVENT_CH1CC     : Timer Capture/compare 1 event
 *        @arg GPTM_EVENT_CH2CC     : Timer Capture/compare 2 event
 *        @arg GPTM_EVENT_CH3CC     : Timer Capture/compare 3 event
 *        @arg GPTM_EVENT_UEV       : Timer update event
 *        @arg GPTM_EVENT_TEV       : Timer trigger event
 * @retval None
 ************************************************************************************************************/
void GPTM_GenerateEvent(AM_GPTM_TypeDef* GPTMx, u32 GPTM_EVENT)
{
  /* Set the event sources */
  GPTMx->EVGR = GPTM_EVENT;
}

/*********************************************************************************************************//**
 * @brief Check whether the specified GPTMx flag has been set.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_FLAG: Specify the flag to be checked.
 *        This parameter can be one of the following values:
 *        @arg GPTM_FLAG_CH0CC    : GPTM Capture/compare 0 flag
 *        @arg GPTM_FLAG_CH1CC    : GPTM Capture/compare 1 flag
 *        @arg GPTM_FLAG_CH2CC    : GPTM Capture/compare 2 flag
 *        @arg GPTM_FLAG_CH3CC    : GPTM Capture/compare 3 flag
 *        @arg GPTM_FLAG_CH0OC    : GPTM channel 0 overcapture flag
 *        @arg GPTM_FLAG_CH1OC    : GPTM channel 1 overcapture flag
 *        @arg GPTM_FLAG_CH2OC    : GPTM channel 2 overcapture flag
 *        @arg GPTM_FLAG_CH3OC    : GPTM channel 3 overcapture flag
 *        @arg GPTM_FLAG_UEV      : GPTM update flag
 *        @arg GPTM_FLAG_TEV      : GPTM trigger flag
 * @return The new state of GPTM_FLAG (SET or RESET).
 ************************************************************************************************************/
FlagStatus GPTM_GetFlagStatus(AM_GPTM_TypeDef* GPTMx, u32 GPTM_FLAG)
{
  if ((GPTMx->INTSR & GPTM_FLAG) != 0)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear flags of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_FLAG: Specify the flag to be cleared.
 *        This parameter can be any combination of the following values:
 *        @arg GPTM_FLAG_CH0CC    : GPTM Capture/compare 0 flag
 *        @arg GPTM_FLAG_CH1CC    : GPTM Capture/compare 1 flag
 *        @arg GPTM_FLAG_CH2CC    : GPTM Capture/compare 2 flag
 *        @arg GPTM_FLAG_CH3CC    : GPTM Capture/compare 3 flag
 *        @arg GPTM_FLAG_CH0OC    : GPTM channel 0 overcapture flag
 *        @arg GPTM_FLAG_CH1OC    : GPTM channel 1 overcapture flag
 *        @arg GPTM_FLAG_CH2OC    : GPTM channel 2 overcapture flag
 *        @arg GPTM_FLAG_CH3OC    : GPTM channel 3 overcapture flag
 *        @arg GPTM_FLAG_UEV      : GPTM update flag
 *        @arg GPTM_FLAG_TEV      : GPTM trigger flag
 * @retval None
 ************************************************************************************************************/
void GPTM_ClearFlag(AM_GPTM_TypeDef* GPTMx, u32 GPTM_FLAG)
{
  /* Clear the flags */
  GPTMx->INTSR = ~GPTM_FLAG;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-M3 when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified interrupts of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_INT: Specify the GPTM interrupts sources to be enabled or disabled.
 *        This parameter can be any combination of the following values:
 *        @arg GPTM_INT_CH0CC     : GPTM Capture/compare 0 interrupt
 *        @arg GPTM_INT_CH1CC     : GPTM Capture/compare 1 interrupt
 *        @arg GPTM_INT_CH2CC     : GPTM Capture/compare 2 interrupt
 *        @arg GPTM_INT_CH3CC     : GPTM Capture/compare 3 interrupt
 *        @arg GPTM_INT_UEV       : GPTM update interrupt
 *        @arg GPTM_INT_TEV       : GPTM trigger interrupt
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_IntConfig(AM_GPTM_TypeDef* GPTMx, u32 GPTM_INT, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the interrupt sources */
    GPTMx->DICTR |= GPTM_INT;
  }
  else
  {
    /* Disable the interrupt sources */
    GPTMx->DICTR &= ~GPTM_INT;
  }
}

/*********************************************************************************************************//**
 * @brief Check whether the GPTMx interrupt has occurred.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_INT: Specify the GPTM interrupt source to be checked.
 *        This parameter can be one of the following values:
 *        @arg GPTM_INT_CH0CC     : GPTM Capture/compare 0 interrupt
 *        @arg GPTM_INT_CH1CC     : GPTM Capture/compare 1 interrupt
 *        @arg GPTM_INT_CH2CC     : GPTM Capture/compare 2 interrupt
 *        @arg GPTM_INT_CH3CC     : GPTM Capture/compare 3 interrupt
 *        @arg GPTM_INT_UEV       : GPTM update interrupt
 *        @arg GPTM_INT_TEV       : GPTM trigger interrupt
 * @return The new state of the GPTM_INT(SET or RESET)
 ************************************************************************************************************/
FlagStatus GPTM_GetIntStatus(AM_GPTM_TypeDef* GPTMx, u32 GPTM_INT)
{
  u32 itstatus, itenable;

  itstatus = GPTMx->INTSR & GPTM_INT;
  itenable = GPTMx->DICTR & GPTM_INT;

  if ((itstatus != 0) && (itenable != 0))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*********************************************************************************************************//**
 * @brief Clear interrupt pending bits of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_INT: Specify the GPTM interrupt to be cleared.
 *        This parameter can be any combination of the following values:
 *        @arg GPTM_INT_CH0CC     : GPTM Capture/compare 0 interrupt
 *        @arg GPTM_INT_CH1CC     : GPTM Capture/compare 1 interrupt
 *        @arg GPTM_INT_CH2CC     : GPTM Capture/compare 2 interrupt
 *        @arg GPTM_INT_CH3CC     : GPTM Capture/compare 3 interrupt
 *        @arg GPTM_INT_UEV       : GPTM update interrupt
 *        @arg GPTM_INT_TEV       : GPTM trigger interrupt
 * @retval None
 ************************************************************************************************************/
void GPTM_ClearIntPendingBit(AM_GPTM_TypeDef* GPTMx, u32 GPTM_INT)
{
  /* Clear the interrupt pending Bit */
  GPTMx->INTSR = ~GPTM_INT;

  /*--------------------------------------------------------------------------------------------------------*/
  /* DSB instruction is added in this function to ensure the write operation which is for clearing interrupt*/
  /* flag is actually completed before exiting ISR. It prevents the NVIC from detecting the interrupt again */
  /* since the write register operation may be pended in the internal write buffer of Cortex-M3 when program*/
  /* has exited interrupt routine. This DSB instruction may be masked if this function is called in the     */
  /* beginning of ISR and there are still some instructions before exiting ISR.                             */
  /*--------------------------------------------------------------------------------------------------------*/
  __DSB();
}

/*********************************************************************************************************//**
 * @brief Disable slave mode to clock the prescaler directly with the internal clock.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @retval None
 ************************************************************************************************************/
void GPTM_InternalClockConfig(AM_GPTM_TypeDef* GPTMx)
{
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  GPTMx->MDCFR &= MDCFR_SMSEL_MASK;
}

/*********************************************************************************************************//**
 * @brief Select Channel Capture/Compare PDMA event of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Selection: This parameter can be GPTM_CHCCDS_CHCCEV or GPTM_CHCCDS_UEV.
 * @retval None
 ************************************************************************************************************/
void GPTM_CHCCDSConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CHCCDS_Enum Selection)
{
  if(Selection != GPTM_CHCCDS_CHCCEV)
  {
    GPTMx->CTR |= CTR_CHCCDS;
  }
  else
  {
    GPTMx->CTR &= ~CTR_CHCCDS;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the specified PDMA requests of the GPTMx.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param GPTM_PDMA: Specify the GPTM PDMA requests to be enabled or disabled.
 *        This parameter can be any combination of the following values:
 *        @arg GPTM_PDMA_CH0CC     : GPTM Capture/compare 0 PDMA request
 *        @arg GPTM_PDMA_CH1CC     : GPTM Capture/compare 1 PDMA request
 *        @arg GPTM_PDMA_CH2CC     : GPTM Capture/compare 2 PDMA request
 *        @arg GPTM_PDMA_CH3CC     : GPTM Capture/compare 3 PDMA request
 *        @arg GPTM_PDMA_UEV       : GPTM update PDMA request
 *        @arg GPTM_PDMA_TEV       : GPTM trigger PDMA request
 * @param NewState: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPTM_PDMAConfig(AM_GPTM_TypeDef* GPTMx, u32 GPTM_PDMA, ControlStatus NewState)
{
  if (NewState != DISABLE)
  {
    /* Enable the PDMA request */
    GPTMx->DICTR |= GPTM_PDMA;
  }
  else
  {
    /* Disable the PDMA request */
    GPTMx->DICTR &= ~GPTM_PDMA;
  }
}

/*********************************************************************************************************//**
 * @brief Configure the CHx as input.
 * @param GPTMx: where GPTMx is the selected GPTM from the GPTM peripheral, x can be 0~3.
 * @param Ch: Specify the GPTM Channel.
 *        This parmeter can be one of the following values:
 *        @arg GPTM_CH_0 : GPTM channel 0
 *        @arg GPTM_CH_1 : GPTM channel 1
 *        @arg GPTM_CH_2 : GPTM channel 2
 *        @arg GPTM_CH_3 : GPTM channel 3
 * @param Pol: The input polarity.
 *        This parameter can be one of the following values:
 *        @arg GPTM_CHP_NONINVERTED : Active high level or rising edge
 *        @arg GPTM_CHP_INVERTED    : Active low level or falling edge
 * @param Sel: Specify the input to be used.
 *        This parameter can be one of the following values:
 *        @arg GPTM_CHCCS_DIRECT   : GPTM CHxI is mapped on CHx.
 *        @arg GPTM_CHCCS_INDIRECT : GPTM CH1I is mapped on CH0 (or CH0I->CH1 or CH2I->CH3 or CH3I->CH2).
 *        @arg GPTM_CHCCS_TRCED    : GPTM CHx is mapped on TRC.
 * @param Filter: Specify the input capture filter.
 *        This parameter must be a value between 0x00 and 0x0F.
 * @retval None
 ************************************************************************************************************/
static void
gptm_CHx_Config(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Ch, GPTM_CHP_Enum Pol, GPTM_CHCCS_Enum Sel, u8 Filter)
{
  vu32* pIcfr = (vu32*)&GPTMx->CH0ICFR + Ch;
  u32 wIcfr, wChpolr;

  /* Disable the channel N: reset the CHxE bit */
  GPTMx->CHCTR &= ~((u32)0x1 << (Ch << 1));

  wIcfr = *pIcfr;
  wChpolr = GPTMx->CHPOLR;

  /* Select the input and set the filter */
  wIcfr &= CHICFR_CHCCS_MASK & CHICFR_CHF_MASK;
  wIcfr |= Sel | Filter;
  *pIcfr = wIcfr;

  /* Select the polarity bit */
  wChpolr &= ~((u32)0x1 << (Ch << 1));
  wChpolr |= (u32)Pol << (Ch << 1);
  GPTMx->CHPOLR = wChpolr;

  /* Set the CHxE Bit */
  GPTMx->CHCTR |= (u32)0x1 << (Ch << 1);
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
