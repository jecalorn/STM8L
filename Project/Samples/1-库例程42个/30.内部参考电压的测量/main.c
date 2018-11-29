#include "stm8l15x.h"//STM8L051/151公用库函数
#include "lcd.h"
//定义LED及按键端口
#define LED_PORT  GPIOD
#define LED_PINS  GPIO_Pin_0
#define KEY_PORT  GPIOB
#define KEY_PINS  GPIO_Pin_1

unsigned char Ht1621Tab[]={0x00,0x00,0x00,0x00};
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：不精确延时函数
****版权信息：蓝旗嵌入式系统
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
****函数说明：主函数
****入口参数:无
****出口参数:无
****函数备注: STM8L151/2带ADC内部基准电压VREFINT，当芯片电源在工作范围内波动时，这个内部
              基准电压保持不变，一般为1.224V。该基准电压可以有专门的测量通道，可以
              获取其采样值。注意：VREFINT不是ADC的参考电压，参考电压还是VDD，一定不要混淆。
              具体可以看一下http://www.51hei.com/bbs/dpj-41009-1.html，利用此原理可以监控VDD.
              段码液晶会显示内部参考电压的电压值
********************************************************************************/
void main(void)
{
  u16 u16_adc1_value;   
  u16 VoltageValue;
  
    InitLCD();
  CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//开启ADC时钟
  ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);//ADC1，单次采样，12位，1分频
  
  ADC_SamplingTimeConfig(ADC1,ADC_Group_FastChannels,ADC_SamplingTime_384Cycles);//采样周期设置
  ADC_VrefintCmd(ENABLE);//内部基准电压使能
  ADC_ChannelCmd (ADC1,ADC_Channel_Vrefint,ENABLE);//使能内部基准电压测量通道
  
  ADC_Cmd(ADC1,ENABLE);//ADC1使能
  
  
  while (1)
  {
       ADC_SoftwareStartConv (ADC1);//开启软件转换
             
       while(!ADC_GetFlagStatus (ADC1,ADC_FLAG_EOC));//等待转换结束
       ADC_ClearFlag (ADC1,ADC_FLAG_EOC);//清除相关标识
       
       u16_adc1_value=ADC_GetConversionValue (ADC1);//获取转换值
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
