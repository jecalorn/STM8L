/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED_I2C.c
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : 小林
* Version: 1.00
* Date   : 2014.4.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64点阵的OLED显示屏驱动文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动IIC通信方式显示屏
*
* Others: none;
*
* Function List:
*	1. void I2C_Configuration(void) -- 配置CPU的硬件I2C
* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- 向寄存器地址写一个byte的数据
* 3. void WriteCmd(unsigned char I2C_Command) -- 写命令
* 4. void WriteDat(unsigned char I2C_Data) -- 写数据
* 5. void OLED_RegInit(void) -- OLED屏初始化
* 6. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 7. void OLED_Fill(unsigned char fill_Data) -- 全屏填充
* 8. void OLED_CLS(void) -- 清屏
* 9. void OLED_ON(void) -- 唤醒
* 10. void OLED_OFF(void) -- 睡眠
* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- 显示字符串(字体大小有6*8和8*16两种)
* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- 显示中文(中文需要先取模，然后放到codetab.h中)
* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMP图片
*
* History: none;
*
*************************************************************************************/

#include "OLED_I2C.h"
#include "stm8l15x.h"
//#include "delay.h"
#include "codetab.h"


extern void Delay(__IO uint16_t nCount);

void I2C_Configuration(void)
{
  I2C_DeInit(I2C1);
  I2C_Init(I2C1,IICSPEED, OLED_ADDRESS, I2C_Mode_I2C,I2C_DutyCycle_2, I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);
  I2C_Cmd(I2C1,ENABLE);
}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//器件地址 -- 默认0x78
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, data);//发送数据
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1, ENABLE);//关闭I2C1总线
}

void WriteCmd(unsigned char I2C_Command)//写命令
{
	I2C_WriteByte(0x00, I2C_Command);
}

void WriteDat(unsigned char I2C_Data)//写数据
{
	I2C_WriteByte(0x40, I2C_Data);
}

/* BEGIN: Added by belife, 2018/11/26 */
void WriteMultiData(unsigned char *I2C_Data, uint8_t size)
{   
    uint8_t addr = 0x40;
    uint8_t i = size;

    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//器件地址 -- 默认0x78
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    while ( i!=0 )
    {
        I2C_SendData(I2C1, *I2C_Data);//发送数据
        I2C_Data ++;
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//        I2C_AcknowledgeConfig(I2C1,ENABLE);

        i--;
    }


//	I2C_SendData(I2C1, data);//发送数据
//	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1, ENABLE);//关闭I2C1总线
}
void WriteMultiData2(unsigned char I2C_Data, uint16_t size)
{   
    uint8_t addr = 0x40;
    uint16_t i = size;

    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//器件地址 -- 默认0x78
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    while ( i!=0 )
    {
        I2C_SendData(I2C1, I2C_Data);//发送数据
        i--;

        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//        I2C_AcknowledgeConfig(I2C1,ENABLE);

    }


//	I2C_SendData(I2C1, data);//发送数据
//	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C1, ENABLE);//关闭I2C1总线
}

/* END:   Added by belife, 2018/11/26   PN: */


void OLED_RegInit(void)
{
	//DelayMs(100); //这里的延时很重要
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel

}

void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char fill_Data)//全屏填充
{
    uint16_t m,n;
//	unsigned char m,n;
      {
          WriteCmd(0xb0);       //page0-page1
          WriteCmd(0x00);     //low column start address
          WriteCmd(0x10);     //high column start address

          WriteMultiData2(fill_Data, 1024);

//          for(n=0;n<1024;n++)
//              {
//                  WriteDat(fill_Data);
//              }
      }


//	for(m=0;m<8;m++)
//	{
//		WriteCmd(0xb0+m);		//page0-page1
//		WriteCmd(0x00);		//low column start address
//		WriteCmd(0x10);		//high column start address
//		for(n=0;n<128;n++)
//			{
//				WriteDat(fill_Data);
//			}
//	}
}

void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}


//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch, unsigned char TextSize)
{
	unsigned char i = 0;
	unsigned char c = 0;

    c = ch - 32;
	switch(TextSize)
	{
		case 1:
            OLED_SetPos(x,y);
            for(i=0;i<6;i++)
                WriteDat(F6x8[c][i]);
            break;
		case 2:
            OLED_SetPos(x,y);
            for(i=0;i<8;i++)
                  WriteDat(F8X16[c*16+i]);

            OLED_SetPos(x,y+1);
            for(i=0;i<8;i++)
                  WriteDat(F8X16[c*16+i+8]);
            break;
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
					WriteDat(F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
//                WriteMultiData((unsigned char *)&F8X16[c*16], 8);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
//                WriteMultiData((unsigned char *)&F8X16[c*16+8], 8);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}


//--------------------------------------------------------------
// Prototype      : void OLED_ShowNum(unsigned char x, unsigned char y, uint16_t Num)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); Num:16位数字,
//                  TextSize,显示codetab.h中的ASCII字符,有6*8和8*16可选择
// Description    : 数字
//--------------------------------------------------------------
void OLED_ShowNum(unsigned char x, unsigned char y, uint16_t Num,unsigned char TextSize)
{

    char ch[9];
    char i = 0;


    if(Num<10)  //9
    { 
        ch[i++]= Num%10+48;
    }
    else if(Num<100) //98
    {
        ch[i++]= Num/10+48;
        ch[i++]= Num%10+48;
    }
    else if(Num<1000) //988
    {
        ch[i++]= Num/100+48;
        ch[i++]= Num%100/10+48;
        ch[i++]= Num%10+48;
    }
    else if(Num<10000) //9999
    {
        ch[i++]= Num/1000+48;
        ch[i++]= Num%1000/100+48;
        ch[i++]= Num%100/10+48;
        ch[i++]= Num%10+48;
    }
    else if(Num<100000) //99999
    {
        ch[i++]= Num/10000+48;
        ch[i++]= Num%10000/1000+48;
        ch[i++]= Num%1000/100+48;
        ch[i++]= Num%100/10+48;
        ch[i++]= Num%10+48;
    } 
    else if(Num<1000000) //999999
    {
        ch[i++]= Num/100000+48;
        ch[i++]= Num%100000/10000+48;
        ch[i++]= Num%10000/1000+48;
        ch[i++]= Num%1000/100+48;
        ch[i++]= Num%100/10+48;
        ch[i++]= Num%10+48;
    }
    else if(Num<10000000) //999999
    {
        ch[i++]= Num/1000000+48;
        ch[i++]= Num%1000000/100000+48;
        ch[i++]= Num%100000/10000+48;
        ch[i++]= Num%10000/1000+48;
        ch[i++]= Num%1000/100+48;
        ch[i++]= Num%100/10+48;
        ch[i++]= Num%10+48;
    }

    ch[i] = '\0';

    OLED_ShowStr(x, y, ch, TextSize);

    return;


}


void OLED_Init()
{
    //初始化I2C
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//开启IIC1时钟门控
    I2C_Configuration();

    Delay(0xFFFF);//需要延时一会

    OLED_RegInit(); 

    OLED_Fill(0);

    return;
}

void OLED_test()
{
    uint16_t i = 0;


    //初始化I2C
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//开启IIC1时钟门控
    I2C_Configuration();

    Delay(0xFFFF);//需要延时一会
    OLED_RegInit(); 

    OLED_Fill(0);

    return;

//    while ( 1 )
    {

        i++;

        OLED_ShowNum(40, 4, i, 2);
//        Delay(0xFF);//延时，便于观察实验现象


//        OLED_Fill(0x00);//全屏灭

//        OLED_ShowStr(0,0,"WWW.BMTECH.COM",2);
//        OLED_ShowStr(1,2,"WWW.BMTECH.COM",2);
//        OLED_ShowStr(2,4,"WWW.BMTECH.COM",2);
//        OLED_ShowStr(3,6,"WWW.BMTECH.COM",2);

//        OLED_Fill(0xFF);
//
//
//        Delay(0xFFFF);//延时，便于观察实验现象
//        Delay(0xFFFF);//延时，便于观察实验现象
//        OLED_Fill(0x00);
//
//        Delay(0xFFFF);//延时，便于观察实验现象
//        Delay(0xFFFF);//延时，便于观察实验现象
    }
}

