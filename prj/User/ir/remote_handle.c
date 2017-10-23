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
U8 port_state[IR_DECODER_MAX][IR_QUEUE_LEN];      /*存放IO电平的队列*/
U8 working_byte[IR_DECODER_MAX];                  /*存放采集到的IO电平,满8bit存入队列*/          
U8 capture_counter[IR_DECODER_MAX];               /*采集IO电平的计数*/
U16 current_ir_code = 0;                           /*遥控按键值*/
U8 remote_timer = 0;                              /*接收到遥控按键的持续时间*/
static U8 write_ptr[IR_DECODER_MAX];              /*队列的写入指针*/
static U8 read_ptr[IR_DECODER_MAX];               /*队列的读取指针*/
static U8 data_length[IR_DECODER_MAX];            /*队列里数据的长度*/
static uint8_t ir_val[IR_DECODER_MAX]={0};        /*接收到的充电座的数据*/
static uint8_t ir_val_test[IR_DECODER_MAX]={0};   /*接收到的红外数据*/

extern REMOTE_DECODE remote_decode[];
extern int16_t remote_decode_ir( u16 instance,u16 ir_state );
//extern int16_t remote_decode_ir( u16 instance,  u16 ir_state );
//extern u16 remote_decode_init( u16 instance );
 
/****************************************************************
*Function   :  ir_rec
*Description:  红外接收函数
*Input      :  枚举中的红外位置
*Output     :  无
*Return     :  IO电平
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
*Description:  申请红外接收的IO  
*Input      :  无
*Output     :  无
*Return     :  无
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
*Description:  红外接收初始化  
*Input      :  无
*Output     :  无
*Return     :  无
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
*Description:  将数据存入队列  
*Input      :  U8 index:接收头ID
*              U8 value:存入的数据
*Output     :  无
*Return     :  无
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
*Description:  从接收队列中取出数据  
*Input      :  U8 index:接收头ID            
*Output     :  取出的数据
*Return     :  无
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
*Description:  接收队列是否为空  
*Input      :  U8 index:接收头ID            
*Output     :  1:接收队列里还有数据 0:接收队列为空
*Return     :  无
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
*Description:  接收队列是否已满 
*Input      :  U8 index:接收头ID            
*Output     :  1:接收队列已满 0:接收队列未满
*Return     :  无
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
*Description:  采集各个接收头的电平,将结果存到接收队列里,4K中断里执行 
*Input      :  无            
*Output     :  无
*Return     :  无
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
*Description:  从接收队列里取出数据,按照编码格式进行解码 
*Input      :  无            
*Output     :  无
*Return     :  无
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
        	/*遥控器和充电座的解码,如果遥控器和充电座的编码方式不一致,需要分开解释*/
          result = remote_decode_ir(index, state);
          if ((result == 0)&&((remote_decode[index].rxByte&0X0fff) != 0))
          {
            current_ir_code = remote_decode[index].rxByte;//存放遥控器的数据
              //将信号数据放入发送数组
						sinal_temp =current_ir_code;
						ir_signal_send[index*2]=(U8)sinal_temp;
						ir_signal_send[index*2+1]=((U8)(sinal_temp>>8));
            remote_timer  = REMOTE_DATA_KEEP_COUNT;
            ir_val[index] = remote_decode[index].rxByte;  //存放充电座的信号
            ir_val_test[index] = ir_val[index]; 
           // printf("%d REC %x  %x state \r\n",((ir_signal_send[index]>>12)&0x0f),((ir_signal_send[index]>>8)),((ir_signal_send[index])&0x03));
					 // printf("%d IR %x  \r\n",index,current_ir_code);
          #ifdef USE_VIRTUAL_WALL
          result = aovw_decode_ir(index, state);//虚拟墙解码
		      if (result == 0)
		      {
            ir_val[index] = AOVW_BYTE;       //检测到虚拟墙
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
*Description:  获取接收头接收到的充电座的信号 
*Input      :  IR_REMOT_POSITION_E index 接收头ID            
*Output     :  无
*Return     :  接收头接收到的数据
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
*Description:  获取接收头接收到遥控器的数据 
*Input      :  IR_REMOT_POSITION_E index 接收头ID            
*Output     :  无
*Return     :  接收头接收到的数据
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
*Description:  获取接收头接收到的数据
*Input      :  IR_REMOT_POSITION_E index 接收头ID            
*Output     :  无
*Return     :  接收头接收到的数据
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
*Description:  将其他方式接收到的数据写到遥控和充电座所使用的变量 
*Input      :  uint8_t chan 接收通道
*              uint8_t val  接收到的数据        
*Output     :  无
*Return     :  无
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
