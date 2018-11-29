#include "stm8l15x.h"//STM8L051/151���ÿ⺯��
#include "lcd.h"
#include "delay.h"
#include "ds18b20.h"
//����LED�������˿�
#define LED_PORT  GPIOD
#define LED_PINS  GPIO_Pin_0
#define KEY_PORT  GPIOB
#define KEY_PINS  GPIO_Pin_1
unsigned int temper=0;
unsigned char Ht1621Tab[]={0x00,0x00,0x00,0x00};
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
****������ע:Һ����ʾDS18B20��õ��¶�,���������ݽŽ�PD4�����ⲿ��������
            
********************************************************************************/
void main(void)
{      
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  InitLCD();
    
  while (1)
  {
    if(init_1820())
       {
          temper=gettemp();
       }
       data_convertor(temper);//��Һ������ʾ�¶�
       Display();//��ʾ 
       Display_lcd_dot();//��ʾС����
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
