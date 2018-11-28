/******************************************************************************

                  ��Ȩ���� (C), 2010--2100, BM TECH

 ******************************************************************************
  �� �� ��   : system.h
  �� �� ��   : ����
  ��    ��   : belife
  ��������   : 2018��11��28��
  ����޸�   :
  ��������   : ϵͳ����ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��11��28��
    ��    ��   : belife
    �޸�����   : �����ļ�

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
	LP_MSG_FP_CHECK_OK,	//ָ��
	LP_MSG_FP_CHECK_FAIL,//ָ��
	LP_MSG_ICC_CHECK_OK,	//IC��
	LP_MSG_ICC_CHECK_FAIL,	//IC��

    LP_MSG_SYS_ENTER_SLEEP, //ϵͳ����˯��ģʽ

	HP_LP_MSG_FLAG,				//�ߵ����ȼ�MSG ��־λ��

	HP_MSG_KEY_PRESS_DETECTED,	//���������ж�
	HP_MSG_FP_PRESS_DETECTED,			//ָ�ƴ��������ж�
	HP_MSG_IC_CARD_DETECTED,	//IC CARD �ӽ��ж�

	MSG_MAX_ENUM,
}MSG_ID_ENUM;

typedef enum SYS_STATE
{
	SYS_STA_SLEEP_MODE,		//˯��ģʽ,�͹���ģʽ
	SYS_STA_AWAKE_MODE,		//����ģʽ,���Խ��н���
	SYS_STA_SETTING_MODE,	//����ģʽ,�������ã����ɽ���
	SYS_STA_BURN_IN_MODE,	//�ϻ�ģʽ,�������������������
          
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

