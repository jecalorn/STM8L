#include "stm8l15x.h"//STM8L051/151公用库函数
#include "lcd.h"
#include "delay.h"
#include "ds18b20.h"
//定义LED及按键端口
#define LED_PORT  GPIOD
#define LED_PINS  GPIO_Pin_0
#define KEY_PORT  GPIOB
#define KEY_PINS  GPIO_Pin_1
unsigned int temper=0;
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
****函数备注:液晶显示DS18B20测得的温度,传感器数据脚接PD4，带外部上拉电阻
            
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
       data_convertor(temper);//在液晶上显示温度
       Display();//显示 
       Display_lcd_dot();//显示小数点
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
