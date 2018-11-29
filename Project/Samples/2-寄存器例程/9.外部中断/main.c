/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
#include"iostm8l152k4.h"

#define LED_PORT PC_ODR_ODR4
/*******************************************************************************
****入口参数：ms，延时的数目
****出口参数：无
****函数备注：延时函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void delay(unsigned int ms)
{
       unsigned char i;
       while(ms!=0)
       {
              for(i=0;i<250;i++)
              {}
              for(i=0;i<75;i++)
              {}
              ms--;
       }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：GPIO配置，配置PC4输出
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Init_GPIO(void)
{
       PC_DDR_DDR4 = 1;
       PC_CR1_C14 = 1; 
       PC_CR2_C24 = 0;
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：中断初始化，PD4映射到外部中断4，PD4端口带上拉输入，下降沿触发
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Init_ExInt(void)
{
    CPU_CCR=0X28;  //等级3
    EXTI_CONF=0x00;//PD4->EXTI4
    EXTI_CR2=0x02;//下降沿触发
    PD_DDR_DDR4=0;//PD4输入
    PD_CR1_C14=1;//PD4上拉
    PD_CR2_C24=1;//PD4中断使能
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：主函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
      Init_GPIO();
      Init_ExInt();
      asm("rim");//开中断，sim为关中断
      while(1)
      {
        
      }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：外部中断4响应函数，下降沿触发
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
#pragma vector= EXTI4_vector
__interrupt void EXTI4_IRQHandler(void)
{
   
    if(EXTI_SR1==0x10) //是否外部中断4触发
    {
        EXTI_SR1=0x10; //清除中断标志
        LED_PORT^=1;   //翻转LED

    }
}
/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/