#include "stm8l15x.h"//STM8L051/151��ϵ�й��ÿ⺯��

//����LED�˿�
#define LED1_PORT  GPIOC
#define LED1_PINS  GPIO_Pin_4

/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע������ȷ��ʱ����
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
****����˵����������
****��ڲ���:��
****���ڲ���:��
****������ע:LED��һ��Ƶ����˸
********************************************************************************/
void main(void)
{
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);  
  GPIO_Init(LED1_PORT,LED1_PINS,GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�˿�

  while (1)
  {  
    GPIO_ToggleBits(LED1_PORT,LED1_PINS);//��תLED�˿�

    delay_ms(1000);
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
