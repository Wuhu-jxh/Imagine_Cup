/**
  ************************************* Copyright ******************************   
  *                 (C) Copyright 2023,--,China, CUIT.
  *                            All Rights Reserved
  * FileName   : oled.h   
  * Version    : v1.0		
  * Author     : JCML
  * Date       : 2023-02-02         
  * Description: OLED
  ******************************************************************************
 */
#ifndef __OLED_H__
#define __OLED_H__

#include <stdint-gcc.h>

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//�����Լ��û��Ŀ�����,��Ƭ��.h�ļ�����Ӻ�Ҫ�ڴ˴�����
extern const unsigned char ICEC_LOGO[];
extern const unsigned char MyLogo[];
extern const unsigned char StickManTest[];

//�ײ㺯����
void OLED_WriteCommand(unsigned char dat);
void OLED_WritrDate(unsigned char dat);
void OLED_WR_Byte(unsigned char dat, unsigned char cmd);

//�û�������
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Full(void);
void OLED_Set_Pos(unsigned char x,unsigned char y);
void OLED_Clear_Part(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);
void OLED_ShowString(unsigned char x,unsigned char y,char *chr,unsigned char Char_Size);
void OLED_Show_A_Chinese(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size);
void OLED_ShowChinese(unsigned char x,unsigned char y,char *chr,unsigned char Char_Size);
void ShowBmp(unsigned char *bmp);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
unsigned int oled_pow(unsigned char m,unsigned char n);
void OLED_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length);
void OLED_ShowSignedNum(unsigned char x, unsigned char y, int num, unsigned char len, unsigned char size2);
void OLED_ShowBinNum(unsigned char x, unsigned char y, unsigned char num, unsigned char len, unsigned char size2);
void OLED_ShowFloatNum(unsigned char x, unsigned char y, float num, unsigned char len, unsigned char size2);
void Gram_clear(void);
void gui_draw_axis(void);
void gui_draw_vline(uint16_t x, uint16_t y0, uint16_t y1);
void gui_draw_hline(uint16_t y,uint16_t x0,uint16_t x1);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Refresh_Gram(void);
#endif
