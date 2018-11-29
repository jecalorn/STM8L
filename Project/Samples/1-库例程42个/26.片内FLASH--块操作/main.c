/*******************************************************************************
****��Ȩ��Ϣ������Ƕ��ʽϵͳ http://lenchimcu.taobao.com
*******************************************************************************/
#include "stm8l15x.h" //151/051���ÿ⺯��

//����LED�������˿�
#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4
#define KEY_PORT  GPIOD
#define KEY_PINS  GPIO_Pin_4

#define BLOCK_OPERATION    125    //��ĺ���
uint8_t GBuffer[FLASH_BLOCK_SIZE];
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
****������ע:����/д/��ָ����ַ��FLASH��
             Ƭ��EEPROM��ַΪ0x1000-0x13ff
             Ƭ��FLASH��ʼ��ַΪ0x8000,0x8000-0x807fΪ��λ���ж�������
             FLASH���Ϊ0-255�飬ע���Ķ�д����RAM�����еģ����õĿ⺯��Ҳ�Ǽ�
             ����ؼ����ˣ�Ҫ��stm8l15X.h ͷ�ļ��н�#define RAM_EXECUTION  (1) ��
             ע��ȥ���ſ��ԣ�
             �����ȶ�ָ���Ŀ�д�����ݣ�Ȼ���ֽڶ���У�飬У������ LED����˸������
             LEDϨ��
********************************************************************************/

void main(void)
{
  uint32_t add = 0, startadd = 0, stopadd = 0;
  uint8_t newval = 0xAA;
  uint8_t i = 0;
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
  GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);//��ʼ��KEY�˿ڣ����������룬�����ж�
  
  
  FLASH_DeInit();
  FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);//��׼���ʱ��
  //����Programд����
  FLASH_Unlock(FLASH_MemType_Program);
  while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET)//�ȴ��������
  {}
  //����EEPROMд����
  //FLASH_Unlock(FLASH_MemType_Data);
  //while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)//�ȴ��������
  //{}
  
  //��RAM�е�д�뻺������ֵ
  for (i = 0; i < FLASH_BLOCK_SIZE; i++)
  {
    GBuffer[i] = newval;
  }
  //BLOCKд��RAM������
  FLASH_ProgramBlock(BLOCK_OPERATION,FLASH_MemType_Program, FLASH_ProgramMode_Standard, GBuffer);
 while (FLASH_GetFlagStatus(FLASH_FLAG_HVOFF) == RESET)
  {}	  
  //У��д�������
  startadd = FLASH_PROGRAM_START_PHYSICAL_ADDRESS + ((uint16_t)BLOCK_OPERATION * (uint16_t)FLASH_BLOCK_SIZE);
  stopadd = startadd + (uint16_t)FLASH_BLOCK_SIZE;
  for (add = startadd; add < stopadd; add++)
      {
        if (FLASH_ReadByte(add) != newval)
        {
          GPIO_SetBits(LED_PORT, LED_PINS);//����д����Ϩ��LED
        while (1)
        {
          
        }
        }
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
