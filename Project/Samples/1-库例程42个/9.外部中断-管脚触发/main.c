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
****������ע���������ᴥ���жϣ�LED�ᷭת
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    //��ʼ��3��LED�������˿�  
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//����������������͵�ƽ
    GPIO_Init(LED2_GPIO_PORT, LED2_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//����������������͵�ƽ
    GPIO_Init(LED3_GPIO_PORT, LED3_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//����������������͵�ƽ
    //��ʼ��3�������ӿ�
    GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPD4�����ж�����
    GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPA2�����ж�����
    GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPB3�����ж�����
        
    EXTI_DeInit (); //�ָ��жϵ��������� 
    EXTI_SetPinSensitivity (EXTI_Pin_4,EXTI_Trigger_Falling);//�ⲿ�ж�4���½��ش������ж�������12
    EXTI_SetPinSensitivity (EXTI_Pin_2,EXTI_Trigger_Falling);//�ⲿ�ж�2���½��ش������ж�������10
    EXTI_SetPinSensitivity (EXTI_Pin_3,EXTI_Trigger_Falling);//�ⲿ�ж�3���½��ش������ж�������11
    
    enableInterrupts();//ʹ���ж�
    while(1)
    {
      
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
