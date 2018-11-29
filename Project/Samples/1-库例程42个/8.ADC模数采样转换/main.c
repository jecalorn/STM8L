/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4�����̹���Demo
*******************************************************************************/
#include "stm8l15x.h"
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

uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/*******************************************************************************
****��ڲ�������Ҫ���͵��ַ���
****���ڲ�������
****������ע��USART���ͺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//��Ϊ����
        {
            USART_SendData8(USART1,*Str);     //�������� 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
            Str++;//��һ������
        }
}
/*******************************************************************************
****��ڲ�������Ҫ���͵�16������
****���ڲ�������
****������ע��USART����16���ƺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
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
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����������RXD-UT TXD-UR����ñ�̽ӣ�ͨ��USB�����Ӽ�����뿪���壬��
              ������Ĵ��ڵ���������������ò��������Խ��յ������巢�͵�ADC������
              ���ݡ�ʹ��ǰ��������Ȱ�װCH340������
              ������ADC�ӿ��õ���PD6
              UT��CPU��USART��TXD-PC3��UR��USART��RXD-PC2��RXD/TXD��CH340��
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
     u16 u16_adc1_value;  
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
     }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
