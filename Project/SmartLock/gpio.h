/******************************************************************************

                  版权所有 (C), 2010--2100, BM TECH

 ******************************************************************************
  文 件 名   : gpio.h
  版 本 号   : 初稿
  作    者   : belife
  生成日期   : 2018年11月28日
  最近修改   :
  功能描述   : GPIO 配置头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 创建文件

******************************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm8l15x.h"



#define KEY1_GPIO_PORT  GPIOD
#define KEY1_GPIO_PINS  GPIO_Pin_4

//不能配置为中断 PORTA
#define KEY2_GPIO_PORT  GPIOA
#define KEY2_GPIO_PINS  GPIO_Pin_2

#define KEY3_GPIO_PORT  GPIOB
#define KEY3_GPIO_PINS  GPIO_Pin_3




#endif /* __GPIO_H__ */


