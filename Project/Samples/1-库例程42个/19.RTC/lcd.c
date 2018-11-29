
#include "stm8l15x.h"
#include "lcd.h"

//__CONST uint16_t mask[4] = {0xF000, 0x0F00, 0x00F0, 0x000F};
//__CONST uint8_t shift[4] = {12 , 8, 4 , 0};
uint8_t LCD_DisBuffer[4];           /* 0     1        2       3      4   */
__CONST uint16_t  NumberMap[10] = {0x3132, 0x2020, 0x3212, 0x3222, 0x2320,
                                   /*  5      6       7       8      9   */
                                   0x1322, 0x1332, 0x3020, 0x3332, 0x3322};



unsigned int tmp,n1, n2, n3, n4;

void InitLCD(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);//LCD驱动时钟门控使能
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//配置RTC LSI或LSE
    LCD_DeInit( );//LCD相关寄存器恢复初值
    LCD_Init(LCD_Prescaler_4, LCD_Divider_16,//LCD驱动初始化，LCD刷新频率
              LCD_Duty_1_4, LCD_Bias_1_3,//1/4DUTY 1/3BIAS，看屏幕参数
              LCD_VoltageSource_External);//选择LCD驱动电源，外部或内部

    LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0x00); //SEG0-7，STM8L152K4T6没有
    LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xFF); //SEG8-SEG15
    LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0x00); //以下SEG均没选用
    LCD_PortMaskConfig(LCD_PortMaskRegister_3, 0x00);
    LCD_PortMaskConfig(LCD_PortMaskRegister_4, 0x00); 
    LCD_PortMaskConfig(LCD_PortMaskRegister_5, 0x00);
    LCD_ContrastConfig(LCD_Contrast_3V3);//配置对比度
    LCD_DeadTimeConfig(LCD_DeadTime_0); //设置死区时间
    LCD_PulseOnDurationConfig(LCD_PulseOnDuration_1);
    LCD_HighDriveCmd(ENABLE);
    LCD_Cmd(ENABLE);
}

/*******************************************************************************
****函数名称:
****函数功能:数据转换函数
****版本:V1.0
****日期:14-2-2014
****入口参数:adc_value-需要转换的数值
****出口参数:
****说明:
********************************************************************************/
void data_convertor(unsigned long adc_value) 
{  
    tmp=adc_value;         //adc 
    n4=tmp/1000;
    tmp=tmp%1000;
    n3=tmp/100;
    tmp=tmp%100;	
    n2=tmp/10;
    tmp=tmp%10;		
    n1=tmp; 
 }
void Display()
{
      //LCD->CR4 &= (uint8_t)~LCD_CR4_PAGECOM;
      //ConvertNum(n4);
      //COM0
     // LCD_WriteRAM(LCD_RAMRegister_1
    
      LCD_DisBuffer[0]=(((NumberMap[n4] &0xf000)>>12)<<0)|(((NumberMap[n3] &0xf000)>>12)<<2)|(((NumberMap[n2] &0xf000)>>12)<<4)|(((NumberMap[n1] &0xf000)>>12)<<6);
      LCD_DisBuffer[1]=(((NumberMap[n4] &0x0f00)>>8)<<0)|(((NumberMap[n3] &0x0f00)>>8)<<2)|(((NumberMap[n2] &0x0f00)>>8)<<4)|(((NumberMap[n1] &0x0f00)>>8)<<6);
      LCD_DisBuffer[2]=(((NumberMap[n4] &0x00f0)>>4)<<0)|(((NumberMap[n3] &0x00f0)>>4)<<2)|(((NumberMap[n2] &0x00f0)>>4)<<4)|(((NumberMap[n1] &0x00f0)>>4)<<6);
      LCD_DisBuffer[3]=(((NumberMap[n4] &0x000f)>>0)<<0)|(((NumberMap[n3] &0x000f)>>0)<<2)|(((NumberMap[n2] &0x000f)>>0)<<4)|(((NumberMap[n1] &0x000f)>>0)<<6);
      
      
      LCD_WriteRAM(LCD_RAMRegister_1,LCD_DisBuffer[0]);
      
      LCD_WriteRAM(LCD_RAMRegister_4,LCD_DisBuffer[1]<<4);
      LCD_WriteRAM(LCD_RAMRegister_5,LCD_DisBuffer[1]>>4);
      
      LCD_WriteRAM(LCD_RAMRegister_8,LCD_DisBuffer[2]);
   
      LCD_WriteRAM(LCD_RAMRegister_11,LCD_DisBuffer[3]<<4);
      LCD_WriteRAM(LCD_RAMRegister_12,LCD_DisBuffer[3]>>4);
    
    
}
void Display_lcd_dot(void) 
{ 
 // Ht1621WrOneData(0 , DispTab[n4]|0x10);//P1
   //Ht1621WrOneData(2 , DispTab[n3]|0x10);    //2P
   //Ht1621WrOneData(4 , DispTab[n2]|0x10);    //3P
   //Ht1621WrOneData(6 , DispTab[n1]|0x10);    //4P
   LCD_WriteRAM(LCD_RAMRegister_11,(LCD_DisBuffer[3]<<4)|0x10);//P1
   //LCD_WriteRAM(LCD_RAMRegister_11,(LCD_DisBuffer[3]<<4)|0x40);//2P
}