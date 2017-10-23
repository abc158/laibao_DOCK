#include "AM8813.h"
#include "main.h"
#include "ckcu.h"
#include "gpio.h"
//#include "flash.h"
//#include "rtc.h"
#include "usart.h"
#include "pdma.h"


extern STATE State[NumMdl];

unsigned short USART_Tx_buffer[40];
unsigned short USART_Rx_buffer[40];
u8 DMA0_RX_complete_flag =0;
u8 RX_NUB=0;
////
unsigned short USART_Tx_buffer_1[40];
unsigned short USART_Rx_buffer_1[40];
u8 DMA2_RX_complete_flag =0;
u8 DMA4_RX_complete_flag =0;
u8 RX_NUB_1=0;


void UART0_int_irq()
{
	int k;
	if (((AM_UART0->IIR) & USART_IID_RDA ) == USART_IID_RDA )
  {
  	AM_UART0->IIR = AM_UART0->IIR;
	 for(k=0;k<8;k++)
	  {
	   	USART_Rx_buffer[RX_NUB]=USART_ReceiveData(AM_UART0);
			RX_NUB++;
	  }		
		if(RX_NUB >= 40)
		{
			RX_NUB = 0;
			USART_DeInit(AM_UART0);
			USART_DeInit(AM_UART1);
			deinit_dma(DMA_CH0);
			State[MdlUart01] = State_StartFinish;
		}
	}
}


void dma0_uart1tx_uart0rx_irq_start(void)
{
	int input,k;
  USART_InitTypeDef USART_InitStructure;

	DMA_InitTypeDef DmaInitStruct;
	DMA0_RX_complete_flag =0;
	
	State[MdlUart01] = State_Continue;
	
/*********************************************************************/		
	AFIO_GPAConfig(AFIO_PIN_13|AFIO_PIN_14,AFIO_MODE_4);
	AFIO_GPDConfig(AFIO_PIN_6|AFIO_PIN_7,AFIO_MODE_4);

  for(k=0;k<40;k++)
	  {
	   USART_Tx_buffer[k] = 34+k;
	  }
  for(k=0;k<40;k++)
	  {
	    USART_Rx_buffer[k] = 0;
	  }	
		
	NVIC_EnableIRQ(UART0_IRQn);	
//NVIC_EnableIRQ(PDMACH3_IRQn);	 
		
/* USART2 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 12000;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART0, &USART_InitStructure);	
	USART_RFITLConfig(AM_UART0, USART_RFITL_08);//??
  //USART_TxCmd(AM_UART0, ENABLE);
  USART_RxCmd(AM_UART0, ENABLE);		
	USART_IntConfig(AM_UART0, USART_IER_RDAIE, ENABLE);
		
		
/* USART3 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 12000;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART1, &USART_InitStructure);
	USART_TFITLConfig(AM_UART1, USART_TFITL_00);
  USART_TxCmd(AM_UART1, ENABLE);
 // USART_RxCmd(AM_UART1, ENABLE);		
	
//RAM->UARTTX:
	deinit_dma(DMA_CH0);
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = LINEAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = CIRCULAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)USART_Tx_buffer;//发送数据
	DmaInitStruct.AddrDest = (uint32_t)&AM_UART1->TBR;;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_HIGH;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x20;//UR1_TX
	init_dma(&DmaInitStruct,DMA_CH0);	
	
  dma_int_enable(TRAN_CPLT_INT,DMA_CH0 );
	DMA_EnaCmd(DMA_CH0,ENABLE);	
	
	
	USART_TxPDMACmd(AM_UART1, ENABLE);	
	
}


FLAG_PASS_FAIL dma0_uart1tx_uart0rx_irq_ok(void)
{
	int k;

	for (k=0;k<40;k++)
		{
			if (USART_Tx_buffer[k] != USART_Rx_buffer[k])
			{
				return FLAG_FAIL;
			}
		}	
		return FLAG_PASS;		
}

////////////////////////////
void UART4_int_irq()
{
	int k;
	if (((AM_UART4->IIR) & USART_IID_RDA ) == USART_IID_RDA )
  {
  	AM_UART4->IIR = AM_UART4->IIR;
	 for(k=0;k<8;k++)
	  {
	   	USART_Rx_buffer_1[RX_NUB_1]=USART_ReceiveData(AM_UART4);
			RX_NUB_1++;
	  }		
		if(RX_NUB_1 >= 40)
		{
			RX_NUB_1 = 0;
			USART_DeInit(AM_UART4);
			USART_DeInit(AM_UART5);
			deinit_dma(DMA_CH2);
			State[MdlUart45] = State_StartFinish;
		}
	}
}


void dma2_uart5tx_uart4rx_irq_start(void)
{
	int input,k;
  USART_InitTypeDef USART_InitStructure;

	DMA_InitTypeDef DmaInitStruct;
	DMA2_RX_complete_flag =0;
	
	State[MdlUart45] = State_Continue;
	
/*********************************************************************/		
	AFIO_GPCConfig(AFIO_PIN_6|AFIO_PIN_7,AFIO_MODE_4);
	AFIO_GPDConfig(AFIO_PIN_3|AFIO_PIN_4,AFIO_MODE_4);

  for(k=0;k<40;k++)
	  {
	   USART_Tx_buffer_1[k] = 34+k;
	  }
  for(k=0;k<40;k++)
	  {
	    USART_Rx_buffer_1[k] = 0;
	  }	
		
	NVIC_EnableIRQ(UART4_IRQn);	
//NVIC_EnableIRQ(PDMACH3_IRQn);	 
		
/* USART2 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 12000;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART4, &USART_InitStructure);	
	USART_RFITLConfig(AM_UART4, USART_RFITL_04);//??
  //USART_TxCmd(AM_UART0, ENABLE);
  USART_RxCmd(AM_UART4, ENABLE);		
	USART_IntConfig(AM_UART4, USART_IER_RDAIE, ENABLE);
		
		
/* USART3 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 12000;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART5, &USART_InitStructure);
	USART_TFITLConfig(AM_UART5, USART_TFITL_00);
  USART_TxCmd(AM_UART5, ENABLE);
 // USART_RxCmd(AM_UART1, ENABLE);		
	
//RAM->UARTTX:
	deinit_dma(DMA_CH2);
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = LINEAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = CIRCULAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)USART_Tx_buffer_1;//发送数据
	DmaInitStruct.AddrDest = (uint32_t)&AM_UART5->TBR;;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_HIGH;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x28;//UR5_TX
	init_dma(&DmaInitStruct,DMA_CH2);	
	
  dma_int_enable(TRAN_CPLT_INT,DMA_CH2 );
	DMA_EnaCmd(DMA_CH2,ENABLE);	
	
	
	USART_TxPDMACmd(AM_UART5, ENABLE);	
	
}


FLAG_PASS_FAIL dma2_uart5tx_uart4rx_irq_ok(void)
{
	int k;

	for (k=0;k<40;k++)
		{
			if (USART_Tx_buffer[k] != USART_Rx_buffer[k])
			{
				return FLAG_FAIL;
			}
		}	
		return FLAG_PASS;		
}

/////////////////////////////////////////////////////////////////
// dma0 -> uart1tx -> uart0rx -> dma2
void uart01_dma2_interrupt_req(void)
{	
	USART_DeInit(AM_UART0);
	USART_DeInit(AM_UART1);
	deinit_dma(DMA_CH0);
	deinit_dma(DMA_CH2);
	State[MdlUart01] = State_StartFinish;
	dma_clear_status(TRAN_CPLT_INT,DMA_CH2);
}

void dma0_uart1tx_uart0rx_dma2_start(void)
{
	int input,k;
  USART_InitTypeDef USART_InitStructure;

	DMA_InitTypeDef DmaInitStruct;
	DMA0_RX_complete_flag =0;
	
	State[MdlUart01] = State_Continue;
	
/*********************************************************************/		
	AFIO_GPAConfig(AFIO_PIN_13|AFIO_PIN_14,AFIO_MODE_4);
	AFIO_GPDConfig(AFIO_PIN_6|AFIO_PIN_7,AFIO_MODE_4);

  for(k=0;k<40;k++)
	  {
	   USART_Tx_buffer[k] = 34+k;
	  }
  for(k=0;k<40;k++)
	  {
	    USART_Rx_buffer[k] = 0;
	  }	
		
//	NVIC_EnableIRQ(UART0_IRQn);	
//NVIC_EnableIRQ(PDMACH3_IRQn);	 
		
/* USART2 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 115200;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART0, &USART_InitStructure);	
	USART_RFITLConfig(AM_UART0, USART_RFITL_04);//??
  //USART_TxCmd(AM_UART0, ENABLE);
	USART_RxPDMACmd(AM_UART0, ENABLE);	
  USART_RxCmd(AM_UART0, ENABLE);		
//	USART_IntConfig(AM_UART0, USART_IER_RDAIE, ENABLE);		
		
/* USART3 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 115200;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART1, &USART_InitStructure);
	USART_TFITLConfig(AM_UART1, USART_TFITL_00);
	USART_TxPDMACmd(AM_UART1, ENABLE);	
  USART_TxCmd(AM_UART1, ENABLE);	
	
//RAM->UARTTX:
	deinit_dma(DMA_CH0);
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = LINEAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = CIRCULAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)USART_Tx_buffer;//发送数据
	DmaInitStruct.AddrDest = (uint32_t)&AM_UART1->TBR;;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_LOW;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x20;//UR1_TX
	init_dma(&DmaInitStruct,DMA_CH0);	
	
  dma_int_enable(TRAN_CPLT_INT,DMA_CH0 );
	DMA_EnaCmd(DMA_CH0,ENABLE);	
		
//UARTRX->RAM:
	deinit_dma(DMA_CH2);
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = CIRCULAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = LINEAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)&AM_UART0->RBR;//接收数据
	DmaInitStruct.AddrDest = (uint32_t)USART_Rx_buffer;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_HIGH;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x1d;//UR0_RX
	init_dma(&DmaInitStruct,DMA_CH2);	
	
  dma_int_enable(TRAN_CPLT_INT,DMA_CH2 );
	dma_int_enable(GLOBAL_INT,DMA_CH2);
	DMA_EnaCmd(DMA_CH2,ENABLE);	
	
	NVIC_EnableIRQ(PDMACH2_IRQn);	
	
}


FLAG_PASS_FAIL dma0_uart1tx_uart0rx_dma2_ok(void)
{
	int k;

	for (k=0;k<40;k++)
		{
			if (USART_Tx_buffer[k] != USART_Rx_buffer[k])
			{
				return FLAG_FAIL;
			}
		}	
		return FLAG_PASS;		
}

/////////////////////////////////////////////////////////////////
// dma3 -> uart5tx -> uart4rx -> dma4
void uart45_dma4_interrupt_req(void)
{	
	USART_DeInit(AM_UART4);
	USART_DeInit(AM_UART5);
	deinit_dma(DMA_CH3);
	deinit_dma(DMA_CH4);
	State[MdlUart45] = State_StartFinish;
	dma_clear_status(TRAN_CPLT_INT,DMA_CH3);
	dma_clear_status(TRAN_CPLT_INT,DMA_CH4);
}

void dma3_uart5tx_uart4rx_dma4_start(void)
{
	int input,k;
  USART_InitTypeDef USART_InitStructure;

	DMA_InitTypeDef DmaInitStruct;
	DMA4_RX_complete_flag =0;
	
	State[MdlUart45] = State_Continue;
	
/*********************************************************************/		
	AFIO_GPDConfig(AFIO_PIN_3|AFIO_PIN_4,AFIO_MODE_4);
	AFIO_GPCConfig(AFIO_PIN_6|AFIO_PIN_7,AFIO_MODE_4);

  for(k=0;k<40;k++)
	  {
	   USART_Tx_buffer_1[k] = 34+k;
	  }
  for(k=0;k<40;k++)
	  {
	    USART_Rx_buffer_1[k] = 0;
	  }	
		
//	NVIC_EnableIRQ(UART0_IRQn);	
//NVIC_EnableIRQ(PDMACH3_IRQn);	 
		
/* USART2 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 96000;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART4, &USART_InitStructure);	
	USART_RFITLConfig(AM_UART4, USART_RFITL_04);//??
  //USART_TxCmd(AM_UART0, ENABLE);
	USART_RxPDMACmd(AM_UART4, ENABLE);	
  USART_RxCmd(AM_UART4, ENABLE);		
//	USART_IntConfig(AM_UART0, USART_IER_RDAIE, ENABLE);		
		
/* USART3 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 96000;//115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART5, &USART_InitStructure);
	USART_TFITLConfig(AM_UART5, USART_TFITL_00);
  USART_TxCmd(AM_UART5, ENABLE);
 // USART_RxCmd(AM_UART1, ENABLE);		
	
//RAM->UARTTX:
	deinit_dma(DMA_CH3);
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = LINEAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = CIRCULAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)USART_Tx_buffer_1;//发送数据
	DmaInitStruct.AddrDest = (uint32_t)&AM_UART5->TBR;;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_LOW;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x28;//UR5_TX
	init_dma(&DmaInitStruct,DMA_CH3);	
	
  dma_int_enable(TRAN_CPLT_INT,DMA_CH3 );
	DMA_EnaCmd(DMA_CH3,ENABLE);	
		
	USART_TxPDMACmd(AM_UART5, ENABLE);	

//UARTRX->RAM:
	deinit_dma(DMA_CH4);
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = CIRCULAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = LINEAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)&AM_UART4->RBR;//接收数据
	DmaInitStruct.AddrDest = (uint32_t)USART_Rx_buffer_1;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_HIGH;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x25;//UR4_RX
	init_dma(&DmaInitStruct,DMA_CH4);	
	
  dma_int_enable(TRAN_CPLT_INT,DMA_CH4 );
	dma_int_enable(GLOBAL_INT,DMA_CH4);
	DMA_EnaCmd(DMA_CH4,ENABLE);	
	
	NVIC_EnableIRQ(PDMACH4_CH5_IRQn);	
	
}


FLAG_PASS_FAIL dma3_uart5tx_uart4rx_dma4_ok(void)
{
	int k;

	for (k=0;k<40;k++)
		{
			if (USART_Tx_buffer_1[k] != USART_Rx_buffer_1[k])
			{
				return FLAG_FAIL;
			}
		}	
		return FLAG_PASS;		
}