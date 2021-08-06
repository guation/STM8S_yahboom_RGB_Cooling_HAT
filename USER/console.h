#ifndef __CONSOLE_H
#define __CONSOLE_H
#include "stm8s.h"

//extern task_struct task[TASK_SIZE];
extern volatile uint8_t fast_reg[9];

void console_Init(void);
void console_write_byte(u16 addr, u8 data);
uint8_t console_read_byte(u16 addr);
uint8_t set_task(u8 addr, u8 data);
uint8_t get_task(u8* addr, u8* data);
uint8_t read_reg(u8 addr);
void Delay_ms(u16 ms);
void fast_reg_save(void);
void fast_reg_Init(void);
void set_fan(u8 data);

#endif