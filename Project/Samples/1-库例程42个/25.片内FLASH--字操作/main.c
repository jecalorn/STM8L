/*******************************************************************************
****��Ȩ��Ϣ������Ƕ��ʽϵͳ http://lenchimcu.taobao.com
*******************************************************************************/
#include "stm8l15x.h" //151/051���ÿ⺯��

//����LED�������˿�
#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4
#define KEY_PORT  GPIOD
#define KEY_PINS  GPIO_Pin_4

uint8_t val= 0x00;
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
****������ע:����/д/��ָ����ַ��FLASH��ͨ��������Ĵ��ڲ鿴�����������Ƿ�Ϊ0F
             Ƭ��EEPROM��ַΪ0x1000-0x13ff
             Ƭ��FLASH��ʼ��ַΪ0x8000,0x8000-0x807fΪ��λ���ж�������
             ����ѡ��flash��ַΪ0x9f40
             �Ƚ��ĸ��ֽ�д�룬Ȼ��һ���ֽ�һ���ֽڵĶ�����֤��������Ǻ�д���
             ������ͬ�������LED����˸������LED����ġ�
********************************************************************************/

void main(void)
{
  uint32_t start_add = 0x9f40;
  uint32_t add = 0x0;
  uint32_t new_val = 0x01234567;
  uint8_t sub_test_count = 0x0;
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�˿�
  GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);//��ʼ��KEY�˿ڣ����������룬�����ж�
  
  
  FLASH_DeInit();
  FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);//��׼���ʱ��
  FLASH_Unlock(FLASH_MemType_Program);//�Ƚ���FLASH����ע�����
  
  FLASH_ProgramWord(start_add, new_val);
  val = FLASH_ReadByte(start_add);
  add = start_add;
  
  if (val != BYTE_3(new_val))
    {
        GPIO_SetBits(LED_PORT, LED_PINS);//����д����Ϩ��LED
        while (1)
        {
        }
    }
    
    add += 1;
    val = FLASH_ReadByte(add);
    if (val != BYTE_2(new_val))
    {
        GPIO_SetBits(LED_PORT, LED_PINS);//����д����Ϩ��LED
        while (1)
        {
        }
    }
    
    add += 1;
    val = FLASH_ReadByte(add);
    if (val != BYTE_1(new_val))
    {
        GPIO_SetBits(LED_PORT, LED_PINS);//����д����Ϩ��LED
        while (1)
        {
        }
    }
    
    
    add += 1;
    val = FLASH_ReadByte(add);
    if (val != BYTE_0(new_val))
    {
        GPIO_SetBits(LED_PORT, LED_PINS);//����д����Ϩ��LED
        while (1)
        {
        }
    }
    
    add = start_add;
    for (sub_test_count = 0; sub_test_count < 4; sub_test_count++)
    {
        FLASH_EraseByte(add);
        add += 1;
    }
    
    add = start_add;
    for (sub_test_count = 0; sub_test_count < 4; sub_test_count++)
    {
        val = FLASH_ReadByte(add);
        if (val != 0x00)
        {
            GPIO_SetBits(LED_PORT, LED_PINS);//����д����Ϩ��LED
            while (1)
            {
            }
        }
        add += 1;
    }
  while (1)
  {
       GPIO_ToggleBits(LED_PORT, LED_PINS);
       Delay(0xFFFF);
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
