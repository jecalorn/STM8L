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
****函数备注：不精确延时函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：系统上电默认时钟为HSI/8=2M，根据LED1闪烁频率来判断时钟源切换是否成功
              采用方法的是手动切换时钟源
****版权信息：蓝旗嵌入式系统,
*******************************************************************************/
int main( void )
{
    uint8_t i;  
   
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED接口，带上拉推挽输出低
    
    
    
    //以下为HSI为系统时钟 16M
    CLK_HSICmd(ENABLE);//开始内部高频RC 16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSI为系统时钟
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频，即1分频，16M
    
    for(i=0;i<10;i++)//翻转LED
    {
       GPIO_ToggleBits(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS);
       Delay(0xFFFF);
    }
    
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);//8分频，2M
    
    for(i=0;i<10;i++)//翻转LED
    {
       GPIO_ToggleBits(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS);
       Delay(0xFFFF);
    }
    
    //以下为HSE为系统时钟    16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);//系统主时钟为HSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//等待HSE准备就绪
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//使能切换
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_HSE)//如果切换成功
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);//2分频,8M
       for(i=0;i<10;i++)
       {
          GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);
          Delay(0xFFFF);
        }
    }
    
    //以下为LSE为系统时钟    32768
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);//系统主时钟为LSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_LSERDY)==RESET);//等待LSE准备就绪
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//使能切换
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSE)//如果切换成功
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//
       for(i=0;i<2;i++)
       {
          GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);
          Delay(0x0FFF);
        }
    }
    
    
    //以下为LSI做系统时钟 32K
    while(1)
    {
        CLK_LSICmd (ENABLE);    //使能LSI
        CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//LSI为系统时钟
        while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY)==RESET);//等待LSI准备就绪
        CLK_SYSCLKSourceSwitchCmd (ENABLE);//使能切换
        if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSI)//如果切换成功
       {
          
          CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频  
          for(i=0;i<2;i++)
          {
             GPIO_ToggleBits(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS);
             Delay(0x0FFF);
          }  
       }
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
