/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4�����ַ����⺯������
*******************************************************************************/
#include "stm8l15x.h"
#include "stdio.h"
//����LED�밴���ӿ�
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4
#define KEY_GPIO_PORT  GPIOD
#define KEY_GPIO_PINS  GPIO_Pin_4
uint8_t HexTable[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
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
****��ڲ�������Ҫ���͵�16������
****���ڲ�������
****������ע��USART����16���ƺ���
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void USART1_SendHex(unsigned char dat)
{
      USART_SendData8(USART1,'0');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,'x');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,HexTable[dat>>4]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,HexTable[dat&0x0f]);
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
      USART_SendData8(USART1,' ');
      while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ��������
}
/*******************************************************************************
****��������:
****��������:��ȡоƬID����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:96λΨһID
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
****��ڲ�������
****���ڲ�������
****������ע����������RXD-UT TXD-UR����ñ�̽ӣ�ͨ��USB�����Ӽ�����뿪���壬��
              ������Ĵ��ڵ���������������ò��������Խ��յ������巢�͵��ַ�����ʽ��
              оƬID���ݡ�ʹ��ǰ��������Ȱ�װCH340������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    u8 ChipID[12];  
    unsigned char str[40];
  
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����USARTʱ��
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//USART��ʼ����9600��8N1
    USART_Cmd (USART1,ENABLE);//ʹ��USART
    
    Get_ChipID(ChipID);//��ȡоƬID
    sprintf(str,"оƬID:%X%X-%X%X-%X%X-%X%X-%X%X-%X%X\r\n",ChipID[0],ChipID[1],ChipID[2],ChipID[3],ChipID[4],ChipID[5],ChipID[6],ChipID[7],ChipID[8],ChipID[9],ChipID[10],ChipID[11]);
    USART1_SendStr(str);//���
    while(1)
    {
        //USART1_SendStr("����Ƕ��ʽ\r\n"); //�����ַ�����ĩβ����
    }
    
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
