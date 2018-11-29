/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4�����̹���Demo
*******************************************************************************/
#include "stm8l15x.h"
//����LED�Ͱ����ӿ�
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4
#define KEY_GPIO_PORT  GPIOD
#define KEY_GPIO_PINS  GPIO_Pin_4
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
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��ʱ�����ú�������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void CLK_Config(void)
{
  
  /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);//ʹ��ʱ���л�
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSI);//ѡ���ⲿ����ʱ����Ϊʱ��Դ
  /* system clock prescaler: 1*/
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);//����ϵͳʱ�ӷ�Ƶ
  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_LSI)//�ȴ�ʱ���ȶ�
  {}
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע���ȴ�ģʽ������WFI/WFE���ֱ�ָ�ȴ��ж�/�ȴ��¼����ȴ�ģʽCPUֹͣ������
              ������жϿ��������������������ȴ�ģʽ���ж��ܿ����Զ��򿪣�
              ʱ�Ӿ���Ƶ�ʵͣ�GPIO��������͵�ƽ��
              ʵ�������Լ200ua����
              WFE�ȴ����¼�������жϣ��򲻻�����ж���Ӧ����
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    CLK_Config();//�л�LSIΪ��ʱ��
    
    //��ʹ�õ�IOȫ������Ϊ����͵�ƽ
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
  
    GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//GPIO��ʼ��
    GPIO_Init(KEY_GPIO_PORT, KEY_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPD4��������
    EXTI_SetPinSensitivity(EXTI_Pin_4,EXTI_Trigger_Falling);
    
    WFE_DeInit ();
    WFE_WakeUpSourceEventCmd (WFE_Source_EXTI_EV4,ENABLE);//ָ���ⲿ�ж�4Ϊ�ȴ����¼�
    
    while(1)
    {
         
        EXTI_ClearITPendingBit (EXTI_IT_Pin4);//���жϱ�־
        GPIO_ToggleBits(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);//��תLED�˿ڵ�ƽ
        Delay(0x00FF);
        
        wfe();
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
