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
****函数备注:擦除/写/读指定地址的FLASH，通过计算机的串口查看读出的数据是否为0F
             片内EEPROM地址为0x1000-0x13ff
             片内FLASH开始地址为0x8000,0x8000-0x807f为复位和中断向量表
             例程将0x0f写入9f40的位置，然后读出后通过UART发送出来

             注意：如果遇到FLASH无法写入的情况，应该通过STVP将选项字节ROP重新OFF一下
********************************************************************************/
  u8 r_byte;

void main(void)
{

  
  GPIO_Init(LED_PORT,LED_PINS,GPIO_Mode_Out_PP_Low_Slow);//初始化LED端口
  GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);//初始化KEY端口，带上拉输入，不带中断
 
  CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启USART时钟
  USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx|USART_Mode_Rx);//设置USART参数9600，8N1，接收/发送
  USART_ITConfig (USART1,USART_IT_RXNE,ENABLE);//使能接收中断
  USART_Cmd (USART1,ENABLE);//使能USART
  enableInterrupts(); 
  
  
  
  FLASH_DeInit();
  FLASH_Unlock(FLASH_MemType_Program);//先解锁，注意参数
  //while (FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET)//等待操作完成
 // {}
  
  FLASH_EraseByte(0x9F40);         //再擦除
  FLASH_ProgramByte(0x9F40,0x0F);  //写数据，第一个参数为地址，第二个参数为写入的数据，9f40为片内flash区域靠近中间的位置

  r_byte = FLASH_ReadByte(0x9F40);//读指定地址的数据
  FLASH_Lock(FLASH_MemType_Program); 
  USART_SendData8 (USART1,r_byte);//通过UART发送，16进制
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
