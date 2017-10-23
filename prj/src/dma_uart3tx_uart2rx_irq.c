#include "user.h"
#include "main.h"
#include "AM38x.h"
#include "AM38x_usart.h"
#include "AM38x_pdma.h"
#include "AM38x_ckcu.h"

#define CK_PLL 0
#define CK_AHB  1
#define CK_SYS 2
#define CK_LSE 5
#define CK_LSI 6
#define CK_DEBUG   7

// ADD BY DJF
#define HT_PERIPH_BASE           ((u32)0x40000000)
#define HT_APB0PERIPH_BASE       (HT_PERIPH_BASE)                 /* 0x40000000                             */
#define HT_USART0_BASE           (HT_APB0PERIPH_BASE + 0x0000)    /* 0x40000000                              */
#define HT_USART0              ( (HT_USART_TypeDef *) HT_USART0_BASE)

#define USART_PDMA_IDLE 0
#define USART_PDMA_BUSY 1
#define RX_BUFFER_SIZE  8
u32 RxBufferReadIndex = 0;

#define GetRxBufferReadIndex() RxBufferReadIndex
#define GetRxBufferWriteIndex() (((AM_PDMA->PDMACH2.CADR & 0xFFFF) - ((u32)RxBuffer & 0xFFFF)) % RX_BUFFER_SIZE)

#define IsRxBufferEmpty() (GetRxBufferWriteIndex() == RxBufferReadIndex)
#define IsRxBufferFull() ((((AM_PDMA->PDMACH2.CADR & 0xFFFF) - ((u32)RxBuffer & 0xFFFF)) + 1) % RX_BUFFER_SIZE \
                           == RxBufferReadIndex )
													 
u8 RxBuffer[RX_BUFFER_SIZE];
vu8 USART_PDMA_TxState = USART_PDMA_IDLE;
DMA_InitTypeDef PDMACH_TxStructure;

unsigned short USART_Tx_buffer[40];
unsigned short USART_Rx_buffer[40];


typedef struct 
{
u8 CKOUTSRC;
u8 DB_CKSRC;
u8 DB_CS;			
}	CK_DEBUG_TypeDef;   

void CLK_ENABLE(void)
{
	
	u32 LED_CLK;	
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
  AM_RSTCU_TypeDef * pRSTCU=AM_RSTCU;
	pCKCU->AHBCCR |=0x3FE8F5;// clock gating		
	pCKCU->APBCCR0 |=0x107C513;// clock gating	
	pCKCU->APBCCR1 |=0xFF07077F;// clock gating		
}


void USART_MFP(void)
{
	AM_GPIO_TypeDef * pGPIOB =AM_GPIOB;
	AM_GPIO_TypeDef * pGPIOC =AM_GPIOC;
	AM_GPIO_TypeDef * pGPIOD =AM_GPIOD;
	
	AM_AFIO_TypeDef * pAFIO =AM_AFIO;
	
	pAFIO->GPBCFGR[1] =0x44000000;
	pAFIO->GPDCFGR[0] =0x00440004;
	pAFIO->GPCCFGR[1] =0x44000044;
  pAFIO->GPDCFGR[0] =0x444444;
	pAFIO->GPDCFGR[1] =0x444400;
	
  pAFIO->GPECFGR[0] =0x44444440;
	pAFIO->GPECFGR[1] =0x440004;	
	
  pAFIO->GPFCFGR[0] =0x44440440;
	pAFIO->GPFCFGR[1] =0x440000;	
	
	pAFIO->GPGCFGR[0] =0x4400;
}
	


/*********************************************************************************************************//**
  * @brief  USART send a buffer used PDMA mode.
  * @retval None
  ***********************************************************************************************************/
u32 USART_PDMA_Tx(char *TxBuffer, u32 length)
{
  while (USART_PDMA_TxState != USART_PDMA_IDLE);

  /* USART0 Tx PDMA channel configuration                                                                   */
  PDMACH_TxStructure.AddrSrc = (u32)TxBuffer;
  PDMACH_TxStructure.BlockCnt = length;
  init_dma(&PDMACH_TxStructure,DMA_CH3);
  DMA_EnaCmd(DMA_CH3, ENABLE);
  USART_TxPDMACmd(AM_UART0, ENABLE);
  USART_PDMA_TxState = USART_PDMA_BUSY;

  return 0;
}

/*********************************************************************************************************//**
  * @brief  To read a byte from Rx buffer. This is a blocked function.
  * @retval Rx data
  ***********************************************************************************************************/
u8 RxBufferBlockedRead(void)
{
  u8 retval;
  while (IsRxBufferEmpty());
  retval = RxBuffer[RxBufferReadIndex++];
  RxBufferReadIndex %= RX_BUFFER_SIZE;
  return retval;
}

void dma2_uart3tx_uart2rx_irq_start(void)
{	

	int input,k;
	CK_DEBUG_TypeDef CKOUT;	
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
  USART_InitTypeDef USART_InitStructure;

	DMA_InitTypeDef PDMACH_TxStructure;
  DMA_InitTypeDef PDMACH_RxStructure;
		
	AM_GPIO_TypeDef * pGPIOB =AM_GPIOB;
	AM_GPIO_TypeDef * pGPIOC =AM_GPIOC;
	AM_GPIO_TypeDef * pGPIOD =AM_GPIOD;	
	AM_AFIO_TypeDef * pAFIO =AM_AFIO;	
	
	AM_USART_TypeDef   * pUSART0= AM_UART0;
	AM_USART_TypeDef   * pUSART1= AM_UART1;
	DMA_InitTypeDef DmaInitStruct;
	AM_PDMA_TypeDef *pAM_PDMA = AM_PDMA;
	char  HelloString[8] ={0xff,0x55,0xaa,0x99,0x66,0xdd,0xcc,0x77} ;
	
   for(k=0;k<40;k++)
	  {
	   USART_Tx_buffer[k] = 1234+k;
	  }
	 for(k=0;k<40;k++)
	  {
	    USART_Rx_buffer[k] = 0;
	  }
		
	Set_sys_Frequency(72);
	pCKCU->GCFGR |=1<<4;	//switch flash clock to 8M	
//add your cod here			
  CLK_ENABLE();	
/*//config GPIO_E8,GPIO_E7, as UART2_RX and UART2_TX
  pAFIO->GPECFGR[0] &=~(0xF0000000);
	pAFIO->GPECFGR[0] |=0x40000000;
	pAFIO->GPECFGR[1] &=~(0xF);
	pAFIO->GPECFGR[1] |=0x4;*/
//config GPIO_C15(FMC_LPC_LA12_N),GPIO_C14(FMC_LPC_LA11_P), as UART2_RX and UART2_TX	. by LINLI 151228	
	pAFIO->GPCCFGR[1] &=~(0xF0000000);
	pAFIO->GPCCFGR[1] |=0x40000000;
		
//config GPIO_D5(FMC_LPC_LA15_N),GPIO_C0(FMC_LPC_LA04_P) as UART3_RX and UART3_TX
  pAFIO->GPCCFGR[0] &=~(0xF);
	pAFIO->GPCCFGR[0] |=  0x4;	
  pAFIO->GPDCFGR[0] &=~(0xF00000);
	pAFIO->GPDCFGR[0] |=  0x400000;
	
/*********************************************************************/	
  //pUSART0->DTR =0X3;   //loop back mod
	//pUSART1->DTR =0X3;  //loop back mod
		
/* USART2 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART0, &USART_InitStructure);

	
	USART_RFITLConfig(AM_UART0, USART_RFITL_04);
  USART_TxCmd(AM_UART0, ENABLE);
  USART_RxCmd(AM_UART0, ENABLE);		

/* USART3 configuration    115200  8b  1stop noparity  normal ----------------------------------------------------------------------------------*/
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
  USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
  USART_InitStructure.USART_Parity = USART_PARITY_ODD;
  USART_InitStructure.USART_Mode = USART_MODE_NORMAL;  
	USART_Init (AM_UART1, &USART_InitStructure);
	USART_TFITLConfig(AM_UART1, USART_TFITL_00);
  USART_TxCmd(AM_UART1, ENABLE);
  USART_RxCmd(AM_UART1, ENABLE);		
	
	
	//RAM->UARTTX:
	deinit_dma(DMA_CH3);
	DmaInitStruct.HardTrigSrc = DMA_HARDTRIG_SRC_UR1_TX;
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
	DmaInitStruct.HardTrigSrc=0x2D;//UR1_TX
	init_dma(&DmaInitStruct,DMA_CH3);	
	DMA_EnaCmd(DMA_CH3,ENABLE);
	
	//UARTRX->RAM:
	deinit_dma(DMA_CH2);
	DmaInitStruct.HardTrigSrc = DMA_HARDTRIG_SRC_UR0_RX;
	DmaInitStruct.AutoReload = DISABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_16BIT;
	DmaInitStruct.AddrFix = ENABLE;
  DmaInitStruct.SrcAddrMode = CIRCULAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode =LINEAR ;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)&AM_UART0->RBR;;//接收数据
	DmaInitStruct.AddrDest = (uint32_t)USART_Rx_buffer;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_MIDDLE;
	DmaInitStruct.BlockLength = 4;
	DmaInitStruct.BlockCnt = 10;
	DmaInitStruct.HardTrigSrc=0x2A;//UR0_RX                       
	init_dma(&DmaInitStruct,DMA_CH2);		
	DMA_EnaCmd(DMA_CH2,ENABLE);
  
	pAM_PDMA->IER0 = ENABLE<<(TRAN_CPLT_INT+5*DMA_CH2)|ENABLE<<(TRAN_CPLT_INT+5*DMA_CH3);	
	
	USART_RxPDMACmd(AM_UART0, ENABLE);
	USART_TxPDMACmd(AM_UART1, ENABLE);

	
	
	while (dma_get_status(TRAN_CPLT_INT,DMA_CH3)==FLAG_NOTSET);	
	while (dma_get_status(TRAN_CPLT_INT,DMA_CH2)==FLAG_NOTSET); 
	
	
	for (k=0;k<40;k++)
		{
			if (USART_Rx_buffer[k] != USART_Rx_buffer[k])
			{
				fail();
				while(1);
			}
		}

	if( 1 )
		pass();
	else 
		fail();	
	while(1);
	
}

