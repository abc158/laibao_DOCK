/********************************************************************************************************//**
 * @file    bsp_spi.h	
 * @brief   The header file of the bsp_usart.
 * @author  Amicro
 * @version V1.00
 * @date:   2017-4-07
 * @Pin
 ***********************************************
 *SPIx | MISO | MOSI | CLK | SS  | AFx *
 ***********************************************
 *SPI0 | PC12 | PC13 | PD2 | PD0 | AF3 *->SPI0_2
 *SPI0 | PD6  | PD7  | PD5 | PD4 | AF3 *->SPI0_3√ MASTER
 ***********************************************
 *SPI1 |      | PA7  | PA8 |     | AF3 *->SPI1_1
 ***********************************************
 * PD6 -> Flash_MISO | PD7 -> Flash_MOSI | PD5 -> Flash_CLK | PD4 -> Flash_SS 
 ****************************************************************************
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#ifndef __BSP_SPI_FLASH_H
#define __BSP_SPI_FLASH_H
#include "AM8813.h"
#include "AM8813_misc.h"
#include "gpio.h"
#include "bsp_usart.h"
#include "spi.h"

#define BUFFER_SIZE			256
/* Private typedef -----------------------------------------------------------*/
//#define  sFLASH_ID                     0xEF3015     //W25X16
#define  sFLASH_ID                       0xEF4015	    //W25Q16
//#define  sFLASH_ID                     0XEF4017     //W25Q64
//#define  sFLASH_ID                     0XEF4018     //W25Q128


//#define SPI_FLASH_PageSize            4096
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256

/* Private define ------------------------------------------------------------*/
/*命令定义-开头*******************************/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		    0x05 
#define W25X_WriteStatusReg		  	0x01 
#define W25X_ReadData			        0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	  	0xAB 
#define W25X_DeviceID			        0xAB 
#define W25X_ManufactDeviceID   	0x90 
#define W25X_JedecDeviceID		    0x9F 

#define WIP_Flag                  0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                0xFF
/*命令定义-结尾*******************************/


/*SPI接口定义-开头****************************/
#define FLASH_SPI                           AM_SPI0
//#define SPI_FLASH_CS_LOW()      {SPI_SoftwareSELCmd(FLASH_SPI,SPI_SEL_ACTIVE);}
//#define SPI_FLASH_CS_HIGH()     {SPI_SoftwareSELCmd(FLASH_SPI,SPI_SEL_INACTIVE);}
#define SPI_FLASH_CS_LOW()      {AM_GPIOD->RR = GPIO_PIN_8;}
#define SPI_FLASH_CS_HIGH()     {AM_GPIOD->SRR = GPIO_PIN_8;}

#define SPI_WIRELESS_CE_LOW()      {AM_GPIOD->RR = GPIO_PIN_4;}
#define SPI_WIRELESS_CE_HIGH()     {AM_GPIOD->SRR = GPIO_PIN_4;}
/*SPI接口定义-结尾****************************/

/*信息输出*/
#define FLASH_DEBUG

void SPI0_Init(void);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t SPI_FLASH_ReadID(void);
uint32_t SPI_FLASH_ReadDeviceID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);
uint8_t SPI_FLASH_ReadByte(void);
uint8_t SPI_RW_Byte(uint8_t byte);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);

#endif
