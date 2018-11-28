


#include "stm8l15x.h"
#include "gpio.h"



/*****************************************************************************
 �� �� ��  : key_init
 ��������  : ������ʼ��������ͨ���жϣ�ģ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��11��28��
    ��    ��   : belife
    �޸�����   : �����ɺ���

*****************************************************************************/
void key_init()
{

    GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPD4�����ж�����
    GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_IT);//��ʼ��������GPD4�����ж�����

    EXTI_DeInit (); //�ָ��жϵ��������� 

    EXTI_SelectPort(EXTI_Port_D);//ѡ��˿�D���ж�������7
    EXTI_SetPortSensitivity(EXTI_Port_D,EXTI_Trigger_Rising_Falling);//�˿�D�½��ش���
    EXTI_SetHalfPortSelection(EXTI_HalfPort_D_MSB,ENABLE);//�˿�D�ĸ���λ�ж�ʹ��


    EXTI_SelectPort(EXTI_Port_B);//ѡ��˿�D���ж�������7
    EXTI_SetPortSensitivity(EXTI_Port_B,EXTI_Trigger_Rising_Falling);//�˿�D�½��ش���
    EXTI_SetHalfPortSelection(EXTI_HalfPort_B_LSB,ENABLE);//�˿�D�ĸ���λ�ж�ʹ��

    enableInterrupts();//ʹ���ж�

}


void key_PD_irq_handler()
{
    EXTI_ClearITPendingBit (EXTI_IT_PortD);//����жϱ�־
    {

        if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PINS)==0)//�жϰ���1�Ƿ���
        {
            extern void test_simulate_key3_press();
            test_simulate_key3_press();
        }
    }

}

void key_PB_irq_handler()
{
    EXTI_ClearITPendingBit (EXTI_IT_PortB);//����жϱ�־
    {

        if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_GPIO_PINS)==0)//�жϰ���3�Ƿ���
        {
            extern void test_simulate_key1_press();
            test_simulate_key1_press();
        }
    }

}



