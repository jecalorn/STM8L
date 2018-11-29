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
****������ע��ϵͳ�ϵ�Ĭ��ʱ��ΪHSI/8=2M������LED1��˸Ƶ�����ж�ʱ��Դ�л��Ƿ�ɹ�
              ���÷��������ֶ��л�ʱ��Դ
****��Ȩ��Ϣ������Ƕ��ʽϵͳ,
*******************************************************************************/
int main( void )
{
    uint8_t i;  
   
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED�ӿڣ����������������
    
    
    
    //����ΪHSIΪϵͳʱ�� 16M
    CLK_HSICmd(ENABLE);//��ʼ�ڲ���ƵRC 16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);//HSIΪϵͳʱ��
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ����1��Ƶ��16M
    
    for(i=0;i<10;i++)//��תLED
    {
       GPIO_ToggleBits(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS);
       Delay(0xFFFF);
    }
    
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);//8��Ƶ��2M
    
    for(i=0;i<10;i++)//��תLED
    {
       GPIO_ToggleBits(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS);
       Delay(0xFFFF);
    }
    
    //����ΪHSEΪϵͳʱ��    16M
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);//ϵͳ��ʱ��ΪHSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_HSERDY)==RESET);//�ȴ�HSE׼������
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//ʹ���л�
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_HSE)//����л��ɹ�
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);//2��Ƶ,8M
       for(i=0;i<10;i++)
       {
          GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);
          Delay(0xFFFF);
        }
    }
    
    //����ΪLSEΪϵͳʱ��    32768
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);//ϵͳ��ʱ��ΪLSE
    
    while(CLK_GetFlagStatus(CLK_FLAG_LSERDY)==RESET);//�ȴ�LSE׼������
    CLK_SYSCLKSourceSwitchCmd(ENABLE);//ʹ���л�
    
    if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSE)//����л��ɹ�
    {
       CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//
       for(i=0;i<2;i++)
       {
          GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);
          Delay(0x0FFF);
        }
    }
    
    
    //����ΪLSI��ϵͳʱ�� 32K
    while(1)
    {
        CLK_LSICmd (ENABLE);    //ʹ��LSI
        CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//LSIΪϵͳʱ��
        while(CLK_GetFlagStatus(CLK_FLAG_LSIRDY)==RESET);//�ȴ�LSI׼������
        CLK_SYSCLKSourceSwitchCmd (ENABLE);//ʹ���л�
        if(CLK_GetSYSCLKSource()==CLK_SYSCLKSource_LSI)//����л��ɹ�
       {
          
          CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����Ƶ  
          for(i=0;i<2;i++)
          {
             GPIO_ToggleBits(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS);
             Delay(0x0FFF);
          }  
       }
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
