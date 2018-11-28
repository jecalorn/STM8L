/******************************************************************************

                  版权所有 (C), 2010--2100, BM TECH

 ******************************************************************************
  文 件 名   : system.h
  版 本 号   : 初稿
  作    者   : belife
  生成日期   : 2018年11月28日
  最近修改   :
  功能描述   : 系统配置头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年11月28日
    作    者   : belife
    修改内容   : 创建文件

******************************************************************************/
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

typedef enum MSG_ID
{
	LP_MSG_KEY_0,		//0
	LP_MSG_KEY_1,		//1
	LP_MSG_KEY_2,		//2
	LP_MSG_KEY_3,		//3
	LP_MSG_KEY_4,		//4
	LP_MSG_KEY_5,		//5
	LP_MSG_KEY_6,		//6
	LP_MSG_KEY_7,		//7
	LP_MSG_KEY_8,		//8
	LP_MSG_KEY_9,		//9
	LP_MSG_KEY_STAR,	//*
	LP_MSG_KEY_HASH,	//#
	LP_MSG_FP_CHECK_OK,	//指纹
	LP_MSG_FP_CHECK_FAIL,//指纹
	LP_MSG_ICC_CHECK_OK,	//IC卡
	LP_MSG_ICC_CHECK_FAIL,	//IC卡

    LP_MSG_SYS_ENTER_SLEEP, //系统进入睡眠模式

	HP_LP_MSG_FLAG,				//高低优先级MSG 标志位。

	HP_MSG_KEY_PRESS_DETECTED,	//按键按下中断
	HP_MSG_FP_PRESS_DETECTED,			//指纹触摸按下中断
	HP_MSG_IC_CARD_DETECTED,	//IC CARD 接近中断

	MSG_MAX_ENUM,
}MSG_ID_ENUM;

typedef enum SYS_STATE
{
	SYS_STA_SLEEP_MODE,		//睡眠模式,低功耗模式
	SYS_STA_AWAKE_MODE,		//唤醒模式,可以进行解锁
	SYS_STA_SETTING_MODE,	//设置模式,可以设置，不可解锁
	SYS_STA_BURN_IN_MODE,	//老化模式,反复进行马达寿命测试
          
}SYS_STATE_ENUM;






extern MSG_ID_ENUM msg_dequeue();
extern void msg_enqueue(MSG_ID_ENUM Msg);
extern uint8_t msg_queue_empty_check();


extern void system_finger_press_handler();
extern void system_init();
extern void system_key_input_handler(MSG_ID_ENUM msg_id);
extern void system_key_press_handler();
extern void system_run();



























#endif /* __SYSTEM_H__ */

