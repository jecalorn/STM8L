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
****������ע����Լ1SLED1�ᷭתһ�Σ�����ԭ���������ע�ͣ��жϴ��������ļ�
              it.c���棬TIM4���ж���������25
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED1��GPC4�����������
    CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //ʹ������ʱ�ӣ�STM8LĬ����������ʱ�ӳ�ʼʱ�رգ�ʹ��ǰ�쿪��
       
    TIM4_TimeBaseInit(TIM4_Prescaler_128, 0xff);//16M/8/128=15.625K��0xff=255,255*��1/15.625��=0.01632S����Լ61���ж���1S
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);//��������жϣ��жϺ���������Ϊ25
    TIM4_Cmd(ENABLE);//ʹ��
    
    enableInterrupts();//ʹ���ж��ܿ���
    
    while(1)
    {
      
    }
    
    
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
