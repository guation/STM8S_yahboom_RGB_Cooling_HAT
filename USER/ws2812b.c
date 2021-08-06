#include "stm8s.h"
#include "ws2812b.h"
#include "console.h"

/*
�˴������stm8s003ƽ̨ @16M
�Ƶ����ʾ�������Ҫһ����ˢ�£�����16���ƾͱ���һ����ˢ��16����
������һ��һ���м��м����ˢ�£�������ֻ��һ�ظ�������
�����Ҫ�����Ѳ���Ҫ���ĵ�����Ϊ����0x000000����
*/
 
/*���¶������û����Ҫ���ж���*/
//#define BYTE_0(n)                 ((u8)((n) & (u8)0xFF))        /*!< Returns the low color of the 32-bit value */
//#define BYTE_1(n)                 ((u8)(BYTE_0((n) >> (u8)8)))  /*!< Returns the second color of the 32-bit value */
//#define BYTE_2(n)                 ((u8)(BYTE_0((n) >> (u8)16))) /*!< Returns the third color of the 32-bit value */
//#define BYTE_3(n)                 ((u8)(BYTE_0((n) >> (u8)24)))
//#define enableInterrupts()	EA=1
//#define disableInterrupts()	EA=0
 
//����ƽ̨����
#define _nop_() asm("nop")
 
#define delay1NOP()	_nop_();
#define delay2NOP()	delay1NOP();_nop_();
#define delay3NOP()	delay2NOP();_nop_();
#define	delay4NOP()	delay3NOP();_nop_();
#define	delay5NOP()	delay4NOP();_nop_();
#define	delay6NOP()	delay5NOP();_nop_();
#define	delay7NOP()	delay6NOP();_nop_();
#define	delay8NOP()	delay7NOP();_nop_();
#define	delay9NOP()	delay8NOP();_nop_();
#define	delay10NOP()	delay9NOP();_nop_();
#define	delay11NOP()	delay10NOP();_nop_();
#define	delay12NOP()	delay11NOP();_nop_();
#define	delay13NOP()	delay12NOP();_nop_();
#define	delay14NOP()	delay13NOP();_nop_();
#define	delay15NOP()	delay14NOP();_nop_();
#define	delay16NOP()	delay15NOP();_nop_();

 
//����
#define RGB_PIN_H() GPIOC->ODR |= 0x10;
#define RGB_PIN_L() GPIOC->ODR &= 0xEF;

#define RGB_WRITE_H() RGB_PIN_H();delay11NOP();RGB_PIN_L();delay1NOP();
#define RGB_WRITE_L() RGB_PIN_H();delay3NOP();RGB_PIN_L();delay10NOP();
//#define RGB_WRITE_R() {}

#define RGB_WRITE(x) if(x){RGB_WRITE_H();}else{RGB_WRITE_L();}
 
void Ws2812b_Configuration(void)
{
    GPIO_Init(GPIOC, (GPIO_Pin_TypeDef)GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);
    RGB_PIN_L();
}
void Ws2812b_Write(u32 color)//RGB
{
  u8 r=color>>0;
  u8 g=color>>8;
  u8 b=color>>16;
  //8λ��Ƭ������32λ��������ʱ��ϳ� ��Ϊ8λ������ٴ���ʱ��
  
  //GBR
  RGB_WRITE(g&0x80);
  RGB_WRITE(g&0x40);
  RGB_WRITE(g&0x20);
  RGB_WRITE(g&0x10);
  RGB_WRITE(g&0x08);
  RGB_WRITE(g&0x04);
  RGB_WRITE(g&0x02);
  RGB_WRITE(g&0x01);
  
  RGB_WRITE(b&0x80);
  RGB_WRITE(b&0x40);
  RGB_WRITE(b&0x20);
  RGB_WRITE(b&0x10);
  RGB_WRITE(b&0x08);
  RGB_WRITE(b&0x04);
  RGB_WRITE(b&0x02);
  RGB_WRITE(b&0x01);
  
  RGB_WRITE(r&0x80);
  RGB_WRITE(r&0x40);
  RGB_WRITE(r&0x20);
  RGB_WRITE(r&0x10);
  RGB_WRITE(r&0x08);
  RGB_WRITE(r&0x04);
  RGB_WRITE(r&0x02);
  RGB_WRITE(r&0x01);
}

/*********************************************����Ϊ�ײ�***********************************************/
 
//���õƵ���ɫ
//color:��ɫ���������ȣ�
//num  :�ܹ���led����
void RGB_Refresh(u32 color,u8 num){
  while(num--){
    u8 i=50;
    disableInterrupts();//�ر������жϱ������
    Ws2812b_Write(color);//ʱ��Ҫ��׼
    enableInterrupts();
    while(i--) delay16NOP();//50um���͸�λ��Ҫ��׼
  }
	
}
 
//��ɫ��ˮ��
//color:��ɫ���������ȣ�
//num  :�ܹ���led����
//speed:��ʱ����λms��
void RGB_Cycle(u32 color,u8 num,u16 speed)
{
	u8 i;
	for(i=1;i<=num;i++){		//������ɫ		
		RGB_Refresh(color,i);
		Delay_ms(speed);
	}
	for(i=1;i<=num;i++){		//��
		RGB_Refresh(0,i);
		Delay_ms(speed);
	}
}
 
//��ɫ������
//color:��ɫ���������ȣ�
//num  :�ܹ���led����
//speed:��ʱ����λms��
void RGB_Wave(u32 color,u8 num,u16 speed)
{
	u32 color_step=0;
	u32 color_temp = color;
	color_step |= (BYTE_2(color)?0x010000:0x000000);
	color_step |= (BYTE_1(color)?0x000100:0x000000);
	color_step |= (BYTE_0(color)?0x000001:0x000000);
    
	while(//�Ȱ���ɫ�����ȼ�����С
          BYTE_2(color_temp)>=BYTE_2(color_step) &&
              BYTE_1(color_temp)>=BYTE_1(color_step) &&
                  BYTE_0(color_temp)>=BYTE_0(color_step)
                      ){
                          color_temp-=color_step;
                      }
	
	while(		//��������	
          BYTE_2(color_temp)<0xff &&
              BYTE_1(color_temp)<0xff &&
                  BYTE_0(color_temp)<0xff
                      )	{
                          color_temp+=color_step;
                          RGB_Refresh(color_temp,num);
                          Delay_ms(speed);
                      }	
	while(//�����䰵
          BYTE_2(color_temp)>=BYTE_2(color_step) &&
              BYTE_1(color_temp)>=BYTE_1(color_step) &&
                  BYTE_0(color_temp)>=BYTE_0(color_step)
                      ){
                          color_temp-=color_step;
                          RGB_Refresh(color_temp,num);
                          Delay_ms(speed);
                      }
	RGB_Refresh(0,num);
}
//��ɫ��ˮ��
//color:��ɫ���������ȣ�
//num  :�ܹ���led����
//speed:��ʱ����λms��
//cnt  :��˸����
void RGB_Flash(u32 color,u8 num,u16 speed,u8 cnt)
{
	while(cnt--){
		RGB_Refresh(color,num);
		Delay_ms(speed);
		RGB_Refresh(0,num);
		Delay_ms(speed);
	}
}
 
/*********************************************END OF FILE**********************************************/