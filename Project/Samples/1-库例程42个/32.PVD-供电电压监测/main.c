/*******************************************************************************
****��Ȩ��Ϣ������Ƕ��ʽϵͳ http://lenchimcu.taobao.com
*******************************************************************************/
#include "stm8l15x.h" //STM8L151/051���ÿ⺯��
#include "stdio.h"
//����LED�������˿�
#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4
#define KEY_PORT  GPIOD
#define KEY_PINS  GPIO_Pin_4

uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����ʱ����
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
****������ע:PVD-Power Voltage Detector,ϵͳ�����ѹ��⣬���VDD��ѹ�����VDD��ѹ
             �����趨����ֵ����������Ӧ����
             �����У����VDD��ѹ������ֵ����LEDϨ�����VDD��ѹ������ֵ��LED��������
             ���̲������ַ�ʽ���жϷ�ʽ���ѯPVD״̬��ʽ�����߲�Ҫͬʱʹ�ã�����
             ʵ����������
********************************************************************************/
void main(void)
{  
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�˿�
  GPIO_SetBits (LED_PORT,LED_PINS);

  
  PWR_DeInit();//��ʼ��
  PWR_PVDLevelConfig (PWR_PVDLevel_3V05);//��ֵΪ3.05V
  PWR_PVDCmd(ENABLE);//PVDʹ��
  
  //ע�͵��Ĳ���ΪPVD�жϷ�ʽ�����VDD��ѹ������ֵ�������PVD�ж�
  //PWR_PVDITConfig(ENABLE);//PVD�ж�ʹ��
  //enableInterrupts();//ʹ���ж�
 
  while (1)
  {    //����Ϊ��ѯ��ʽ�ж�PVD״̬
       if(PWR_GetFlagStatus(PWR_FLAG_PVDOF)==RESET)//��ȡPVD״̬�����VDD��ѹ������ֵ����Ϩ��LED
       {
         GPIO_SetBits (LED_PORT,LED_PINS);
         Delay(0xffff);
       }
       else                                       //���VDD��ѹ������ֵ�������LED
       {
         GPIO_ResetBits (LED_PORT,LED_PINS);
         Delay(0xffff);
       }
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
