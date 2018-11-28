


#include "stm8l15x.h"
#include "gpio.h"



/*****************************************************************************
 函 数 名  : key_init
 功能描述  : 按键初始化函数，通过中断，模拟
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void key_init()
{

    GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPD4上拉中断输入
    GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPD4上拉中断输入

    EXTI_DeInit (); //恢复中断的所有设置 

    EXTI_SelectPort(EXTI_Port_D);//选择端口D，中断向量号7
    EXTI_SetPortSensitivity(EXTI_Port_D,EXTI_Trigger_Rising_Falling);//端口D下降沿触发
    EXTI_SetHalfPortSelection(EXTI_HalfPort_D_MSB,ENABLE);//端口D的高四位中断使能


    EXTI_SelectPort(EXTI_Port_B);//选择端口D，中断向量号7
    EXTI_SetPortSensitivity(EXTI_Port_B,EXTI_Trigger_Rising_Falling);//端口D下降沿触发
    EXTI_SetHalfPortSelection(EXTI_HalfPort_B_LSB,ENABLE);//端口D的高四位中断使能

    enableInterrupts();//使能中断

}


void key_PD_irq_handler()
{
    EXTI_ClearITPendingBit (EXTI_IT_PortD);//清除中断标志
    {

        if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PINS)==0)//判断按键1是否按下
        {
            extern void test_simulate_key3_press();
            test_simulate_key3_press();
        }
    }

}

void key_PB_irq_handler()
{
    EXTI_ClearITPendingBit (EXTI_IT_PortB);//清除中断标志
    {

        if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_GPIO_PINS)==0)//判断按键3是否按下
        {
            extern void test_simulate_key1_press();
            test_simulate_key1_press();
        }
    }

}



