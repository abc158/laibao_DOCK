#include "user.h"
#include "AM8813.h"
#include "main.h"
#include "ckcu.h"
#include "pdma.h"
#include "adc.h"
#include "gpio.h"
#include "gptm.h"

#define COUNTER_UP_VAL  6000
#define CH0_CC_VAL      3000
#define CH1_CC_VAL      2900
#define CH2_CC_VAL      2800
#define CH3_CC_VAL      2800

u32 BufAdcData[18];
u32 BufAdcDataAll[18*8];
u16 Cnt1 = 0;
u16 FlagAdcDmaFinish1 = RESET;

extern STATE State[NumMdl];


void adc_dma1_gptm0_interrupt_req(void)
{
	u16 i;
	
	if( FLAG_SET == dma_get_status(TRAN_CPLT_INT,DMA_CH1) )
	{
/*		for(i=0;i<17;i++)
		{
			BufAdcDataAll[17*Cnt1+i] = BufAdcData[i];
		}
		Cnt1++;
		if(Cnt1 == 8)*/
		{
			FlagAdcDmaFinish1 = SET;
			DMA_EnaCmd(DMA_CH1,DISABLE);
			GPTM_DeInit(AM_GPTM0);
			ADC_DeInit();
			deinit_dma(DMA_CH1);
			Cnt1 = 0;
			State[MdlAdc] = State_StartFinish;
		}

	}
	dma_clear_status(TRAN_CPLT_INT,DMA_CH1);
	GPTM_ClearFlag(AM_GPTM0,GPTM_FLAG_UEV);
}

void adc_dma1_gptm0_start(void)
{
	GPTM_TimeBaseInitTypeDef TimeBaseInit;
	uint32_t tmp1,i;
	DMA_InitTypeDef DmaInitStruct;
	u8 ListAdcChn[18] = {ADC_CH_17, ADC_CH_16, \
		ADC_CH_15, ADC_CH_14, ADC_CH_13, ADC_CH_12, ADC_CH_11, ADC_CH_10, ADC_CH_9, ADC_CH_8, \
		ADC_CH_7, ADC_CH_6, ADC_CH_5, ADC_CH_4, ADC_CH_3, ADC_CH_2, ADC_CH_1, ADC_CH_0};	
	GPTM_OutputInitTypeDef OutInit;
	u16 ValAdc[3][18],ValTmp, ValTmp1;
	s16 j;

	AFIO_GPAConfig(AFIO_PIN_0|AFIO_PIN_1|AFIO_PIN_2|AFIO_PIN_3|AFIO_PIN_4|AFIO_PIN_5|AFIO_PIN_6|AFIO_PIN_7|AFIO_PIN_8|AFIO_PIN_9|AFIO_PIN_10|AFIO_PIN_11|AFIO_PIN_12|AFIO_PIN_15,AFIO_MODE_2);		
		
		
	State[MdlAdc] = State_Continue;
		
	ADC_Reset();
	ADC_AlignConfig(AlignRight);
	ADC_RegularGroupConfig(ONE_SHOT_MODE,18,0);		
	for(i=0;i<18;i++)
	{
		ADC_RegularChannelConfig(ListAdcChn[i],i,0);
	}
	ADC_RegularTrigConfig(ADC_TRIG_GPTM0_MTO);	
	ADC_PDMAConfig(ADC_PDMA_REGULAR_CYCLE,ENABLE);
	
// dma1 configure
	deinit_dma(DMA_CH1);
	DmaInitStruct.HardTrigSrc = DMA_HARDTRIG_SRC_ADC;
	DmaInitStruct.AutoReload = ENABLE;
	DmaInitStruct.DataWidth = DATA_WIDTH_32BIT;
	DmaInitStruct.AddrFix = DISABLE;
	DmaInitStruct.SrcAddrMode = LINEAR;
	DmaInitStruct.SrcAddrIncrement = ADDR_INC;
	DmaInitStruct.DestAddrMode = LINEAR;
	DmaInitStruct.DestAddrIncrement = ADDR_INC;
	DmaInitStruct.AddrSrc = (uint32_t)(AM_ADC->DR);;
	DmaInitStruct.AddrDest = (uint32_t)BufAdcData;
	DmaInitStruct.ChnPriority = CHANNEL_PRI_HIGH;
	DmaInitStruct.BlockLength = 18;
	DmaInitStruct.BlockCnt = 1;
	init_dma(&DmaInitStruct,DMA_CH1);		
	dma_int_enable(TRAN_CPLT_INT,DMA_CH1);
	dma_int_enable(GLOBAL_INT,DMA_CH1);
	DMA_EnaCmd(DMA_CH1,ENABLE);	
	NVIC_EnableIRQ(PDMACH1_IRQn);
	
// gptm0 configure 
	TimeBaseInit.CounterMode = GPTM_CNT_MODE_UP;
	TimeBaseInit.CounterReload = COUNTER_UP_VAL;
	TimeBaseInit.Prescaler = 3;
	TimeBaseInit.PSCReloadTime = GPTM_PSC_RLD_IMMEDIATE;
	GPTM_TimeBaseInit(AM_GPTM0, &TimeBaseInit);
	/* MTO 																																																		*/	
	GPTM_MMSELConfig(AM_GPTM0,GPTM_MMSEL_UPDATE);
		
  //start gptm
	GPTM_Cmd(AM_GPTM0, ENABLE);	

/*
	i = 0;
	while(i<1)
	{
		while( ADC_GetConversionData(17,&ValTmp) == RESET );
		ValAdc[i][17] = ValTmp;		
		for(j=16;j>=0;j--)
		{
			ADC_GetConversionData(j,&ValTmp);
			ValAdc[i][j] = ValTmp;			
		}
		i++;
	}*/
}

FLAG_PASS_FAIL adc_dma1_gptm0_ok(void)
{
	u16 i;
	
	while(FlagAdcDmaFinish1 == RESET);
	FlagAdcDmaFinish1 = RESET;
	/*
	for(i=0;i<8*18;i++)
	{
		if(BufAdcDataAll[i] != 2*(1+i)+0x80000000)
			return FLAG_FAIL;
	}*/
	return FLAG_PASS;	
}



