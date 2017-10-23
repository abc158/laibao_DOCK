#include "user.h"
#include "main.h"
#include "AM8813.h"
#include "gptm.h"
#include "ckcu.h"
#include "gpio.h"
#include "pdma.h"
#include "rstcu.h"

//gptm trigger

extern STATE State[NumMdl];

#define CMP_VAL		100
u32 FlagTimer[10] = {0};

int gptm0_ch0_irq_flag=10;
int gptm0_ch1_irq_flag=10;
int gptm0_ch2_irq_flag=10;
int gptm0_ch3_irq_flag=10;
int gptm0_uev_irq_flag=10;
int gptm0_tev_irq_flag=10;

int gptm1_ch0_irq_flag=0;
int gptm1_ch1_irq_flag=0;
int gptm1_ch2_irq_flag=0;
int gptm1_ch3_irq_flag=0;
int gptm1_uev_irq_flag=0;
int gptm1_tev_irq_flag=0;

int gptm2_ch0_irq_flag=0;
int gptm2_ch1_irq_flag=0;
int gptm2_ch2_irq_flag=0;
int gptm2_ch3_irq_flag=0;
int gptm2_uev_irq_flag=0;
int gptm2_tev_irq_flag=0;

int gptm3_ch0_irq_flag=0;
int gptm3_ch1_irq_flag=0;
int gptm3_ch2_irq_flag=0;
int gptm3_ch3_irq_flag=0;
int gptm3_uev_irq_flag=0;
int gptm3_tev_irq_flag=0;

int m0_brk_count=10;
int m0_uev1_count=10;
int m0_uev2_count=10;
int m0_tr_count=10;
int m0_cc_ch0_count=10;
int m0_cc_ch1_count=10;
int m0_cc_ch2_count=10;
int m0_cc_ch3_count=10;

int m1_brk_count=10;
int m1_uev1_count=10;
int m1_uev2_count=10;
int m1_tr_count=10;
int m1_cc_ch0_count=10;
int m1_cc_ch1_count=10;
int m1_cc_ch2_count=10;
int m1_cc_ch3_count=10;

int gptm_pdma_test(u32 dma_ch_num);
int timer_dma_pid_ok();


void gptm1_int_irq()
{
	if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_CH0CC)==SET)
	{
		gptm1_ch0_irq_flag++;
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_CH0CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_CH1CC)==SET)
	{
		gptm1_ch1_irq_flag++;
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_CH1CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_CH2CC)==SET)
	{
		gptm1_ch2_irq_flag++;
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_CH2CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_CH3CC)==SET)
	{
		gptm1_ch3_irq_flag++;
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_CH3CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_UEV)==SET)
	{
		gptm1_uev_irq_flag++;
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_UEV);
	}

	if(GPTM_GetFlagStatus(AM_GPTM1, GPTM_FLAG_TEV)==SET)
	{
		gptm1_tev_irq_flag++;
		GPTM_ClearFlag(AM_GPTM1, GPTM_FLAG_TEV);
	}
}

void gptm2_int_irq()
{
	if(GPTM_GetFlagStatus(AM_GPTM2, GPTM_FLAG_CH0CC)==SET)
	{
		gptm2_ch0_irq_flag++;
		GPTM_ClearFlag(AM_GPTM2, GPTM_FLAG_CH0CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM2, GPTM_FLAG_CH1CC)==SET)
	{
		gptm2_ch1_irq_flag++;
		GPTM_ClearFlag(AM_GPTM2, GPTM_FLAG_CH1CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM2, GPTM_FLAG_CH2CC)==SET)
	{
		gptm2_ch2_irq_flag++;
		GPTM_ClearFlag(AM_GPTM2, GPTM_FLAG_CH2CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM2, GPTM_FLAG_CH3CC)==SET)
	{
		gptm2_ch3_irq_flag++;
		GPTM_ClearFlag(AM_GPTM2, GPTM_FLAG_CH3CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM2, GPTM_FLAG_UEV)==SET)
	{
		gptm2_uev_irq_flag++;
		GPTM_ClearFlag(AM_GPTM2, GPTM_FLAG_UEV);
	}

	if(GPTM_GetFlagStatus(AM_GPTM2, GPTM_FLAG_TEV)==SET)
	{
		gptm2_tev_irq_flag++;
		GPTM_ClearFlag(AM_GPTM2, GPTM_FLAG_TEV);
	}
}

void gptm3_int_irq()
{
	if(GPTM_GetFlagStatus(AM_GPTM3, GPTM_FLAG_CH0CC)==SET)
	{
		gptm3_ch0_irq_flag++;
		GPTM_ClearFlag(AM_GPTM3, GPTM_FLAG_CH0CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM3, GPTM_FLAG_CH1CC)==SET)
	{
		gptm3_ch1_irq_flag++;
		GPTM_ClearFlag(AM_GPTM3, GPTM_FLAG_CH1CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM3, GPTM_FLAG_CH2CC)==SET)
	{
		gptm3_ch2_irq_flag++;
		GPTM_ClearFlag(AM_GPTM3, GPTM_FLAG_CH2CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM3, GPTM_FLAG_CH3CC)==SET)
	{
		gptm3_ch3_irq_flag++;
		GPTM_ClearFlag(AM_GPTM3, GPTM_FLAG_CH3CC);
	}

	if(GPTM_GetFlagStatus(AM_GPTM3, GPTM_FLAG_UEV)==SET)
	{
		gptm3_uev_irq_flag++;
		GPTM_ClearFlag(AM_GPTM3, GPTM_FLAG_UEV);
	}

	if(GPTM_GetFlagStatus(AM_GPTM3, GPTM_FLAG_TEV)==SET)
	{
		gptm3_tev_irq_flag++;
		GPTM_ClearFlag(AM_GPTM3, GPTM_FLAG_TEV);
	}
	
	if(gptm3_uev_irq_flag == 100)
		State[MdlTimer] = State_StartFinish;
}

FLAG_PASS_FAIL timer_ok()
{
	int t_temp;
	int p_temp;
	t_temp=gptm0_ch0_irq_flag;
	//p_temp=(AM_PID->PID0_PS) & 0x3ff;
//	print("timer dma pid wait ok.");
	//if(p_temp==0)
	//{
	//	return 1;
	//}
	
	if( (gptm0_ch0_irq_flag==0) || (gptm0_ch1_irq_flag==0) || (gptm0_ch2_irq_flag==0) || (gptm0_ch3_irq_flag==0) \
		|| (gptm0_uev_irq_flag==0) || (gptm1_ch0_irq_flag==0) || (gptm1_ch1_irq_flag==0) || (gptm1_ch2_irq_flag==0) \
	  || (gptm1_ch3_irq_flag==0) || (gptm1_uev_irq_flag==0) || (gptm2_ch0_irq_flag==0) || (gptm2_ch1_irq_flag==0) \
		|| (gptm2_ch2_irq_flag==0) || (gptm2_ch3_irq_flag==0) || (gptm2_uev_irq_flag==0) || (m0_cc_ch0_count==0) || (m0_cc_ch1_count==0) \
		|| (m0_cc_ch2_count==0) || (m0_cc_ch3_count==0) || (m1_cc_ch0_count==0) || (m1_cc_ch1_count==0) \
	  || (m1_cc_ch2_count==0) || (m1_cc_ch3_count==0) || (gptm2_ch2_irq_flag==0) ) 
	{
	gptm1_ch0_irq_flag = 0;
	gptm1_ch1_irq_flag = 0;
	gptm1_ch2_irq_flag = 0;
	gptm1_ch3_irq_flag = 0;
	gptm1_uev_irq_flag = 0;
	gptm2_ch0_irq_flag = 0;
	gptm2_ch1_irq_flag = 0;
	gptm2_ch2_irq_flag = 0;
	gptm2_ch3_irq_flag = 0;
	gptm2_uev_irq_flag = 0;
	gptm3_ch0_irq_flag = 0;
	gptm3_ch1_irq_flag = 0;
	gptm3_ch2_irq_flag = 0;
	gptm3_ch3_irq_flag = 0;
	gptm3_uev_irq_flag = 0;		

	GPTM_DeInit(AM_GPTM1);
	GPTM_DeInit(AM_GPTM2);
	GPTM_DeInit(AM_GPTM3);
	GPTM_ClearIntPendingBit(AM_GPTM1,GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC|GPTM_INT_UEV|GPTM_INT_TEV);
	GPTM_ClearIntPendingBit(AM_GPTM2,GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC|GPTM_INT_UEV|GPTM_INT_TEV);
	GPTM_ClearIntPendingBit(AM_GPTM3,GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC|GPTM_INT_UEV|GPTM_INT_TEV);
	
		return FLAG_FAIL;
	}
	else
	{
	gptm1_ch0_irq_flag = 0;
	gptm1_ch1_irq_flag = 0;
	gptm1_ch2_irq_flag = 0;
	gptm1_ch3_irq_flag = 0;
	gptm1_uev_irq_flag = 0;
	gptm2_ch0_irq_flag = 0;
	gptm2_ch1_irq_flag = 0;
	gptm2_ch2_irq_flag = 0;
	gptm2_ch3_irq_flag = 0;
	gptm2_uev_irq_flag = 0;
	gptm3_ch0_irq_flag = 0;
	gptm3_ch1_irq_flag = 0;
	gptm3_ch2_irq_flag = 0;
	gptm3_ch3_irq_flag = 0;
	gptm3_uev_irq_flag = 0;		
	
	GPTM_DeInit(AM_GPTM1);
	GPTM_DeInit(AM_GPTM2);
	GPTM_DeInit(AM_GPTM3);
	GPTM_ClearIntPendingBit(AM_GPTM1,GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC|GPTM_INT_UEV|GPTM_INT_TEV);
	GPTM_ClearIntPendingBit(AM_GPTM2,GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC|GPTM_INT_UEV|GPTM_INT_TEV);
	GPTM_ClearIntPendingBit(AM_GPTM3,GPTM_INT_CH0CC|GPTM_INT_CH1CC|GPTM_INT_CH2CC|GPTM_INT_CH3CC|GPTM_INT_UEV|GPTM_INT_TEV);		
		return FLAG_PASS;
	}
}

int timer_start(void)
{
	  GPTM_TimeBaseInitTypeDef TimeBaseInit;
	  GPTM_OutputInitTypeDef OutInit;
	  DMA_InitTypeDef PDMACH_InitStructure;

	  int t_temp, p_temp;
	
	  //--------------------gptm0 config----------------------------//
	  /* Time base configuration                                                                                */
	  TimeBaseInit.CounterMode = GPTM_CNT_MODE_UP;
	  TimeBaseInit.CounterReload = 1024;
	  TimeBaseInit.Prescaler = 4;
	  TimeBaseInit.PSCReloadTime = GPTM_PSC_RLD_IMMEDIATE;
	  GPTM_TimeBaseInit(AM_GPTM1, &TimeBaseInit);
	  GPTM_TimeBaseInit(AM_GPTM2, &TimeBaseInit);
		GPTM_TimeBaseInit(AM_GPTM3, &TimeBaseInit);
	
	  /* Force channel output reference to inactive level                                                       */
	  GPTM_OutputModeConfig(AM_GPTM1, GPTM_CH_0 | GPTM_CH_1 | GPTM_CH_2 | GPTM_CH_3, GPTM_OM_FORCED_INACTIVE);
	  GPTM_OutputModeConfig(AM_GPTM2, GPTM_CH_0 | GPTM_CH_1 | GPTM_CH_2 | GPTM_CH_3, GPTM_OM_FORCED_INACTIVE);
		GPTM_OutputModeConfig(AM_GPTM3, GPTM_CH_0 | GPTM_CH_1 | GPTM_CH_2 | GPTM_CH_3, GPTM_OM_FORCED_INACTIVE);

	  /* GPTM0 Match Output Active Mode configuration: Channel0~3                                              */
	  OutInit.Channel = GPTM_CH_0;
	  OutInit.OutputMode = GPTM_OM_PWM1;
	  OutInit.Control = GPTM_CHCTL_ENABLE;
	  OutInit.Polarity = GPTM_CHP_NONINVERTED;
	  OutInit.Compare = 512;
	  GPTM_OutputInit(AM_GPTM1, &OutInit);
	  GPTM_OutputInit(AM_GPTM2, &OutInit);
		GPTM_OutputInit(AM_GPTM3, &OutInit);

	  OutInit.Channel = GPTM_CH_1;
	  OutInit.OutputMode = GPTM_OM_PWM1;
	  OutInit.Control = GPTM_CHCTL_ENABLE;
	  OutInit.Polarity = GPTM_CHP_NONINVERTED;
	  OutInit.Compare = 512;
	  GPTM_OutputInit(AM_GPTM1, &OutInit);
	  GPTM_OutputInit(AM_GPTM2, &OutInit);
		GPTM_OutputInit(AM_GPTM3, &OutInit);
		

	  OutInit.Channel = GPTM_CH_2;
	  OutInit.OutputMode = GPTM_OM_PWM1;
	  OutInit.Control = GPTM_CHCTL_ENABLE;
	  OutInit.Polarity = GPTM_CHP_NONINVERTED;
	  OutInit.Compare = 512;
	  GPTM_OutputInit(AM_GPTM1, &OutInit);
	  GPTM_OutputInit(AM_GPTM2, &OutInit);
		GPTM_OutputInit(AM_GPTM3, &OutInit);

	  OutInit.Channel = GPTM_CH_3;
	  OutInit.OutputMode = GPTM_OM_PWM1;
	  OutInit.Control = GPTM_CHCTL_ENABLE;
	  OutInit.Polarity = GPTM_CHP_NONINVERTED;
	  OutInit.Compare = 512;
	  GPTM_OutputInit(AM_GPTM1, &OutInit);
	  GPTM_OutputInit(AM_GPTM2, &OutInit);
		GPTM_OutputInit(AM_GPTM3, &OutInit);
		
	  GPTM_IntConfig(AM_GPTM1, GPTM_INT_CH0CC | GPTM_INT_CH1CC | GPTM_INT_CH2CC | GPTM_INT_CH3CC | GPTM_INT_UEV | GPTM_INT_TEV, ENABLE);
	  GPTM_IntConfig(AM_GPTM2, GPTM_INT_CH0CC | GPTM_INT_CH1CC | GPTM_INT_CH2CC | GPTM_INT_CH3CC | GPTM_INT_UEV | GPTM_INT_TEV, ENABLE);
		GPTM_IntConfig(AM_GPTM3, GPTM_INT_CH0CC | GPTM_INT_CH1CC | GPTM_INT_CH2CC | GPTM_INT_CH3CC | GPTM_INT_UEV | GPTM_INT_TEV, ENABLE);
		
	  GPTM_ClearIntPendingBit(AM_GPTM1, GPTM_INT_CH0CC | GPTM_INT_CH1CC | GPTM_INT_CH2CC | GPTM_INT_CH3CC | GPTM_INT_UEV | GPTM_INT_TEV);
	  GPTM_ClearIntPendingBit(AM_GPTM2, GPTM_INT_CH0CC | GPTM_INT_CH1CC | GPTM_INT_CH2CC | GPTM_INT_CH3CC | GPTM_INT_UEV | GPTM_INT_TEV);
		GPTM_ClearIntPendingBit(AM_GPTM3, GPTM_INT_CH0CC | GPTM_INT_CH1CC | GPTM_INT_CH2CC | GPTM_INT_CH3CC | GPTM_INT_UEV | GPTM_INT_TEV);
		
	  NVIC_EnableIRQ(GPTM1_IRQn);
	  NVIC_EnableIRQ(GPTM2_IRQn);
		NVIC_EnableIRQ(GPTM3_IRQn);

	  //start gptm
	  GPTM_Cmd(AM_GPTM1, ENABLE);
	  GPTM_Cmd(AM_GPTM2, ENABLE);
		GPTM_Cmd(AM_GPTM3, ENABLE);
		
		State[MdlTimer] = State_Continue;
	  return 0;
}





