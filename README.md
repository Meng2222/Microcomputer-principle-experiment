# 微机原理实验相关资料仓库
## Description
   本仓库中包含微机原理实验相资料，包括代码，部分芯片dataSheet和实验装置的原理图
### 1.  键盘与LED文件夹中包含实验相关代码
   大部分代码主要为驱动层代码，应用层的代码主要在main.c,basicIO.c,P1IO.c,89C51_it.c,brushDcMotor.c和stepMotor.c中
#### main.c:包含主函数相关代码
#### HD7279.c:包含HD7279驱动程序
#### delay.c:包含延时函数
#### basicIO.c:包含简单IO输入输出部分程序
#### decode.c:包含译码器实验部分代码
#### p1IO.c:包含P1口IO部分实验代码
#### dataMemory.c:包含数据部分代码
#### timer.c:包含定时器部分代码
#### 89C51_it.c:包含外部中断和中断服务函数
#### usart.c: 串口部分的代码
#### 8255.c:可编程IO8255代码
#### 8254.c:可编程定时器8254部分代码
#### 8251A.c:可编程串口8251A（未完成）
#### CS5550.c:AD转换CS5550驱动程序
#### pwm.c: 单片机pwm部分代码
#### brushDcMotor.c:直流电机速度控制代码
#### stepMotor.c: 步进电机控制代码
#### speaker.c:扬声器部分代码（未完成）
#### gpio.c:单片机通用IO部分的代码
### 2. DataSheet文件夹中包含大部分实验装置上芯片的DataSheet，书中对芯片的介绍并不全面，对于芯片详细的描述还是要参考DataSheet
### 3.Schematic文件夹中包含实验装置图
