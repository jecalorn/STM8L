/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L151K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"
#include "flash.h"
//以下定义LED与按键的接口
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
uint8_t i=0;
unsigned short FlashID;
#define countof(a) (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(SendBuf))
unsigned char SendBuf[]="STM8L SPI操作25X16 实验！\r\n";
unsigned char RecBuf[BufferSize];
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
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
void Send_Dat(u8 dat)
{
   while(( USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET));
   USART_SendData8(USART1,dat);
}
void Send_Hex(unsigned char dat)
{
   Send_Dat('0');
   Send_Dat('x');
   Send_Dat(HexTable[dat>>4]);
   Send_Dat(HexTable[dat&0x0f]);
   Send_Dat(' ');
}




/*******************************************************************************
****入口参数：需要发送的字符串
****出口参数：无
****函数备注：USART发送函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//不为结束
        {
            USART_SendData8(USART1,*Str);     //发送数据 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//等待发送完毕
            Str++;//下一个数据
        }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：GPIO测试程序，三个LED都为灌流方式连接LED，通过控制对应LED接口输出高
              低电平，使LED闪烁
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED1接口
   CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启USART时钟
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，9600，8N1
    USART_Cmd (USART1,ENABLE);//使能USART 
 
 
  CLK_PeripheralClockConfig (CLK_Peripheral_SPI1,ENABLE);//开启SPI时钟
  GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_In_PU_No_IT);
  SPI_Flash_Init();
  USART1_SendStr("正在读取芯片ID\r\n");
  FlashID=SPI_FLASH_ReadID();
  USART1_SendStr("芯片ID为:");
  Send_Hex(FlashID>>8);
  Send_Hex(FlashID&0xff);
   USART1_SendStr("\r\n");

  
  SPI_FLASH_WriteEnable();
  USART1_SendStr("开始擦除整块芯片......\r\n");
  SPI_Flash_EraseChip();
  SPI_FLASH_BlockErase(0);
 USART1_SendStr("芯片擦除完毕！\r\n");
 
  
  
  USART1_SendStr("开始写入数据\r\n");
 
  SPI_FLASH_BufferWrite(SendBuf, 0, BufferSize);
  //SPI_FLASH_PageWrite(SendBuf, 10, BufferSize);
  //SPI_FLASH_PageWrite("2020", 0, 4);
 USART1_SendStr("写入数据完毕！\r\n");
  
 USART1_SendStr("开始读出数据\r\n");
  SPI_FLASH_BufferRead(RecBuf, 0,BufferSize);
 USART1_SendStr("读出数据完毕！\r\n");
  
  USART1_SendStr(RecBuf);
    while(1)
    {
        GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//翻转LED1接口电平，实现LED1闪烁
        Delay(0xFFFF);//延时，便于观察实验现象
    }

}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
