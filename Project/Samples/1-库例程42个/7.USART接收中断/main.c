/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4�����̹���Demo
*******************************************************************************/
#include "stm8l15x.h"
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
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע������ȷ��ʱ����
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
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����������RXD-UT TXD-UR����ñ�̽ӣ�ͨ��USB�����Ӽ�����뿪���壬��
              ������Ĵ��ڵ���������������ò�������ͨ�����ڵ������ָ������巢������
              Ȼ�󴮿ڵ������ֻ���յ������巢�ͻ��������ݡ�ʹ��ǰ��������Ȱ�װCH340������
              ������115200ʱϵͳʱ��������
              UT��CPU��USART��TXD-PC3��UR��USART��RXD-PC2��RXD/TXD��CH340��
              �жϴ��������ļ�IT.C��USART�����ж�������Ϊ28
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    CLK_HSICmd(ENABLE);//��ʼ�ڲ���ƵRC 16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSIΪϵͳʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ����1��Ƶ��16M
  
    //��ʼ��USART��TXD RXD��Ӧ��2���ܽ�
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//��ʼ�������������룬�����ж�
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//��ʼ�����������������  
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����USARTʱ��
    
    USART_Init(USART1,115200,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Rx|USART_Mode_Tx);//����USART����115200��8N1������/����
    USART_ITConfig (USART1,USART_IT_OR,ENABLE);//ʹ�ܽ����ж�,�ж�������Ϊ28
    USART_Cmd (USART1,ENABLE);//ʹ��USART
    enableInterrupts(); //�����ж��ܿ���
    
    while(1)
    {
      //GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�ӿڣ����������������
    }
    
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
