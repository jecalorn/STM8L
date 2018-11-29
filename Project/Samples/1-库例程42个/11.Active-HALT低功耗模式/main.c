/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4�����̹���Demo
*******************************************************************************/
#include "stm8l15x.h"
//����LED�밴���ӿ�
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4
#define KEY_GPIO_PORT  GPIOD
#define KEY_GPIO_PINS  GPIO_Pin_4
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע���Ǿ�ȷ��ʱ����
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

void RTC_Config(void)
{
        CLK_LSEConfig(CLK_LSE_ON);
        while (CLK_GetFlagStatus(CLK_FLAG_LSERDY) == RESET);
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);//38K
        
        RTC_WakeUpCmd(DISABLE);
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ���ſ�ʹ��
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//38K/16=2375HZ t=0.421ms
        
        Delay(0xffff);//��ʱ һ��Ҫ��
    
        RTC_ITConfig(RTC_IT_WUT, ENABLE);//���Ѷ�ʱ���ж�ʹ��
        RTC_SetWakeUpCounter(3000);
        RTC_WakeUpCmd(ENABLE);//RTC����ʹ��

        //ITC_SetSoftwarePriority(RTC_IRQn, ITC_PriorityLevel_3);//���ȼ�
        
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��Ҫʵ����͹���CPU��IO��Ҫ���ȷ���ĵ�ƽ�����̳��˰�����LED�ӿ�����IOȫ������ͣ�
              ����Ҫʹ�ó��͹���ָ�
                            
              ʵ�������
              ACTIVE-HALT��������/CPU/���������ֹͣ��LSI/LSE���У�BEEP/IWDG/RTC/LCD��һ������
              ʹ�ܣ�����ͨ��HALTָ�����ACTIVD-HALTģʽ��
              
              ʵ�������Լ1.1ua
              RTC�жϻ��ѣ�LED��һ��Ƶ����˸
              ���������AN3147
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    PWR_FastWakeUpCmd(ENABLE);  //���ٻ���ʹ��
   
    RTC_Config();
     //����IO����͵�ƽ
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_Low_Slow);

    PWR_UltraLowPowerCmd(ENABLE);//���͹���
     
    enableInterrupts();  
    while(1)
    {
      
         halt();
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
