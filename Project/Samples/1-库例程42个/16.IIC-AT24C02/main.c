/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
********************************************************************************
****例程简介:STM8L152K4库例程GPIO例程
*******************************************************************************/
#include "stm8l15x.h"
#include "24c0x.h"
//定义LED与按键接口
#define LED1_GPIO_PORT  GPIOC
#define LED1_GPIO_PINS  GPIO_Pin_4


unsigned char WBuf[]={"STM8L IIC读写24C0X!\r\n"};
#define BufferSize  30
unsigned char RBuf[BufferSize];
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：延时函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：先将字符串写入AT24C02，然后从AT24C02里面读出
              SCL-PC1，SDA-PC0
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
int main( void )
{
    GPIO_Init(LED1_GPIO_PORT, LED1_GPIO_PINS, GPIO_Mode_Out_PP_Low_Slow);//初始化LED1接口
    CLK_PeripheralClockConfig (CLK_Peripheral_I2C1,ENABLE);//开启IIC1时钟门控
      
    InitIIC();                                             //初始化IIC
    EEPROM_WriteData(WBuf,EEPROM_BASE_ADDRESS,BufferSize); //写入AT24C02
    EEPROM_ReadData(RBuf,EEPROM_BASE_ADDRESS,BufferSize);  //从AT24C02里面读出
 
    while(1)
    {
        GPIO_ToggleBits(LED1_GPIO_PORT, LED1_GPIO_PINS);//翻转LED1接口电平，实现LED1闪烁
        Delay(0xFFFF);//延时，便于观察实验现象
    }

}

/*******************************************************************************
*******************************蓝旗嵌入式系统***********************************
*************************http://lenchimcu.taobao.com****************************
*******************************************************************************/
