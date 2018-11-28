/******************************************************************************

                  ��Ȩ���� (C), 2010--2100, BM TECH

 ******************************************************************************
  �� �� ��   : system.c
  �� �� ��   : ����
  ��    ��   : belife
  ��������   : 2018��11��28��
  ����޸�   :
  ��������   : ָ����ϵͳ����
  �����б�   :
              system_finger_press_handler
              system_init
              system_key_input_handler
              system_key_press_handler
              system_run
  �޸���ʷ   :
  1.��    ��   : 2018��11��28��
    ��    ��   : belife
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "stm8l15x.h"
#include "system.h"
#include "OLED_I2C.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/




/*****************************************************************************
 �� �� ��  : system_init
 ��������  : ϵͳ��ʼ������
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
void system_init()
{
    extern void key_init();
    extern void OLED_Init();

    //OLED ��ʼ��
    OLED_Init();

    //������ʼ��
    key_init();
}

/*****************************************************************************
 �� �� ��  : system_sleep
 ��������  : ϵͳ����͹���˯��ģʽ
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
void system_sleep()
{



}
/*****************************************************************************
 �� �� ��  : system_sleep_timer_start
 ��������  : ��������˯�ߵĶ�ʱ��
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
void system_sleep_timer_start()
{

#if  0
/*--------------CLK CONFIG---------------------------------------------------*/
    /* High speed internal clock prescaler: 1 */
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
    
    /* Select HSE as system clock source */
    CLK_SYSCLKSourceSwitchCmd(ENABLE);
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);
    
    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSE)
    {}
    
    /* Enable TIM4 CLK */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);

/*--------------TIM4 CONFIG--------------------------------------------------*/
    /* TIM4 configuration:
     - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
     clock used is 16 MHz / 128 = 125 000 Hz
    - With 125 000 Hz we can generate time base:
        max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
        min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
    - In this example we need to generate a time base equal to 1 ms
     so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */
    
    /* Time base configuration */
    TIM4_TimeBaseInit(TIM4_Prescaler_128, TIM4_PERIOD);
    /* Clear TIM4 update flag */
    TIM4_ClearFlag(TIM4_FLAG_Update);
    /* Enable update interrupt */
    TIM4_ITConfig(TIM4_IT_Update, ENABLE);
    /* enable interrupts */
    enableInterrupts();
    
    /* Enable TIM4 */
    TIM4_Cmd(ENABLE);

#endif /* #if 0 */

}
/*****************************************************************************
 �� �� ��  : system_sleep_timer_stop
 ��������  : �رս���˯�ߵĶ�ʱ��
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
void system_sleep_timer_stop()
{
    /* Disable TIM4 CLK */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);

    /* Disable TIM4 */
    TIM4_Cmd(DISABLE);
}
/*****************************************************************************
 �� �� ��  : system_sleep_timer_handler
 ��������  : ˯�߶�ʱ���жϴ�����
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
void system_sleep_timer_handler()
{

}

/*****************************************************************************
 �� �� ��  : system_run
 ��������  : ָ����ϵͳ����������
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
void system_run()
{
    MSG_ID_ENUM msg_id;

    while (1)
    {
        //�����Ϣ����Ϊ�գ�����볬�͹������У��ȴ��ж�
        while(msg_queue_empty_check())
        {
            //��������ͣ���Ķ�ʱ��������ʱ��󣬽���͹���ģʽ��
            system_sleep_timer_start();

            //����ȴ��ж�ģʽ
            wfi();
        }
        //�رս��볬�͹���ģʽ��ʱ��
        system_sleep_timer_stop();

        msg_id  = msg_dequeue();

        switch ( msg_id )
        {
            case LP_MSG_KEY_0:
            case LP_MSG_KEY_1:
            case LP_MSG_KEY_2:
            case LP_MSG_KEY_3:
            case LP_MSG_KEY_4:
            case LP_MSG_KEY_5:
            case LP_MSG_KEY_6:
            case LP_MSG_KEY_7:
            case LP_MSG_KEY_8:
            case LP_MSG_KEY_9:
            case LP_MSG_KEY_STAR:
            case LP_MSG_KEY_HASH:
            case LP_MSG_FP_CHECK_OK:
            case LP_MSG_FP_CHECK_FAIL:
            case LP_MSG_ICC_CHECK_OK:
            case LP_MSG_ICC_CHECK_FAIL:
                system_key_input_handler(msg_id);
                break;
            case LP_MSG_SYS_ENTER_SLEEP :
                system_sleep();
                break;

            case HP_MSG_KEY_PRESS_DETECTED:
                system_key_press_handler();
                break;

            case HP_MSG_FP_PRESS_DETECTED:
                system_finger_press_handler();
                break;

            case HP_MSG_IC_CARD_DETECTED:
                break;

            default:
                break;
        }

    }

}
/*****************************************************************************
 �� �� ��  : system_key_input_handler
 ��������  : ������ֵ������
 �������  : MSG_ID_ENUM msg_id  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��11��28��
    ��    ��   : belife
    �޸�����   : �����ɺ���

*****************************************************************************/
void system_key_input_handler(MSG_ID_ENUM msg_id)
{
    char ch[] = "MSG HANDLER";
    uint16_t num = msg_id;

    OLED_ShowStr(4, 2, ch, 2);
    OLED_ShowNum(40, 4, num, 2);
}

/*****************************************************************************
 �� �� ��  : system_key_press_handler
 ��������  : �����жϴ�����
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
void system_key_press_handler()
{
    static MSG_ID_ENUM msg = LP_MSG_KEY_0;

    msg_enqueue(msg);

    msg ++;

    if ( msg >=  HP_LP_MSG_FLAG)
    {
        msg = LP_MSG_KEY_0;
    }

}


/*****************************************************************************
 �� �� ��  : system_finger_press_handler
 ��������  : ָ�ư����жϴ�����
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
void system_finger_press_handler()
{

    msg_enqueue(LP_MSG_FP_CHECK_OK);

}



/*****************************************************************************/
//����Ϊ���Ժ���������ɾ��
/*****************************************************************************/

void test_simulate_key1_press()
{
    msg_enqueue(HP_MSG_KEY_PRESS_DETECTED);
}

void test_simulate_key3_press()
{
    msg_enqueue(HP_MSG_FP_PRESS_DETECTED);
}

