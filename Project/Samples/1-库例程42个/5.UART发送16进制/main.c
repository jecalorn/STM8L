/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4  USART����16�������ݿ⺯������
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
****������ע����������RXD-UT TXD-UR����ñ�̽ӣ�ͨ��USB�����Ӽ�����뿪���壬��
              ������Ĵ��ڵ���������������ò��������Խ��յ������巢�͵�HEX��ʽ��
              ���ݡ�ʹ��ǰ��������Ȱ�װCH340������
              UT��CPU��USART��TXD-PC3��UR��USART��RXD-PC2��RXD/TXD��CH340��
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    uint8_t i;
    //��ʼ��USART��Ӧ��2���ܽ�
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//��ʼ�������������룬�����ж�
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//��ʼ�����������������
    
    CLK_PeripheralClockConfig (CLK_Peripheral_USART1,ENABLE);//����USARTʱ��,��������ʱ�ӳ�ʼĬ�Ϲرգ�ʹ������ǰ�迪����Ӧ����ʱ��
    USART_Init(USART1,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx);//����USART����9600��8N1
    USART_Cmd (USART1,ENABLE);//ʹ��USART
    while(1)
    {
        USART_SendData8(USART1,i);//����16����
        while(!USART_GetFlagStatus (USART1,USART_FLAG_TXE));//�ȴ�����
        i++;
    }
    
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
