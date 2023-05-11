/**
  ************************************* Copyright ****************************** 
  *
  *                 (C) Copyright 2022,--,China, CUIT.
  *                            All Rights Reserved
  *                              
  *                     By(JCML)
    *
  *    
  * FileName   : MatrixKey.c   
  * Version    : v2.0
  * Author     : JCML			
  * Date       : 2023-05-10
  * Description: 利用TIM定时器对按键进行扫描（定时器的定时时间为10ms）所有矩阵键盘的电平初始状态都为高电平
  *
******************************************************************************
 */

#include "main.h"
#include "tim.h"
#include "MatrixKey.h"


#define TIM htim1
uint8_t KeyNumber;

/***********************************************************
*@fuction	:MatrixKey_GetState
*@brief		:检测按键是否按下，单独对每一行的按键进行检测
*@param		:void
*@return	:被按下的按键
*@author	:JCML
*@date		:2022-12-24
***********************************************************/

uint8_t MatrixKey_GetState()
{
	unsigned char KeyNum = 0;
  //由于初始化为上拉状态故此处拉低X1行的电平
  HAL_GPIO_WritePin(X1_GPIO_Port, X1_Pin, GPIO_PIN_RESET);
	if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=1;}//如果接收到Y1为低电平则判定1按键按下
	if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=2;}
	if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=3;}
	if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=4;}
  HAL_GPIO_WritePin(X1_GPIO_Port, X1_Pin, GPIO_PIN_SET);

  //由于初始化为上拉状态故此处拉低X2行的电平
  HAL_GPIO_WritePin(X2_GPIO_Port, X2_Pin, GPIO_PIN_RESET);
  if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=5;}//如果接收到Y1为低电平则判定1按键按下
  if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=6;}
  if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=7;}
  if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=8;}
  HAL_GPIO_WritePin(X2_GPIO_Port, X2_Pin, GPIO_PIN_SET);

  //由于初始化为上拉状态故此处拉低X3行的电平
  HAL_GPIO_WritePin(X3_GPIO_Port, X3_Pin, GPIO_PIN_RESET);
  if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=9;}//如果接收到Y1为低电平则判定1按键按下
  if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=10;}
  if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=11;}
  if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=12;}
  HAL_GPIO_WritePin(X3_GPIO_Port, X3_Pin, GPIO_PIN_SET);

  //由于初始化为上拉状态故此处拉低X4行的电平
  HAL_GPIO_WritePin(X4_GPIO_Port, X4_Pin, GPIO_PIN_RESET);
  if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=13;}//如果接收到Y1为低电平则判定1按键按下
  if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=14;}
  if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=15;}
  if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=16;}
  HAL_GPIO_WritePin(X4_GPIO_Port, X4_Pin, GPIO_PIN_SET);
	return KeyNum;//返回按键的值
}

/***********************************************************
*@fuction	:MatrixKey
*@brief		:返回按下的按键值，该函数需要在main函数调用来获取按键值
*@param		:void
*@return	:被按下的按键
*@author	:JCML
*@date		:2022-12-24
***********************************************************/

uint8_t MatrixKey(void)
{
//  uint8_t Temp = 0;
//	Temp = KeyNumber;
//	KeyNumber = 0;
	return KeyNumber;
}


/***********************************************************
*@fuction	:MatrixKey_Loop
*@brief		:TIM 的循环扫描函数
*@param		:void
*@return	:void
*@author	:JCML
*@date		:2022-12-24
***********************************************************/

void MatrixKey_Loop(void)
{
	static uint8_t NewState, LastState;
	LastState = NewState;//将上一次的按键状态保存
	NewState = MatrixKey_GetState();//获取当前的状态
	if(LastState == 1 && NewState == 0){KeyNumber = 1;}//如果上一次状态为按下的按键且当前状态为未按下的状态则说明该按键被按下
	if(LastState == 2 && NewState == 0){KeyNumber = 2;}
	if(LastState == 3 && NewState == 0){KeyNumber = 3;}
	if(LastState == 4 && NewState == 0){KeyNumber = 4;}
	if(LastState == 5 && NewState == 0){KeyNumber = 5;}
	if(LastState == 6 && NewState == 0){KeyNumber = 6;}
	if(LastState == 7 && NewState == 0){KeyNumber = 7;}
	if(LastState == 8 && NewState == 0){KeyNumber = 8;}
	if(LastState == 9 && NewState == 0){KeyNumber = 9;}
	if(LastState == 10 && NewState == 0){KeyNumber = 10;}
	if(LastState == 11 && NewState == 0){KeyNumber = 11;}
	if(LastState == 12 && NewState == 0){KeyNumber = 12;}
	if(LastState == 13 && NewState == 0){KeyNumber = 13;}
	if(LastState == 14 && NewState == 0){KeyNumber = 14;}
	if(LastState == 15 && NewState == 0){KeyNumber = 15;}
	if(LastState == 16 && NewState == 0){KeyNumber = 16;}
}











