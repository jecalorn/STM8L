

#include "stm8l15x.h"


extern void OLED_ShowNum(unsigned char x, unsigned char y, uint16_t Num,unsigned char TextSize);
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


extern void Delay(__IO uint16_t nCount);

void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//不为结束
        {
            USART_SendData8(USART1,*Str);     //发送数据 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
            Str++;//下一个数据
        }
}



void USART1_SendHex(unsigned char dat)
{
      USART_SendData8(USART1,'0');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,'x');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,HexTable[dat>>4]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,HexTable[dat&0x0f]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
      USART_SendData8(USART1,' ');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
}


void ADC_test()
{
    uint16_t u16_adc1_value;
    //初始化USART的TXD RXD对应的2个管脚
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//初始化，带上拉输入，不带中断
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//初始化，推挽输出，快速 


    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启ADC/USART时钟
    CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//开启ADC/USART时钟


    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，9600，8N1
    USART_Cmd (USART1,ENABLE);//使能USART

    ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//单次转换，12位，ADC转换时钟1分频
    ADC_Cmd(ADC1,ENABLE);//使能ADC1
    ADC_ChannelCmd (ADC1,ADC_Channel_8,ENABLE);//使能通道8------PD6



    while(1)
    {
        ADC_SoftwareStartConv (ADC1);//开始ADC软件转换

        USART1_SendStr("ADC转换结果为: ");

        while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));//等待转换结束
        ADC_ClearFlag (ADC1,ADC_FLAG_EOC);//清除对应标志

        
        u16_adc1_value=ADC_GetConversionValue (ADC1);//获取转换值

        USART1_SendHex((u16_adc1_value>>8));
        USART1_SendHex((u16_adc1_value&0xff));
        
        USART1_SendStr("\r\n");//换行


        OLED_ShowNum(40, 4, u16_adc1_value, 2);

        Delay(0xFFFF);
    }


}









