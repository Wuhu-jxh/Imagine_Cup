//
// Created by 神奇bug在哪里 on 2023/5/11.
//
#include <stdbool.h>
#include "main.h"
#include "tim.h"
#include "Frectest.h"
#include "settings.h"
uint64_t cnt = -1;
uint32_t SampleTimeMS = 200;
uint8_t overflow = 0;
uint64_t frec = 0;
bool isTiger = false;
void calResistance();
float resistance = 0; //测量电路中电阻的值
float cap = CAP_VALUE; //电路中固定电容的值

void Frec_init()
{
    HAL_TIM_Base_Stop(&htim2);
    HAL_TIM_Base_Stop(&htim3);
    htim2.Instance->CNT = 0;
}
void Frec_Start_Test()
{
    if (!isTiger) {
        //TIM3用于计时
        //TIM2用于计数
        __HAL_TIM_SET_PRESCALER(&htim3, 720);
        __HAL_TIM_SET_COUNTER(&htim3, 1999);
        HAL_TIM_Base_Start_IT(&htim3);
        HAL_TIM_Base_Start(&htim2);
        htim2.Instance->CNT=0;
        HAL_TIM_Base_Start_IT(&htim2);
        isTiger = true;
    }
}
void Frec_Trec_TIMer_Handle()
{
    if (isTiger) {
        HAL_TIM_Base_Stop_IT(&htim3);
        HAL_TIM_Base_Stop(&htim3);
        HAL_TIM_Base_Stop(&htim2);
        cnt = htim2.Instance->CNT;
        frec =(cnt+65535*overflow)/0.2; // NOLINT(cppcoreguidelines-narrowing-conversions)
        overflow = 0;
        Frec_Cal_Resistance();
        isTiger = false;
    }
}
void Frec_Overflow_Handle()
{
    overflow++;
}
float Frec_Get_Frec()
{
    return frec;
}
float Frec_Get_Resistance()
{
    return resistance;
}
void Frec_Cal_Resistance()
{
//    resistance = 1.0f / (2.0f * PI * frec * cap);
//        resistance = 1.44f / (cap * frec)*100;
//    resistance = 1.44f / (cap * frec)*1000;
    resistance =  (float )(1.445e+07)/(frec+(24.15))-2723;
}
