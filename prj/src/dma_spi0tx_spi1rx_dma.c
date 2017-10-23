#include "user.h"
#include "main.h"
#include "AM8813.h"
#include "gpio.h"
#include "pdma.h"
#include "spi.h"

extern STATE State[NumMdl];

extern void pass(void);
extern void fail(void);
extern void cpu_delay(unsigned int tns);		
extern void switch_to_pll(void);
extern void Set_sys_Frequency(int Frequency);

unsigned char SPI0_Tx_buffer[256];
//unsigned char SPI1_Tx_buffer[256];
//unsigned char SPI0_Rx_buffer[256];
unsigned char SPI1_Rx_buffer[256];

void Dma_ch7_irq_handle(void)
{
	AM_PDMA_TypeDef *pAM_PDMA = AM_PDMA;
	if( FLAG_SET == dma_get_status(TRAN_CPLT_INT,DMA_CH7) )
	{
		deinit_dma(DMA_CH6);
		deinit_dma(DMA_CH7);
		SPI_DeInit(AM_SPI0);
		SPI_DeInit(AM_SPI1);
		State[MdlSpi] = State_StartFinish;
	}
	dma_clear_status(TRAN_CPLT_INT,DMA_CH6);	
	dma_clear_status(TRAN_CPLT_INT,DMA_CH7);	
}

void CLK_ENABLE(void)
{
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;
  AM_RSTCU_TypeDef * pRSTCU=AM_RSTCU;
	pCKCU->AHBCCR |=0x3FE8F5;               // clock gating		
	pCKCU->APBCCR0 |=0x107C513;             // clock gating	
	pCKCU->APBCCR1 |=0xFF07077F;            // clock gating		
}

void dma6_spi0tx_spi1rx_dma7_start(void)
{   
	AM_CKCU_TypeDef * pCKCU= AM_CKCU;	
	int i;	
	
	State[MdlSpi] = State_Continue;	

//	CLK_ENABLE();
	
//	deinit_dma(DMA_CH6);
	deinit_dma(DMA_CH7);
//	  AM_CKCU->LPCR |= 1;                 //disable isolation cell
	cpu_delay(40);
	
	for(i=0;i<256;i++)
	{
		SPI0_Tx_buffer[i] = i;
	}
		
//	for(i=0;i<256;i++)
//	{
//		SPI1_Tx_buffer[i] = 255-i;
//	}
	
	AFIO_GPDConfig(AFIO_PIN_10|AFIO_PIN_11|AFIO_PIN_12|AFIO_PIN_13,AFIO_MODE_3); //SPI1
	AFIO_GPCConfig(AFIO_PIN_8|AFIO_PIN_9,AFIO_MODE_3); //SPI0
	AFIO_GPDConfig(AFIO_PIN_0|AFIO_PIN_5,AFIO_MODE_3); //SPI0
	
//	AM_PDMACH4->CR |= 0x020581;          //DMACH0, SPI0_Rx, medium priority,Dwidth=8,chen=1
	AM_PDMACH6->CR |= 0x020421;          //DMACH0, SPI0_Tx, Low priority,Dwidth=8,chen=1
//	AM_PDMACH7->CR |= 0x290581;          //DMACH0, SPI1_Rx, medium priority,Dwidth=8,chen=1
	AM_PDMACH7->CR |= 0x290781;          //DMACH0, SPI1_Rx, very high priority,Dwidth=8,chen=1
//	AM_PDMACH7->CR |= 0x050621;          //DMACH0, SPI1_Tx, High priority,Dwidth=8,chen=1
	
//	AM_PDMACH4->DADR = (uint32_t)(SPI0_Rx_buffer);
//	AM_PDMACH4->SADR = 0x40004010;
	AM_PDMACH6->DADR = 0x40004010;
	AM_PDMACH6->SADR = (uint32_t)(SPI0_Tx_buffer);
	AM_PDMACH7->DADR = (uint32_t)(SPI1_Rx_buffer);
	AM_PDMACH7->SADR = 0x40005010;
//	AM_PDMACH7->DADR = 0x40044010;
//	AM_PDMACH7->SADR = (uint32_t)(SPI1_Tx_buffer);
	
//	AM_PDMACH4->TSR = 0x200008;
//	AM_PDMACH6->TSR = 0x200008;
//	AM_PDMACH7->TSR = 0x200008;
	AM_PDMACH6->TSR = 0x400004;
	AM_PDMACH7->TSR = 0x400004;
//	AM_PDMACH7->TSR = 0x200008;

	AM_PDMA->IER1 |= (1<<8)|(1<<5);			 //pdma ch7 cplt int, glob int enable
	NVIC_EnableIRQ(PDMACH6_CH7_IRQn);	
	
	AM_SPI0->CR1 |= 0x6108;              //Master mode, Set SEL as hardware mode, MSB first, SEL is active low, CPOL/CPHA=00, Data Length 8 bits 	
	AM_SPI0->CPR = 23;                    //SPI CLK = 24M/24 = 1M
//	AM_SPI0->FCR |= 0x480;               //enable FIFO,Tx Trigger level=0, Rx Trigger level=8
	AM_SPI0->FCR |= 0x440;               //enable FIFO,Tx Trigger level=0, Rx Trigger level=4
	
//	AM_SPI1->CR1 |= 0x108;               //Slave mode, MSB first, SEL is active low, CPOL/CPHA=00, Data Length 8 bits
//	AM_SPI1->FCR |= 0x480;               //enable FIFO,Tx Trigger level=0, Rx Trigger level=8
	AM_SPI1->CR1 |= 0x108;               //Slave mode, MSB first, SEL is active low, CPOL/CPHA=00, Data Length 8 bits
	AM_SPI1->FCR |= 0x444;               //enable FIFO,Tx Trigger level=4, Rx Trigger level=4
	
//enable SPI and DMA request
	AM_SPI1->CR0 |= 7;
	AM_SPI0->CR0 |= 0xF;

// Wait for transmission completed
//	while((AM_PDMACH4->CTSR & 0xFFFF0000) != 0);
//	while((AM_PDMACH6->CTSR & 0xFFFF0000) != 0);
//	while((AM_PDMACH7->CTSR & 0xFFFF0000) != 0);
//	while((AM_PDMACH7->CTSR & 0xFFFF0000) != 0);
	

/*	
	for (i=0;i<256;i++)
	{
		if (SPI1_Tx_buffer[i] != SPI0_Rx_buffer[i])
		{
			fail();
			while(1);
		}
	} 
*/
}

FLAG_PASS_FAIL dma6_spi0tx_spi1rx_dma7_ok(void)
{
	u32 i;
	
	for (i=0;i<256;i++)
	{
		if (SPI0_Tx_buffer[i] != SPI1_Rx_buffer[i])
		{
			return FLAG_FAIL;
		}
	}	
	return FLAG_PASS;
}
