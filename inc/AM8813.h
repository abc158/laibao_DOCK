/********************************************************************************************************//**
 * @file    AM8813.h	
 * @brief   The header file of the AM8813.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#ifndef __AM8813_H__
#define __AM8813_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */
#define __MPU_PRESENT             0    /*!< MPU present or not                                              */
#define __NVIC_PRIO_BITS          2    /*!< Number of Bits used for Priority Levels                         */
#define __Vendor_SysTickConfig    0    /*!< Set to 1 if different SysTick Config is used                    */

/** @addtogroup Configuration_for_Interrupt_Number
  * @{
  */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ******************************                              */
  NonMaskableInt_IRQn     = -14,    /*!< 2 Non Maskable Interrupt                                           */
  HardFault_IRQn          = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                                   */
  SVCall_IRQn             = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                                     */
  DebugMonitor_IRQn       = -4,     /*!< 12 Cortex-M0 Debug Monitor Interrupt                               */
  PendSV_IRQn             = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                                     */
  SysTick_IRQn            = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                                 */
/******  AM8813 Specific Interrupt Numbers ************************************                             */
  CKRDY_IRQn              = 0,      /*!< Clock ready interrupt                                              */
  LVD_IRQn                = 1,      /*!< Low voltage detection interrupt                                    */
  WDT_IRQn                = 2,      /*!< WDT global interrupt                                               */
  RTC_IRQn                = 3,      /*!< RTC Wake-up Interrupt                                              */
  FLASH_IRQn              = 4,      /*!< FLASH global Interrupt                                             */
  EVWUP_IRQn              = 5,      /*!< Event Wake-up Interrupt                                            */
  LPWUP_POR_IRQn          = 6,      /*!< WAKEUP pin and POR Interrupt                                       */
  EXTI0_1_2_3_IRQn        = 7,      /*!< EXTI0~3 Line detection Interrupt                                   */
  EXTI4_5_6_7_IRQn        = 8,      /*!< EXTI4~7 Line detection Interrupt                                   */
  EXTI8_9_10_11_IRQn      = 9,      /*!< EXTI8~11 Line detection Interrupt                                  */
  EXTI12_13_14_15_IRQn    = 10,     /*!< EXTI12~15 Line detection Interrupt                                 */
  ADC_IRQn                = 11,     /*!< ADC Interrupt                                                      */
  GPTM0_IRQn              = 12,     /*!< General-Purpose Timer0 Interrupt                                   */
  GPTM1_IRQn              = 13,     /*!< General-Purpose Timer1 Interrupt                                   */
  GPTM2_IRQn              = 14,     /*!< General-Purpose Timer2 Interrupt                                   */
  GPTM3_IRQn              = 15,     /*!< General-Purpose Timer3 Interrupt                                   */
  I2C0_IRQn               = 16,     /*!< I2C0 global Interrupt                                              */
  SPI0_IRQn               = 17,     /*!< SPI0 global Interrupt                                              */
  UART0_IRQn              = 18,     /*!< UART0 global Interrupt                                             */
  UART1_IRQn              = 19,     /*!< UART1 global Interrupt                                             */
  UART2_IRQn              = 20,     /*!< UART2 global Interrupt                                             */
	UART3_IRQn              = 21,     /*!< UART3 global Interrupt                                             */
	UART4_IRQn              = 22,     /*!< UART4 global Interrupt                                             */
	UART5_IRQn              = 23,     /*!< UART5 global Interrupt                                             */
  PDMACH0_IRQn            = 24,     /*!< PDMA channel 0 global interrupt                                    */
  PDMACH1_IRQn            = 25,     /*!< PDMA channel 1 global interrupt                                    */
  PDMACH2_IRQn            = 26,     /*!< PDMA channel 2 global interrupt                                    */
  PDMACH3_IRQn            = 27,     /*!< PDMA channel 3 global interrupt                                    */
  PDMACH4_CH5_IRQn        = 28,     /*!< PDMA channel 4~5 global interrupt                                  */
  PDMACH6_CH7_IRQn        = 29,     /*!< PDMA channel 6~7 global interrupt                                  */
  COMP_IRQn               = 30,     /*!< COMPARATORS global interrupt                                       */
  CAN_IRQn                = 31      /*!< CAN Controller global interrupt                                    */
} IRQn_Type;

#include "core_cm0.h"               /* Cortex-M0 processor and core peripherals                             */

typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef const int32_t sc32;           /*!< Read Only                                                        */
typedef const int16_t sc16;           /*!< Read Only                                                        */
typedef const int8_t  sc8;            /*!< Read Only                                                        */

typedef __IO int32_t vs32;
typedef __IO int16_t vs16;
typedef __IO int8_t  vs8;

typedef __I int32_t vsc32;            /*!< Read Only                                                        */
typedef __I int16_t vsc16;            /*!< Read Only                                                        */
typedef __I int8_t  vsc8;             /*!< Read Only                                                        */

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;    /*!< Read Only                                                        */
typedef unsigned short const uc16;    /*!< Read Only                                                        */
typedef unsigned char  const uc8;     /*!< Read Only                                                        */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t  vu16;
typedef __IO uint8_t   vu8;

typedef __I uint32_t vuc32;           /*!< Read Only                                                        */
typedef __I uint16_t vuc16;           /*!< Read Only                                                        */
typedef __I uint8_t  vuc8;            /*!< Read Only                                                        */


typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus,FunctionalState;

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus, ErrorStatus;

//typedef enum {FLAG_NOTSET = 0, FLAG_SET = !FLAG_NOTSET} FLAG_STATUS;

/**
  * @}
  */

#if defined (__CC_ARM)
  #define __ALIGN4 __align(4)
#elif defined (__ICCARM__)
  #define __ALIGN4 _Pragma("data_alignment = 4")
#elif defined (__GNUC__)
  #define __ALIGN4  __attribute__((aligned(4)))
#endif

#if defined (__GNUC__)
  #define __PACKED_H
  #define __PACKED_F __attribute__ ((packed))
#elif defined (__ICCARM__) || (__CC_ARM)
  #define __PACKED_H __packed
  #define __PACKED_F
#endif

#if defined (__CC_ARM)
#pragma anon_unions
#endif


#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)

/**
 * @brief Exported constants and macro
 */
#define IS_CONTROL_STATUS(STATUS) ((STATUS == DISABLE) || (STATUS == ENABLE))

#define wb(addr, value)     (*((u8  volatile *) (addr)) = value)
#define rb(addr)            (*((u8  volatile *) (addr)))
#define whw(addr, value)    (*((u16 volatile *) (addr)) = value)
#define rhw(addr)           (*((u16 volatile *) (addr)))
#define ww(addr, value)     (*((u32 volatile *) (addr)) = value)
#define rw(addr)            (*((u32 volatile *) (addr)))


#define ResetBit_BB(Addr, BitNumber) ((*(vu32 *)Addr) = ((*(vu32 *)Addr)&(~(1<<BitNumber))))
#define SetBit_BB(Addr, BitNumber)   ((*(vu32 *)Addr) = ((*(vu32 *)Addr)|(1<<BitNumber)))


/**
 * @brief Analog to Digital Converter
 */
typedef struct
{
                                 /* ADC: 0x40010000                                                         */
  __IO uint32_t CTL;					   /*!< 0x000  				ADC Control Register 					                          */
  __IO uint32_t CONV;            /*!< 0x004         ADC Regular Conversion Mode Register                    */
  __IO uint32_t HCONV;           /*!< 0x008         ADC High-priority Conversion Mode Register              */
  __IO uint32_t LST[5];          /*!< 0x00C - 0x01C ADC Regular Conversion List Register 0-4                */
  __IO uint32_t HLST;            /*!< 0x020         ADC High-priority Conversion List Register              */
  __IO uint32_t DR[18];          /*!< 0x024 - 0x068 ADC Regular Conversion Data Register 0-17               */
  __IO uint32_t HDR[4];          /*!< 0x06C - 0x078 ADC High-priority Conversion Data Register 0-3          */
  __IO uint32_t TCR;             /*!< 0x07C         ADC Regular Trigger Control Register                    */
  __IO uint32_t TSR;             /*!< 0x080         ADC Regular Trigger Source Register                     */
  __IO uint32_t HTCR;            /*!< 0x084         ADC High-priority Trigger Control Register              */
  __IO uint32_t HTSR;            /*!< 0x088         ADC High-priority Trigger Source Register               */
  __IO uint32_t WCR;             /*!< 0x08C       	ADC Watchdog Control Register                           */
  __IO uint32_t LTR;             /*!< 0x090         ADC Lower Threshold Register                            */
  __IO uint32_t UTR;             /*!< 0x094         ADC Upper Threshold Register                            */
  __IO uint32_t IER;             /*!< 0x098         ADC Interrupt Enable Register                           */
  __IO uint32_t IRAW;            /*!< 0x09C         ADC Interrupt Raw Status Register                       */
  __IO uint32_t ISR;             /*!< 0x0A0         ADC Interrupt Status Register                           */
  __IO uint32_t ICLR;            /*!< 0x0A4         ADC Interrupt Clear Register                            */
  __IO uint32_t PDMAR;           /*!< 0x0A8         ADC PDMA Request Register                               */
} AM_ADC_TypeDef;
/**
 * @brief Current Source Grobal
 */
typedef struct
{
                                 /* CS: 0x400100b4                                                         */
  __IO uint32_t CTL;					   /*!< 0x000  				Current Source Control Register 					             */
} AM_CS_TypeDef;
/**
 * @brief General Purpose I/O
 */
typedef struct
{
                                /* GPIOA: 0x400B0000                                                        */
                                /* GPIOB: 0x400B2000                                                        */
                                /* GPIOC: 0x400B4000                                                        */
                                /* GPIOD: 0x400B6000                                                        */
                                /* GPIOE: 0x400B8000                                                        */
  __IO uint32_t DIRCR;          /*!< 0x000         Data Direction Control Register                          */
  __IO uint32_t INER;           /*!< 0x004         Input function enable register                           */
  __IO uint32_t PUR;            /*!< 0x008         Pull-Up Selection Register                               */
  __IO uint32_t PDR;            /*!< 0x00C         Pull-Down Selection Register                             */
  __IO uint32_t ODR;            /*!< 0x010         Open Drain Selection Register                            */
  __IO uint32_t DRVR;           /*!< 0x014         Drive Current Selection Register                         */
  __IO uint32_t LOCKR;          /*!< 0x018         Lock Register                                            */
  __IO uint32_t DINR;           /*!< 0x01c         Data Input Register                                      */
  __IO uint32_t DOUTR;          /*!< 0x020         Data Output Register                                     */
  __IO uint32_t SRR;            /*!< 0x024         Output Set and Reset Control Register                    */
  __IO uint32_t RR;             /*!< 0x028         Output Reset Control Register                            */
} AM_GPIO_TypeDef;
/**
 * @brief AFIO
 */
typedef struct
{
                                /* AFIO: 0x40022000                                                         */
  __IO uint32_t ESSR[2];        /*!< 0x000         EXTI Source Selection Register 0 ~ 1                     */
       uint32_t RESERVE0[6];    /*!< 0x008 - 0x01C Reserved                                                 */
  __IO uint32_t GPACFGR[2];     /*!< 0x020         GPIO Port A Configuration Register 0 ~ 1                 */
  __IO uint32_t GPBCFGR[2];     /*!< 0x028         GPIO Port B Configuration Register 0 ~ 1                 */
  __IO uint32_t GPCCFGR[2];     /*!< 0x030         GPIO Port C Configuration Register 0 ~ 1                 */
  __IO uint32_t GPDCFGR[2];     /*!< 0x038         GPIO Port D Configuration Register 0 ~ 1                 */
  __IO uint32_t GPECFGR[2];   	/*!< 0x040         GPIO Port E Configuration Register 0               */
} AM_AFIO_TypeDef;
/**
 * @brief External Interrupt/Event Controller
 */
typedef struct
{
                                 /* EXTI: 0x40024000                                                        */
  __IO uint32_t CFGR0;           /*!< 0x000         EXTI Interrupt 0 Configuration Register                 */
  __IO uint32_t CFGR1;           /*!< 0x004         EXTI Interrupt 1 Configuration Register                 */
  __IO uint32_t CFGR2;           /*!< 0x008         EXTI Interrupt 2 Configuration Register                 */
  __IO uint32_t CFGR3;           /*!< 0x00C         EXTI Interrupt 3 Configuration Register                 */
  __IO uint32_t CFGR4;           /*!< 0x010         EXTI Interrupt 4 Configuration Register                 */
  __IO uint32_t CFGR5;           /*!< 0x014         EXTI Interrupt 5 Configuration Register                 */
  __IO uint32_t CFGR6;           /*!< 0x018         EXTI Interrupt 6 Configuration Register                 */
  __IO uint32_t CFGR7;           /*!< 0x01C         EXTI Interrupt 7 Configuration Register                 */
  __IO uint32_t CFGR8;           /*!< 0x020         EXTI Interrupt 8 Configuration Register                 */
  __IO uint32_t CFGR9;           /*!< 0x024         EXTI Interrupt 9 Configuration Register                 */
  __IO uint32_t CFGR10;          /*!< 0x028         EXTI Interrupt 10 Configuration Register                */
  __IO uint32_t CFGR11;          /*!< 0x02C         EXTI Interrupt 11 Configuration Register                */
  __IO uint32_t CFGR12;          /*!< 0x030         EXTI Interrupt 12 Configuration Register                */
  __IO uint32_t CFGR13;          /*!< 0x034         EXTI Interrupt 13 Configuration Register                */
  __IO uint32_t CFGR14;          /*!< 0x038         EXTI Interrupt 14 Configuration Register                */
  __IO uint32_t CFGR15;          /*!< 0x03C         EXTI Interrupt 15 Configuration Register                */
  __IO uint32_t CR;              /*!< 0x040         EXTI Interrupt Control Register                         */
  __IO uint32_t EDGEFLGR;        /*!< 0x044         EXTI Interrupt Edge Flag Register                       */
  __IO uint32_t EDGESR;          /*!< 0x048         EXTI Interrupt Edge Status Register                     */
  __IO uint32_t SSCR;            /*!< 0x04C         EXTI Interrupt Software Set Command Register            */
  __IO uint32_t WAKUPCR;         /*!< 0x050         EXTI Interrupt Wakeup Control Register                  */
  __IO uint32_t WAKUPPOLR;       /*!< 0x054         EXTI Interrupt Wakeup Polarity Register                 */
  __IO uint32_t WAKUPFLG;        /*!< 0x058         EXTI Interrupt Wakeup Flag Register                     */
} AM_EXTI_TypeDef;
/**
 * @brief General-Purpose Timer
 */
typedef struct
{
                                 /* GPTM0: 0x4006E000                                                       */
                                 /* GPTM1: 0x4006F000                                                       */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[7];    /*!< 0x058 - 0x070  Reserved                                               */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
       uint32_t RESERVED4[1];    /*!< 0x08C          Reserved                                               */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
} AM_GPTM_TypeDef;
/**
 * @brief Clock Control Unit
 */
typedef struct
{
                                 /* CKCU: 0x40088000                                                        */
  __IO uint32_t GCFGR;           /*!< 0x000         Global Clock Configuration Register                     */
  __IO uint32_t GCCR;            /*!< 0x004         Global Clock Control Register                           */
  __IO uint32_t GCSR;            /*!< 0x008         Global Clock Status Register                            */
  __IO uint32_t GCIR;            /*!< 0x00C         Global Clock Interrupt Register                         */
       uint32_t RESERVED0[2];    /*!< 0x010 ~ 0x14  Reserved                                                */
  __IO uint32_t PLLCFGR;         /*!< 0x018         PLL Configuration Register                              */
  __IO uint32_t PLLCR;           /*!< 0x01C         PLL Control Register                                    */
  __IO uint32_t AHBCFGR;         /*!< 0x020         AHB Configuration Register                              */
  __IO uint32_t AHBCCR;          /*!< 0x024         AHB Clock Control Register                              */
  __IO uint32_t APBCFGR;         /*!< 0x028         APB Configuration Register                              */
  __IO uint32_t APBCCR0;         /*!< 0x02C         APB Clock Control Register 0                            */
  __IO uint32_t APBCCR1;         /*!< 0x030         APB Clock Control Register 1                            */
  uint32_t RESERVED4[4];         /*!< 0x034~0x040         																									*/   
	
	__IO uint32_t CKCU_LCD;        /*!< 0x044         LCD CLK Register               													*/
	uint32_t RESERVED1[174];       /*!< 0x048 ~ 0x2FC Reserved                                                */
  __IO uint32_t LPCR;            /*!< 0x300         Low Power Control Register                              */
  __IO uint32_t MCUDBGCR;        /*!< 0x304         MCU Debug Control Register                              */
} AM_CKCU_TypeDef;
/**
 * @brief Reset Control Unit
 */
typedef struct
{
                                 /* RSTCU: 0x40088100                                                       */
  __IO uint32_t GRSR;            /*!< 0x000         Global Reset Status Register                            */
  __IO uint32_t AHBPRST;         /*!< 0x004         AHB Peripheral Reset Register                           */
  __IO uint32_t APBPRST0;        /*!< 0x008         APB Peripheral Reset Register 0                         */
  __IO uint32_t APBPRST1;        /*!< 0x00C         APB Peripheral Reset Register 1                         */
} AM_RSTCU_TypeDef;
/**
 * @brief Peripheral Direct Memory Access Channel
 */
typedef struct
{
  __IO uint32_t CR;              /*!< 0x000    PDMA Channel Control Register                                */
  __IO uint32_t SADR;            /*!< 0x004    PDMA Channel Source Address Register                         */
  __IO uint32_t DADR;            /*!< 0x008    PDMA Channel Destination Address Register                    */
  __IO uint32_t CADR;            /*!< 0x00C    PDMA Channel Current Address Register                        */
  __IO uint32_t TSR;             /*!< 0x010    PDMA Channel Transfer Size Register                          */
  __IO uint32_t CTSR;            /*!< 0x014    PDMA Channel Current Transfer Size Register                  */
} AM_PDMACH_TypeDef;
/**
 * @brief Peripheral Direct Memory Access Global
 */
typedef struct
{
                                  /* PDMA: 0x40090000                                                       */
  AM_PDMACH_TypeDef PDMACH0;      /*!< 0x000          PDMA channel  0 registers                             */
  AM_PDMACH_TypeDef PDMACH1;      /*!< 0x018          PDMA channel  1 registers                             */
  AM_PDMACH_TypeDef PDMACH2;      /*!< 0x030          PDMA channel  2 registers                             */
  AM_PDMACH_TypeDef PDMACH3;      /*!< 0x048          PDMA channel  3 registers                             */
  AM_PDMACH_TypeDef PDMACH4;      /*!< 0x060          PDMA channel  4 registers                             */
  AM_PDMACH_TypeDef PDMACH5;      /*!< 0x078          PDMA channel  5 registers                             */
  AM_PDMACH_TypeDef PDMACH6;      /*!< 0x090          PDMA channel  6 registers                             */
  AM_PDMACH_TypeDef PDMACH7;      /*!< 0x0A8          PDMA channel  7 registers                             */
  uint32_t     RESERVED0[24];			/*!< 0x0C0 - 0x011C Reserved                                              */
  __IO uint32_t     ISR0;         /*!< 0x120          PDMA Interrupt Status Register 0                      */
  __IO uint32_t     ISR1;         /*!< 0x124          PDMA Interrupt Status Register 1                      */
  __IO uint32_t     ISCR0;        /*!< 0x128          PDMA Interrupt Status Clear Register 0                */
  __IO uint32_t     ISCR1;        /*!< 0x12C          PDMA Interrupt Status Clear Register 1                */
  __IO uint32_t     IER0;         /*!< 0x130          PDMA Interrupt Enable Register 0                      */
  __IO uint32_t     IER1;         /*!< 0x134          PDMA Interrupt Enable Register 1                      */
	__IO uint32_t   	STTR;					/*!< 0x138					PDMA software trigger test register										*/
} AM_PDMA_TypeDef;

/**
 * @brief SPI
 */
typedef struct
{
                                 /* SPI0: 0x40004000                                                        */
                                 /* SPI1: 0x40005000                                                        */
  __IO uint32_t CR0;             /*!< 0x000         Control Register 0                                      */
  __IO uint32_t CR1;             /*!< 0x004         Control Register 1                                      */
  __IO uint32_t IER;             /*!< 0x008         Interrupt Enable Register                               */
  __IO uint32_t CPR;             /*!< 0x00C         Clock Prescaler Register                                */
  __IO uint32_t DR;              /*!< 0x010         Data Register                                           */
  __IO uint32_t SR;              /*!< 0x014         Status Register                                         */
  __IO uint32_t FCR;             /*!< 0x018         FIFO Control Register                                   */
  __IO uint32_t FSR;             /*!< 0x01C         FIFO Status Register                                    */
  __IO uint32_t FTOCR;           /*!< 0x020         FIFO Time Out Counter Register                          */
} AM_SPI_TypeDef;

/**
 * @brief UART
 */
typedef struct
{
                                 /* UART0: 0x40000000                                                       */
                                 /* UART1: 0x40040000                                                       */
                                 /* UART2: 0x40001000                                                       */
                                 /* UART3: 0x40041000                                                       */
																 /* UART4: 0x40002000                                                       */
																 /* UART5: 0x40003000                                                       */
  union {
  __IO uint32_t RBR;             /*!< 0x000         Receive Buffer Register                                 */
  __IO uint32_t TBR;             /*!< 0x000         Transmit Holding Register                               */
  };
  __IO uint32_t IER;             /*!< 0x004         Interrupt Enable Register                               */
  __IO uint32_t IIR;             /*!< 0x008         Interrupt Identification Register/FIFO Control Register */
  __IO uint32_t FCR;             /*!< 0x00C         FIFO Control Register                                   */
  __IO uint32_t LCR;             /*!< 0x010         Line Control Register                                   */
  __IO uint32_t MCR;             /*!< 0x014         Modem Control Register                                  */
  __IO uint32_t LSR;             /*!< 0x018         Line Status Register                                    */
  __IO uint32_t MSR;             /*!< 0x01C         Modem Status Register                                   */
  __IO uint32_t TPR;             /*!< 0x020         Timing Parameter Register                               */
  __IO uint32_t MDR;             /*!< 0x024         Mode Register                                           */
  __IO uint32_t ICR;             /*!< 0x028         IrDA Register                                           */
  __IO uint32_t RCR;             /*!< 0x02C         RS485 Control Register                                  */
  __IO uint32_t SCR;             /*!< 0x030         Synchronous Control Register                            */
  __IO uint32_t FSR;             /*!< 0x034         FIFO Status Register                                    */
  __IO uint32_t DLR;             /*!< 0x038         Divisor Latch Register                                  */
  __IO uint32_t RESERVE;         /*!< 0x03C        Divisor Latch Register                                   */
	__IO uint32_t DTR;             /*!< 0x040         Debug/Test Register                                     */
} AM_USART_TypeDef;
/**
 * @brief CAN
 */
typedef struct
{
                                 /* CAN: 0x40098000                                                         */
																 /* CAN1: 0x40099000                                                        */
  __IO uint32_t MOD;             /*!< 0x000            Mode Setting Register                            		*/
  __IO uint32_t CMR;             /*!< 0x004            Command Register                              				*/
  __IO uint32_t SR;              /*!< 0x008            Status Register                                			*/
  __IO uint32_t IR;              /*!< 0x00C            Interrupt Register                                 	*/
  __IO uint32_t IER;             /*!< 0x010            Interrupt enableRegister                							*/
	     uint32_t RESERVED0;
	__IO uint32_t BTR0;						 /*!< 0x018            Bus Timing 0 Register                								*/
	__IO uint32_t BTR1;						 /*!< 0x01C            Bus Timing 1 Register               									*/
	__IO uint32_t OCR;						 /*!< 0x020            Output Control Register               								*/
	     uint32_t RESERVED1[2];
	__IO uint32_t ALC;						 /*!< 0x02C            Arbitration Lost Capture             								*/
	__IO uint32_t ECC;						 /*!< 0x030            Error Code Capture             											*/
	__IO uint32_t EWLR;						 /*!< 0x034            Error Warning Limit             											*/
	__IO uint32_t RXERR;					 /*!< 0x038            Receive Error Counter             										*/
	__IO uint32_t TXERR;					 /*!< 0x03C            Transmit Error Counter             									*/
	__IO uint32_t TRFDI_ACAMR[13]; /*!< 0x040-0x70  		 Transmit and Receive Frame Data Information and 
																													Acceptance Code Mask Register        							*/
	__IO uint32_t RMC;						 /*!< 0x074            Receive Message Counter             									*/
	__IO uint32_t RBSA;						 /*!< 0x078            Receive Buffer Start Address             						*/
	__IO uint32_t CDR;						 /*!< 0x07C            Clock Divider             														*/
	__IO uint32_t RFIFO[64];			 /*!< 0x080-0x17C      Receive FIFO            															*/
	__IO uint32_t TXBUF[13];			 /*!< 0x180-0x1B0      Transmit Buffer            													*/
} AM_CAN_TypeDef;
/**
 * @brief LCD Global
 */
typedef struct
{
                                  /* LCD LED: 0x4002C000                                                        */
  __IO uint32_t LCD_ENABLE;                                             
  __IO uint32_t LCD_CTRL;                                             
	__IO uint32_t LCD_DATA0;                                  
  __IO uint32_t LCD_DATA1; 
	__IO uint32_t LCD_DATA2;                                  
  __IO uint32_t LCD_DATA3; 
	__IO uint32_t LCD_DATA4;                                  
  __IO uint32_t LCD_DATA5; 
	__IO uint32_t LCD_DATA6;                                  
  __IO uint32_t LCD_DATA7; 
	__IO uint32_t PWM_CNT;                                  
  __IO uint32_t LCD_ANALOGE; 	
	
} AM_LCD_TypeDef;
/**
 * @brief Flash Global
 */
typedef struct
{
                                /* FLASH: 0x40080000                                                        */
  __IO uint32_t OSR;            /*!< 0x000         EXTI Source Selection Register 0 ~ 1                     */
  __IO uint32_t OCMR;           /*!< 0x008 - 0x01C Reserved                                                 */
  __IO uint32_t TADR;           /*!< 0x020         GPIO Port A Configuration Register 0 ~ 1                 */
  __IO uint32_t WRDR;           /*!< 0x028         GPIO Port B Configuration Register 0 ~ 1                 */
  __IO uint32_t OPCR;           /*!< 0x030         GPIO Port C Configuration Register 0 ~ 1                 */
  __IO uint32_t RDDR;           /*!< 0x038         GPIO Port D Configuration Register 0 ~ 1                 */
       uint32_t RESERVED1[58];
	__IO uint32_t WCR;   	        /*!< 0x040         GPIO Port E Configuration Register 0                     */
	     uint32_t RESERVED2[64];
	__IO uint32_t MDID;
} AM_FLASH_TypeDef;
/**
 * @brief I2C Global
 */
typedef struct
{
                                 /* I2C0: 0x40048000                                                        */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t IER;             /*!< 0x004         Interrupt Enable Register                               */
  __IO uint32_t ADDR;            /*!< 0x008         Address Register                                        */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t SHPGR;           /*!< 0x010         SCL High Period Generation Register                     */
  __IO uint32_t SLPGR;           /*!< 0x014         SCL Low Period Generation Register                      */
  __IO uint32_t DR;              /*!< 0x018         Data Register                                           */
  __IO uint32_t TAR;             /*!< 0x01C         Target Register                                         */
  __IO uint32_t ADDMR;           /*!< 0x020         Address Mask Register                                   */
  __IO uint32_t ADDBR;           /*!< 0x024         Address Buffer Register                                 */
  __IO uint32_t TOUT;            /*!< 0x028         Timeout Register                                        */
} AM_I2C_TypeDef;
/**
 * @brief Power Control Global
 */
typedef struct
{
                                 /* PWRCU: 0x4006A100                                                       */
  __IO uint32_t BAKSR;           /*!< 0x000         Backup Domain Status Register                           */
  __IO uint32_t BAKCR;           /*!< 0x004         Backup Domain Control Register                          */
  __IO uint32_t BAKTEST;         /*!< 0x008         Backup Domain Test Register                             */
  __IO uint32_t OTBCR;           /*!< 0x00C         HSI Ready Counter Control Register                      */
  __IO uint32_t LVDCSR;          /*!< 0x010         Low Voltage/Brown Out Detect Control and Status Register*/
	__IO uint32_t VDDSETR;
	__IO uint32_t RTCVDDSETR;
       uint32_t RESERVE0[57];    /*!< 0x014 ~ 0x0FC Reserved                                                */
  __IO uint32_t BAKREG[10];      /*!< 0x100 ~ 0x124 Backup Register 0 ~ 9                                   */
} AM_PWRCU_TypeDef;
/**
 * @brief RTC Global
 */
typedef struct
{
                                 /* RTC: 0x4006A000                                                         */
  __IO uint32_t CNT;             /*!< 0x000         RTC Counter Register                                    */
  __IO uint32_t CMP;             /*!< 0x004         RTC Compare Register                                    */
  __IO uint32_t CR;              /*!< 0x008         RTC Control Register                                    */
  __IO uint32_t SR;              /*!< 0x00C         RTC Status Register                                     */
  __IO uint32_t IWEN;            /*!< 0x010         RTC Interrupt/Wake-up Enable Register                   */
	__IO uint32_t RTCCALSET;			 /*!< 0x014         RTC Calendar Setting Register				                    */
	__IO uint32_t RTCCALCNT;			 /*!< 0x018         RTC Calendar Counter Register				                    */
	__IO uint32_t RTCALM;			     /*!< 0x01C         RTC Alarm Setting Register					                    */
	__IO uint32_t RTCOSCIM;				 /*!< 0x020         RTC RC OSC Current Setting Register		                  */
	__IO uint32_t RTCOSCRM;				 /*!< 0x024         RTC RC OSC Resistor Setting Register                    */
} AM_RTC_TypeDef;
/**
 * @brief WATCHDOG Global
 */
typedef struct
{
                                 /* WDT: 0x40068000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t MR0;             /*!< 0x004         Mode 0 Register                                         */
  __IO uint32_t MR1;             /*!< 0x008         Mode 1 Register                                         */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t PR;              /*!< 0x010         Write Protect Register                                  */
  __IO uint32_t CNTR;            /*!< 0x014         Counter Register                                        */
  __IO uint32_t CSR;             /*!< 0x018         Clock Selection Register                                */
} AM_WDT_TypeDef;
/**
 * @brief CRC Global
 */
typedef struct
{
                                 /* CRC: 0x4008A000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t SDR;             /*!< 0x004         Seed Register                                           */
  __IO uint32_t CSR;             /*!< 0x008         Checksum Register                                       */
  __IO uint32_t DR;              /*!< 0x00C         Data Register                                           */
} AM_CRC_TypeDef;
/**
 * @brief COMP Global
 */
typedef struct
{
                                 /* COMP: 0x40043000                                                         */
  __IO uint32_t CCSR;            /*!< 0x000         Control and Status Register                              */
  __IO uint32_t WICR;            /*!< 0x004         COMP Wake-up and Interrupt Control Register              */
} AM_COMP_TypeDef;
/**
 * @brief TRNG Global
 */
typedef struct
{
                                /* TRNG: 0x40006000                                                         */
  __IO uint32_t CTRL;           /*!< 0x000         Control Register 											                  */
  __IO uint32_t DATA;           /*!< 0x004 				 Data Register                                            */
} AM_TRNG_TypeDef;

/** @addtogroup Peripheral_Memory_Map
  * @{
  */
#define AM_SRAM_BASE             ((u32)0x20000000)

#define AM_PERIPH_BASE           ((u32)0x40000000)

#define AM_APB0PERIPH_BASE       (AM_PERIPH_BASE)                 /* 0x40000000                             */
#define AM_APB1PERIPH_BASE       (AM_PERIPH_BASE + 0x40000)       /* 0x40040000                             */
#define AM_AHBPERIPH_BASE        (AM_PERIPH_BASE + 0x80000)       /* 0x40080000                             */

/* APB0      																																																*/
#define AM_UART0_BASE            (AM_APB0PERIPH_BASE + 0x0000)    /* 0x40000000                             */
#define AM_UART2_BASE            (AM_APB0PERIPH_BASE + 0x1000)    /* 0x40001000                             */
#define AM_UART4_BASE            (AM_APB0PERIPH_BASE + 0x2000)    /* 0x40001000                             */
#define AM_UART5_BASE            (AM_APB0PERIPH_BASE + 0x3000)    /* 0x40001000                             */
#define AM_SPI0_BASE             (AM_APB0PERIPH_BASE + 0x4000)    /* 0x40004000                             */
#define AM_SPI1_BASE             (AM_APB0PERIPH_BASE + 0x5000)    /* 0x40005000                             */
#define AM_TRNG_BASE             (AM_APB0PERIPH_BASE + 0x6000)    /* 0x40006000                             */
#define AM_ADC_BASE              (AM_APB0PERIPH_BASE + 0x10000)   /* 0x40010000                             */
#define AM_CS_BASE               (AM_APB0PERIPH_BASE + 0x100b4)   /* 0x400100b4                             */
#define AM_AFIO_BASE             (AM_APB0PERIPH_BASE + 0x22000)   /* 0x40022000                             */
#define AM_EXTI_BASE             (AM_APB0PERIPH_BASE + 0x24000)   /* 0x40024000                             */
#define AM_LCD_BASE       	     (AM_APB0PERIPH_BASE + 0x2C000)   /* 0x4002C000                             */

/* APB1                                                                                                     */
#define AM_UART1_BASE            (AM_APB1PERIPH_BASE + 0x0000)    /* 0x40040000                             */
#define AM_UART3_BASE            (AM_APB1PERIPH_BASE + 0x1000)    /* 0x40041000                             */
#define AM_COMP_BASE             (AM_APB1PERIPH_BASE + 0x3000)    /* 0x40043000                             */
#define AM_I2C0_BASE             (AM_APB1PERIPH_BASE + 0x8000)    /* 0x40048000                             */
#define AM_WDT_BASE              (AM_APB1PERIPH_BASE + 0x28000)   /* 0x40068000                             */
#define AM_RTC_BASE              (AM_APB1PERIPH_BASE + 0x2A000)   /* 0x4006A000                             */
#define AM_PWRCU_BASE            (AM_APB1PERIPH_BASE + 0x2A100)   /* 0x4006A100                              */
#define AM_GPTM0_BASE            (AM_APB1PERIPH_BASE + 0x2E000)   /* 0x4006E000                             */
#define AM_GPTM1_BASE            (AM_APB1PERIPH_BASE + 0x2F000)   /* 0x4006F000                             */
#define AM_GPTM2_BASE            (AM_APB1PERIPH_BASE + 0x30000)   /* 0x40070000                             */
#define AM_GPTM3_BASE            (AM_APB1PERIPH_BASE + 0x31000)   /* 0x40071000                             */

/* AHB                 																																										  */                                                                                   
#define AM_PDMA_BASE             (AM_AHBPERIPH_BASE + 0x10000)    /* 0x40090000                             */
#define AM_PDMACH0_BASE					 (AM_PDMA_BASE + 0x0000)				 	/* 0x40090000															*/
#define AM_PDMACH1_BASE					 (AM_PDMA_BASE + 0x0018)					/* 0x40090018															*/
#define AM_PDMACH2_BASE					 (AM_PDMA_BASE + 0x0030)					/* 0x40090030															*/
#define AM_PDMACH3_BASE					 (AM_PDMA_BASE + 0x0048)					/* 0x40090048															*/
#define AM_PDMACH4_BASE					 (AM_PDMA_BASE + 0x0060)					/* 0x40090060															*/
#define AM_PDMACH5_BASE					 (AM_PDMA_BASE + 0x0078)					/* 0x40090078															*/
#define AM_PDMACH6_BASE					 (AM_PDMA_BASE + 0x0090)					/* 0x40090090															*/
#define AM_PDMACH7_BASE					 (AM_PDMA_BASE + 0x00A8)					/* 0x400900A8															*/

#define AM_CAN_BASE            	 (AM_AHBPERIPH_BASE + 0x18000)    /* 0x40098000 												  	*/
#define AM_CAN1_BASE             (AM_AHBPERIPH_BASE + 0x19000)    /* 0x40099000 												  	*/
#define AM_FLASH_BASE            (AM_AHBPERIPH_BASE + 0x0000)     /* 0x40080000                             */
#define AM_CKCU_BASE             (AM_AHBPERIPH_BASE + 0x8000)     /* 0x40088000                             */
#define AM_RSTCU_BASE            (AM_AHBPERIPH_BASE + 0x8100)     /* 0x40088100                             */
#define AM_CRC_BASE              (AM_AHBPERIPH_BASE + 0xA000)     /* 0x4008A000                             */
#define AM_GPIOA_BASE            (AM_AHBPERIPH_BASE + 0x30000)    /* 0x400B0000                             */
#define AM_GPIOB_BASE            (AM_AHBPERIPH_BASE + 0x32000)    /* 0x400B2000                             */
#define AM_GPIOC_BASE            (AM_AHBPERIPH_BASE + 0x34000)    /* 0x400B4000                             */
#define AM_GPIOD_BASE            (AM_AHBPERIPH_BASE + 0x36000)    /* 0x400B6000                             */
#define AM_GPIOE_BASE            (AM_AHBPERIPH_BASE + 0x38000)    /* 0x400B8000                             */

/**
  * @}
  */

/* Peripheral declaration                                                                                   */
#define AM_UART0               ((AM_USART_TypeDef *) AM_UART0_BASE)
#define AM_UART1               ((AM_USART_TypeDef *) AM_UART1_BASE)
#define AM_UART2               ((AM_USART_TypeDef *) AM_UART2_BASE)
#define AM_UART3               ((AM_USART_TypeDef *) AM_UART3_BASE)
#define AM_UART4               ((AM_USART_TypeDef *) AM_UART4_BASE)
#define AM_UART5               ((AM_USART_TypeDef *) AM_UART5_BASE)
#define AM_SPI0                ((AM_SPI_TypeDef *) AM_SPI0_BASE)
#define AM_SPI1                ((AM_SPI_TypeDef *) AM_SPI1_BASE)
#define AM_I2C0                ((AM_I2C_TypeDef *) AM_I2C0_BASE)
#define AM_ADC                 ((AM_ADC_TypeDef *) AM_ADC_BASE)
#define AM_CS                  ((AM_CS_TypeDef *) AM_CS_BASE)
#define AM_AFIO                ((AM_AFIO_TypeDef *) AM_AFIO_BASE)
#define AM_EXTI                ((AM_EXTI_TypeDef *) AM_EXTI_BASE)
#define AM_WDT                 ((AM_WDT_TypeDef *) AM_WDT_BASE)
#define AM_RTC                 ((AM_RTC_TypeDef *) AM_RTC_BASE)
#define AM_PWRCU               ((AM_PWRCU_TypeDef *) AM_PWRCU_BASE)
#define AM_GPTM0               ((AM_GPTM_TypeDef *) AM_GPTM0_BASE)
#define AM_GPTM1               ((AM_GPTM_TypeDef *) AM_GPTM1_BASE)
#define AM_GPTM2               ((AM_GPTM_TypeDef *) AM_GPTM2_BASE)
#define AM_GPTM3               ((AM_GPTM_TypeDef *) AM_GPTM3_BASE)
#define AM_COMP								 ((AM_COMP_TypeDef *) AM_COMP_BASE)
#define AM_LCD                 ((AM_LCD_TypeDef *) AM_LCD_BASE)
#define AM_FLASH               ((AM_FLASH_TypeDef *) AM_FLASH_BASE)
#define AM_CKCU                ((AM_CKCU_TypeDef *) AM_CKCU_BASE)
#define AM_RSTCU               ((AM_RSTCU_TypeDef *) AM_RSTCU_BASE)
#define AM_CRC                 ((AM_CRC_TypeDef *) AM_CRC_BASE)
#define AM_CAN                ((AM_CAN_TypeDef *) AM_CAN_BASE)
#define AM_CAN1                ((AM_CAN_TypeDef *) AM_CAN1_BASE)
#define AM_PDMA                ((AM_PDMA_TypeDef *) AM_PDMA_BASE)
#define AM_GPIOA               ((AM_GPIO_TypeDef *) AM_GPIOA_BASE)
#define AM_GPIOB               ((AM_GPIO_TypeDef *) AM_GPIOB_BASE)
#define AM_GPIOC               ((AM_GPIO_TypeDef *) AM_GPIOC_BASE)
#define AM_GPIOD               ((AM_GPIO_TypeDef *) AM_GPIOD_BASE)
#define AM_GPIOE               ((AM_GPIO_TypeDef *) AM_GPIOE_BASE)
#define AM_TRNG								 ((AM_TRNG_TypeDef *) AM_TRNG_BASE)
#define AM_PDMACH0						 ((AM_PDMACH_TypeDef *)AM_PDMACH0_BASE)
#define AM_PDMACH1						 ((AM_PDMACH_TypeDef *)AM_PDMACH1_BASE)
#define AM_PDMACH2						 ((AM_PDMACH_TypeDef *)AM_PDMACH2_BASE)
#define AM_PDMACH3						 ((AM_PDMACH_TypeDef *)AM_PDMACH3_BASE)
#define AM_PDMACH4						 ((AM_PDMACH_TypeDef *)AM_PDMACH4_BASE)
#define AM_PDMACH5						 ((AM_PDMACH_TypeDef *)AM_PDMACH5_BASE)
#define AM_PDMACH6						 ((AM_PDMACH_TypeDef *)AM_PDMACH6_BASE)
#define AM_PDMACH7						 ((AM_PDMACH_TypeDef *)AM_PDMACH7_BASE)

#define SystemCoreClock        24000000UL    //24M

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
