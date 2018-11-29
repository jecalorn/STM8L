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
****函数备注：开发板上RXD-UT TXD-UR跳线帽短接，通过USB线连接计算机与开发板，打开
              计算机的串口调试助手软件，设置参数，先通过串口调试助手给开发板发送数据
              然后串口调试助手会接收到开发板发送回来的数据。使用前计算机需先安装CH340驱动。
              波特率115200时系统时钟需升高
              UT是CPU的USART的TXD-PC3，UR是USART的RXD-PC2；RXD/TXD是CH340的
              中断处理函数在文件IT.C，USART接收中断向量号为28
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    CLK_HSICmd(ENABLE);//开始内部高频RC 16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSI为系统时钟
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频，即1分频，16M
  
    //初始化USART的TXD RXD对应的2个管脚
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//初始化，带上拉输入，不带中断
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//初始化，推挽输出，快速  
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启USART时钟
    
    USART_Init(USART1,115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Rx|USART_Mode_Tx);//设置USART参数115200，8N1，接收/发送
    USART_ITConfig (USART1,USART_IT_OR,ENABLE);//使能接收中断,中断向量号为28
    USART_Cmd (USART1,ENABLE);//使能USART
    enableInterrupts(); //开启中断总开关
    
    while(1)
    {
      //GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED接口，带上拉推挽输出低
    }
    
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
