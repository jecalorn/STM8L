/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程工程Demo
*******************************************************************************/
#include "stm8l15x.h"
//以下定义LED与按键的接口
#define LED1_GPIO_PORT  GPIOC      //BLUE
#define LED1_GPIO_PINS  GPIO_Pin_4
#define LED2_GPIO_PORT  GPIOB      //RED
#define LED2_GPIO_PINS  GPIO_Pin_0
#define LED3_GPIO_PORT  GPIOD      //GREEN
#define LED3_GPIO_PINS  GPIO_Pin_2

#define KEY1_GPIO_PORT  GPIOD      //K1
#define KEY1_GPIO_PINS  GPIO_Pin_4
#define KEY2_GPIO_PORT  GPIOA      //K2
#define KEY2_GPIO_PINS  GPIO_Pin_2
#define KEY3_GPIO_PORT  GPIOB      //K3
#define KEY3_GPIO_PINS  GPIO_Pin_3
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：按按键会触发中断，LED会翻转
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    //初始化3个LED的驱动端口  
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    GPIO_Init(LED2_GPIO_PORT, LED2_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    GPIO_Init(LED3_GPIO_PORT, LED3_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    //初始化3个按键接口
    GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPD4上拉中断输入
    GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPA2上拉中断输入
    GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，GPB3上拉中断输入
        
    EXTI_DeInit (); //恢复中断的所有设置 
    EXTI_SetPinSensitivity (EXTI_Pin_4,EXTI_Trigger_Falling);//外部中断4，下降沿触发，中断向量号12
    EXTI_SetPinSensitivity (EXTI_Pin_2,EXTI_Trigger_Falling);//外部中断2，下降沿触发，中断向量号10
    EXTI_SetPinSensitivity (EXTI_Pin_3,EXTI_Trigger_Falling);//外部中断3，下降沿触发，中断向量号11
    
    enableInterrupts();//使能中断
    while(1)
    {
      
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
