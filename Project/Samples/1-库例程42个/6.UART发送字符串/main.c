/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4发送字符串库函数例程
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
****入口参数：需要发送的字符串
****出口参数：无
****函数备注：USART发送函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//不为结束
        {
            USART_SendData8(USART1,*Str);     //发送数据 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
            Str++;//下一个数据
        }
}
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
    //初始化USART的TXD RXD对应的2个管脚
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//初始化，带上拉输入，不带中断
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//初始化，推挽输出，快速  
    
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启USART时钟
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，9600，8N1
    USART_Cmd (USART1,ENABLE);//使能USART
    while(1)
    {
        USART1_SendStr("蓝旗嵌入式\r\n"); //发送字符串，末尾换行
    }
    
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
