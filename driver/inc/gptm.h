/********************************************************************************************************//**
 * @file    gptm.h	
 * @brief   The header file of the Gptm Unit library.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __AM8813_GPTM_H
#define __AM8813_GPTM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "AM8813.h"

/**
 * @brief  Enumeration of GPTM counter mode.
 */
typedef enum
{
  GPTM_CNT_MODE_UP   = 0x00000000,  /*!< Edge up-counting mode */
  GPTM_CNT_MODE_CA1  = 0x00010000,  /*!< Center-align mode 1 */
  GPTM_CNT_MODE_CA2  = 0x00020000,  /*!< Center-align mode 2 */
  GPTM_CNT_MODE_CA3  = 0x00030000,  /*!< Center-align mode 3 */
  GPTM_CNT_MODE_DOWN = 0x01000000   /*!< Edge down-counting mode */
} GPTM_CNT_MODE_Enum;
/**
 * @brief Enumeration of  GPTM prescaler reload time.
 */
typedef enum
{
  GPTM_PSC_RLD_UPDATE    = 0x0000,  /*!< Reload prescaler at next update event */
  GPTM_PSC_RLD_IMMEDIATE = 0x0100   /*!< Reload prescaler immediately */
} GPTM_PSC_RLD_Enum;
/**
 * @brief Enumeration of GPTM channel.
 */
typedef enum
{
  GPTM_CH_0 = 0,                    /*!< GPTM channel 0 */
  GPTM_CH_1,                        /*!< GPTM channel 1 */
  GPTM_CH_2,                        /*!< GPTM channel 2 */
  GPTM_CH_3                         /*!< GPTM channel 3 */
} GPTM_CH_Enum;
/**
 * @brief Enumeration of GPTM channel control.
 */
typedef enum
{
  GPTM_CHCTL_DISABLE = 0,           /*!< GPTM channel disable */
  GPTM_CHCTL_ENABLE                 /*!< GPTM channel enable */
} GPTM_CHCTL_Enum;
/**
 * @brief Enumeration of GPTM channel polarity.
 */
typedef enum
{
  GPTM_CHP_NONINVERTED = 0,         /*!< GPTM channel polarity is active high or rising edge */
  GPTM_CHP_INVERTED                 /*!< GPTM channel polarity is active low or falling edge */
} GPTM_CHP_Enum;
/**
 * @brief Enumeration of GPTM channel capture source selection.
 */
typedef enum
{
  GPTM_CHCCS_DIRECT   = 0x00010000,  /*!< GPTM channel capture selection direct input  */
  GPTM_CHCCS_INDIRECT = 0x00020000,  /*!< GPTM channel capture selection indirect input  */
  GPTM_CHCCS_TRCED    = 0x00030000   /*!< GPTM channel capture selection TRCED of trigger control block */
} GPTM_CHCCS_Enum;
/**
 * @brief Enumeration of GPTM channel capture prescaler.
 */
typedef enum
{
  GPTM_CHPSC_OFF = 0x00000000,     /*!< GPTM channel capture no prescaler, capture is done each event */
  GPTM_CHPSC_2   = 0x00040000,     /*!< GPTM channel capture is done once every 2 event */
  GPTM_CHPSC_4   = 0x00080000,     /*!< GPTM channel capture is done once every 4 event */
  GPTM_CHPSC_8   = 0x000C0000      /*!< GPTM channel capture is done once every 8 event */
} GPTM_CHPSC_Enum;
/**
 * @brief Enumeration of GPTM fDTS clock divider.
 */
typedef enum
{
  GPTM_CKDIV_OFF = 0x0000,          /*!< fDTS = fCLKIN */
  GPTM_CKDIV_2   = 0x0100,          /*!< fDTS = fCLKIN / 2 */
  GPTM_CKDIV_4   = 0x0200           /*!< fDTS = fCLKIN / 4 */
} GPTM_CKDIV_Enum;
/**
 * @brief Enumeration of GPTM ETI input prescaler.
 */
typedef enum
{
  GPTM_ETIPSC_OFF = 0x00000000,     /*!< ETI prescaler off */
  GPTM_ETIPSC_2   = 0x00001000,     /*!< ETIP frequency divided by 2 */
  GPTM_ETIPSC_4   = 0x00002000,     /*!< ETIP frequency divided by 4 */
  GPTM_ETIPSC_8   = 0x00003000      /*!< ETIP frequency divided by 8 */
} GPTM_ETIPSC_Enum;
/**
 * @brief Enumeration of GPTM ETI input polarity.
 */
typedef enum
{
  GPTM_ETIPOL_NONINVERTED = 0x00000000, /*!< GPTM ETI polarity is active high or rising edge */
  GPTM_ETIPOL_INVERTED    = 0x00010000  /*!< GPTM ETI polarity is active low or falling edge */
} GPTM_ETIPOL_Enum;
/**
 * @brief Enumeration of GPTM slave trigger input selection.
 */
typedef enum
{
  GPTM_TRSEL_UEVG   = 0x0,         /*!< Software trigger by seting UEVG bit */
  GPTM_TRSEL_TI0S0  = 0x1,         /*!< Filtered channel 0 input */
  GPTM_TRSEL_TI1S1  = 0x2,         /*!< Filtered channel 1 input */
  GPTM_TRSEL_ETIF   = 0x3,         /*!< External Trigger input */
  GPTM_TRSEL_TI0BED = 0x8,         /*!< Trigger input 0 both edge detector */
  GPTM_TRSEL_ITI0   = 0x9,         /*!< Internal trigger 0 */
  GPTM_TRSEL_ITI1   = 0xA,         /*!< Internal trigger 1 */
  GPTM_TRSEL_ITI2   = 0xB          /*!< Internal trigger 2 */
} GPTM_TRSEL_Enum;
/**
 * @brief Enumeration of GPTM slave mode selection.
 */
typedef enum
{
  GPTM_SMSEL_DISABLE  = 0x0000,     /*!< The prescaler is clocked directly by the internal clock */
  GPTM_SMSEL_DECODER1 = 0x0100,     /*!< Counter counts up/down on CH0 edge depending on CH1 level */
  GPTM_SMSEL_DECODER2 = 0x0200,     /*!< Counter counts up/down on CH1 edge depending on CH0 level */
  GPTM_SMSEL_DECODER3 = 0x0300,     /*!< Counter counts up/down on both CH0 & CH1 edges depending on the
                                       level of the other input */
  GPTM_SMSEL_RESTART  = 0x0400,     /*!< Slave restart mode */
  GPTM_SMSEL_PAUSE    = 0x0500,     /*!< Slave pause mode */
  GPTM_SMSEL_TRIGGER  = 0x0600,     /*!< Slave trigger mode */
  GPTM_SMSEL_STIED    = 0x0700      /*!< Rising edge of the selected trigger(STI) clock the counter */
} GPTM_SMSEL_Enum;
/**
 * @brief  Enumeration of GPTM master mode selection.
 */
typedef enum
{
  GPTM_MMSEL_RESET   = 0x00000000,  /*!< Send trigger signal when S/W setting UEVG or slave restart */
  GPTM_MMSEL_ENABLE  = 0x00010000,  /*!< The counter enable signal is used as trigger output. */
  GPTM_MMSEL_UPDATE  = 0x00020000,  /*!< The update event is used as trigger output. */
  GPTM_MMSEL_CH0CC   = 0x00030000,  /*!< Channel 0 capture or compare match occurred as trigger output. */
  GPTM_MMSEL_CH0OREF = 0x00040000,  /*!< The CH0OREF signal is used as trigger output. */
  GPTM_MMSEL_CH1OREF = 0x00050000,  /*!< The CH1OREF signal is used as trigger output. */
  GPTM_MMSEL_CH2OREF = 0x00060000,  /*!< The CH2OREF signal is used as trigger output. */
  GPTM_MMSEL_CH3OREF = 0x00070000   /*!< The CH3OREF signal is used as trigger output. */
} GPTM_MMSEL_Enum;
/**
 * @brief Enumeration of GPTM channel Capture / Compare PDMA selection.
 */
typedef enum
{
  GPTM_CHCCDS_CHCCEV = 0,       /*!< Send CHx PDMA request when channel capture/compare event occurs */
  GPTM_CHCCDS_UEV               /*!< Send CHx PDMA request when update event occurs */
} GPTM_CHCCDS_Enum;
/**
 * @brief Definition of GPTM timebase init structure.
 */
typedef struct
{
  u16                CounterReload; /*!< Period (Value for CRR register) */
  u16                Prescaler;     /*!< Prescaler (Value for PSCR register) */
  GPTM_CNT_MODE_Enum CounterMode;   /*!< Counter mode refer to \ref GPTM_CNT_MODE_Enum */
  GPTM_PSC_RLD_Enum  PSCReloadTime; /*!< Prescaler reload mode refer to \ref GPTM_PSC_RLD_Enum */
} GPTM_TimeBaseInitTypeDef;
/**
 * @brief Definition of GPTM channel output init structure.
 */
typedef struct
{
  GPTM_CH_Enum    Channel;              /*!< Channel selection refer to \ref GPTM_CH_Enum */
  u32             OutputMode;           /*!< Channel output mode selection refer to \ref GPTM_OM_Enum */
  GPTM_CHCTL_Enum Control;              /*!< CHxO output state refer to \ref GPTM_CHCTL_Enum */
  GPTM_CHP_Enum   Polarity;             /*!< CHxO polarity refer to \ref GPTM_CHP_Enum */
  u16             Compare;              /*!< Value for CHxCCR register */
  u16             AsymmetricCompare;    /*!< Value for CHxCCR register */
} GPTM_OutputInitTypeDef;
/**
 * @brief Definition of GPTM channel input init structure.
 */
typedef struct
{
  GPTM_CH_Enum    Channel;         /*!< Channel selection refer to \ref GPTM_CH_Enum */
  GPTM_CHP_Enum   Polarity;        /*!< Channel input polarity refer to \ref GPTM_CHP_Enum */
  GPTM_CHCCS_Enum Selection;       /*!< Channel capture source selection refer to \ref GPTM_CHCCS_Enum */
  GPTM_CHPSC_Enum Prescaler;       /*!< Channel Capture prescaler refer to \ref GPTM_CHPSC_Enum */
  u8              Filter;          /*!< Digital filter Confuration, it must between 0x0 ~ 0xF. */
} GPTM_CaptureInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/

/** @defgroup GPTM_Exported_Constants GPTM exported constants
  * @{
  */

/* Definitions of GPTM_INT */
#define GPTM_INT_CH0CC        0x0001  /*!< Channel 0 capture/compare interrupt */
#define GPTM_INT_CH1CC        0x0002  /*!< Channel 1 capture/compare interrupt */
#define GPTM_INT_CH2CC        0x0004  /*!< Channel 2 capture/compare interrupt */
#define GPTM_INT_CH3CC        0x0008  /*!< Channel 3 capture/compare interrupt */
#define GPTM_INT_UEV          0x0100  /*!< Update interrupt */
#define GPTM_INT_TEV          0x0400  /*!< Trigger interrupt */

/* GPTM channel output modes */
#define GPTM_OM_MATCH_NOCHANGE        0x0000  /*!< GPTM channel output no change on match */
#define GPTM_OM_MATCH_INACTIVE        0x0001  /*!< GPTM channel output inactive level on match */
#define GPTM_OM_MATCH_ACTIVE          0x0002  /*!< GPTM channel output active level on match */
#define GPTM_OM_MATCH_TOGGLE          0x0003  /*!< GPTM channel output toggle on match */
#define GPTM_OM_FORCED_INACTIVE       0x0004  /*!< GPTM channel output forced inactive level */
#define GPTM_OM_FORCED_ACTIVE         0x0005  /*!< GPTM channel output forced active level */
#define GPTM_OM_PWM1                  0x0006  /*!< GPTM channel pwm1 output mode */
#define GPTM_OM_PWM2                  0x0007  /*!< GPTM channel pwm2 output mode */
#define GPTM_OM_ASYMMETRIC_PWM1       0x0106  /*!< GPTM channel asymmetric pwm1 output mode */
#define GPTM_OM_ASYMMETRIC_PWM2       0x0107  /*!< GPTM channel asymmetric pwm2 output mode */

/* Definitions of GPTM_PDMA */
#define GPTM_PDMA_CH0CC        0x00010000  /*!< Channel 0 capture/compare PDMA request */
#define GPTM_PDMA_CH1CC        0x00020000  /*!< Channel 1 capture/compare PDMA request */
#define GPTM_PDMA_CH2CC        0x00040000  /*!< Channel 2 capture/compare PDMA request */
#define GPTM_PDMA_CH3CC        0x00080000  /*!< Channel 3 capture/compare PDMA request */
#define GPTM_PDMA_UEV          0x01000000  /*!< Update PDMA request */
#define GPTM_PDMA_TEV          0x04000000  /*!< Trigger PDMA request */

/* Definitions of GPTM_EVENT */
#define GPTM_EVENT_CH0CC      0x0001  /*!< Channel 0 capture/compare event */
#define GPTM_EVENT_CH1CC      0x0002  /*!< Channel 1 capture/compare event */
#define GPTM_EVENT_CH2CC      0x0004  /*!< Channel 2 capture/compare event */
#define GPTM_EVENT_CH3CC      0x0008  /*!< Channel 3 capture/compare event */
#define GPTM_EVENT_UEV        0x0100  /*!< Update event */
#define GPTM_EVENT_TEV        0x0400  /*!< Trigger event */

/* Definitions of GPTM_FLAG */
#define GPTM_FLAG_CH0CC       0x0001  /*!< Channel 0 capture/compare flag */
#define GPTM_FLAG_CH1CC       0x0002  /*!< Channel 1 capture/compare flag */
#define GPTM_FLAG_CH2CC       0x0004  /*!< Channel 2 capture/compare flag */
#define GPTM_FLAG_CH3CC       0x0008  /*!< Channel 3 capture/compare flag */
#define GPTM_FLAG_CH0OC       0x0010  /*!< Channel 0 over capture flag */
#define GPTM_FLAG_CH1OC       0x0020  /*!< Channel 1 over capture flag */
#define GPTM_FLAG_CH2OC       0x0040  /*!< Channel 2 over capture flag */
#define GPTM_FLAG_CH3OC       0x0080  /*!< Channel 3 over capture flag */
#define GPTM_FLAG_UEV         0x0100  /*!< Update flag */
#define GPTM_FLAG_TEV         0x0400  /*!< Trigger flag */

/* check parameter of the GPTMx */
#define IS_GPTM(x) ((x == AM_GPTM0) || (x == AM_GPTM1))

/* check parameter of the output compare mode */
#define IS_GPTM_OM_CMP(x) (((x) == GPTM_OM_MATCH_NOCHANGE) || \
                           ((x) == GPTM_OM_MATCH_INACTIVE) || \
                           ((x) == GPTM_OM_MATCH_ACTIVE) || \
                           ((x) == GPTM_OM_MATCH_TOGGLE) || \
                           ((x) == GPTM_OM_PWM1) || \
                           ((x) == GPTM_OM_PWM2))

/* check parameter of the output mode */
#define IS_GPTM_OM(x) (((x) == GPTM_OM_MATCH_NOCHANGE) || \
                       ((x) == GPTM_OM_MATCH_INACTIVE) || \
                       ((x) == GPTM_OM_MATCH_ACTIVE) || \
                       ((x) == GPTM_OM_MATCH_TOGGLE) || \
                       ((x) == GPTM_OM_PWM1) || \
                       ((x) == GPTM_OM_PWM2) || \
                       ((x) == GPTM_OM_FORCED_INACTIVE) || \
                       ((x) == GPTM_OM_FORCED_ACTIVE) || \
                       ((x) == GPTM_OM_ASYMMETRIC_PWM1) || \
                       ((x) == GPTM_OM_ASYMMETRIC_PWM2))

/* check parameter of the channel */
#define IS_GPTM_CH(x) (((x) == GPTM_CH_0) || ((x) == GPTM_CH_1) || \
                       ((x) == GPTM_CH_2) || ((x) == GPTM_CH_3))

/* check parameter of the channel for PWM input function */
#define IS_GPTM_CH_PWMI(x) (((x) == GPTM_CH_0) || ((x) == GPTM_CH_1))

/* check parameter of the clock divider */
#define IS_GPTM_CKDIV(x)  ((x == GPTM_CKDIV_OFF) || \
                           (x == GPTM_CKDIV_2) || \
                           (x == GPTM_CKDIV_4))

/* check parameter of the counter mode */
#define IS_GPTM_CNT_MODE(x) ((x == GPTM_CNT_MODE_UP) ||  \
                             (x == GPTM_CNT_MODE_CA1) || \
                             (x == GPTM_CNT_MODE_CA2) || \
                             (x == GPTM_CNT_MODE_CA3) || \
                             (x == GPTM_CNT_MODE_DOWN))

/* check parameter of the channel polarity */
#define IS_GPTM_CHP(x)    ((x == GPTM_CHP_NONINVERTED) || (x == GPTM_CHP_INVERTED))

/* check parameter of the channel control */
#define IS_GPTM_CHCTL(x)  ((x == GPTM_CHCTL_DISABLE) || (x == GPTM_CHCTL_ENABLE))

/* check parameter of the channel capture / compare PDMA selection */
#define IS_GPTM_CHCCDS(x) ((x == GPTM_CHCCDS_CHCCEV) || (x == GPTM_CHCCDS_UEV))

/* check parameter of the channel input selection */
#define IS_GPTM_CHCCS(x)  ((x == GPTM_CHCCS_DIRECT) || \
                           (x == GPTM_CHCCS_INDIRECT) || \
                           (x == GPTM_CHCCS_TRCED))

/* check parameter of the channel capture prescaler */
#define IS_GPTM_CHPSC(x)  ((x == GPTM_CHPSC_OFF) || \
                           (x == GPTM_CHPSC_2) || \
                           (x == GPTM_CHPSC_4) || \
                           (x == GPTM_CHPSC_8))

/* check parameter of the ETI prescaler */
#define IS_GPTM_ETIPSC(x) ((x == GPTM_ETIPSC_OFF) || \
                           (x == GPTM_ETIPSC_2) || \
                           (x == GPTM_ETIPSC_4) || \
                           (x == GPTM_ETIPSC_8))

/* check parameter of the GPTM interrupt */
#define IS_GPTM_INT(x) (((x & 0xFFFFFAF0) == 0x0) && (x != 0))

/* check parameter of the GPTM PDMA request */
#define IS_GPTM_PDMA(x) (((x & 0xFAF0FFFF) == 0x0) && (x != 0))

/* check parameter of the GPTM interrupt for \ref GPTM_GetIntStatus function */
#define IS_GPTM_GET_INT(x)  ((x == GPTM_INT_CH0CC) || \
                             (x == GPTM_INT_CH1CC) || \
                             (x == GPTM_INT_CH2CC) || \
                             (x == GPTM_INT_CH3CC) || \
                             (x == GPTM_INT_UEV) || \
                             (x == GPTM_INT_TEV))

/* check parameter of the GPTM STI selection */
#define IS_GPTM_TRSEL(x) ((x == GPTM_TRSEL_UEVG) || \
                           (x == GPTM_TRSEL_TI0S0) || \
                           (x == GPTM_TRSEL_TI1S1) || \
                           (x == GPTM_TRSEL_ETIF) || \
                           (x == GPTM_TRSEL_TI0BED) || \
                           (x == GPTM_TRSEL_ITI0) || \
                           (x == GPTM_TRSEL_ITI1) || \
                           (x == GPTM_TRSEL_ITI2))

/* check parameter of the ITI */
#define IS_GPTM_ITI(x)  ((x == GPTM_TRSEL_ITI0) || (x == GPTM_TRSEL_ITI1) || (x == GPTM_TRSEL_ITI2))

/* check parameter of the GPTM_TRSEL for \ref GPTM_ChExternalClockConfig function */
#define IS_GPTM_TRSEL_CH(x)  ((x == GPTM_TRSEL_TI0S0) || (x == GPTM_TRSEL_TI1S1) || \
                              (x == GPTM_TRSEL_TI0BED))

/* check parameter of the GPTM ETI polarity */
#define IS_GPTM_ETIPOL(x) ((x == GPTM_ETIPOL_NONINVERTED) || (x == GPTM_ETIPOL_INVERTED))

/* check parameter of the GPTM prescaler reload time */
#define IS_GPTM_PSC_RLD(x) ((x == GPTM_PSC_RLD_UPDATE) || (x == GPTM_PSC_RLD_IMMEDIATE))

/* check parameter of the forced action */
#define IS_GPTM_OM_FORCED(x) ((x == GPTM_OM_FORCED_ACTIVE) || (x == GPTM_OM_FORCED_INACTIVE))

/* check parameter of the decoder mode */
#define IS_GPTM_SMSEL_DECODER(x)  ((x == GPTM_SMSEL_DECODER1) || (x == GPTM_SMSEL_DECODER2) || \
                                   (x == GPTM_SMSEL_DECODER3))

/* check parameter of the event */
#define IS_GPTM_EVENT(x)  (((x & 0xFFFFFAF0) == 0x0000) && (x != 0x0000))

/* check parameter of the GPTM master mode selection */
#define IS_GPTM_MMSEL(x)  (((x) == GPTM_MMSEL_RESET) || \
                           ((x) == GPTM_MMSEL_ENABLE) || \
                           ((x) == GPTM_MMSEL_UPDATE) || \
                           ((x) == GPTM_MMSEL_CH0CC) || \
                           ((x) == GPTM_MMSEL_CH0OREF) || \
                           ((x) == GPTM_MMSEL_CH1OREF) || \
                           ((x) == GPTM_MMSEL_CH2OREF) || \
                           ((x) == GPTM_MMSEL_CH3OREF))

/* check parameter of the GPTM slave mode */
#define IS_GPTM_SLAVE_MODE(x) ((x == GPTM_SMSEL_RESTART) || (x == GPTM_SMSEL_PAUSE) || \
                               (x == GPTM_SMSEL_TRIGGER) || (x == GPTM_SMSEL_STIED))

/* check parameter of the GPTM flag */
#define IS_GPTM_FLAG(x) ((x == GPTM_FLAG_CH0CC) || \
                         (x == GPTM_FLAG_CH1CC) || \
                         (x == GPTM_FLAG_CH2CC) || \
                         (x == GPTM_FLAG_CH3CC) || \
                         (x == GPTM_FLAG_CH0OC) || \
                         (x == GPTM_FLAG_CH1OC) || \
                         (x == GPTM_FLAG_CH2OC) || \
                         (x == GPTM_FLAG_CH3OC) || \
                         (x == GPTM_FLAG_UEV) || \
                         (x == GPTM_FLAG_TEV))

/* check parameter of the GPTM flag for \ref GPTM_ClearFlag function */
#define IS_GPTM_FLAG_CLR(x) (((x & 0xFFFFFA00) == 0) && (x != 0))

/* check value of GPTM digital filter */
#define IS_GPTM_FILTER(x) (x <= 0xF)

/**
  * @}
  */

/** @defgroup GPTM_Exported_Functions GPTM exported functions
  * @{
  */
void GPTM_DeInit(AM_GPTM_TypeDef* GPTMx);
void GPTM_TimeBaseInit(AM_GPTM_TypeDef* GPTMx, GPTM_TimeBaseInitTypeDef* TimeBaseInit);
void GPTM_OutputInit(AM_GPTM_TypeDef* GPTMx, GPTM_OutputInitTypeDef* OutInit) ;
void GPTM_CaptureInit(AM_GPTM_TypeDef* GPTMx, GPTM_CaptureInitTypeDef* CapInit);
void GPTM_PwmInputInit(AM_GPTM_TypeDef* GPTMx, GPTM_CaptureInitTypeDef* CapInit);
void GPTM_TimeBaseStructInit(GPTM_TimeBaseInitTypeDef* TimeBaseInit);
void GPTM_OutputStructInit(GPTM_OutputInitTypeDef* OutInit);
void GPTM_CaptureStructInit(GPTM_CaptureInitTypeDef* CapInit);
void GPTM_Cmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_ItiExternalClockConfig(AM_GPTM_TypeDef* GPTMx, GPTM_TRSEL_Enum Iti);
void GPTM_ChExternalClockConfig(AM_GPTM_TypeDef* GPTMx, GPTM_TRSEL_Enum Sel, GPTM_CHP_Enum Pol, u8 Filter);
void GPTM_EtiExternalClockConfig(AM_GPTM_TypeDef* GPTMx, GPTM_ETIPSC_Enum Psc, GPTM_ETIPOL_Enum Pol, u8 Filter);
void GPTM_EtiConfig(AM_GPTM_TypeDef* GPTMx, GPTM_ETIPSC_Enum Psc, GPTM_ETIPOL_Enum Pol, u8 Filter);
void GPTM_PrescalerConfig(AM_GPTM_TypeDef* GPTMx, u16 Psc, GPTM_PSC_RLD_Enum PscReloadTime);
void GPTM_CounterModeConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CNT_MODE_Enum Mod);
void GPTM_StiConfig(AM_GPTM_TypeDef* GPTMx, GPTM_TRSEL_Enum Sel);
void GPTM_DecoderConfig(AM_GPTM_TypeDef* GPTMx, GPTM_SMSEL_Enum DecoderMod,
                        GPTM_CHP_Enum CH0P, GPTM_CHP_Enum CH1P);
void GPTM_ForcedOREF0(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction);
void GPTM_ForcedOREF1(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction);
void GPTM_ForcedOREF2(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction);
void GPTM_ForcedOREF3(AM_GPTM_TypeDef* GPTMx, u32 ForcedAction);
void GPTM_CRRPreloadCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_CHCCRPreloadConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, ControlStatus NewState) ;
void GPTM_ClearOREFConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, ControlStatus NewState) ;
void GPTM_ChPolarityConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, GPTM_CHP_Enum Pol);

void GPTM_ImmActiveConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, ControlStatus NewState);
void GPTM_ChannelConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, GPTM_CHCTL_Enum Control);

void GPTM_OutputModeConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, u32 Mod);
void GPTM_UpdateCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_UEVG_IntConfig(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_HallInterfaceCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_SinglePulseModeCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_MMSELConfig(AM_GPTM_TypeDef* GPTMx, GPTM_MMSEL_Enum Sel);
void GPTM_SlaveModeConfig(AM_GPTM_TypeDef* GPTMx, GPTM_SMSEL_Enum Sel);
void GPTM_TimSyncCmd(AM_GPTM_TypeDef* GPTMx, ControlStatus NewState);
void GPTM_SetCounter(AM_GPTM_TypeDef* GPTMx, u16 Counter);
void GPTM_SetCounterReload(AM_GPTM_TypeDef* GPTMx, u16 Reload);
void GPTM_SetCaptureCompare0(AM_GPTM_TypeDef* GPTMx, u16 Cmp);
void GPTM_SetCaptureCompare1(AM_GPTM_TypeDef* GPTMx, u16 Cmp);
void GPTM_SetCaptureCompare2(AM_GPTM_TypeDef* GPTMx, u16 Cmp);
void GPTM_SetCaptureCompare3(AM_GPTM_TypeDef* GPTMx, u16 Cmp);

void GPTM_SetAsymmetricCompare0(AM_GPTM_TypeDef* MCTMx, u16 Cmp);
void GPTM_SetAsymmetricCompare1(AM_GPTM_TypeDef* MCTMx, u16 Cmp);
void GPTM_SetAsymmetricCompare2(AM_GPTM_TypeDef* MCTMx, u16 Cmp);
void GPTM_SetAsymmetricCompare3(AM_GPTM_TypeDef* MCTMx, u16 Cmp);

void GPTM_CHPSCConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CH_Enum Channel, GPTM_CHPSC_Enum Psc) ;
void GPTM_CKDIVConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CKDIV_Enum Div);
u32 GPTM_GetCaptureCompare0(AM_GPTM_TypeDef* GPTMx);
u32 GPTM_GetCaptureCompare1(AM_GPTM_TypeDef* GPTMx);
u32 GPTM_GetCaptureCompare2(AM_GPTM_TypeDef* GPTMx);
u32 GPTM_GetCaptureCompare3(AM_GPTM_TypeDef* GPTMx);
u32 GPTM_GetCounter(AM_GPTM_TypeDef* GPTMx);
u32 GPTM_GetPrescaler(AM_GPTM_TypeDef* GPTMx);
void GPTM_GenerateEvent(AM_GPTM_TypeDef* GPTMx, u32 GPTM_EVENT);
FlagStatus GPTM_GetFlagStatus(AM_GPTM_TypeDef* GPTMx, u32 GPTM_FLAG);
void GPTM_ClearFlag(AM_GPTM_TypeDef* GPTMx, u32 GPTM_FLAG);
void GPTM_IntConfig(AM_GPTM_TypeDef* GPTMx, u32 GPTM_INT, ControlStatus NewState);
FlagStatus GPTM_GetIntStatus(AM_GPTM_TypeDef* GPTMx, u32 GPTM_INT);
void GPTM_ClearIntPendingBit(AM_GPTM_TypeDef* GPTMx, u32 GPTM_INT);
void GPTM_InternalClockConfig(AM_GPTM_TypeDef* GPTMx);

void GPTM_CHCCDSConfig(AM_GPTM_TypeDef* GPTMx, GPTM_CHCCDS_Enum Selection);
void GPTM_PDMAConfig(AM_GPTM_TypeDef* GPTMx, u32 GPTM_PDMA, ControlStatus NewState);

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
