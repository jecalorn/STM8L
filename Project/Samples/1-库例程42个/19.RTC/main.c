/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程
*******************************************************************************/
#include "stm8l15x.h"
#include "lcd.h"


typedef uint8_t* string;
unsigned char Ht1621Tab[]={0x00,0x00,0x00,0x00};
RTC_InitTypeDef   RTC_InitStr;
RTC_TimeTypeDef   RTC_TimeStr;
RTC_DateTypeDef   RTC_DateStr;
RTC_AlarmTypeDef  RTC_AlarmStr;
/* Days names definition */
CONST string WeekDayNames[7] =
  {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

/* Months names definition */
CONST   uint8_t MonthNames[] = {'J', 'A', 'N', 'F', 'E', 'B', 'M', 'A', 'R', 'A', 'P', 'R',
                                  'M', 'A', 'Y', 'J', 'U', 'N', 'J', 'U', 'L', 'A', 'U', 'G',
                                  'S', 'E', 'P', 'O', 'C', 'T', 'N', 'O', 'V', 'D', 'E', 'C'};
/*******************************************************************************
****函数名称:
****函数功能:延时函数
****版本:V1.0
****日期:14-2-2014
****入口参数:需要延时的数目
****出口参数:无
****说明:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：时钟初始化函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Calendar_Init(void)
{
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStr.RTC_AsynchPrediv = 0x7f;
  RTC_InitStr.RTC_SynchPrediv = 0x0139;//调大 时间变慢，调小 时间变快
  RTC_Init(&RTC_InitStr);

  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Friday;
  RTC_DateStr.RTC_Date = 13;
  RTC_DateStr.RTC_Month = RTC_Month_May;
  RTC_DateStr.RTC_Year = 11;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);

  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 01;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);


  RTC_AlarmStructInit(&RTC_AlarmStr);
  RTC_AlarmStr.RTC_AlarmTime.RTC_Hours   = 01;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes = 01;
  RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds = 00;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(ENABLE);
}

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    unsigned short temp1,temp2;
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//RTC时钟使用LSE
    CLK_PeripheralClockConfig (CLK_Peripheral_RTC,ENABLE);//开启RTC时钟门控
    RTC_DeInit( ); //RTC初始化至初始状态
      
    Calendar_Init();
    
    Delay(100);           //延时一段时间 
    InitLCD();            //初始化屏幕
    Delay(100);           //延时一段时间 

  
    while (1)
    {
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);//获取目前时间
        temp1 = RTC_TimeStr.RTC_Seconds;//秒
        temp2=RTC_TimeStr.RTC_Minutes;  //分
        //以下为显示处理
        data_convertor(temp2*100+temp1);
        Display();//显示时间
        Display_lcd_dot();//显示符号
       
    }

}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
