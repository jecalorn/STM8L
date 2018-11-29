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
****������ע��GPIO������Գ���PC4������ʽ����LED1-��ɫ��PB0������ʽ����LED2-��ɫ��PD2
              ͨ��������ʽ����LED3-��ɫ��PD4���Ӷ�������K1��PD4���Ӷ�������K1��PA2����
              ��������K2��PB3���Ӷ�������K3��ͨ�����϶�ȡ��������ӦIO�ڵĵ�ƽ�ж��Ƿ���
              �������£�ע��Ҫʹ���������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    //��ʼ��3��LED�������˿�  
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//����������������͵�ƽ
    GPIO_Init(LED2_GPIO_PORT, LED2_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//����������������͵�ƽ
    GPIO_Init(LED3_GPIO_PORT, LED3_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//����������������͵�ƽ
    //��ʼ��3�������ӿ�
    GPIO_Init(KEY1_GPIO_PORT, KEY1_GPIO_PINS, GPIO_Mode_In_PU_No_IT);//��ʼ��������GPD4��������
    GPIO_Init(KEY2_GPIO_PORT, KEY2_GPIO_PINS, GPIO_Mode_In_PU_No_IT);//��ʼ��������GPA2��������
    GPIO_Init(KEY3_GPIO_PORT, KEY3_GPIO_PINS, GPIO_Mode_In_PU_No_IT);//��ʼ��������GPB3��������
    while(1)
    {
         if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PINS)==0)//��GPD4����״̬
         {
             Delay(0x3FFF);  //�������
             if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT,KEY1_GPIO_PINS)==0)  //��GPD4����״̬
                GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//��תGPC4���״̬
         }
         if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PINS)==0)//��GPA2����״̬
         {
             Delay(0x3FFF);  //�������
             if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT,KEY2_GPIO_PINS)==0)  //��GPA2����״̬
                GPIO_ToggleBits(LED2_GPIO_PORT, LED2_GPIO_PINS);//��תGPB0���״̬
         }
         if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_GPIO_PINS)==0)//��GPB3����״̬
         {
             Delay(0x3FFF);  //�������
             if(GPIO_ReadInputDataBit(KEY3_GPIO_PORT,KEY3_GPIO_PINS)==0)  //��GPB3����״̬
                GPIO_ToggleBits(LED3_GPIO_PORT, LED3_GPIO_PINS);//��תGPD2���״̬
         }
    }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
