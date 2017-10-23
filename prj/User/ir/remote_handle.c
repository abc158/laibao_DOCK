//------------------------------------------------------------------------------
//  Copyright (C) 2014-2017, Amicro, Inc.
//  All rights reserved.
//------------------------------------------------------------------------------
#include "ui-ir.h"
#include <string.h>
#include "bsp_usart.h"
//#define     AM_IO_IR_REC_MIDDLE_LEFT          2
//#define  		AM_IO_IR_REC_MIDDLE_RIGHT         2  
//#define  		AM_IO_IR_REC_LEFT                 2
//#define  		AM_IO_IR_REC_RIGHT                2
//#define     AM_IO_IR_REC_MIDDLE               2
U8 port_state[IR_DECODER_MAX][IR_QUEUE_LEN];      /*���IO��ƽ�Ķ���*/
U8 working_byte[IR_DECODER_MAX];                  /*��Ųɼ�����IO��ƽ,��8bit�������*/          
U8 capture_counter[IR_DECODER_MAX];               /*�ɼ�IO��ƽ�ļ���*/
U16 current_ir_code = 0;                           /*ң�ذ���ֵ*/
U8 remote_timer = 0;                              /*���յ�ң�ذ����ĳ���ʱ��*/
static U8 write_ptr[IR_DECODER_MAX];              /*���е�д��ָ��*/
static U8 read_ptr[IR_DECODER_MAX];               /*���еĶ�ȡָ��*/
static U8 data_length[IR_DECODER_MAX];            /*���������ݵĳ���*/
static uint8_t ir_val[IR_DECODER_MAX]={0};        /*���յ��ĳ����������*/
static uint8_t ir_val_test[IR_DECODER_MAX]={0};   /*���յ��ĺ�������*/

extern REMOTE_DECODE remote_decode[];
extern int16_t remote_decode_ir( u16 instance,u16 ir_state );
//extern int16_t remote_decode_ir( u16 instance,  u16 ir_state );
//extern u16 remote_decode_init( u16 instance );
 
/****************************************************************
*Function   :  ir_rec
*Description:  ������պ���
*Input      :  ö���еĺ���λ��
*Output     :  ��
*Return     :  IO��ƽ
*Others     :  
******************************************************************/

U8 ir_rec(IR_POSITION position)
{

			if( position==AM_IO_IR_REC_LEFT)
			   return(GPIO_ReadInBit(AM_GPIOB,GPIO_PIN_4));
     	else if( position==AM_IO_IR_REC_RIGHT)
			  return(GPIO_ReadInBit(AM_GPIOB,GPIO_PIN_6));
			else if( position==AM_IO_IR_REC_BACK_LEFT)
			  return(GPIO_ReadInBit(AM_GPIOC,GPIO_PIN_11));
			else if( position==AM_IO_IR_REC_BACK_RIGHT)
			  return(GPIO_ReadInBit(AM_GPIOC,GPIO_PIN_4));
  	  else if( position==AM_IO_IR_REC_MIDDLE)
			  return(GPIO_ReadInBit(AM_GPIOB,GPIO_PIN_5));
			else 
				return 0;
		
}
/****************************************************************
*Function   :  ir_gpio_init
*Description:  ���������յ�IO  
*Input      :  ��
*Output     :  ��
*Return     :  ��
*Others     :  
******************************************************************/
U8 ir_gpio_init(void)
{
  int ret = -1;
	int i;
  for( i=0; i<IR_DECODER_MAX; i++ )
  {
 //   ret = gpio_request_one(ir_gpio[i],GPIO_F_DIR_IN);
    
    if(ret != -1)
    {
      ;
    }
    else
    {
      printf("ir io not ok i=%d\r\n",i);
    }
  }  
  return 0;
}

/****************************************************************
*Function   :  ir_rx_init
*Description:  ������ճ�ʼ��  
*Input      :  ��
*Output     :  ��
*Return     :  ��
*Others     :  
******************************************************************/
void ir_rx_init(void)
{
  U8 i;
  printf("ir_rx_init\r\n");
  memset(port_state, 0, sizeof(port_state));
  memset(write_ptr, 0, sizeof(write_ptr));
  memset(read_ptr, 0, sizeof(read_ptr));
  memset(data_length, 0, sizeof(data_length));
  memset(working_byte, 0, sizeof(working_byte));
  memset(capture_counter, 0, sizeof(capture_counter));
  ir_gpio_init();
  for(i=0;i<REMOTE_DECODER_MAX;i++)
  {
    //remote_decode_init(i);
    #ifdef USE_VIRTUAL_WALL
      aovw_decode_init(i);
    #endif
  }

  printf("ir_rx_init ok!!\r\n");
}

/****************************************************************
*Function   :  ir_rx_q_put
*Description:  �����ݴ������  
*Input      :  U8 index:����ͷID
*              U8 value:���������
*Output     :  ��
*Return     :  ��
*Others     :  
******************************************************************/
void ir_rx_q_put(U8 index, U8 value)
{
  port_state[index][write_ptr[index]] = value;
  write_ptr[index]++;
  if (write_ptr[index] >= IR_QUEUE_LEN)
  {
    write_ptr[index] = 0;
  }
  data_length[index]++;
}

/****************************************************************
*Function   :  ir_rx_q_get
*Description:  �ӽ��ն�����ȡ������  
*Input      :  U8 index:����ͷID            
*Output     :  ȡ��������
*Return     :  ��
*Others     :  
******************************************************************/
U8 ir_rx_q_get(U8 index)
{
  U8 state;
  //hal_ints_off( );
  state = port_state[index][read_ptr[index]];
  read_ptr[index]++;
  if (read_ptr[index] >= IR_QUEUE_LEN)
  {
    read_ptr[index] = 0;
  }
  data_length[index]--;
  //hal_ints_on( );
  
  return state;    
}

/****************************************************************
*Function   :  ir_rx_q_empty
*Description:  ���ն����Ƿ�Ϊ��  
*Input      :  U8 index:����ͷID            
*Output     :  1:���ն����ﻹ������ 0:���ն���Ϊ��
*Return     :  ��
*Others     :  
******************************************************************/
U8 ir_rx_q_empty(U8 index)
{
  if (data_length[index] == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/****************************************************************
*Function   :  ir_rx_q_full
*Description:  ���ն����Ƿ����� 
*Input      :  U8 index:����ͷID            
*Output     :  1:���ն������� 0:���ն���δ��
*Return     :  ��
*Others     :  
******************************************************************/
U8 ir_rx_q_full(U8 index)
{
  if (data_length[index] == IR_QUEUE_LEN)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/****************************************************************
*Function   :  ir_rx_capture_4khz
*Description:  �ɼ���������ͷ�ĵ�ƽ,������浽���ն�����,4K�ж���ִ�� 
*Input      :  ��            
*Output     :  ��
*Return     :  ��
*Others     :  
******************************************************************/
void ir_rx_capture_4khz(void)
{
  U8 index;
  U8 state;
  
  for (index=0; index<IR_DECODER_MAX; index++)
  {
   // printf("ir rx gpio:%x\r\n",ir_gpio[index]);
		state = ir_rec((IR_POSITION) index);
		//printf("state %d\r\n",state);
    state = (~state) & 0x01;
    working_byte[index] = (working_byte[index] << 1) | state;
    capture_counter[index]++;
    if (capture_counter[index] == 8)
    {
      if (ir_rx_q_full(index) != 1)
      {
        ir_rx_q_put(index, working_byte[index]);
        working_byte[index] = 0;
        capture_counter[index] = 0;
      }
    }
  }
}

/****************************************************************
*Function   :  ir_rx_decode
*Description:  �ӽ��ն�����ȡ������,���ձ����ʽ���н��� 
*Input      :  ��            
*Output     :  ��
*Return     :  ��
*Others     :  
******************************************************************/
#define W_TX_PAYLOAD_NOACK_CMD	 0xb0
#define BACK_LEFT_STRONG         0XF001
#define BACK_LEFT_WEAK           0XF002
#define BACK_RIGHT_STRONG        0XF004
#define BACK_RIGHT_WEAK          0XF008
#define LEFT_STRONG              0XF010
#define LEFT_WEAK                0XF020
#define RIGHT_STRONG             0XF040
#define RIGHT_WEAK               0XF080
#define MIDDLE_STRONG            0XF100
#define MIDDLE_WEAK              0XF200
extern void Send_Packet(U8 type,U8* pbuf,U8 len);
static volatile U8 ir_signal_send[IR_DECODER_MAX*2];
void IR_signal_tans_code(U16 data,U8 *p,U8 index);
void ir_rx_decode(void)
{
  U8 state, value;
  U8 index, i;
  int16_t result;
	U16 sinal_temp;
  
  for (index=0; index<IR_DECODER_MAX; index++)
  {
    while (ir_rx_q_empty(index) != 1)
    { 
      value = ir_rx_q_get(index);	
      if (value != 0x00)
      { 
        //printf("0x%x ", value);
      }
      for(i=0; i<8; i++)
      {	  	
        state = (value >> (7-i))&0x01; 
        if (value != 0x00)
        {   
          //printf("i=%d state=%d ", i, state); 
        }

        //if (index == IR_POSITION_OMNI) 
        {     
        	/*ң�����ͳ�����Ľ���,���ң�����ͳ�����ı��뷽ʽ��һ��,��Ҫ�ֿ�����*/
          result = remote_decode_ir(index, state);
          if ((result == 0)&&((remote_decode[index].rxByte&0X0fff) != 0))
          {
            current_ir_code = remote_decode[index].rxByte;//���ң����������
              //���ź����ݷ��뷢������
						sinal_temp =current_ir_code;
						ir_signal_send[index*2]=(U8)sinal_temp;
						ir_signal_send[index*2+1]=((U8)(sinal_temp>>8));
            remote_timer  = REMOTE_DATA_KEEP_COUNT;
            ir_val[index] = remote_decode[index].rxByte;  //��ų�������ź�
            ir_val_test[index] = ir_val[index]; 
           // printf("%d REC %x  %x state \r\n",((ir_signal_send[index]>>12)&0x0f),((ir_signal_send[index]>>8)),((ir_signal_send[index])&0x03));
					 // printf("%d IR %x  \r\n",index,current_ir_code);
          #ifdef USE_VIRTUAL_WALL
          result = aovw_decode_ir(index, state);//����ǽ����
		      if (result == 0)
		      {
            ir_val[index] = AOVW_BYTE;       //��⵽����ǽ
            ir_val_test[index] = AOVW_BYTE;
		        //printf("aovw\r\n");	                        
		      }
		      #endif
         }
        }
		  }
    }
  }
	{
	 Send_Packet(W_TX_PAYLOAD_NOACK_CMD,(U8 *)ir_signal_send,sizeof(ir_signal_send));

	}
	memset((U8 *)ir_signal_send,0,sizeof(ir_signal_send));
}
/****************************************************************
*Function   :  remote_ir_get
*Description:  ��ȡ����ͷ���յ��ĳ�������ź� 
*Input      :  IR_REMOT_POSITION_E index ����ͷID            
*Output     :  ��
*Return     :  ����ͷ���յ�������
*Others     :  
******************************************************************/
uint8_t remote_ir_get(IR_REMOT_POSITION_E index)
{
  uint8_t val;
  val = ir_val[index];
  ir_val[index] = 0;
  return val;
}

/****************************************************************
*Function   :  get_ir_local
*Description:  ��ȡ����ͷ���յ�ң���������� 
*Input      :  IR_REMOT_POSITION_E index ����ͷID            
*Output     :  ��
*Return     :  ����ͷ���յ�������
*Others     :  
******************************************************************/
uint8_t get_ir_local(void)
{
  uint8_t val;
  val = current_ir_code;
  if (remote_timer > 0)
  {
    remote_timer--;
    if (remote_timer == 0)
    {
      current_ir_code = 0;
    } 
  }    
  return val;
}

/****************************************************************
*Function   :  get_ir_test
*Description:  ��ȡ����ͷ���յ�������
*Input      :  IR_REMOT_POSITION_E index ����ͷID            
*Output     :  ��
*Return     :  ����ͷ���յ�������
*Others     :  
******************************************************************/
uint8_t get_ir_test(IR_REMOT_POSITION_E index)
{
  uint8_t val;
  val = ir_val_test[index];
  ir_val_test[index] = 0;
  return val;
}

/****************************************************************
*Function   :  ir_rx_code_get
*Description:  ��������ʽ���յ�������д��ң�غͳ������ʹ�õı��� 
*Input      :  uint8_t chan ����ͨ��
*              uint8_t val  ���յ�������        
*Output     :  ��
*Return     :  ��
*Others     :  
******************************************************************/
void ir_rx_code_get(uint8_t chan, uint8_t val)
{
    ir_val_test[chan] = val;

    current_ir_code = val;
    ir_val[chan]=val;
    
   //if(chan == 1)
   //    local_ir_code = val;

   remote_timer = 16;
}
