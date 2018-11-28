/******************************************************************************

                  版权所有 (C), 2010--2100, BM TECH

 ******************************************************************************
  文 件 名   : queue.c
  版 本 号   : 初稿
  作    者   : belife
  生成日期   : 2018年11月26日
  最近修改   :
  功能描述   : 消息队列处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年11月26日
    作    者   : belife
    修改内容   : 创建文件

******************************************************************************/
/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "stm8l15x.h"
#include "system.h"

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
#define MAX_HP_MSG_QUEUE 3	    //高优先级队列深度
#define MAX_LP_MSG_QUEUE 4	    //低优先级队列深度

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/
static uint8_t HP_msg_in_index = 0;        //高优先级队列IN指针
static uint8_t HP_msg_out_index = 0;     //高优先级队列OUT指针
static uint8_t LP_msg_in_index = 0;        //低优先级队列IN指针
static uint8_t LP_msg_out_index = 0;     //低优先级队列OUT指针
static MSG_ID_ENUM HP_MSG_QUEUE[MAX_HP_MSG_QUEUE]; //HP消息队列
static MSG_ID_ENUM LP_MSG_QUEUE[MAX_LP_MSG_QUEUE]; //LP消息队列


/*****************************************************************************
 函 数 名  : msg_enqueue
 功能描述  : 消息进入队列
 输入参数  : MSG_ID_ENUM Msg  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年11月26日
    作    者   : belife
    修改内容   : 新生成函数

*****************************************************************************/
void msg_enqueue(MSG_ID_ENUM Msg)
{

	if(Msg >= MSG_MAX_ENUM) return;

	if(Msg > HP_LP_MSG_FLAG)     //HP_MSG
    {
    	if((HP_msg_in_index+1)%MAX_HP_MSG_QUEUE != HP_msg_out_index)//队列未满
        {
        	HP_MSG_QUEUE[HP_msg_in_index++] = Msg;
        	if(HP_msg_in_index >= MAX_HP_MSG_QUEUE) //数据归零
            {
            	HP_msg_in_index = 0;
            }
        }
    	else	 //队列已满
        {
            //assert(0)
        }
    }
	else	                     //LP_MSG
    {
    	if((LP_msg_in_index+1)%MAX_LP_MSG_QUEUE != LP_msg_out_index)//队列未满
        {
        	LP_MSG_QUEUE[LP_msg_in_index++] = Msg;
        	if(LP_msg_in_index >= MAX_LP_MSG_QUEUE) //数据归零
            {
            	LP_msg_in_index = 0;
            }
        }
    	else	 //队列已满
        {
            //assert(0)
        }

    }
}
/*****************************************************************************
 函 数 名  : msg_dequeue
 功能描述  : 消息队列出列
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
MSG_ID_ENUM msg_dequeue()
{
	MSG_ID_ENUM Msg;

	if(HP_msg_in_index != HP_msg_out_index) //高优先级队列不为空
    {
    	Msg = HP_MSG_QUEUE[HP_msg_out_index++];
    	if(HP_msg_out_index >= MAX_HP_MSG_QUEUE) //数据归零
        {
        	HP_msg_out_index = 0;
        }
    }
	else if(LP_msg_in_index != LP_msg_out_index)//低优先级队列不为空
    {
    	Msg = LP_MSG_QUEUE[LP_msg_out_index++];
    	if(LP_msg_out_index >= MAX_LP_MSG_QUEUE) //数据归零
        {
        	LP_msg_out_index = 0;
        }
    }
	else	 //消息队列为空
    {
    	Msg = MSG_MAX_ENUM;
    }

	return Msg;

}

/*****************************************************************************
 函 数 名  : msg_queue_empty_check
 功能描述  : 判断消息队列是否为空；
                 1：消息队列空； 
                 0：消息队列不空
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
uint8_t msg_queue_empty_check()
{
    if (( HP_msg_in_index == HP_msg_out_index )
        && (LP_msg_in_index == LP_msg_out_index))
    {
        return 1;
    }
    else
    {
        return 0;
    }
      


}

