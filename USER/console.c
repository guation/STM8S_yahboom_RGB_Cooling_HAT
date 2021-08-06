#include "console.h"
#include "stm8s_it.h"

typedef struct{
//  unsigned char flag;
  unsigned char addr;
  unsigned char data;
}task_struct;

#define TASK_SIZE 20

task_struct task[TASK_SIZE];
uint32_t task_index1=0,task_index2=0;
volatile uint8_t fast_reg[9];

void Delay_ms(u16 ms)//ms延时函数
{
  count=ms;
  while(count) /*IWDG_ReloadCounter()*/; //计数时喂狗防止因为占用cpu时间过长导致重启
}

void console_Init(void){
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
}

void fast_reg_Init(void){
  for(u8 i=0;i<8;i++){
    fast_reg[i]=console_read_byte(i);
  }
  if(console_read_byte(8)){
    fast_reg[8]=0x00;
  }else{
    fast_reg[8]=0x01;
  }
  set_fan(fast_reg[8]);
}

void set_fan(u8 data){
  switch(data){
  case 0x00:
    TIM2_SetCompare1(0);
    break;
  case 0x01:
    TIM2_SetCompare1(799);
    break;
  case 0x02:
    TIM2_SetCompare1(399);
    break;
  case 0x03:
    TIM2_SetCompare1(499);
    break;
  case 0x04:
    TIM2_SetCompare1(549);
    break;
  case 0x05:
    TIM2_SetCompare1(599);
    break;
  case 0x06:
    TIM2_SetCompare1(649);
    break;
  case 0x07:
    TIM2_SetCompare1(699);
    break;
  case 0x08:
    TIM2_SetCompare1(749);
    break;
  case 0x09:
    TIM2_SetCompare1(799);
    break;
  default:
    break;
  }
}

void fast_reg_save(void){
  for(u8 i=0;i<8;i++){
    console_write_byte(i,fast_reg[i]);
    Delay_ms(1);
  }
}

void console_write_byte(u16 addr, u8 data){
  if(addr > 0x027F) return;
  FLASH_ProgramByte(FLASH_DATA_START_PHYSICAL_ADDRESS + addr, data);
}

uint8_t console_read_byte(u16 addr){
  if(addr > 0x027F) return 0x00;
  return FLASH_ReadByte(FLASH_DATA_START_PHYSICAL_ADDRESS + addr);
}

uint8_t set_task(u8 addr, u8 data){
  if((task_index1-task_index2)==TASK_SIZE)
    return 0;
  uint8_t tmp=task_index1%TASK_SIZE;
  task[tmp].addr=addr;
  task[tmp].data=data;
  task_index1++;
  return 1;
}

uint8_t get_task(u8* addr,u8* data){
  if(task_index1==task_index2)
    return 0;
  uint8_t tmp=task_index2%TASK_SIZE;
  *addr=task[tmp].addr;
  *data=task[tmp].data;
  task_index2++;
  return 1;
}

uint8_t read_reg(u8 addr){
  if(addr<=0x08){
    return fast_reg[addr];
  }else if(addr==0x09){
    return console_read_byte(0x0008);
  }else if(addr==0x0a){
    return 0x00;
  }else if(addr==0x0b){
    return console_read_byte(0x0009);
  }else if(addr==0x0c){
    return console_read_byte(0x000a);
  }else if(addr<=0x0f){
    return 0x00;
  }else{
    return console_read_byte((addr-0x0010)*read_reg(0x0c)+0x000b);
  }
}

/*
uint8_t set_task(u8 addr, u8 data){
  for(int i=0;i<TASK_SIZE;i++){
    if(task[i].flag==0){
      task[i].flag=1;
      task[i].addr=addr;
      task[i].data=data;
      return 1;
    }
  }
  return 0;
}

uint8_t get_task(u8* addr,u8* data){
  if(task[0].flag==0) return 0;
  *addr=task[0].addr;
  *data=task[0].data;
  for(int i=1,i<TASK_SIZE;i++){
    if(task[i].flag==1){
      task[i-1].addr=task[i].addr;
      task[i-1].data=task[i].data;
    }else{
      task[i-1].flag=0;
      return 1;
    }
  }
  task[TASK_SIZE].flag=0;
  return 1;
}*/