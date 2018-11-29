/*******************************************************************************
****��Ȩ��Ϣ������Ƕ��ʽϵͳ http://lenchimcu.taobao.com
*******************************************************************************/
#include "stm8l15x.h" //151/051���ÿ⺯��

//����LED�������˿�
#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4
#define KEY_PORT  GPIOD
#define KEY_PINS  GPIO_Pin_4
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
****������ע:����/д/��ָ����ַ��EEPROM��ͨ��������Ĵ��ڲ鿴�����������Ƿ�Ϊ0F
             Ƭ��EEPROM��ַΪ0x1000-0x13ff
             Ƭ��FLASH��ʼ��ַΪ0x8000,0x8000-0x807fΪ��λ���ж�������
             ���̽�0x0fд��1000��λ�ã�Ȼ�������ͨ��UART���ͳ���
********************************************************************************/
void main(void)
{

  
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�˿�
  GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);//��ʼ��KEY�˿ڣ����������룬�����ж�
 
  CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����USARTʱ��
  USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx|USART_Mode_Rx);//����USART����9600��8N1������/����
  USART_ITConfig (USART1,USART_IT_RXNE,ENABLE);//ʹ�ܽ����ж�
  USART_Cmd (USART1,ENABLE);//ʹ��USART
  enableInterrupts(); 
  
  
  
  FLASH_DeInit();
  FLASH_Unlock(FLASH_MemType_Data);//�Ƚ�����ע�����
  FLASH_EraseByte(0x1000);         //�ٲ���
  FLASH_ProgramByte(0x1000,0x0F);  //д���ݣ���һ������Ϊ��ַ���ڶ�������Ϊд������ݣ�1000ΪƬ��EEPROM�������ʼλ��
  u8 r_byte;
  r_byte = FLASH_ReadByte(0x1000);//��ָ����ַ������
  USART_SendData8 (USART1,r_byte);//ͨ��UART���ͣ�16����
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
