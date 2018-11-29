/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"  //包含头文件，头文件里面要选择STM8L15X_MD
//以下定义LED与按键的接口
#define LED1_GPIO_PORT  GPIOC      //BLUE
#define LED1_GPIO_PINS  GPIO_Pin_4
#define LED2_GPIO_PORT  GPIOB      //RED
#define LED2_GPIO_PINS  GPIO_Pin_0
#define LED3_GPIO_PORT  GPIOD      //GREEN
#define LED3_GPIO_PINS  GPIO_Pin_2

#define KEY1_GPIO_PORT  GPIOD
#define KEY1_GPIO_PINS  GPIO_Pin_4
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
****函数备注：GPIO测试程序，PC4灌流方式连接LED1-蓝色，PB0灌流方式连接LED2-红色，PD2
              通过灌流方式连接LED3-绿色，主循环里面翻转3个LED的驱动端口的输出电平状态
              即可控制3个LED闪烁。输出低电平，LED被点亮，输出高电平LED被熄灭。
****版权信息：蓝旗嵌入式系统--无锡市纳诺物联网科技有限公司
*******************************************************************************/
int main( void )
{
  //初始化3个LED的驱动端口  
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    GPIO_Init(LED2_GPIO_PORT, LED2_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    GPIO_Init(LED3_GPIO_PORT, LED3_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//带上拉，推挽输出低电平
    Delay(0xFFFF);
    while(1)
    {
        GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//翻转PC4电平，实现闪烁
        Delay(0xFFFF);
        GPIO_ToggleBits(LED2_GPIO_PORT, LED2_GPIO_PINS);//翻转PB0电平，实现闪烁
        Delay(0xFFFF);
        GPIO_ToggleBits(LED3_GPIO_PORT, LED3_GPIO_PINS);//翻转PD2电平，实现闪烁
        Delay(0xFFFF);
    }

}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
