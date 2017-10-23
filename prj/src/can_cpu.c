//500kHz, standard mode,数据帧，传输5笔数，每笔数据8个字节
#include "user.h"
#include "main.h"
#include "AM8813.h"
#include "AM8813_misc.h"
#include "ckcu.h"
#include "gpio.h"

extern STATE State[NumMdl];

int can_start(void)
{
	int i,j;
	unsigned char data[13];
	//static unsigned int CHIPID;
	cpu_delay(10);
	State[MdlCan] = State_StartFinish;
	
	AFIO_GPCConfig(AFIO_PIN_14|AFIO_PIN_15,AFIO_MODE_12);
//	AM_AFIO->GPCCFGR[1] = 0xCC000000;   //AFIO12,PC14-15
	AM_CAN->OCR = 3;                    //2-Normal output, 3-clock output
	AM_CAN->MOD |= 0x0C;                //Single filter, Self-Test Mode
	AM_CAN->TRFDI_ACAMR[0] = 0xAA;      //ID.28-21
	AM_CAN->TRFDI_ACAMR[1] = 0x40;      //ID.20-18=010;RTR=0, data frame
	                                    //SFF,TRFDI_ACAMR[3:2] don't care
	AM_CAN->TRFDI_ACAMR[4] = 0x00;      //All match
	AM_CAN->TRFDI_ACAMR[5] = 0x00;      //All match
	AM_CAN->TRFDI_ACAMR[6] = 0xFF;      //Data byte don't care
	AM_CAN->TRFDI_ACAMR[7] = 0xFF;      //Data byte don't care
	
	AM_CAN->BTR0 = 0x41;                //SJW=2; TQ=2*2/24M ??
	AM_CAN->BTR1 = 0x36;                //Sample once; TSEG1=7, TSEG2=4, Bit Time=12TQ=48/24M
	
	AM_CAN->MOD &= 0xFE;                //Release Reset mode
	
	
	while((AM_CAN->SR & 0x04) == 0);    //0-Transmit buffer locked
	AM_CAN->TRFDI_ACAMR[0] = 0x08;      //FF=0, Standard frame; RTR=0, data frame; Data length=8
	AM_CAN->TRFDI_ACAMR[1] = 0xAA;      //ID.28-21
	AM_CAN->TRFDI_ACAMR[2] = 0x40;      //ID.20-18=010;RTR=0
	
	for(j=0;j<5;j++)
	{	
    while((AM_CAN->SR & 0x04) == 0);    //0-Transmit buffer locked		
		for(i=0;i<8;i++)
		{
			AM_CAN->TRFDI_ACAMR[3+i] = (i<<4)+i+j; //data
		}
		
		AM_CAN->CMR |= 0x10;                //Issue Self-Reception CMD
  }
	
	while((AM_CAN->SR & 0x08) == 0);    //Wait for transmit completed
}

FLAG_PASS_FAIL can_ok(void)
{
	int i,j;
	unsigned char data[13];
	
	while((AM_CAN->SR & 0x01) == 0);
	j = 0;
	while((AM_CAN->SR & 0x01) != 0)
	{
		for(i=0;i<11;i++)
		{
			if(i<3)
			{
				data[i] = AM_CAN->TRFDI_ACAMR[i];
				if(data[i] != AM_CAN->TXBUF[i])
				{
					fail();
					while(1);
				}
			}
			else
			{
				data[i] = AM_CAN->TRFDI_ACAMR[i];
				if(data[i] != (((i-3)<<4)+(i-3)+j))
				{
					fail();
					while(1);
				}				
			}
		}
		AM_CAN->CMR |= 4;                   //Release reveive buffer
	  j++;
  }
	
}