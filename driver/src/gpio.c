/********************************************************************************************************//**
 * @file    gpio.c	
 * @brief   The c file of the Gpio Unit firmware functions.
 * @author  
 * @version V1.00
 * @date:   2016-12-30
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/


#include "gpio.h"
#include "rstcu.h"

/*********************************************************************************************************//**
 * @brief Deinitializes the GPIOx peripheral registers to their default reset values.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @retval None
 ************************************************************************************************************/
void GPIO_DeInit(AM_GPIO_TypeDef* GPIOx)
{
  if(GPIOx == AM_GPIOA)
  {
    RSTCU_AHBPeripReset(RSTCU_AHBRST_PA, ENABLE);
  }
  else if(GPIOx == AM_GPIOB)
  {
    RSTCU_AHBPeripReset(RSTCU_AHBRST_PB, ENABLE);
  }
  else if(GPIOx == AM_GPIOC)
  {
    RSTCU_AHBPeripReset(RSTCU_AHBRST_PC, ENABLE);
  }
  else if(GPIOx == AM_GPIOD)
  {
    RSTCU_AHBPeripReset(RSTCU_AHBRST_PD, ENABLE);
  }
  else
  {
    RSTCU_AHBPeripReset(RSTCU_AHBRST_PE, ENABLE);
  }
}

/*********************************************************************************************************//**
 * @brief Configure the direction of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Direction: This parameter can be one of below:
 *        @arg GPIO_DIR_IN  : The pins are input mode.
 *        @arg GPIO_DIR_OUT : The pins are output mode.
 * @retval None
 ************************************************************************************************************/
void GPIO_DirectionConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DIR_Enum Direction)
{
  if(Direction != GPIO_DIR_IN)
    GPIOx->DIRCR |= GPIO_PIN ;
  else
    GPIOx->DIRCR &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Configure the pull resistor of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param PR: Selection of Pull resistor. This parameter can be one of below:
 *        @arg GPIO_PR_UP      : The pins with internal pull-up resistor
 *        @arg GPIO_PR_DOWN    : The pins with internal pull-down resistor
 *        @arg GPIO_PR_DISABLE : The pins without pull resistor
 * @retval None
 ************************************************************************************************************/
void GPIO_PullResistorConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_PR_Enum PR)
{
  if(PR == GPIO_PR_UP)
  {
    GPIOx->PUR |= GPIO_PIN ;
    GPIOx->PDR &= ~GPIO_PIN ;
  }
  else if(PR == GPIO_PR_DOWN)
  {
    GPIOx->PDR |= GPIO_PIN ;
    GPIOx->PUR &= ~GPIO_PIN ;
  }
  else
  {
    GPIOx->PUR &= ~GPIO_PIN ;
    GPIOx->PDR &= ~GPIO_PIN ;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the input control of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPIO_InputConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd)
{
  if(Cmd != DISABLE)
    GPIOx->INER |= GPIO_PIN ;
  else
    GPIOx->INER &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Select the driving current of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Drive: This parameter can be one of below:
 *        @arg GPIO_DV_3MA  : Selects output driving current as 3 mA
 *        @arg GPIO_DV_6MA  : Selects output driving current as 6 mA
 * @retval None
 ************************************************************************************************************/
void GPIO_DriveConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, GPIO_DV_Enum Drive)
{
  if(Drive != GPIO_DV_3MA)
    GPIOx->DRVR |= GPIO_PIN ;
  else
    GPIOx->DRVR &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable the open drain function of specified GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: The port pins.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Cmd: This parameter can be ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void GPIO_OpenDrainConfig(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, ControlStatus Cmd)
{
  if(Cmd != DISABLE)
    GPIOx->ODR |= GPIO_PIN ;
  else
    GPIOx->ODR &= ~GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Get the input data of specified port pin.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: This parameter can be GPIO_PIN_x where x can be 0 ~ 15.
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus GPIO_ReadInBit(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  if ((GPIOx->DINR & GPIO_PIN) != RESET)
    return SET;
  else
    return RESET;
}

/*********************************************************************************************************//**
 * @brief Get the input data of specified GPIO port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @return The value of input data register.
 ************************************************************************************************************/
u16 GPIO_ReadInData(AM_GPIO_TypeDef* GPIOx)
{
  return ((u16)GPIOx->DINR);
}

/*********************************************************************************************************//**
 * @brief Get the output data of specified port pin.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: This parameter can be GPIO_PIN_x where x can be 0 ~ 15.
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus GPIO_ReadOutBit(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  if ((GPIOx->DOUTR & GPIO_PIN) != RESET)
    return SET;
  else
    return RESET;
}

/*********************************************************************************************************//**
 * @brief Get the output data of specified GPIO port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @return The value of output data register.
 ************************************************************************************************************/
u16 GPIO_ReadOutData(AM_GPIO_TypeDef* GPIOx)
{
  return ((u16)GPIOx->DOUTR);
}

/*********************************************************************************************************//**
 * @brief Set the selected port bits of output data.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: Specify the port bit to be set.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @retval None
 ************************************************************************************************************/
void GPIO_SetOutBits(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  GPIOx->SRR = GPIO_PIN;
}

/*********************************************************************************************************//**
 * @brief Clear the selected port bits of output data.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: Specify the port bit to be clear.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @retval None
 ************************************************************************************************************/
void GPIO_ClearOutBits(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  GPIOx->RR = GPIO_PIN;
}

/*********************************************************************************************************//**
 * @brief Set or Clear the selected port bits of data.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: Specify the port bits.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @param Status: Specify the value to be put to the selected bits.
 *        This parameter can be one of below:
 *        @arg RESET : To clear the port pins
 *        @arg SET   : To set the port pins
 * @retval None
 ************************************************************************************************************/
void GPIO_WriteOutBits(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN, FlagStatus Status)
{
  if (Status != RESET)
    GPIOx->SRR = GPIO_PIN;
  else
    GPIOx->RR = GPIO_PIN;
}

/*********************************************************************************************************//**
 * @brief Put data to the specified GPIO data port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param Data: Specify the data to be written to the port data register.
 * @retval None
 ************************************************************************************************************/
void GPIO_WriteOutData(AM_GPIO_TypeDef* GPIOx, u16 Data)
{
  GPIOx->DOUTR = Data;
}

/*********************************************************************************************************//**
 * @brief Select the GPIO pin to be used as EXTI channel.
 * @param Channel: Specify the EXTI channel to be configured.
 *        This parameter can be AFIO_EXTI_CH_x where x can be 0 ~ 15.
 * @param Source: Specify the GPIO port to be used for EXTI channel.
 *        This parameter can be AFIO_ESS_Px where x can be A ~ E.
 * @retval None
 ************************************************************************************************************/
void AFIO_EXTISourceConfig(AFIO_EXTI_CH_Enum Channel, AFIO_ESS_Enum Source)
{
  u8 index = 0 ;
  u32 tmp = 0 ;

  if(Channel > AFIO_EXTI_CH_7)
  {
    index = 1 ;
    Channel -= AFIO_EXTI_CH_8 ;
  }

  tmp = AM_AFIO->ESSR[index] ;
  tmp &= ~((u32)0x0F << Channel) ;
  tmp |= (u32)Source << Channel ;
  AM_AFIO->ESSR[index] = tmp ;

}

/*********************************************************************************************************//**
 * @brief Lock configuration of GPIO pins.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: Specify the port bits.
 *        This parameter can be any combination of GPIO_PIN_x where x can be 0 ~ 15.
 * @retval None
 ************************************************************************************************************/
void GPIO_PinLock(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  GPIOx->LOCKR = (u32)0x5FA00000 | GPIO_PIN ;
}

/*********************************************************************************************************//**
 * @brief Get the lock state of specified GPIO port.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @return TRUE or FALSE
 ************************************************************************************************************/
bool GPIO_IsPortLocked(AM_GPIO_TypeDef* GPIOx)
{
  if((GPIOx->LOCKR >> 16) == 0)
    return FALSE ;
  else
    return TRUE ;
}

/*********************************************************************************************************//**
 * @brief Get the lock state of specified GPIO port pin.
 * @param GPIOx: where GPIOx is the selected GPIO from the GPIO peripheral, x can be A ~ E.
 * @param GPIO_PIN: This parameter can be GPIO_PIN_x where x can be 0 ~ 15.
 * @return TRUE or FALSE
 ************************************************************************************************************/
bool GPIO_IsPinLocked(AM_GPIO_TypeDef* GPIOx, u16 GPIO_PIN)
{
  if((GPIOx->LOCKR & GPIO_PIN) == 0)
    return FALSE ;
  else
    return TRUE ;
}

/*********************************************************************************************************//**
 * @brief Deinitialize the AFIO peripheral registers to their default reset values.
 * @retval None
 ************************************************************************************************************/
void AFIO_DeInit(void)
{
  RSTCU_APBPerip0Reset(RSTCU_APBRST0_AFIO, ENABLE);
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOA with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
          @arg AFIO_MODE_4       : Alternated mode 4
          @arg AFIO_MODE_5       : Alternated mode 5
          @arg AFIO_MODE_6       : Alternated mode 6
          @arg AFIO_MODE_7       : Alternated mode 7
          @arg AFIO_MODE_8       : Alternated mode 8
          @arg AFIO_MODE_9       : Alternated mode 9
          @arg AFIO_MODE_10      : Alternated mode 10
          @arg AFIO_MODE_11      : Alternated mode 11
          @arg AFIO_MODE_12      : Alternated mode 12
          @arg AFIO_MODE_13      : Alternated mode 13
          @arg AFIO_MODE_14      : Alternated mode 14
          @arg AFIO_MODE_15      : Alternated mode 15
 * @retval None
 ************************************************************************************************************/
void AFIO_GPAConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE)
{
  u8 index = 0;
  u32 Mask = 0, PinMode = 0;

  if(AFIO_PIN & 0x00FF)
  {
    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0001)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPACFGR[0] =(AM_AFIO->GPACFGR[0] & ~Mask) | PinMode;
  }

  if(AFIO_PIN & 0xFF00)
  {
    Mask = 0;
    PinMode = 0;

    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0100)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPACFGR[1] =(AM_AFIO->GPACFGR[1] & ~Mask) | PinMode;
  }
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOB with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
          @arg AFIO_MODE_4       : Alternated mode 4
          @arg AFIO_MODE_5       : Alternated mode 5
          @arg AFIO_MODE_6       : Alternated mode 6
          @arg AFIO_MODE_7       : Alternated mode 7
          @arg AFIO_MODE_8       : Alternated mode 8
          @arg AFIO_MODE_9       : Alternated mode 9
          @arg AFIO_MODE_10      : Alternated mode 10
          @arg AFIO_MODE_11      : Alternated mode 11
          @arg AFIO_MODE_12      : Alternated mode 12
          @arg AFIO_MODE_13      : Alternated mode 13
          @arg AFIO_MODE_14      : Alternated mode 14
          @arg AFIO_MODE_15      : Alternated mode 15
 * @retval None
 ************************************************************************************************************/
void AFIO_GPBConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE)
{
  u8 index = 0;
  u32 Mask = 0, PinMode = 0;

  if(AFIO_PIN & 0x00FF)
  {
    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0001)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPBCFGR[0] =(AM_AFIO->GPBCFGR[0] & ~Mask) | PinMode;
  }

  if(AFIO_PIN & 0xFF00)
  {
    Mask = 0;
    PinMode = 0;

    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0100)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPBCFGR[1] =(AM_AFIO->GPBCFGR[1] & ~Mask) | PinMode;
  }
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOC with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
          @arg AFIO_MODE_4       : Alternated mode 4
          @arg AFIO_MODE_5       : Alternated mode 5
          @arg AFIO_MODE_6       : Alternated mode 6
          @arg AFIO_MODE_7       : Alternated mode 7
          @arg AFIO_MODE_8       : Alternated mode 8
          @arg AFIO_MODE_9       : Alternated mode 9
          @arg AFIO_MODE_10      : Alternated mode 10
          @arg AFIO_MODE_11      : Alternated mode 11
          @arg AFIO_MODE_12      : Alternated mode 12
          @arg AFIO_MODE_13      : Alternated mode 13
          @arg AFIO_MODE_14      : Alternated mode 14
          @arg AFIO_MODE_15      : Alternated mode 15
 * @retval None
 ************************************************************************************************************/
void AFIO_GPCConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE)
{
  u8 index = 0;
  u32 Mask = 0, PinMode = 0;

  if(AFIO_PIN & 0x00FF)
  {
    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0001)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPCCFGR[0] =(AM_AFIO->GPCCFGR[0] & ~Mask) | PinMode;
  }

  if(AFIO_PIN & 0xFF00)
  {
    Mask = 0;
    PinMode = 0;

    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0100)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPCCFGR[1] =(AM_AFIO->GPCCFGR[1] & ~Mask) | PinMode;
  }
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOD with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
          @arg AFIO_MODE_4       : Alternated mode 4
          @arg AFIO_MODE_5       : Alternated mode 5
          @arg AFIO_MODE_6       : Alternated mode 6
          @arg AFIO_MODE_7       : Alternated mode 7
          @arg AFIO_MODE_8       : Alternated mode 8
          @arg AFIO_MODE_9       : Alternated mode 9
          @arg AFIO_MODE_10      : Alternated mode 10
          @arg AFIO_MODE_11      : Alternated mode 11
          @arg AFIO_MODE_12      : Alternated mode 12
          @arg AFIO_MODE_13      : Alternated mode 13
          @arg AFIO_MODE_14      : Alternated mode 14
          @arg AFIO_MODE_15      : Alternated mode 15
 * @retval None
 ************************************************************************************************************/
void AFIO_GPDConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE)
{
  u8 index = 0;
  u32 Mask = 0, PinMode = 0;

  if(AFIO_PIN & 0x00FF)
  {
    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0001)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPDCFGR[0] =(AM_AFIO->GPDCFGR[0] & ~Mask) | PinMode;
  }

  if(AFIO_PIN & 0xFF00)
  {
    Mask = 0;
    PinMode = 0;

    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0100)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPDCFGR[1] =(AM_AFIO->GPDCFGR[1] & ~Mask) | PinMode;
  }
}

/*********************************************************************************************************//**
 * @brief Configure alternated mode of GPIOE with specified pins.
 * @param AFIO_PIN: This parameter can be any combination of AFIO_PIN_x where x can be 0 ~ 15.
 * @param AFIO_MODE: This parameter can be one of the following values:
          @arg AFIO_MODE_DEFAULT : The default I/O function
          @arg AFIO_MODE_1       : Alternated mode 1
          @arg AFIO_MODE_2       : Alternated mode 2
          @arg AFIO_MODE_3       : Alternated mode 3
          @arg AFIO_MODE_4       : Alternated mode 4
          @arg AFIO_MODE_5       : Alternated mode 5
          @arg AFIO_MODE_6       : Alternated mode 6
          @arg AFIO_MODE_7       : Alternated mode 7
          @arg AFIO_MODE_8       : Alternated mode 8
          @arg AFIO_MODE_9       : Alternated mode 9
          @arg AFIO_MODE_10      : Alternated mode 10
          @arg AFIO_MODE_11      : Alternated mode 11
          @arg AFIO_MODE_12      : Alternated mode 12
          @arg AFIO_MODE_13      : Alternated mode 13
          @arg AFIO_MODE_14      : Alternated mode 14
          @arg AFIO_MODE_15      : Alternated mode 15
 * @retval None
 ************************************************************************************************************/
void AFIO_GPEConfig(u32 AFIO_PIN, AFIO_MODE_Enum AFIO_MODE)
{
  u8 index = 0;
  u32 Mask = 0, PinMode = 0;

  if(AFIO_PIN & 0x00FF)
  {
    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0001)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPECFGR[0] =(AM_AFIO->GPECFGR[0] & ~Mask) | PinMode;
  }

  if(AFIO_PIN & 0xFF00)
  {
    Mask = 0;
    PinMode = 0;

    for(index = 0; index < 8; index++)
    {
      if((AFIO_PIN>>index) & 0x0100)
      {
        Mask |= (0xF << (index*4));
        PinMode |= (AFIO_MODE << (index*4));
      }
    }
    AM_AFIO->GPECFGR[1] =(AM_AFIO->GPECFGR[1] & ~Mask) | PinMode;
  }
}

/*********************************************************************************************************//**
 * @brief 
 * @param 
 * @param 
 * @retval None
 ************************************************************************************************************/
FlagStatus exti_clear_edge_flag(AFIO_EXTI_CH_Enum exti_line_x)
{
	AM_EXTI_TypeDef *pAM_EXTI = AM_EXTI;
	uint32_t reg_val;

	pAM_EXTI->EDGEFLGR |= (1<<(exti_line_x>>2));
	reg_val = pAM_EXTI->EDGEFLGR;
	if( (reg_val&(exti_line_x>>2)) == 0)
		return RESET;
	else
	{
		return SET;
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
