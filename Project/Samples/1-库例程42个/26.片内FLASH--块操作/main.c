/*******************************************************************************
****版权信息：蓝旗嵌入式系统 http://lenchimcu.taobao.com
*******************************************************************************/
#include "stm8l15x.h" //151/051公用库函数

//定义LED及按键端口
#define LED_PORT  GPIOC
#define LED_PINS  GPIO_Pin_4
#define KEY_PORT  GPIOD
#define KEY_PINS  GPIO_Pin_4

#define BLOCK_OPERATION    125    //块的号码
uint8_t GBuffer[FLASH_BLOCK_SIZE];
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
****函数备注:擦除/写/读指定地址的FLASH，
             片内EEPROM地址为0x1000-0x13ff
             片内FLASH开始地址为0x8000,0x8000-0x807f为复位和中断向量表
             FLASH块分为0-255块，注意块的读写是在RAM中运行的，调用的库函数也是加
             特殊关键字了，要在stm8l15X.h 头文件中将#define RAM_EXECUTION  (1) 的
             注释去掉才可以！
             例程先对指定的块写入数据，然后按字节读出校验，校验无误 LED会闪烁，否则
             LED熄灭
********************************************************************************/

void main(void)
{
  uint32_t add = 0, startadd = 0, stopadd = 0;
  uint8_t newval = 0xAA;
  uint8_t i = 0;
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
  GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);//初始化KEY端口，带上拉输入，不带中断
  
  
  FLASH_DeInit();
  FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);//标准编程时间
  //解锁Program写保护
  FLASH_Unlock(FLASH_MemType_Program);
  while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET)//等待操作完成
  {}
  //解锁EEPROM写保护
  //FLASH_Unlock(FLASH_MemType_Data);
  //while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)//等待操作完成
  //{}
  
  //将RAM中的写入缓冲区赋值
  for (i = 0; i < FLASH_BLOCK_SIZE; i++)
  {
    GBuffer[i] = newval;
  }
  //BLOCK写，RAM中运行
  FLASH_ProgramBlock(BLOCK_OPERATION,FLASH_MemType_Program, FLASH_ProgramMode_Standard, GBuffer);
 while (FLASH_GetFlagStatus(FLASH_FLAG_HVOFF) == RESET)
  {}	  
  //校验写入的内容
  startadd = FLASH_PROGRAM_START_PHYSICAL_ADDRESS + ((uint16_t)BLOCK_OPERATION * (uint16_t)FLASH_BLOCK_SIZE);
  stopadd = startadd + (uint16_t)FLASH_BLOCK_SIZE;
  for (add = startadd; add < stopadd; add++)
      {
        if (FLASH_ReadByte(add) != newval)
        {
          GPIO_SetBits(LED_PORT, LED_PINS);//如果有错误就熄灭LED
        while (1)
        {
          
        }
        }
      }
  
  
  
  while (1)
  {
       GPIO_ToggleBits(LED_PORT, LED_PINS);
       Delay(0xFFFF);
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
