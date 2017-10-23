/********************************************************************************************************//**
 * @file    bsp_spi.c
 * @brief   SPI Driver
 * @author  Amicro
 * @version V1.00
 * @date:   2017-4-09
 * @note		W25Q16��д����
 * @Pin
 ***********************************************
 *SPIx | MISO | MOSI | CLK | SS  | AFx *
 ***********************************************
 *SPI0 | PC12 | PC13 | PD2 | PD0 | AF3 *->SPI0_2
 *SPI0 | PD6  | PD7  | PD5 | PD4 | AF3 *->SPI0_3�� MASTER
 ***********************************************
 *SPI1 |      | PA7  | PA8 |     | AF3 *->SPI1_1
 ***********************************************
 * PD6 -> Flash_MISO | PD7 -> Flash_MOSI | PD5 -> Flash_CLK | PD4 -> Flash_SS 
 ****************************************************************************
 * Copyright (C) 2017 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
#include "bsp_spi.h" 

void SPI0_Init(void)
{
SPI_InitTypeDef SPI_InitStructure;
	
	SPI_DeInit(FLASH_SPI);
	
	GPIO_PullResistorConfig(AM_GPIOD,AFIO_PIN_4,GPIO_PR_UP); //��������Ϊ����ģʽ
	
AFIO_GPDConfig(AFIO_PIN_6 ,AFIO_MODE_3);  //SPI0
AFIO_GPDConfig(AFIO_PIN_7 ,AFIO_MODE_3);  //PASS
//AFIO_GPDConfig(AFIO_PIN_4 ,AFIO_MODE_3);
AFIO_GPDConfig(AFIO_PIN_5 ,AFIO_MODE_3);
	
//AFIO_GPCConfig(AFIO_PIN_8 ,AFIO_MODE_3);  //SPI0
//AFIO_GPCConfig(AFIO_PIN_9 ,AFIO_MODE_3);  //PASS
//AFIO_GPCConfig(AFIO_PIN_10,AFIO_MODE_3);
//AFIO_GPCConfig(AFIO_PIN_11,AFIO_MODE_3);
	
//AFIO_GPCConfig(AFIO_PIN_12,AFIO_MODE_3);  //SPI0
//AFIO_GPCConfig(AFIO_PIN_13,AFIO_MODE_3);  //PASS
//AFIO_GPDConfig(AFIO_PIN_2 ,AFIO_MODE_3);
//AFIO_GPDConfig(AFIO_PIN_0 ,AFIO_MODE_3);
	
//AFIO_GPAConfig(AFIO_PIN_6 ,AFIO_MODE_3);  //SPI1
//AFIO_GPAConfig(AFIO_PIN_7 ,AFIO_MODE_3);  //PASS
//AFIO_GPAConfig(AFIO_PIN_8 ,AFIO_MODE_3);
//AFIO_GPAConfig(AFIO_PIN_9 ,AFIO_MODE_3);
	
//	AFIO_GPCConfig(AFIO_PIN_4 ,AFIO_MODE_3);  //SPI1
//	AFIO_GPCConfig(AFIO_PIN_5 ,AFIO_MODE_3);	//Failure
//	AFIO_GPCConfig(AFIO_PIN_6 ,AFIO_MODE_3);
//	AFIO_GPCConfig(AFIO_PIN_7 ,AFIO_MODE_3);
	
//AFIO_GPDConfig(AFIO_PIN_10,AFIO_MODE_3);  //SPI1
//AFIO_GPDConfig(AFIO_PIN_11,AFIO_MODE_3);  //PASS
//AFIO_GPDConfig(AFIO_PIN_12,AFIO_MODE_3);
//AFIO_GPDConfig(AFIO_PIN_13,AFIO_MODE_3);
	
	SPI_StructInit(&SPI_InitStructure);
	SPI_InitStructure.SPI_ClockPrescaler = 2;
	SPI_InitStructure.SPI_DataLength = SPI_DATALENGTH_8;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_FIRST;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_LOW;              //���е�ƽ����Ϊ��
	SPI_InitStructure.SPI_FIFO = SPI_FIFO_DISABLE;
	SPI_InitStructure.SPI_FirstBit = SPI_FIRSTBIT_MSB;
	SPI_InitStructure.SPI_Mode = SPI_MASTER;
	SPI_InitStructure.SPI_SELMode = SPI_SEL_SOFTWARE;
	SPI_InitStructure.SPI_SELPolarity = SPI_SELPOLARITY_LOW;
//SPI_InitStructure.SPI_RxFIFOTriggerLevel = 8;
//SPI_InitStructure.SPI_TxFIFOTriggerLevel = 7;
	SPI_Init(FLASH_SPI,&SPI_InitStructure);
//	
	SPI_SELOutputCmd(FLASH_SPI,ENABLE);
	SPI_SoftwareSELCmd(FLASH_SPI,SPI_SEL_INACTIVE);
	SPI_Cmd(FLASH_SPI,ENABLE);
	SPI_IntConfig(FLASH_SPI,SPI_INT_TXE,ENABLE);
	SPI_IntConfig(FLASH_SPI,SPI_INT_RXBNE,ENABLE);
	SPI_FLASH_CS_HIGH();
}

uint8_t SPI_RW_Byte(uint8_t byte)
{
	/* �ȴ����ͻ�����Ϊ�գ�TXE�¼� */
  while (SPI_GetFlagStatus(FLASH_SPI, SPI_INT_TXE) == RESET){}

  /* д�����ݼĴ�������Ҫд�������д�뷢�ͻ����� */
  SPI_SendData(FLASH_SPI, byte);

  /* �ȴ����ջ������ǿգ�RXNE�¼� */
  while (SPI_GetFlagStatus(FLASH_SPI, SPI_INT_RXBNE) == RESET){}

  /* ��ȡ���ݼĴ�������ȡ���ջ��������� */
  return SPI_ReceiveData(FLASH_SPI);
}

uint8_t SPI_FLASH_ReadByte(void)
{
	return (SPI_RW_Byte(Dummy_Byte));
}

 /**
  * @brief  ��FLASH���� дʹ�� ����
  * @param  none
  * @retval none
  */
void SPI_FLASH_WriteEnable(void)
{
  /* ͨѶ��ʼ��CS�� */
  SPI_FLASH_CS_LOW();

  /* ����дʹ������*/
  SPI_RW_Byte(W25X_WriteEnable);

  /*ͨѶ������CS�� */
  SPI_FLASH_CS_HIGH();
}

 /**
  * @brief  �ȴ�WIP(BUSY)��־����0�����ȴ���FLASH�ڲ�����д�����
  * @param  none
  * @retval none
  */
void SPI_FLASH_WaitForWriteEnd(void)
{
  u8 FLASH_Status = 0;

  /* ѡ�� FLASH: CS �� */
  SPI_FLASH_CS_LOW();

  /* ���� ��״̬�Ĵ��� ���� */
  SPI_RW_Byte(W25X_ReadStatusReg);
	
  /* ��FLASHæµ����ȴ� */
  do
  {
    /* ��ȡFLASHоƬ��״̬�Ĵ��� */
    FLASH_Status = SPI_RW_Byte(Dummy_Byte);
  }
  while ((FLASH_Status & WIP_Flag) == SET); /* ����д���־ */

  /* ֹͣ�ź�  FLASH: CS �� */
  SPI_FLASH_CS_HIGH();
}


//�������ģʽ
void SPI_Flash_PowerDown(void)   
{ 
  /* ѡ�� FLASH: CS �� */
  SPI_FLASH_CS_LOW();

  /* ���� ���� ���� */
  SPI_RW_Byte(W25X_PowerDown);

  /* ֹͣ�ź�  FLASH: CS �� */
  SPI_FLASH_CS_HIGH();
}   

//����
void SPI_Flash_WAKEUP(void)   
{
  /*ѡ�� FLASH: CS �� */
  SPI_FLASH_CS_LOW();

  /* ���� �ϵ� ���� */
  SPI_RW_Byte(W25X_ReleasePowerDown);

  /* ֹͣ�ź� FLASH: CS �� */
  SPI_FLASH_CS_HIGH();                   //�ȴ�TRES1
}

 /**
  * @brief  ����FLASH����
  * @param  SectorAddr��Ҫ������������ַ
  * @retval ��
  */
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();
  SPI_FLASH_WaitForWriteEnd();
  /* �������� */
  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();
  /* ������������ָ��*/
  SPI_RW_Byte(W25X_SectorErase);
  /*���Ͳ���������ַ�ĸ�λ*/
  SPI_RW_Byte((SectorAddr & 0xFF0000) >> 16);
  /* ���Ͳ���������ַ����λ */
  SPI_RW_Byte((SectorAddr & 0xFF00) >> 8);
  /* ���Ͳ���������ַ�ĵ�λ */
  SPI_RW_Byte(SectorAddr & 0xFF);
  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();
  /* �ȴ��������*/
  SPI_FLASH_WaitForWriteEnd();
}


 /**
  * @brief  ����FLASH��������Ƭ����
  * @param  ��
  * @retval ��
  */
void SPI_FLASH_BulkErase(void)
{
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();

  /* ���� Erase */
  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();
  /* �����������ָ��*/
  SPI_RW_Byte(W25X_ChipErase);
  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();

  /* �ȴ��������*/
  SPI_FLASH_WaitForWriteEnd();
}



 /**
  * @brief  ��FLASH��ҳд�����ݣ����ñ�����д������ǰ��Ҫ�Ȳ�������
  * @param	pBuffer��Ҫд�����ݵ�ָ��
  * @param WriteAddr��д���ַ
  * @param  NumByteToWrite��д�����ݳ��ȣ�����С�ڵ���SPI_FLASH_PerWritePageSize
  * @retval ��
  */
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  /* ����FLASHдʹ������ */
  SPI_FLASH_WriteEnable();

  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();
  /* дҳдָ��*/
  SPI_RW_Byte(W25X_PageProgram);
  /*����д��ַ�ĸ�λ*/
  SPI_RW_Byte((WriteAddr & 0xFF0000) >> 16);
  /*����д��ַ����λ*/
  SPI_RW_Byte((WriteAddr & 0xFF00) >> 8);
  /*����д��ַ�ĵ�λ*/
  SPI_RW_Byte(WriteAddr & 0xFF);

  if(NumByteToWrite > SPI_FLASH_PerWritePageSize)
  {
     NumByteToWrite = SPI_FLASH_PerWritePageSize;
		 #if defined (FLASH_DEBUG)
     printf("SPI_FLASH_PageWrite too large!");
		#endif
  }

  /* д������*/
  while (NumByteToWrite--)
  {
    /* ���͵�ǰҪд����ֽ����� */
    SPI_RW_Byte(*pBuffer);
    /* ָ����һ�ֽ����� */
    pBuffer++;
  }

  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();

  /* �ȴ�д�����*/
  SPI_FLASH_WaitForWriteEnd();
}


 /**
  * @brief  ��FLASHд�����ݣ����ñ�����д������ǰ��Ҫ�Ȳ�������
  * @param	pBuffer��Ҫд�����ݵ�ָ��
  * @param  WriteAddr��д���ַ
  * @param  NumByteToWrite��д�����ݳ���
  * @retval ��
  */
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
	
	/*mod�������࣬��writeAddr��SPI_FLASH_PageSize��������������AddrֵΪ0*/
  Addr = WriteAddr % SPI_FLASH_PageSize;
	
	/*��count������ֵ���պÿ��Զ��뵽ҳ��ַ*/
  count = SPI_FLASH_PageSize - Addr;	
	/*�����Ҫд��������ҳ*/
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
	/*mod�������࣬�����ʣ�಻��һҳ���ֽ���*/
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

	 /* Addr=0,��WriteAddr �պð�ҳ���� aligned  */
  if (Addr == 0) 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
			/*�Ȱ�����ҳ��д��*/
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			
			/*���ж���Ĳ���һҳ�����ݣ�����д��*/
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
	/* ����ַ�� SPI_FLASH_PageSize ������  */
  else 
  {
		/* NumByteToWrite < SPI_FLASH_PageSize */
    if (NumOfPage == 0) 
    {
			/*��ǰҳʣ���count��λ�ñ�NumOfSingleС��д����*/
      if (NumOfSingle > count) 
      {
        temp = NumOfSingle - count;
				
				/*��д����ǰҳ*/
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;
				
				/*��дʣ�������*/
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else /*��ǰҳʣ���count��λ����д��NumOfSingle������*/
      {				
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
			/*��ַ����������count�ֿ������������������*/
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;
			
			/*������ҳ��д��*/
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
			/*���ж���Ĳ���һҳ�����ݣ�����д��*/
      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

 /**
  * @brief  ��ȡFLASH����
  * @param 	pBuffer���洢�������ݵ�ָ��
  * @param   ReadAddr����ȡ��ַ
  * @param   NumByteToRead����ȡ���ݳ���
  * @retval ��
  */
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  /* ѡ��FLASH: CS�͵�ƽ */
  SPI_FLASH_CS_LOW();

  /* ���� �� ָ�� */
  SPI_RW_Byte(W25X_ReadData);

  /* ���� �� ��ַ��λ */
  SPI_RW_Byte((ReadAddr & 0xFF0000) >> 16);
  /* ���� �� ��ַ��λ */
  SPI_RW_Byte((ReadAddr& 0xFF00) >> 8);
  /* ���� �� ��ַ��λ */
  SPI_RW_Byte(ReadAddr & 0xFF);
  
	/* ��ȡ���� */
  while (NumByteToRead--)
  {
    /* ��ȡһ���ֽ�*/
    *pBuffer = SPI_RW_Byte(Dummy_Byte);
    /* ָ����һ���ֽڻ����� */
    pBuffer++;
  }

  /* ֹͣ�ź� FLASH: CS �ߵ�ƽ */
  SPI_FLASH_CS_HIGH();
}


 /**
  * @brief  ��ȡFLASH ID
  * @param 	��
  * @retval FLASH ID
  */
uint32_t SPI_FLASH_ReadID(void)
{
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

  /* ��ʼͨѶ��CS�͵�ƽ */
  SPI_FLASH_CS_LOW();

  /* ����JEDECָ���ȡID */
  SPI_RW_Byte(W25X_JedecDeviceID);

  /* ��ȡһ���ֽ����� */
  Temp0 = SPI_RW_Byte(Dummy_Byte);

  /* ��ȡһ���ֽ����� */
  Temp1 = SPI_RW_Byte(Dummy_Byte);

  /* ��ȡһ���ֽ����� */
  Temp2 = SPI_RW_Byte(Dummy_Byte);

  /* ֹͣͨѶ��CS�ߵ�ƽ */
  SPI_FLASH_CS_HIGH();

	/*�����������������Ϊ�����ķ���ֵ*/
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}

 /**
  * @brief  ��ȡFLASH Device ID
  * @param 	��
  * @retval FLASH Device ID
  */
uint32_t SPI_FLASH_ReadDeviceID(void)
{
  uint32_t Temp = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
  SPI_RW_Byte(W25X_DeviceID);
  SPI_RW_Byte(Dummy_Byte);
  SPI_RW_Byte(Dummy_Byte);
  SPI_RW_Byte(Dummy_Byte);
  
  /* Read a byte from the FLASH */
  Temp = SPI_RW_Byte(Dummy_Byte);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  return Temp;
}
/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_RW_Byte(W25X_ReadData);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  SPI_RW_Byte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte */
  SPI_RW_Byte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte */
  SPI_RW_Byte(ReadAddr & 0xFF);
}
