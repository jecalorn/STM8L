#include "stm8l15x.h"//STM8L051/151等系列共用库函数

//定义LED端口

#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4

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
****函数备注:CCO-PC4管脚会输出设定频率的信号，用示波器观察
********************************************************************************/
void main(void)
{
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_Low_Slow);//初始化CCO端口，输出/带上拉
   
  CLK_CCOConfig(CLK_CCOSource_HSE,CLK_CCODiv_16);//LSI做时钟源，16分频
  while (1)
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
