# STM8S_yahboom_RGB_Cooling_HAT
本项目为[亚博树莓派智能贴身管家](https://www.yahboom.com/study/RGB_Cooling_HAT)STM8S003F3U6单片机三方固件，基于[ST官方](https://www.st.com/)STM8S标准外设库[en.stsw-stm8069_v2.3.1.zip](https://www.st.com/content/st_com/zh/products/embedded-software/mcu-mpu-embedded-software/stm8-embedded-software/stsw-stm8069.html)制作，作者挂神。   
## 项目目的：
1.修复原机固件在400K时钟下通信异常的BUG。  
2.修复收到错误数据包造成的设备假死。  
3.修改风扇上电状态，避免因驱动程序未生效造成的树莓派机身过热。  
4.增加更多RGB灯光效果
## 项目基本情况：
#### 1.引脚定义:
PB4--SCL  
PB5--SDA  
PC3--呼吸灯PWM  
PC4--RGB灯  
PD4--风扇PWM  
#### 2.框架状态:
- [x] I2C通信
- [x] 设置呼吸灯
- [x] RGB灯通信
- [x] 设置风扇转速
- [ ] 温度测量
#### 3.计划任务：
- [ ] RGB灯
  - [ ] 点亮RGB灯
  - [ ] 预设RGB灯效
  - [ ] 自定义RGB灯效
- [x] 风扇
  - [x] 默认上电状态
  - [x] 设置转速
- [x] 呼吸灯
## I2C通讯协议
待完善
