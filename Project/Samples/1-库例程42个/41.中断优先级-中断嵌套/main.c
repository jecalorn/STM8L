#include "stm8l15x.h"//STM8L051/151���ÿ⺯��

//���¶���LED�밴���Ľӿ�
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
****������ע:��������
              �жϵ����ȼ�����ͨ����������������ȼ����ı䣬Ĭ�����ȼ���3
              ���̽��ⲿ�ж�1��������ȼ�����Ϊ1�������ȼ�3Ҫ�͡����Ե��ⲿ�ж�1
              ����������ʱ���ⲿ�ж�2/3�ǿ��Դ���ⲿ�ж�1�Ĵ������ȴ����ⲿ�ж�
              2/3���������֮���ٷ�����������ϵ��ⲿ�ж�1����Ϊ�ж�Ƕ�ס�
              ���ⲿ�ж�2/3�ȷ���������ʱ���ⲿ�ж�1���ܴ�����ǵĴ�����Ȼ��
              ��ͬ������ȼ����ⲿ�ж�2/3�໥֮��Ҳ���ܴ�ϡ�
              �ⲿ�ж�1����---������1���װ�LED1-��ɫ�������������Ϩ��
              �ⲿ�ж�2����---������2����չ��LED2-��ɫ�������������Ϩ��
              �ⲿ�ж�3����---������3����չ��LED3-��ɫ�������������Ϩ��
              �Ȱ�����1���ⲿ�ж�1��Ӧ��LED1-��ɫ���������жϴ����������ʱ�����
              �װ�LED1��ûϨ��ʱ������2/3����LED2/3��������LED2/3
              ��ʱһ��ʱ����Ϩ��Ȼ��LED1��ʱһ��ʱ����Ϩ����˵��������
              �ж�Ƕ�ס�
********************************************************************************/
void main(void)
{
  GPIO_Init(LED1_GPIO_PORT,LED1_GPIO_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
  GPIO_Init(LED2_GPIO_PORT,LED2_GPIO_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
  GPIO_Init(LED3_GPIO_PORT,LED3_GPIO_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
  
  GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ���������������룬���ж�
  GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ���������������룬���ж�
  GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ���������������룬���ж�
  
  
  EXTI_DeInit (); //�ָ��жϵ��������� 
  EXTI_SetPinSensitivity (EXTI_Pin_4,EXTI_Trigger_Falling);//�ⲿ�ж�4���½��ش�����������12
  EXTI_SetPinSensitivity (EXTI_Pin_2,EXTI_Trigger_Falling);//�ⲿ�ж�2���½��ش�����������10
  EXTI_SetPinSensitivity (EXTI_Pin_3,EXTI_Trigger_Falling);//�ⲿ�ж�3���½��ش�����������11
  
  ITC_SetSoftwarePriority(EXTI4_IRQn,ITC_PriorityLevel_1);//�����ⲿ�ж�4��������ȼ�Ϊ1�����ⲿ�ж�2/3Ĭ�ϵ�3�����ȼ�Ҫ�͡�
    
  enableInterrupts();//ʹ���ж�
  
  while (1)//�ȴ��ж�
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
