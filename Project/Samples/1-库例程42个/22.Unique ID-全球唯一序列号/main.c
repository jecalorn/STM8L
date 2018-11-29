/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4发送字符串库函数例程
*******************************************************************************/
#include "stm8l15x.h"
#include "stdio.h"
//定义LED与按键接口
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4
#define KEY_GPIO_PORT  GPIOD
#define KEY_GPIO_PINS  GPIO_Pin_4
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
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
****入口参数：需要发送的16进制数
****出口参数：无
****函数备注：USART发送16进制函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
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
/*******************************************************************************
****函数名称:
****函数功能:获取芯片ID函数
****版本:V1.0
****日期:14-2-2014
****入口参数:无
****出口参数:无
****说明:96位唯一ID
********************************************************************************/
void Get_ChipID(u8 *ChipID)
{
	ChipID[0] = *(__IO u8 *)(0X4926); 
	ChipID[1] = *(__IO u8 *)(0X4927); 
	ChipID[2] = *(__IO u8 *)(0X4928);
        ChipID[3] = *(__IO u8 *)(0X4929);
	ChipID[4] = *(__IO u8 *)(0X492A); 
	ChipID[5] = *(__IO u8 *)(0X492B); 
	ChipID[6] = *(__IO u8 *)(0X492C);
	ChipID[7] = *(__IO u8 *)(0X492D); 
	ChipID[8] = *(__IO u8 *)(0X492E); 
	ChipID[9] = *(__IO u8 *)(0X492F);
	ChipID[10] = *(__IO u8 *)(0X4930); 
	ChipID[11] = *(__IO u8 *)(0X4931); 
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：开发板上RXD-UT TXD-UR跳线帽短接，通过USB线连接计算机与开发板，打开
              计算机的串口调试助手软件，设置参数，可以接收到开发板发送的字符串格式的
              芯片ID数据。使用前计算机需先安装CH340驱动。
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    u8 ChipID[12];  
    unsigned char str[40];
  
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//开启USART时钟
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART初始化，9600，8N1
    USART_Cmd (USART1,ENABLE);//使能USART
    
    Get_ChipID(ChipID);//获取芯片ID
    sprintf(str,"芯片ID:%X%X-%X%X-%X%X-%X%X-%X%X-%X%X\r\n",ChipID[0],ChipID[1],ChipID[2],ChipID[3],ChipID[4],ChipID[5],ChipID[6],ChipID[7],ChipID[8],ChipID[9],ChipID[10],ChipID[11]);
    USART1_SendStr(str);//输出
    while(1)
    {
        //USART1_SendStr("蓝旗嵌入式\r\n"); //发送字符串，末尾换行
    }
    
}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
