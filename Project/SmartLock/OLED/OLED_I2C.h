#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

#include "stm8l15x.h"
#define IICSPEED 300000       //100K速度，时钟速度至少1M，400K速度，时钟速度至少4M
#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_RegInit(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
void WriteMultiData(unsigned char *I2C_Data, uint8_t size);
void WriteMultiData2(unsigned char I2C_Data, uint16_t size);
void OLED_ShowNum(unsigned char x, unsigned char y, uint16_t Num,unsigned char TextSize);

#endif
