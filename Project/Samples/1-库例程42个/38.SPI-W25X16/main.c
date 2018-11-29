/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L151K4������GPIO����
*******************************************************************************/
#include "stm8l15x.h"
#include "flash.h"
//���¶���LED�밴���Ľӿ�
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
unsigned char SendBuf[]="STM8L SPI����25X16 ʵ�飡\r\n";
unsigned char RecBuf[BufferSize];
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����ʱ����
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
****��ڲ�������Ҫ���͵��ַ���
****���ڲ�������
****������ע��USART���ͺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void USART1_SendStr(unsigned char *Str) 
{
        while(*Str!=0)//��Ϊ����
        {
            USART_SendData8(USART1,*Str);     //�������� 
            while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
            Str++;//��һ������
        }
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��GPIO���Գ�������LED��Ϊ������ʽ����LED��ͨ�����ƶ�ӦLED�ӿ������
              �͵�ƽ��ʹLED��˸
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED1�ӿ�
   CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����USARTʱ��
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����9600��8N1
    USART_Cmd (USART1,ENABLE);//ʹ��USART 
 
 
  CLK_PeripheralClockConfig (CLK_Peripheral_SPI1,ENABLE);//����SPIʱ��
  GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_In_PU_No_IT);
  SPI_Flash_Init();
  USART1_SendStr("���ڶ�ȡоƬID\r\n");
  FlashID=SPI_FLASH_ReadID();
  USART1_SendStr("оƬIDΪ:");
  Send_Hex(FlashID>>8);
  Send_Hex(FlashID&0xff);
   USART1_SendStr("\r\n");

  
  SPI_FLASH_WriteEnable();
  USART1_SendStr("��ʼ��������оƬ......\r\n");
  SPI_Flash_EraseChip();
  SPI_FLASH_BlockErase(0);
 USART1_SendStr("оƬ������ϣ�\r\n");
 
  
  
  USART1_SendStr("��ʼд������\r\n");
 
  SPI_FLASH_BufferWrite(SendBuf, 0, BufferSize);
  //SPI_FLASH_PageWrite(SendBuf, 10, BufferSize);
  //SPI_FLASH_PageWrite("2020", 0, 4);
 USART1_SendStr("д��������ϣ�\r\n");
  
 USART1_SendStr("��ʼ��������\r\n");
  SPI_FLASH_BufferRead(RecBuf, 0,BufferSize);
 USART1_SendStr("����������ϣ�\r\n");
  
  USART1_SendStr(RecBuf);
    while(1)
    {
        GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//��תLED1�ӿڵ�ƽ��ʵ��LED1��˸
        Delay(0xFFFF);//��ʱ�����ڹ۲�ʵ������
    }

}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
