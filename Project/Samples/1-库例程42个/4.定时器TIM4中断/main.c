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
****函数备注：大约1SLED1会翻转一次，具体原理请见代码注释；中断处理函数在文件
              it.c里面，TIM4的中断向量号是25
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED1，GPC4低速推挽输出
    CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //使能外设时钟，STM8L默认所有外设时钟初始时关闭，使用前徐开启
       
    TIM4_TimeBaseInit(TIM4_Prescaler_128, 0xff);//16M/8/128=15.625K，0xff=255,255*（1/15.625）=0.01632S，大约61次中断是1S
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);//向上溢出中断，中断函数向量号为25
    TIM4_Cmd(ENABLE);//使能
    
    enableInterrupts();//使能中断总开关
    
    while(1)
    {
      
    }
    
    
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
