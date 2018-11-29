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
****函数备注：GPIO输入测试程序，PC4灌流方式连接LED1-蓝色，PB0灌流方式连接LED2-红色，PD2
              通过灌流方式连接LED3-绿色，PD4连接独立按键K1，PD4连接独立按键K1，PA2连接
              独立按键K2，PB3连接独立按键K3，通过不断读取。按键对应IO口的电平判断是否有
              按键按下，注意要使用软件消抖
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    //初始化3个LED的驱动端口  
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    GPIO_Init(LED2_GPIO_PORT, LED2_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    GPIO_Init(LED3_GPIO_PORT, LED3_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    //初始化3个按键接口
    GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_No_IT);//初始化按键，GPD4上拉输入
    GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_Mode_In_PU_No_IT);//初始化按键，GPA2上拉输入
    GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_No_IT);//初始化按键，GPB3上拉输入
    while(1)
    {
         if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PINS)==0)//读GPD4输入状态
         {
             Delay(0x3FFF);  //软件防抖
             if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PINS)==0)  //读GPD4输入状态
                GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//翻转GPC4输出状态
         }
         if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PINS)==0)//读GPA2输入状态
         {
             Delay(0x3FFF);  //软件防抖
             if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PINS)==0)  //读GPA2输入状态
                GPIO_ToggleBits(LED2_GPIO_PORT, LED2_GPIO_PINS);//翻转GPB0输出状态
         }
         if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_GPIO_PINS)==0)//读GPB3输入状态
         {
             Delay(0x3FFF);  //软件防抖
             if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_GPIO_PINS)==0)  //读GPB3输入状态
                GPIO_ToggleBits(LED3_GPIO_PORT, LED3_GPIO_PINS);//翻转GPD2输出状态
         }
    }
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
