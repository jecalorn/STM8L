/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"
#include "lcd.h"
//定义LED与按键接口
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4


/*******************************************************************************
****函数名称:
****函数功能:延时函数
****版本:V1.0
****日期:14-2-2014
****入口参数:需要延时的数目
****出口参数:无
****说明:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}


/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：断码液晶显示ADC转换后的电压值
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
   GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);
   
    //CLK_HSICmd(ENABLE);//开始内部高频RC
    //CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSI为系统时钟
  //  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//不分频
    InitLCD();
    u16 u16_adc1_value;   
    u16 VoltageValue;
    CLK_PeripheralClockConfig (CLK_Peripheral_ADC1,ENABLE);//开启ADC/USART时钟
    ADC_Init (ADC1,ADC_ConversionMode_Single,ADC_Resolution_12Bit,ADC_Prescaler_1);
    ADC_Cmd(ADC1,ENABLE);
    ADC_ChannelCmd (ADC1,ADC_Channel_8,ENABLE);
    
    Delay(100);           //延时一段时间 
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
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
