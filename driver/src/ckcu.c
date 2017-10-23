/********************************************************************************************************//**
 * @file    ckcu.c
 * @brief   This file provides all the Clock Control Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/

#include "ckcu.h"

extern void SystemCoreClockUpdate(void);

/** @defgroup CKCU_Private_Define CKCU private definitions
  * @{
  */

/* GCFGR bit field definition */
#define CKCU_POS_CKOUTSRC       0
#define CKCU_MASK_CKOUTSRC      ((u32)0x7 << CKCU_POS_CKOUTSRC)

#define CKCU_POS_CKREFPRE       11
#define CKCU_MASK_CKREFPRE      ((u32)0x1F << CKCU_POS_CKREFPRE)

#define CKCU_POS_URPRE          20
#define CKCU_MASK_URPRE         ((u32)0x3 << CKCU_POS_URPRE)

#define CKCU_POS_USBPRE         22
#define CKCU_MASK_USBPRE        ((u32)0x3 << CKCU_POS_USBPRE)

/* GCCR bit field definition */
#define CKCU_POS_SW             0
#define CKCU_MASK_SW            ((u32)0x3 << CKCU_POS_SW)

/* PLLCFGR bit field definition */
#define CKCU_POS_POTD           21
#define CKCU_MASK_POTD          ((u32)0x3 << CKCU_POS_POTD)

#define CKCU_POS_PFBD           23
#define CKCU_MASK_PFBD          ((u32)0x3F << CKCU_POS_PFBD)

/* APBCFGR bit field definition */
#define CKCU_POS_ADCDIV         16
#define CKCU_MASK_ADCDIV        ((u32)0x7 << CKCU_POS_ADCDIV)

/* CKST bit field definition */
#define CKCU_POS_PLLST          8
#define CKCU_MASK_PLLST         ((u32)0xF << CKCU_POS_PLLST)

#define CKCU_POS_HSEST          16
#define CKCU_MASK_HSEST         ((u32)0x3 << CKCU_POS_HSEST)

#define CKCU_POS_HSIST          24
#define CKCU_MASK_HSIST         ((u32)0x7 << CKCU_POS_HSIST)

#define CKCU_POS_CKSWST         30
#define CKCU_MASK_CKSWST        ((u32)0x3 << CKCU_POS_CKSWST)

/** @defgroup CKCU_Private_Macro CKCU private macros
  * @{
  */

#define CKCU_BF_WRITE(Reg, Mask, Pos, WriteValue)   (Reg = ((Reg & ~((u32)Mask)) | ((u32)WriteValue << Pos)))
#define CKCU_BF_READ(Reg, Mask, Pos)                ((Reg & (u32)Mask) >> Pos)

/*********************************************************************************************************//**
 * @brief Enable or Disable the APB peripheral 0 clock.
 * @param CKCU_APBP: specify the APB peripheral 0.
 *        This parameter can be:
 *        @arg CKCU_APBEN0_SPI0,CKCU_APBEN0_SPI1,CKCU_APBEN0_AFIO,CKCU_APBEN0_EXTI,CKCU_APBEN0_ADC,
 *             CKCU_APBEN0_USART0,CKCU_APBEN0_USART2,CKCU_APBEN0_USART4,CKCU_APBEN0_USART5,
 *             or CKCU_APBEN0_LCD.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CKCU_APBPerip0ClockConfig(u32 CKCU_APBP, ControlStatus Cmd)
{
  if (Cmd == ENABLE)
  {
    AM_CKCU->APBCCR0 |= CKCU_APBP;
  }
  else
  {
    AM_CKCU->APBCCR0 &= ~CKCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the APB peripheral 1 clock.
 * @param CKCU_APBP: specify the APB peripheral 1.
 *        This parameter can be:
 *        @arg CKCU_APBEN1_I2C,CKCU_APBEN1_WDT,CKCU_APBEN1_RTC,CKCU_APBEN1_GPTM0,CKCU_APBEN1_GPTM1,
 *             CKCU_APBEN1_GPTM2,CKCU_APBEN1_GPTM3,CKCU_APBEN1_COMP,CKCU_APBEN1_USART1, or CKCU_APBEN1_USART3.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CKCU_APBPerip1ClockConfig(u32 CKCU_APBP, ControlStatus Cmd)
{
  if (Cmd == ENABLE)
  {
    AM_CKCU->APBCCR1 |= CKCU_APBP;
  }
  else
  {
    AM_CKCU->APBCCR1 &= ~CKCU_APBP;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the AHB peripheral clock.
 * @param CKCU_CLK: specify the clock which is enabled or disabled.
 *        This parameter can be:
 *        @arg CKCU_AHBEN_FMC,CKCU_AHBEN_PDMA,CKCU_AHBEN_CRC,CKCU_AHBEN_PA,CKCU_AHBEN_PB,CKCU_AHBEN_PC,
 *             CKCU_AHBEN_PD,CKCU_AHBEN_PE,CKCU_AHBEN_CAN,CKCU_AHBEN_CAN1.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void CKCU_AHBPeripClockConfig(u32 CKCU_CLK, ControlStatus Cmd)
{
  if (Cmd == ENABLE)
  {
    AM_CKCU->AHBCCR |= CKCU_CLK;
  }
  else
  {
    AM_CKCU->AHBCCR &= ~CKCU_CLK;
  }
}

/*********************************************************************************************************//**
 * @brief ADC clock div configure.
 * @param Div: specify the adc clock dividor from system clock. dividor = Div+1 . 
 *        This parameter can be:
 *        @arg 0~47
 * @retval None
 ************************************************************************************************************/
void CKCU_AdcClockDivConfig(u8 Div)
{
	AM_CKCU->APBCFGR = Div;
}

/*********************************************************************************************************//**
 * @brief LCD clock div configure.
 * @param Div: specify the lcd clock dividor from lsi or lse clock.  
 *        This parameter can be:
 *        @arg 0~10
 * @retval None
 ************************************************************************************************************/
void CKCU_LcdClockDivConfig(u8 Div)
{
	AM_CKCU->CKCU_LCD = Div;
}

/*********************************************************************************************************//**
 * @brief This function is used to select LCD  clock Source select.
 * @param src: specify the lcd clock source. 
 *        This parameter can be:
 *        @arg CKCU_LCDSRC_LSI: from LSI,
 *        @arg CKCU_LCDSRC_LSE: from LSE.
 * @retval None
 ************************************************************************************************************/
void CKCU_LCDSrcSel(u8 src)
{
	u32 ck_led = AM_CKCU->CKCU_LCD;
  ck_led &= ~(0x1<<8);
  ck_led |= (src<<8);
  AM_CKCU->CKCU_LCD = ck_led;  
}

/*********************************************************************************************************//**
 * @brief Return the operating frequcncy of the USART.
 * @retval Frequency in Hz
 ************************************************************************************************************/
u32 CKCU_GetUSARTClockFreq(void)
{
  u32 URPRE = CKCU_BF_READ(AM_CKCU->GCFGR, CKCU_MASK_URPRE, CKCU_POS_URPRE);

  SystemCoreClockUpdate();
  return (SystemCoreClock >> URPRE);
}

/*********************************************************************************************************//**
 * @brief This function is used to set pll clock, ahb clock, flash clock.
 * @param Frequency: system clock. 
 *        This parameter can be:
 *        @arg 48, or 24.
 * @retval None
 ************************************************************************************************************/
void Set_sys_Frequency(int Frequency)
{
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;

	if (Frequency == 48)
	{
		pCKCU->PLLCFGR &= ~(0x000000FF);
		pCKCU->PLLCFGR |= (0x5b9<<8);
		pCKCU->AHBCFGR=(1<<0)|(4<<3);		//ahb div2, flash div8
	}
  else if(Frequency == 24)
	{
		pCKCU->PLLCFGR &= ~(0x000000FF);
		pCKCU->PLLCFGR |= (0x2dd<<8);
		pCKCU->AHBCFGR=(0<<0)|(2<<3);		//ahb div1, flash div4
	}

	pCKCU->GCFGR |= (1<<4);		//flash 6M clk from AHB

	pCKCU->GCCR |=1<<9;
	while((pCKCU->GCSR&0x22) != 0x22) ;
	//cpu_delay(10);
	pCKCU->GCCR &=~(3<<0);
}

void Set_sys_Frequency_LSE(int Frequency)
{
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;	
  int tmp;
	if (Frequency == 48)
	{
		pCKCU->AHBCFGR=(0<<0)|(4<<3);
	  pCKCU->PLLCFGR &= ~(0x000000FF);
		pCKCU->PLLCFGR |= (0x5b9<<8);
	}
  else if(Frequency == 24)
	{
		pCKCU->AHBCFGR=(0<<0)|(2<<3);
		pCKCU->PLLCFGR &= ~(0x000000FF);
		pCKCU->PLLCFGR |= (0x2dd<<8);
	}
	
	tmp=(pCKCU->GCCR & (~(3)) ) | 1<<1;
	pCKCU->GCCR  =tmp;
	pCKCU->AHBCCR &=~(1<<11);//disable CKREFEN	
	pCKCU->GCCR &=~(1<<9);//disable PLL		
  while((pCKCU->GCSR & 0x2) != 0x0) ;	
	//pCKCU->PLLCFGR = 0x112B25;//AM8816 ??????,???????
	pCKCU->LPCR |=1<<0;
	pCKCU->GCCR |=1<<10; //CKCU enable LSE
	pCKCU->APBCCR1 |=1<<6;// Enable RTC	
	while(AM_PWRCU->BAKTEST !=0x27);
	AM_RTC->CR |=(1<<3|1<<1); //RTC enable LSE , LSE is selected as the clock input of RTC
	while((pCKCU->GCSR &1<<4)==0);//LSE not ready	
	pCKCU->GCFGR &= ~(1<<8);
	pCKCU->GCCR |=1<<9;//enable PLL	
  while((pCKCU->GCSR & 0x2) != 0x2) ;
	pCKCU->GCCR &=~(3<<0); 	
}

/*********************************************************************************************************//**
 * @brief This function is used to Convert HSI to HSE.
 * @Note  You must set NMI_Handler and CKRDY_IRQHandler which in 'exception.c'.
 * @param None
 * @retval None
 ************************************************************************************************************/
void Convert_HSI_to_HSE(void)
{
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
	
	pCKCU->APBCCR1 |= (1<<6);// Enable RTC	
	pCKCU->LPCR |= (1<<0);  //bk_iso 
	while(AM_PWRCU->BAKTEST !=0X27);
	
	pCKCU->GCIR = ((pCKCU->GCIR)&(0xffff0000))|(1<<5)|(1<<2)|(1<<0);  //clear lse ready ,pll ready, stuck interrupt pending	
	pCKCU->GCIR = ((pCKCU->GCIR)&(0xffff0000))|(1<<21)|(1<<18);		//enable lse ready interrupt, enable pll ready interrupt
	NVIC_EnableIRQ(CKRDY_IRQn); //允许NVIC中断
	pCKCU->GCIR = ((pCKCU->GCIR)&(0xffff0000))|(1<<0);			//clear lse error interrupt pending
	
	AM_RTC->CR |= (1<<3); 		//允许LSE，等待LSE Ready中断
}

/*********************************************************************************************************//**
 * @brief This function is used to set NMI_Handler in 'exception.c' when you are using 'Convert_HSI_to_HSE' function.
 * @param None
 * @retval None
 ************************************************************************************************************/
void NMI_Handler_IRQ(void)
{
	AM_CKCU_TypeDef * pCKCU= AM_CKCU; 
	if( (pCKCU->GCIR & (1<<0)) != 0 )
	{
		pCKCU->GCIR = ((pCKCU->GCIR)&(0xffff0000))|(1<<0);			//clear lse error interrupt pending
	}
}

/*********************************************************************************************************//**
 * @brief This function is used to set CKRDY_IRQHandler in 'exception.c' when you are using 'Convert_HSI_to_HSE' function.
 * @param None
 * @retval None
 ************************************************************************************************************/
void CKRDY_IRQHandler_IRQ(void)
{
	if( (AM_CKCU->GCIR & (1<<2)) != 0 )	//pll ready
	{
		AM_CKCU->GCCR = (AM_CKCU->GCCR & (~(3<<0)))|(0<<1);			//ahb from ck_sys		
		AM_CKCU->GCIR = ((AM_CKCU->GCIR)&(0xffff0000))|(1<<2);  //clear pll ready interrupt pending
		AM_CKCU->GCIR = ((AM_CKCU->GCIR)&(0xffff0000))|(1<<21);  //lse interrupt enable
	}
	else if( (AM_CKCU->GCIR & (1<<5)) != 0 ) //lse ready
	{
		AM_RTC->CR |= (1<<1);																		//rtc clock & pll from lse
		AM_CKCU->GCFGR = (AM_CKCU->GCFGR & (~(1<<8)))|(1<<3);		//ck_sys & wdog from lse
		AM_CKCU->CKCU_LCD = AM_CKCU->CKCU_LCD |(1<<8);					//lcd from lse
		AM_CKCU->GCIR = ((AM_CKCU->GCIR)&(0xffff0000))|(1<<0);	//clear lse error interrupt pending
		AM_CKCU->GCCR = AM_CKCU->GCCR|(1<<16);									//enable lse error monitor
		AM_CKCU->GCIR = AM_CKCU->GCIR|(1<<16);									//enable lse error monitor irq
		AM_CKCU->GCIR = ((AM_CKCU->GCIR)&(0xffff0000))|(1<<5);  //clear lse ready interrupt pending
	}
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
