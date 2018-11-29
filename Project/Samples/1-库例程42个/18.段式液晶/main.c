/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4������GPIO����
*******************************************************************************/
#include "stm8l15x.h"
#include "lcd.h"
//����LED�밴���ӿ�
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4


/*******************************************************************************
****��������:
****��������:��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʱ����Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}


/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע������Һ����ʾADCת����ĵ�ѹֵ
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
   GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
   
    //CLK_HSICmd(ENABLE);//��ʼ�ڲ���ƵRC
    //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSIΪϵͳʱ��
  //  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ
    InitLCD();
    u16 u16_adc1_value;   
    u16 VoltageValue;
    CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//����ADC/USARTʱ��
    ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);
    ADC_Cmd(ADC1,ENABLE);
    ADC_ChannelCmd (ADC1,ADC_Channel_8,ENABLE);
    
    Delay(100);           //��ʱһ��ʱ�� 
    while (1)
    {
        Delay(5000);  
        Delay(5000); 
        Delay(5000); 
        Delay(5000); 
        ADC_SoftwareStartConv (ADC1);
        while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));
        ADC_ClearFlag (ADC1,ADC_FLAG_EOC);
        Delay(5000);  
        Delay(5000); 
        Delay(5000); 
        Delay(5000); 
        u16_adc1_value=ADC_GetConversionValue (ADC1);
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

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
