

#include "stm8l15x.h"


extern void OLED_ShowNum(unsigned char x, unsigned char y, uint16_t Num,unsigned char TextSize);
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


extern void Delay(__IO uint16_t nCount);

void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//��Ϊ����
        {
            USART_SendData8(USART1,*Str);     //�������� 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
            Str++;//��һ������
        }
}



void USART1_SendHex(unsigned char dat)
{
      USART_SendData8(USART1,'0');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,'x');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,HexTable[dat>>4]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,HexTable[dat&0x0f]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,' ');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
}


void ADC_test()
{
    uint16_t u16_adc1_value;
    //��ʼ��USART��TXD RXD��Ӧ��2���ܽ�
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//��ʼ�������������룬�����ж�
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//��ʼ����������������� 


    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����ADC/USARTʱ��
    CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//����ADC/USARTʱ��


    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����9600��8N1
    USART_Cmd (USART1,ENABLE);//ʹ��USART

    ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//����ת����12λ��ADCת��ʱ��1��Ƶ
    ADC_Cmd(ADC1,ENABLE);//ʹ��ADC1
    ADC_ChannelCmd (ADC1,ADC_Channel_8,ENABLE);//ʹ��ͨ��8------PD6



    while(1)
    {
        ADC_SoftwareStartConv (ADC1);//��ʼADC���ת��

        USART1_SendStr("ADCת�����Ϊ: ");

        while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));//�ȴ�ת������
        ADC_ClearFlag (ADC1,ADC_FLAG_EOC);//�����Ӧ��־

        
        u16_adc1_value=ADC_GetConversionValue (ADC1);//��ȡת��ֵ

        USART1_SendHex((u16_adc1_value>>8));
        USART1_SendHex((u16_adc1_value&0xff));
        
        USART1_SendStr("\r\n");//����


        OLED_ShowNum(40, 4, u16_adc1_value, 2);

        Delay(0xFFFF);
    }


}









