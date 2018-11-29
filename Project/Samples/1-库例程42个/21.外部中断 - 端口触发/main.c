/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程工程Demo
*******************************************************************************/
#include "stm8l15x.h"
//定义LED与按键接口
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4
#define KEY_GPIO_PORT  GPIOD
#define KEY_GPIO_PINS  GPIO_Pin_4
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：按按键会触发中断，LED会翻转
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//GPIO初始化
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPD4上拉中断输入
    
    EXTI_DeInit (); //恢复中断的所有设置 
    EXTI_SelectPort(EXTI_Port_D);//选择端口D，中断向量号7
    EXTI_SetPortSensitivity(EXTI_Port_D,EXTI_Trigger_Falling);//端口D下降沿触发
    EXTI_SetHalfPortSelection(EXTI_HalfPort_D_MSB,ENABLE);//端口D的高四位中断使能
    enableInterrupts();//使能中断
    while(1)
    {
      
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
