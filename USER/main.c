/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_it.h"
#include "ws2812b.h"
#include "console.h"

/* Private defines -----------------------------------------------------------*/
#define WDG() IWDG_ReloadCounter() //255ms之内需要喂狗一次
#if 0
#define I2C_ADDR 0x0e
#else
#define I2C_ADDR 0x0d
#endif
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  /* Infinite loop */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//16MHz
  
  GPIO_Init(GPIOD,GPIO_PIN_4,GPIO_MODE_OUT_PP_LOW_FAST);//风扇
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 799);//20kHz这个频率没有噪音
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);//399-799 低于50%PWM风扇不转
  TIM2_OC1PreloadConfig(ENABLE);
  TIM2_Cmd(ENABLE);
  
  GPIO_Init(GPIOC,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_FAST);//LED
  TIM1_TimeBaseInit(0x0001, TIM1_COUNTERMODE_UP, 799,0x00);//10kHz
  TIM1_OC3Init(TIM1_OCMODE_PWM1, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE, 0, TIM1_OCPOLARITY_HIGH, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_RESET, TIM1_OCNIDLESTATE_RESET);
  TIM1_OC3PreloadConfig(ENABLE);
  TIM1_Cmd(ENABLE);
  TIM1_CtrlPWMOutputs(ENABLE);
  
  TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249);//1kHz
  TIM4_ARRPreloadConfig(ENABLE);//使能自动重装
  TIM4_ITConfig(TIM4_IT_UPDATE , ENABLE);//数据更新中断
  TIM4_Cmd(ENABLE);
  
  I2C_Init(I2C_MAX_FAST_FREQ, I2C_ADDR<<1, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, I2C_MAX_INPUT_FREQ);//原机0x0d此处地址需要写作0x1a
  I2C_ITConfig((I2C_IT_TypeDef)(I2C_IT_ERR | I2C_IT_EVT | I2C_IT_BUF), ENABLE);
  /*
  IWDG_Enable();
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  IWDG_SetReload((uint8_t)(0xFF));//255ms
  IWDG_ReloadCounter();
  */
  Ws2812b_Configuration();
  console_Init();
  fast_reg_Init();
  
  enableInterrupts();
  
  //RGB_Refresh(0x000000, 3);
  
  while (1)
  {
    u8 addr,data;
    if(get_task(&addr,&data)){
      switch(addr){
      case 0x08://风扇寄存器
        fast_reg[8]=data;
        set_fan(data);
        break;
      case 0x09://风扇上电寄存器
        console_write_byte(0x0008, data);
        Delay_ms(1);
        break;
      case 0x0d:
        if(data==0x01){
          WWDG->CR = 0x80;
          Delay_ms(1000);
        }
        break;
      default:
        break;
      }
    }else{
      Delay_ms(1);
    }
    //RGB_Refresh(0x000000, 3);
    //Delay_ms(1000);
    //RGB_Refresh(0x000000, 3);
    //Delay_ms(1000);
    //RGB_Flash(COLOR_ORANGE,3,200,100);
    //RGB_Wave(0x00ffff,3,10);
  }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
