#include "stm8l15x.h"//STM8L051/151���ÿ⺯��
#include "lcd.h"
//����LED�������˿�
#define LED_PORT  GPIOD
#define LED_PINS  GPIO_Pin_0
#define KEY_PORT  GPIOB
#define KEY_PINS  GPIO_Pin_1

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
****������ע: STM8L151/2��ADC�ڲ���׼��ѹVREFINT����оƬ��Դ�ڹ�����Χ�ڲ���ʱ������ڲ�
              ��׼��ѹ���ֲ��䣬һ��Ϊ1.224V���û�׼��ѹ������ר�ŵĲ���ͨ��������
              ��ȡ�����ֵ��ע�⣺VREFINT����ADC�Ĳο���ѹ���ο���ѹ����VDD��һ����Ҫ������
              ������Կ�һ��http://www.51hei.com/bbs/dpj-41009-1.html�����ô�ԭ����Լ��VDD.
              ����Һ������ʾ�ڲ��ο���ѹ�ĵ�ѹֵ
********************************************************************************/
void main(void)
{
  u16 u16_adc1_value;   
  u16 VoltageValue;
  
    InitLCD();
  CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//����ADCʱ��
  ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//ADC1�����β�����12λ��1��Ƶ
  
  ADC_SamplingTimeConfig(ADC1,ADC_Group_FastChannels,ADC_SamplingTime_384Cycles);//������������
  ADC_VrefintCmd(ENABLE);//�ڲ���׼��ѹʹ��
  ADC_ChannelCmd (ADC1,ADC_Channel_Vrefint,ENABLE);//ʹ���ڲ���׼��ѹ����ͨ��
  
  ADC_Cmd(ADC1,ENABLE);//ADC1ʹ��
  
  
  while (1)
  {
       ADC_SoftwareStartConv (ADC1);//�������ת��
             
       while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));//�ȴ�ת������
       ADC_ClearFlag (ADC1,ADC_FLAG_EOC);//�����ر�ʶ
       
       u16_adc1_value=ADC_GetConversionValue (ADC1);//��ȡת��ֵ
       VoltageValue=u16_adc1_value*3300UL/4095UL;
      
        data_convertor(VoltageValue);
        Display();
        Display_lcd_dot();
        Delay(5000);  
        Delay(5000); 
        Delay(5000); 
        Delay(5000); 
        Delay(5000);  
        Delay(5000); 
        Delay(5000); 
        Delay(5000);
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
