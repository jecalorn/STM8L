/******************************************************************************

                  版权所有 (C), 2010--2100, BM TECH

 ******************************************************************************
  文 件 名   : system.c
  版 本 号   : 初稿
  作    者   : belife
  生成日期   : 2018年11月28日
  最近修改   :
  功能描述   : 指纹锁系统处理
  函数列表   :
              system_finger_press_handler
              system_init
              system_key_input_handler
              system_key_press_handler
              system_run
  修改历史   :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "stm8l15x.h"
#include "system.h"
#include "OLED_I2C.h"

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/




/*****************************************************************************
 函 数 名  : system_init
 功能描述  : 系统初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_init()
{
    extern void key_init();
    extern void OLED_Init();

    //OLED 初始化
    OLED_Init();

    //按键初始化
    key_init();
}

/*****************************************************************************
 函 数 名  : system_sleep
 功能描述  : 系统进入低功耗睡眠模式
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_sleep()
{



}
/*****************************************************************************
 函 数 名  : system_sleep_timer_start
 功能描述  : 启动进入睡眠的定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

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
 函 数 名  : system_sleep_timer_stop
 功能描述  : 关闭进入睡眠的定时器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_sleep_timer_stop()
{
    /* Disable TIM4 CLK */
    CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, DISABLE);

    /* Disable TIM4 */
    TIM4_Cmd(DISABLE);
}
/*****************************************************************************
 函 数 名  : system_sleep_timer_handler
 功能描述  : 睡眠定时器中断处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_sleep_timer_handler()
{

}

/*****************************************************************************
 函 数 名  : system_run
 功能描述  : 指纹锁系统处理主函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_run()
{
    MSG_ID_ENUM msg_id;

    while (1)
    {
        //如果消息队列为空，则进入超低功耗运行，等待中断
        while(msg_queue_empty_check())
        {
            //启动进入停机的定时器，若干时间后，进入低功耗模式。
            system_sleep_timer_start();

            //进入等待中断模式
            wfi();
        }
        //关闭进入超低功耗模式定时器
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
 函 数 名  : system_key_input_handler
 功能描述  : 按键键值处理函数
 输入参数  : MSG_ID_ENUM msg_id  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_key_input_handler(MSG_ID_ENUM msg_id)
{
    char ch[] = "MSG HANDLER";
    uint16_t num = msg_id;

    OLED_ShowStr(4, 2, ch, 2);
    OLED_ShowNum(40, 4, num, 2);
}

/*****************************************************************************
 函 数 名  : system_key_press_handler
 功能描述  : 按键中断处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

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
 函 数 名  : system_finger_press_handler
 功能描述  : 指纹按下中断处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void system_finger_press_handler()
{

    msg_enqueue(LP_MSG_FP_CHECK_OK);

}



/*****************************************************************************/
//以下为测试函数，可以删除
/*****************************************************************************/

void test_simulate_key1_press()
{
    msg_enqueue(HP_MSG_KEY_PRESS_DETECTED);
}

void test_simulate_key3_press()
{
    msg_enqueue(HP_MSG_FP_PRESS_DETECTED);
}

