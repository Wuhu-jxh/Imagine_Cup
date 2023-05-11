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
  * Description: ����TIM��ʱ���԰�������ɨ�裨��ʱ���Ķ�ʱʱ��Ϊ10ms�����о�����̵ĵ�ƽ��ʼ״̬��Ϊ�ߵ�ƽ
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
*@brief		:��ⰴ���Ƿ��£�������ÿһ�еİ������м��
*@param		:void
*@return	:�����µİ���
*@author	:JCML
*@date		:2022-12-24
***********************************************************/

uint8_t MatrixKey_GetState()
{
	unsigned char KeyNum = 0;
  //���ڳ�ʼ��Ϊ����״̬�ʴ˴�����X1�еĵ�ƽ
  HAL_GPIO_WritePin(X1_GPIO_Port, X1_Pin, GPIO_PIN_RESET);
	if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=1;}//������յ�Y1Ϊ�͵�ƽ���ж�1��������
	if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=2;}
	if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=3;}
	if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=4;}
  HAL_GPIO_WritePin(X1_GPIO_Port, X1_Pin, GPIO_PIN_SET);

  //���ڳ�ʼ��Ϊ����״̬�ʴ˴�����X2�еĵ�ƽ
  HAL_GPIO_WritePin(X2_GPIO_Port, X2_Pin, GPIO_PIN_RESET);
  if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=5;}//������յ�Y1Ϊ�͵�ƽ���ж�1��������
  if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=6;}
  if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=7;}
  if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=8;}
  HAL_GPIO_WritePin(X2_GPIO_Port, X2_Pin, GPIO_PIN_SET);

  //���ڳ�ʼ��Ϊ����״̬�ʴ˴�����X3�еĵ�ƽ
  HAL_GPIO_WritePin(X3_GPIO_Port, X3_Pin, GPIO_PIN_RESET);
  if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=9;}//������յ�Y1Ϊ�͵�ƽ���ж�1��������
  if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=10;}
  if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=11;}
  if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=12;}
  HAL_GPIO_WritePin(X3_GPIO_Port, X3_Pin, GPIO_PIN_SET);

  //���ڳ�ʼ��Ϊ����״̬�ʴ˴�����X4�еĵ�ƽ
  HAL_GPIO_WritePin(X4_GPIO_Port, X4_Pin, GPIO_PIN_RESET);
  if(!HAL_GPIO_ReadPin(Y1_GPIO_Port, Y1_Pin)){KeyNum=13;}//������յ�Y1Ϊ�͵�ƽ���ж�1��������
  if(!HAL_GPIO_ReadPin(Y2_GPIO_Port, Y2_Pin)){KeyNum=14;}
  if(!HAL_GPIO_ReadPin(Y3_GPIO_Port, Y3_Pin)){KeyNum=15;}
  if(!HAL_GPIO_ReadPin(Y4_GPIO_Port, Y4_Pin)){KeyNum=16;}
  HAL_GPIO_WritePin(X4_GPIO_Port, X4_Pin, GPIO_PIN_SET);
	return KeyNum;//���ذ�����ֵ
}

/***********************************************************
*@fuction	:MatrixKey
*@brief		:���ذ��µİ���ֵ���ú�����Ҫ��main������������ȡ����ֵ
*@param		:void
*@return	:�����µİ���
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
*@brief		:TIM ��ѭ��ɨ�躯��
*@param		:void
*@return	:void
*@author	:JCML
*@date		:2022-12-24
***********************************************************/

void MatrixKey_Loop(void)
{
	static uint8_t NewState, LastState;
	LastState = NewState;//����һ�εİ���״̬����
	NewState = MatrixKey_GetState();//��ȡ��ǰ��״̬
	if(LastState == 1 && NewState == 0){KeyNumber = 1;}//�����һ��״̬Ϊ���µİ����ҵ�ǰ״̬Ϊδ���µ�״̬��˵���ð���������
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











