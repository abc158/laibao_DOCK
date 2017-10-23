/********************************************************************************************************//**
 * @file    clib_min.c
 * @brief   print for debug
 * @author  lzh
 * @version V0.00
 * @date:   2016-09-02
 * @note
 * Copyright (C) 2016 Amicro Semiconductor Inc. All rights reserved.
 ************************************************************************************************************/
 
int * tube = (int *)0x4008830c;
int putchar (int ch)
{
  *tube = ch;
  return ch;
}

void putd (int nu)
{

}


void puth (unsigned int nu)
{
  unsigned int temp;
  int i;
  for(i=0;i<8;i++){
	temp = 0;
    temp = nu >> (4*(7-i));
    temp = temp%16;
    if(temp < 0xa)
      temp = temp + 48;
    else
      temp = temp + 55;
    putchar(temp);
  }
}

void print(char a[],int nu)
{
  char *i;
  i = &a[0];


  while(*i != '\0'  ){
    if(*i == '%'){
      i++;
      if(*i == 'd'){
    	  putd(nu);
      }else if(*i == 'h'){
    	  puth(nu);
      }
    }else {
      putchar(*i);
    }
    i++;
  }
  putchar('\n');
}

void finish(){
	*tube = 0x4;
}

void pass(){
	*tube = 0x5;
}

void fail(){
	*tube = 0x6;
}

void cpu_delay(unsigned int tns){
	int i = 0;
	while(i < tns){
		__asm("NOP");
		i++;
	}
}
