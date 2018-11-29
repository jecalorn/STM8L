/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4�����̹���Demo
*******************************************************************************/
#include "stm8l15x.h"

//���¶���LED�밴���Ľӿ�
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PINS  GPIO_Pin_4

#define KEY_GPIO_PORT  GPIOD
#define KEY_GPIO_PINS  GPIO_Pin_4
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
/**
  * @brief  Compute the frequency of the LSI clock expressed in Hertz.
  * @note   The timer clock must be a high speed clock: HSI or HSE
  * @note   It is recommended to use the maximum clock frequency, that is 10 MHz,
  *         to obtain a more precise result.
  * @param  TIM2_TimerClockFreq The TIM2 clock frequency expressed in Hertz.
  * @retval LSI Clock Frequency value.
  */
uint32_t TIM2_ComputeLsiClockFreq(uint32_t TIM2_TimerClockFreq)
{
  uint32_t LSIClockFreq;
  uint16_t ICValue1, ICValue2;

  /* Capture only every 8 events!!! */
  TIM2_ICInit(TIM2_Channel_1, TIM2_ICPolarity_Rising, TIM2_ICSelection_DirectTI, TIM2_ICPSC_DIV8, 0x0);

  /* Enable CC1 interrupt */
  TIM2_ITConfig(TIM2_IT_CC1, ENABLE);

  /* Enable TIM2 */
  TIM2_Cmd(ENABLE);

  TIM2->SR1 = 0x00;
  TIM2->SR2 = 0x00;

  /* Clear CC1 Flag*/
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* wait a capture on cc1 */
  while ((TIM2->SR1 & (uint8_t)TIM2_FLAG_CC1) != (uint8_t)TIM2_FLAG_CC1)
  {}
  /* Get CCR1 value*/
  ICValue1 = TIM2_GetCapture1();
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* wait a capture on cc1 */
  while ((TIM2->SR1 & (uint8_t)TIM2_FLAG_CC1) != (uint8_t)TIM2_FLAG_CC1)
  {}
  /* Get CCR1 value*/
  ICValue2 = TIM2_GetCapture1();
  TIM2_ClearFlag(TIM2_FLAG_CC1);

  /* Disable IC1 input capture */
  TIM2->CCER1 &= (uint8_t)(~TIM_CCER1_CC1E);
  /* Reset CCMR1 register */
  TIM2->CCMR1 = 0x00;
  /* Disable TIM2 */
  TIM2_Cmd(DISABLE);

  /* Compute LSI clock frequency */
  LSIClockFreq = (8 * TIM2_TimerClockFreq) / (ICValue2 - ICValue1);
  return LSIClockFreq;
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����������J13���ߣ��ճ����ʱ����Ҫ�Ͽ�����������ٶ̽ӡ���ΪSWIM�ܽ�
             �ͷ������ܽ��Ǹ��õġ�
             ʹ��LSI��������ʱ��Դ��Ҫ��У׼LSI
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
uint32_t frq=0;//LSIƵ��
int main( void )
{
    
    CLK_PeripheralClockConfig(CLK_Peripheral_BEEP, ENABLE);//����������ʱ���ſ�
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);//��ҪTIM2���벶�����LSIƵ�ʣ�����TIM2ʱ���ſ�Ҳ����
    
    BEEP_DeInit();//��ʼ����������ؼĴ���
    BEEP_Cmd(DISABLE); //����������ǰ�����
    
    CLK_BEEPClockConfig(CLK_BEEPCLKSource_LSI);//ѡ��ʱ��Դ
    BEEP_LSClockToTIMConnectCmd(ENABLE);//LSIоƬ�ڲ�������TIM2���Ա����LSIƵ��
    frq=TIM2_ComputeLsiClockFreq(2000000);//TIM2���벶�����LSIƵ�� 
    BEEP_LSClockToTIMConnectCmd(DISABLE);//LSIоƬ�ڲ�������TIM2���Ա����LSIƵ��  
    
    BEEP_LSICalibrationConfig(frq);//У׼LSI
        
    BEEP_Init(BEEP_Frequency_1KHz);//��������Ƶ��
    BEEP_Cmd(ENABLE);
  
  while (1)
  {  
    
  }
}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
