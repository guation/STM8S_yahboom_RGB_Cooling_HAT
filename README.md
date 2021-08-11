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
<table border=0 cellpadding=0 cellspacing=0 width=902 style='border-collapse:
 collapse;table-layout:fixed;width:676pt'>
 <col width=83 span=2 style='mso-width-source:userset;mso-width-alt:2656;
 width:62pt'>
 <col width=215 style='mso-width-source:userset;mso-width-alt:6880;width:161pt'>
 <col width=521 style='mso-width-source:userset;mso-width-alt:16672;width:391pt'>
 <tr height=33 style='mso-height-source:userset;height:24.75pt'>
  <td colspan=4 height=33 class=xl6611337 width=902 style='height:24.75pt;
  width:676pt'>树莓派智能贴身管家单片机I2C通讯协议（I2C地址：0x0e）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'></td>
  <td class=xl1511337>寄存器</td>
  <td class=xl1511337>数据值</td>
  <td class=xl1511337>备注</td>
 </tr>
 <tr height=47 style='mso-height-source:userset;height:35.25pt'>
  <td rowspan=4 height=113 class=xl1511337 style='height:84.75pt'>R<font
  class="font611337">GB灯点亮</font></td>
  <td class=xl1511337>0<font class="font611337">x00</font></td>
  <td class=xl1511337>0<font class="font611337">x00,0x01,0x02,0xFF</font></td>
  <td class=xl6511337 width=521 style='width:391pt'>选择灯：0x00不操作灯<font
  class="font811337">,</font><font class="font011337">0x0</font><font
  class="font811337">1</font><font class="font011337">操作第一个灯，0x0</font><font
  class="font811337">2</font><font class="font011337">操作第二个灯，0x0</font><font
  class="font811337">3</font><font class="font011337">操作第三个灯，0xFF操作所有灯</font></td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font611337">x01</font></td>
  <td class=xl1511337>0<font class="font611337">x00~0xFF</font></td>
  <td class=xl1511337>R值（0~255）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font611337">x02</font></td>
  <td class=xl1511337>0<font class="font611337">x00~0xFF</font></td>
  <td class=xl1511337>G值（0~255）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font611337">x03</font></td>
  <td class=xl1511337>0<font class="font611337">x00~0xFF</font></td>
  <td class=xl1511337>B值（0~255）<font class="font711337"><span
  style='mso-spacerun:yes'>&nbsp;&nbsp;</span></font></td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td rowspan=4 height=116 class=xl1511337 style='height:87.0pt'>R<font
  class="font711337">GB灯特效</font></td>
  <td class=xl1511337>0<font class="font611337">x04</font></td>
  <td class=xl1511337>0x00,0x01,0x02,0x03,0x04</td>
  <td class=xl1511337>RGB灯模式：0x00流水灯，0x01呼吸灯,0x02跑马灯，0x03彩虹灯，0x04炫彩<span
  style='display:none'>灯</span></td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font611337">x05</font></td>
  <td class=xl1511337>0x01,0x02,0x03</td>
  <td class=xl1511337>RGB速度：0x01低速，0x02中速（默认），0x03高速</td>
 </tr>
 <tr height=50 style='mso-height-source:userset;height:37.5pt'>
  <td height=50 class=xl1511337 style='height:37.5pt'>0<font class="font611337">x06</font></td>
  <td class=xl1511337>0x00~0x06</td>
  <td class=xl6511337 width=521 style='width:391pt'>流水灯/呼吸灯颜色：0x00红色，0x01绿色（默认），0x02蓝色，0x03黄色，0x04紫色，0x05青色，0x06白色</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font611337">x07</font></td>
  <td class=xl1511337>0x00</td>
  <td class=xl1511337>0x00关闭所有灯,0x01开启RGB灯,0x02开启点灯,0x03自定义灯效</td>
 </tr>
 <tr height=47 style='mso-height-source:userset;height:35.25pt'>
  <td height=47 class=xl1511337 style='height:35.25pt'>风扇</td>
  <td class=xl1511337>0<font class="font611337">x08</font></td>
  <td class=xl1511337>0x00~0x09</td>
  <td class=xl6511337 width=521 style='width:391pt'>风扇速度控制：0x00关闭，0x01全速，0x02：20%速度，0x03：30%速度，…，0x09：90%速度</td>
 </tr>
 <tr height=24 style='mso-height-source:userset;height:18.0pt'>
  <td height=24 class=xl1511337 style='height:18.0pt'>风扇上电</td>
  <td class=xl1511337>0x09</td>
  <td class=xl1511337>0x00<font class="font811337">,</font><font
  class="font011337">0x0</font><font class="font811337">1</font></td>
  <td class=xl6511337 width=521 style='width:391pt'>风扇速度控制：0x00全速，0x01关闭</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>保存灯效</td>
  <td class=xl1511337>0x0<font class="font811337">a</font></td>
  <td class=xl1511337>0x01,0x02</td>
  <td class=xl6511337 width=521 style='width:391pt'>0x01保存0x00~0x07寄存器,0x02清除0x00~0x07寄存器</td>
 </tr>
 <tr height=38 style='mso-height-source:userset;height:28.5pt'>
  <td height=38 class=xl6511337 width=83 style='height:28.5pt;width:62pt'>自定义灯效长度</td>
  <td class=xl1511337>0<font class="font911337">x0b</font></td>
  <td class=xl1511337>n=[0,150]</td>
  <td class=xl6511337 width=521 style='width:391pt'>0不点灯<font class="font911337">,1~150对应长度循环</font></td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>设置灯效页</td>
  <td class=xl1511337>0<font class="font911337">x0c</font></td>
  <td class=xl1511337>m=[0,2]</td>
  <td class=xl6511337 width=521 style='width:391pt'>0<font class="font911337">~2页</font></td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>软件复位</td>
  <td class=xl1511337>0<font class="font1111337">x0d</font></td>
  <td class=xl1511337>0x0<font class="font1111337">1</font></td>
  <td class=xl6511337 width=521 style='width:391pt'>重启单片机</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>保留</td>
  <td class=xl1511337>0<font class="font911337">x0</font><font
  class="font1011337">e</font><font class="font911337">~0x0f</font></td>
  <td class=xl1511337>0<font class="font911337">x00</font></td>
  <td class=xl1511337></td>
 </tr>
 <tr height=43 style='mso-height-source:userset;height:32.25pt'>
  <td rowspan=4 height=109 class=xl6711337 width=83 style='height:81.75pt;
  width:62pt'>第n=60m+1组灯</td>
  <td class=xl1511337>0<font class="font911337">x10</font></td>
  <td class=xl1511337>0d000_0_0000~0d111_1_1111</td>
  <td class=xl6511337 width=521 style='width:391pt'>第7~5位0/1对应第1~3个灯灭/亮，第4位0/1对应点亮时钟分度值0.1s/1s，第3~0位0000~1111对应时钟长度1-16倍时钟分度值</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font911337">x11</font></td>
  <td class=xl1511337>0x00~0xFF</td>
  <td class=xl1511337>R值（0~255）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font911337">x12</font></td>
  <td class=xl1511337>0x00~0xFF</td>
  <td class=xl1511337>G值（0~255）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font911337">x13</font></td>
  <td class=xl1511337>0x00~0xFF</td>
  <td class=xl1511337>B值（0~255）<font class="font711337"><span
  style='mso-spacerun:yes'>&nbsp;&nbsp;</span></font></td>
 </tr>
 <tr height=42 style='mso-height-source:userset;height:31.5pt'>
  <td height=42 class=xl1511337 style='height:31.5pt'>…</td>
  <td class=xl1511337>…</td>
  <td class=xl1511337>…</td>
  <td class=xl6511337 width=521 style='width:391pt'>0x09,0x0b,0x0c,0x10~0xff寄存器操作间隔需大于等于1ms,0x0a寄存器操作间隔需大于等于10ms</td>
 </tr>
 <tr height=44 style='mso-height-source:userset;height:33.0pt'>
  <td rowspan=4 height=110 class=xl6711337 width=83 style='height:82.5pt;
  width:62pt'>第n=60m+60组灯</td>
  <td class=xl1511337>0xfc</td>
  <td class=xl1511337>0d000_0_0000~0d111_1_1111</td>
  <td class=xl6511337 width=521 style='width:391pt'>第7~5位0/1对应第1~3个灯灭/亮，第4位0/1对应点亮时钟分度值0.1s/1s，第3~0位0000~1111对应时钟长度1-16倍时钟分度值</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font911337">xfd</font></td>
  <td class=xl1511337>0x00~0xFF</td>
  <td class=xl1511337>R值（0~255）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font911337">xfe</font></td>
  <td class=xl1511337>0x00~0xFF</td>
  <td class=xl1511337>G值（0~255）</td>
 </tr>
 <tr height=22 style='mso-height-source:userset;height:16.5pt'>
  <td height=22 class=xl1511337 style='height:16.5pt'>0<font class="font911337">xff</font></td>
  <td class=xl1511337>0x00~0xFF</td>
  <td class=xl1511337>B值（0~255）<font class="font711337"><span
  style='mso-spacerun:yes'>&nbsp;&nbsp;</span></font></td>
 </tr>
</table>

