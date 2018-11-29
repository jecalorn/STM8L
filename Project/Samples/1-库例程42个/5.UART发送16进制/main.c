/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4  USART发送16进制数据库函数例程
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
****函数备注：开发板上RXD-UT TXD-UR跳线帽短接，通过USB线连接计算机与开发板，打开
              计算机的串口调试助手软件，设置参数，可以接收到开发板发送的HEX格式的
              数据。使用前计算机需先安装CH340驱动。
              UT是CPU的USART的TXD-PC3，UR是USART的RXD-PC2；RXD/TXD是CH340的
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    uint8_t i;
    //初始化USART对应的2个管脚
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//初始化，带上拉输入，不带中断
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//初始化，推挽输出，快速
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启USART时钟,所有外设时钟初始默认关闭，使用外设前需开启对应外设时钟
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//设置USART参数9600，8N1
    USART_Cmd (USART1,ENABLE);//使能USART
    while(1)
    {
        USART_SendData8(USART1,i);//发送16进制
        while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送
        i++;
    }
    
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
