/*******************************************************************************
****版权信息：蓝旗嵌入式系统 http://lenchimcu.taobao.com
*******************************************************************************/
#include "stm8l15x.h" //151/051公用库函数

//定义LED及按键端口
#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4
#define KEY_PORT  GPIOD
#define KEY_PINS  GPIO_Pin_4
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：延时函数
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
****函数备注:Option Bytes属于片内EEPROM的一部分；故解锁的时候要解锁片内EEPROM的
             保护；
             STM8L15X中等密度芯片的BOOT LOADER控制位的地址为0x480b、0x480c,要将
             0x55、0xAA分别写入，这个时候芯片的BOOT LOADER功能就开启了。可以通过
             UART烧写编译好的HEX。可以通过STVP读取芯片的Option Bytes来查看有没有
             成功。
             具体烧写方法请参照我们的视频教程。
********************************************************************************/
void main(void)
{ 
  FLASH_DeInit();
  FLASH_Unlock(FLASH_MemType_Data);//先解锁，注意参数
 
  FLASH_ProgramOptionByte(0x480b,0x55);  
  FLASH_ProgramOptionByte(0x480c,0xaa);  
  while (1)
  {
       
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
