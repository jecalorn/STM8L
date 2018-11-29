
#include "stm8l15x.h"
#include "lcd.h"
#include "dht11.h"
//����LED�˿�
#define LED_PORT  GPIOD
#define LED_PINS  GPIO_Pin_0
#include "stdio.h"

unsigned char DHTData[4];//={0,0,0,0};
unsigned char Temp;
unsigned char Humi;
unsigned char Ht1621Tab[]={0x00,0x00,0x00,0x00};
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
****������ע: Һ��������ʾ��ǰ���¶ȡ�ʪ�ȣ����������ݽŽ�PD4
********************************************************************************/
void main(void)
{
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    InitLCD();
    DHT11_Init();
    while (1)
    {
       while(!DHT11_Start());
     
        while(!Get_data(DHTData));
        Delay(0xFFFF);
        Delay(0xFFFF); 
        Delay(0xFFFF); 
        Delay(0xFFFF);
        Temp=(DHTData[2]>>4)*16+(DHTData[2]&0x0f);
        Humi=(DHTData[0]>>4)*16+(DHTData[0]&0x0f);
       data_convertor(Temp*100);//��Һ������ʾ�¶�
       Display();//��ʾ
       Display_lcd_dot();//��ʾС����
       //������ʱΪ������Ļ�Ϲ۲쵽
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       data_convertor(Humi*100);//��Һ������ʾʪ��
       Display();//��ʾ
       Display_lcd_dot();//��ʾС����
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
       Delay(0xFFFF);
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
