/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  *                     By(JCML)
  * FileName   : oled.c
  * Version    : v1.0
  * Author     : JCML
  * Date       : 2023-02-02
  * Description: OLED显示的函数
******************************************************************************
 */

#include "OLED.h"
#include "SoftWare_I2C.h"
#include "OLEDFont.h"

uint16_t OLED_GRAM[128][64];//画线存数据
/***********************************************************
*@fuction:OLED_WR_Byte
*@brief	:OLED写一个字节
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/

void OLED_WR_Byte(unsigned char dat, unsigned char cmd)
{

    if (cmd == OLED_DATA)
        OLED_WritrDate(dat);
    else
        OLED_WriteCommand(dat);
}

/***********************************************************
*@fuction:OLED_WritrDate
*@brief	:OLED写数据
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/

void OLED_WritrDate(unsigned char dat)
{
    I2C_Start();
    Write_I2C_Byte(0x78);
    I2C_Wait_Ack();
    Write_I2C_Byte(0x40);//数字寄存器
    I2C_Wait_Ack();
    Write_I2C_Byte(dat);
    I2C_Wait_Ack();
    I2C_Stop();
}
/***********************************************************
*@fuction:OLED_WriteCommand
*@brief	:OLED写命令
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/

void OLED_WriteCommand(unsigned char dat)
{
    I2C_Start();
    Write_I2C_Byte (0x78);
    I2C_Wait_Ack();
    Write_I2C_Byte(0x00);//命令寄存器
    I2C_Wait_Ack();
    Write_I2C_Byte(dat);
    I2C_Wait_Ack();
    I2C_Stop();

}
/***********************************************************
*@fuction:OLED_Init
*@brief	:初始化
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/

void OLED_Init(void)
{
    OLED_WR_Byte(0xAE, OLED_CMD); //关显示

    OLED_WR_Byte(0x00, OLED_CMD); //列地址  低 00-0F
    OLED_WR_Byte(0x10, OLED_CMD); //列地址  高 10-1F

    OLED_WR_Byte(0x40, OLED_CMD); //显示起始行
    OLED_WR_Byte(0xB0, OLED_CMD); //--设置页地址 B0-B7

    OLED_WR_Byte(0x81, OLED_CMD); // 对比度  00~FF 越大越亮哦
    OLED_WR_Byte(0xFF, OLED_CMD); //--128

    OLED_WR_Byte(0xA1, OLED_CMD); //设置左右方向，0xA1正常 0xA0左右反置
	
    OLED_WR_Byte(0xC8, OLED_CMD); //设置上下方向，0xC8正常 0xC0上下反置
	
    OLED_WR_Byte(0xA6, OLED_CMD); //正常A6/反向A7 显示模式

    OLED_WR_Byte(0xA8, OLED_CMD); //设置驱动路数 1-64
    OLED_WR_Byte(0x3F, OLED_CMD); //--1/32 duty -----63

    OLED_WR_Byte(0xD3, OLED_CMD); //显示偏移offset
    OLED_WR_Byte(0x00, OLED_CMD); //

    OLED_WR_Byte(0xD5, OLED_CMD); //设置时钟分频、震荡频率
    OLED_WR_Byte(0x80, OLED_CMD); //[3:0]分频 [7:4]震荡频率

    OLED_WR_Byte(0xD8, OLED_CMD); //set area color mode off
    OLED_WR_Byte(0x05, OLED_CMD); //

    OLED_WR_Byte(0xD9, OLED_CMD); //预充电期
    OLED_WR_Byte(0xF1, OLED_CMD); //

    OLED_WR_Byte(0xDA, OLED_CMD); //引脚配置
    OLED_WR_Byte(0x12, OLED_CMD); //可选的引脚、不可重映射

    OLED_WR_Byte(0xDB, OLED_CMD); //set Vcomh(没试过)
    OLED_WR_Byte(0x30, OLED_CMD); //0x30: 0.83*Vcc  0x20: 0.77*Vcc  0x00: 0.65Vcc

    OLED_WR_Byte(0x8D, OLED_CMD); //电荷泵
    OLED_WR_Byte(0x14, OLED_CMD); //开启  0x10关闭

    OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel

    OLED_Clear();
}
/***********************************************************
*@fuction	:OLED_Set_Pos
*@brief	:设置起始点
*@param	:x的范围0～127，y为页的范围0～7
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0 + y, OLED_CMD);
    OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD); //高地址
    OLED_WR_Byte((x & 0x0f), OLED_CMD); //低地址
}
/***********************************************************
*@fuction:OLED_ShowChar
*@brief	:显示一个字符
*@param	:x的范围0～127，y为页的范围0～7，目前Char_Size可选 16，6
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char chr, unsigned char Char_Size)
{
    unsigned char gap = 0, i = 0;
    gap = chr - ' '; //得到偏移 即差值
    if(Char_Size == 16)
    {
        OLED_Set_Pos(x, y);
        for(i = 0; i < 8; i++)
            OLED_WR_Byte(F8X16[gap * 16 + i], OLED_DATA);

        OLED_Set_Pos(x, y + 1);
        for(i = 0; i < 8; i++)
            OLED_WR_Byte(F8X16[gap * 16 + i + 8], OLED_DATA);
    }
    else if(Char_Size == 6)
    {
        OLED_Set_Pos(x, y);
        for(i = 0; i < 6; i++)
            OLED_WR_Byte(F6x8[gap][i], OLED_DATA);
    }
    else
    {
        OLED_Set_Pos(x, y);
        for(i = 0; i < 8; i++)
            OLED_WR_Byte(~F8X16[gap * 16 + i], OLED_DATA);

        OLED_Set_Pos(x, y + 1);
        for(i = 0; i < 8; i++)
            OLED_WR_Byte(~F8X16[gap * 16 + i + 8], OLED_DATA);
    }
}
/***********************************************************
*@fuction:OLED_ShowString
*@brief	:显示字符串
*@param	:x的范围0～127，y为页的范围0～7，目前Char_Size可选 16，6
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowString(unsigned char x, unsigned char y, char *chr, unsigned char Char_Size)
{
    unsigned char j = 0;
    while (chr[j] != '\0')
    {
        OLED_ShowChar(x, y, chr[j], Char_Size);
        x += 8;
        if(x > 120)
        {
            x = 0;
            y += 2;
        }
        j++;
    }
}
/***********************************************************
*@fuction:oled_pow
*@brief	:搭配显示数字函数一起用
*@param	:void
*@return:m^n
*@author：JCML
*@date	:2023-02-02
***********************************************************/
unsigned int oled_pow(unsigned char m, unsigned char n)
{
    unsigned int result = 1;
    while(n--)result *= m;
    return result;
}
/***********************************************************
*@fuction:OLED_ShowNum
*@brief	:显示数字
*@param	:x的范围0～127，y为页的范围0～7，len:数的位数，Char_Size可选 16，6
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char len, unsigned char size2)
{
    unsigned char t, temp;
    for(t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10; //取各个位 从高位开始

        if(size2 == 16)
            OLED_ShowChar(x + (size2 / 2)*t, y, temp + '0', size2); //调整间隔、紧挨显示
        else if(size2 == 6)
            OLED_ShowChar(x + size2 * t, y, temp + '0', size2); //调整间隔、紧挨显示
				else
						 OLED_ShowChar(x + (size2 / 2)*t, y, temp + '0', size2); //调整间隔、紧挨显示
    }
}
/***********************************************************
*@fuction:OLED_ShowSignedNum
*@brief	:带符号数字显示
*@param	:x的范围0～127，y为页的范围0～7，len:数的位数，Char_Size可选 16，6
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowSignedNum(unsigned char x, unsigned char y, int num, unsigned char len, unsigned char size2)
{
	int Number;
	if (num >= 0)
	{
		OLED_ShowChar(x, y, '+', size2);
		Number = num;
	}
	else
	{
		OLED_ShowChar(x, y, '-', size2);
		Number = -num;
	}
	if(size2 == 16)
		OLED_ShowNum(x + (size2 / 2), y, Number, len, size2); //调整间隔、紧挨显示
	else if(size2 == 6)
		OLED_ShowNum(x + size2, y, Number, len, size2); //调整间隔、紧挨显示
}
/***********************************************************
*@fuction:OLED_ShowFloatNum
*@brief	:带小数数字显示
*@param	:x的范围0～127，y为页的范围0～7，len:小数点前面数的位数十倍加后面的位数，Char_Size可选 16，6
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowFloatNum(unsigned char x, unsigned char y, float num, unsigned char len, unsigned char size2)
{
	int Num_int, Num_float;
	Num_int = (int)num;
	Num_float = (int)((num-(int)num) * oled_pow(10, len%10+1));
	
	if(size2 == 16){
		OLED_ShowNum(x + (size2 / 2), y, Num_int, len/10, size2); //调整间隔、紧挨显示
		OLED_ShowChar(x + (size2 / 2)*(len/10+1), y, '.', size2);
		OLED_ShowNum(x + (size2 / 2)*(len/10+2), y, Num_float, len%10, size2);} //调整间隔、紧挨显示
	else if(size2 == 6){
		OLED_ShowNum(x + size2, y, Num_int, len/10, size2); //调整间隔、紧挨显示
		OLED_ShowChar(x + size2+len/10, y, '.', size2);
		OLED_ShowNum(x + size2+len/10+5, y, Num_float, len%10, size2);} //调整间隔、紧挨显示
}
/***********************************************************
*@fuction:OLED_ShowHexNum
*@brief	:显示16进制数字
*@param	:x的范围0～127，y为页的范围0～7，Length:数的位数，Char_Size可选 16，6
*@retur :void
*@author:JCML
*@date	:2023-02-02
**********************************************************/
void OLED_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
    unsigned char i, SingleNumber;
    for (i = 0; i < Length; i++)
    {
        SingleNumber = Number / oled_pow(16, Length - i - 1) % 16;
        if (SingleNumber < 10)
        {
            OLED_ShowChar(Line + i * 8, Column, SingleNumber + '0', 16);
        }
        else
        {
            OLED_ShowChar(Line + i * 8, Column, SingleNumber - 10 + 'A', 16);
        }
    }
}
/***********************************************************
*@fuction:OLED_ShowBinNum
*@brief	:OLED显示数字（二进制，正数）
*@param	:x的范围0～127，y为页的范围0～7，Length:数的此处指总位数，Char_Size可选 16，6
*@return :void
*@author :JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowBinNum(unsigned char x, unsigned char y, unsigned char num, unsigned char len, unsigned char size2)
{
	unsigned char i;
	for (i = 0; i < len; i++)							
	{
		if(size2 == 16)
			OLED_ShowChar(x + (size2 / 2)*i, y, num / oled_pow(2, len - i - 1) % 2 + '0', size2);
		else if(size2 == 6)
			OLED_ShowChar(x + size2*i, y, num / oled_pow(2, len - i - 1) % 2 + '0', size2);
	}
}
/***********************************************************
*@fuction:OLED_Clear
*@brief	:清屏函数
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_Clear (void)
{
    unsigned char i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_Set_Pos(0, i);
        for (n = 0; n < 128; n++)
            OLED_WR_Byte(0x00, OLED_DATA);
    }
}
/***********************************************************
*@fuction:OLED_Clear_Part
*@brief	:清除部分屏幕
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_Clear_Part(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
    unsigned char i, n;
    for (i = y1; i < y2; i++)
    {
        OLED_Set_Pos(0, i);
        for (n = x1; n < x2; n++)//x1没用，只能从一行的第一个像素开始清除，所以效果是x2-x1的长度被清除
            OLED_WR_Byte(0x00, OLED_DATA);
    }
}
/***********************************************************
*@fuction:OLED_Full
*@brief	:屏幕全满
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_Full (void)
{
    unsigned char i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_Set_Pos(0, i);
        for (n = 0; n < 128; n++)OLED_WR_Byte(0xff, OLED_DATA);

    }
}
/***********************************************************
*@fuction:ShowBmp
*@brief	:显示图片
*@param	:void
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void ShowBmp (unsigned char *bmp)
{
    int i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_Set_Pos(0, i);
        for (n = 0; n < 128; n++)
            OLED_WR_Byte(bmp[i * 128 + n], OLED_DATA);
    }
}
/***********************************************************
*@fuction:OLED_Show_A_CHinese
*@brief	:显示单个汉字字符
*@param	:x的范围0～127，y为页的范围0～7，Char_Size可选 16
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_Show_A_CHinese(unsigned char x, unsigned char y, unsigned char *chr, unsigned char Char_Size)
{
    unsigned char t, i;
    OLED_Set_Pos(x, y);
    for(i = 0; i < 10; i++)
    {
        if(Char_Size == 16 && Chinese_16[i].name[0] == chr[0] && Chinese_16[i].name[1] == chr[1])
        {
            for(t = 0; t < 16; t++)
            {
                OLED_WR_Byte(Chinese_16[i].DaTa[t], OLED_DATA);
            }
            OLED_Set_Pos(x, y + 1);
            for(t = 16; t < 32; t++)
            {
                OLED_WR_Byte(Chinese_16[i].DaTa[t], OLED_DATA);
            }
        }
        if(Char_Size == 32 && Chinese_Bold16[i].name[0] == chr[0] && Chinese_Bold16[i].name[1] == chr[1])
        {
            for(t = 0; t < 16; t++)
            {
                OLED_WR_Byte(Chinese_Bold16[i].DaTa[t], OLED_DATA);
            }
            OLED_Set_Pos(x, y + 1);
            for(t = 16; t < 32; t++)
            {
                OLED_WR_Byte(Chinese_Bold16[i].DaTa[t], OLED_DATA);
            }
        }
        if(Char_Size == 2 && Chinese_1602[i].name[0] == chr[0] && Chinese_1602[i].name[1] == chr[1])
        {
            for(t = 0; t < 16; t++)
            {
                OLED_WR_Byte(Chinese_1602[i].DaTa[t], OLED_DATA);
            }
            OLED_Set_Pos(x, y + 1);
            for(t = 16; t < 32; t++)
            {
                OLED_WR_Byte(Chinese_1602[i].DaTa[t], OLED_DATA);
            }
        }
    }
}
/***********************************************************
*@fuction:OLED_ShowChinese
*@brief	:显示汉字串
*@param	:x的范围0～127，y为页的范围0～7，Char_Size可选 16
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_ShowChinese(unsigned char x, unsigned char y, char *chr, unsigned char Char_Size)
{
    unsigned char j = 0, ch[2];
    while (chr[j] != '\0')
    {
        ch[0] = chr[j];
        ch[1] = chr[j + 1];
        OLED_Show_A_CHinese(x, y, ch, Char_Size);
        x += 16;
        if(x > 120)
        {
            x = 0;
            y += 2;
        }
        j += 2;
    }
}
/***********************************************************
*@fuction:OLED_DrawBMP
*@brief	:显示显示BMP图片
*@param	:128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
*@return:void
*@author:JCML
*@date	:2023-02-02
***********************************************************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[])
{
    unsigned int j = 0;
    unsigned char x, y;

    if(y1 % 8 == 0) y = y1 / 8;
    else y = y1 / 8 + 1;
    for(y = y0; y < y1; y++)
    {
        OLED_Set_Pos(x0, y);
        for(x = x0; x < x1; x++)
        {
            OLED_WR_Byte(BMP[j++], OLED_DATA);
        }
    }
}
/***********************************************************
*@fuction:OLED_Refresh_Gram
*@brief	:更新显存
*@param	:更新显存
*@return:void
*@author:HY
*@date	:2023-05-12
***********************************************************/
void OLED_Refresh_Gram(void)
{
    uint8_t i, n;
    for (i = 0; i < 8; i++)
    {
        OLED_WR_Byte(0xb0+i,OLED_CMD);
        OLED_WR_Byte(0x00,OLED_CMD);
        OLED_WR_Byte(0x10,OLED_CMD);
        for (n = 0; n < 128; n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
    }
}
/***********************************************************
*@fuction:OLED_DrawPoint
*@brief	:画点
*@param	:画点x0-127 y0-32 t 1填充 0清空
*@return:void
*@author:HY
*@date	:2023-05-12
***********************************************************/
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
{
    uint8_t pos,bx,temp=0;
    if (x>127||y>31)return;
    pos=y/8;
    bx=y%8;
    temp=1<<bx;
    if(t)OLED_GRAM[x][pos] |= temp;
    else OLED_GRAM[x][pos]&=-temp;
}
/***********************************************************
*@fuction:gui_draw_hline
*@brief	:画水平线条
*@param	:y为水平线，x0为起始位子，x1为结束位子
*@return:void
*@author:HY
*@date	:2023-05-12
***********************************************************/
void gui_draw_hline(uint16_t y,uint16_t x0,uint16_t x1)
{
    uint16_t x = 0;
    for (x = x0; x <= x1; x++)
    {
        OLED_DrawPoint(x,y,1);
    }
}
/***********************************************************
*@fuction:gui_draw_vline
*@brief	:画垂直线条
*@param	:x为垂直线位子，y0为起始位子，y1为结束位子
*@return:void
*@author:HY
*@date	:2023-05-12
***********************************************************/
void gui_draw_vline(uint16_t x, uint16_t y0, uint16_t y1)
{
    uint16_t y = 0;
    for (y = y0; y <= y1; y++)
    {
        OLED_DrawPoint(x,y,1);
    }
}
/***********************************************************
*@fuction:gui_draw_axis
*@brief	:画一个坐标系
*@param	:
*@return:void
*@author:HY
*@date	:2023-05-12
***********************************************************/
void gui_draw_axis(void)
{
    gui_draw_hline(31,0,120);
    gui_draw_vline(0,0,31);
}
/***********************************************************
*@fuction:Gram_clear
*@brief	:数组清零
*@param	:数组清零
*@return:void
*@author:HY
*@date	:2023-05-12
***********************************************************/
void Gram_clear(void)
{
    uint8_t i,n;
    for (i = 0; i < 8; i++)
    {
        for (n = 0; n < 128; n++) OLED_GRAM[n][i] = 0;
    }
}