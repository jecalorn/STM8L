#include "stm8l15x.h"//STM8L051/151公用库函数

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
****函数说明：主函数
****入口参数:无
****出口参数:无
****函数备注:主函数，
              中断的优先级可以通过设置它的软件优先级来改变，默认优先级是3
              例程将外部中断1的软件优先级设置为1，比优先级3要低。所以当外部中断1
              发生并处理时，外部中断2/3是可以打断外部中断1的处理，优先处理外部中断
              2/3，处理完毕之后再返回来处理被打断的外部中断1。此为中断嵌套。
              当外部中断2/3先发生并处理时，外部中断1不能打断它们的处理。当然，
              相同软件优先级的外部中断2/3相互之间也不能打断。
              外部中断1现象---按按键1，底板LED1-蓝色被点亮，过会才熄灭；
              外部中断2现象---按按键2，扩展板LED2-红色被点亮，过会才熄灭；
              外部中断3现象---按按键3，扩展板LED3-绿色被点亮，过会才熄灭；
              先按按键1，外部中断1响应，LED1-蓝色被点亮，中断处理程序中延时，如果
              底板LED1还没熄灭时按按键2/3，则LED2/3被点亮，LED2/3
              延时一段时间后才熄灭，然后LED1延时一段时间后才熄灭。这说明发生了
              中断嵌套。
********************************************************************************/
void main(void)
{
  GPIO_Init(LED1_GPIO_PORT,LED1_GPIO_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
  GPIO_Init(LED2_GPIO_PORT,LED2_GPIO_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
  GPIO_Init(LED3_GPIO_PORT,LED3_GPIO_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
  
  GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，上拉输入，带中断
  GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，上拉输入，带中断
  GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_IT);//初始化按键，上拉输入，带中断
  
  
  EXTI_DeInit (); //恢复中断的所有设置 
  EXTI_SetPinSensitivity (EXTI_Pin_4,EXTI_Trigger_Falling);//外部中断4，下降沿触发，向量号12
  EXTI_SetPinSensitivity (EXTI_Pin_2,EXTI_Trigger_Falling);//外部中断2，下降沿触发，向量号10
  EXTI_SetPinSensitivity (EXTI_Pin_3,EXTI_Trigger_Falling);//外部中断3，下降沿触发，向量号11
  
  ITC_SetSoftwarePriority(EXTI4_IRQn,ITC_PriorityLevel_1);//设置外部中断4的软件优先级为1，比外部中断2/3默认的3级优先级要低。
    
  enableInterrupts();//使能中断
  
  while (1)//等待中断
  {
      
  }
}




#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
