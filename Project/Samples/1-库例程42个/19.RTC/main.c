/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****���̼��:STM8L152K4������
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
****��������:
****��������:��ʱ����
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��Ҫ��ʱ����Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }
}
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��ʱ�ӳ�ʼ������
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
void Calendar_Init(void)
{
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStr.RTC_AsynchPrediv = 0x7f;
  RTC_InitStr.RTC_SynchPrediv = 0x0139;//���� ʱ���������С ʱ����
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
****��ڲ�������
****���ڲ�������
****������ע��
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
*******************************************************************************/
int main( void )
{
    unsigned short temp1,temp2;
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//RTCʱ��ʹ��LSE
    CLK_PeripheralClockConfig (CLK_Peripheral_RTC,ENABLE);//����RTCʱ���ſ�
    RTC_DeInit( ); //RTC��ʼ������ʼ״̬
      
    Calendar_Init();
    
    Delay(100);           //��ʱһ��ʱ�� 
    InitLCD();            //��ʼ����Ļ
    Delay(100);           //��ʱһ��ʱ�� 

  
    while (1)
    {
        RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);//��ȡĿǰʱ��
        temp1 = RTC_TimeStr.RTC_Seconds;//��
        temp2=RTC_TimeStr.RTC_Minutes;  //��
        //����Ϊ��ʾ����
        data_convertor(temp2*100+temp1);
        Display();//��ʾʱ��
        Display_lcd_dot();//��ʾ����
       
    }

}

/*******************************************************************************
*******************************����Ƕ��ʽϵͳ***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
