/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"
#include "MatrixKey.h"
#include "Frectest.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t huandang(float data)
{
        if (data != 0) {
            if (data > 0 && data <= 100)
            {
                return 10;
            }else if(data > 100 && data <=1000)
            {
                return 11;
            }
            else if (data >1000 && data <=10000)

            {
                return 12;
            }
        }else
        {
            return 13;
        }

}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */


int main(void)
{
  /* USER CODE BEGIN 1 */
  uint8_t temp, temp1=0;
  int num = 10, cnt1 = 0, cnt2, zidong;
  uint8_t i,j=0,k = 0;
  uint16_t h;
  uint8_t H[128];
  float zuzhi;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);
  OLED_Init();

  Frec_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      Frec_Start_Test();
      zuzhi = Frec_Get_Resistance();
      cnt1 = MatrixKey();//按键值
      cnt2 = huandang(zuzhi);//换挡值
//      pl = Frec_Get_Frec();


      if (cnt1 == 15)
      {
          zidong = 1;

      }
      else
      {
          zidong = 0;
      }
      if (zidong == 1)
      {
          if (num != cnt2 && cnt2 != 13)
          {
              if (cnt1 != cnt2)
              {
                  OLED_Clear();
              }
              cnt1 = cnt2;

          }
      }
      if (num != cnt1)
      {
          OLED_Clear();
          num = cnt1;
      }
      if (cnt1 == 14)
      {
          for (i = 0; i < 128; i++)
          {
              H[i] = 32;
          }
          if (k == 0)
          {
              Gram_clear();

              OLED_Clear();
              k = 1;

          }
        h = zuzhi*(32.0/100000);
        h=(int)h;
        gui_draw_axis();
        H[j] = 32-h;
        for (i = 0; i < 128; i++)
        {
            OLED_DrawPoint(i, H[i], 1);

        }

        j++;
          OLED_Refresh_Gram();
        if (j>127)
        {
            j = 0;
            k = 0;
            OLED_Refresh_Gram();
            Gram_clear();
            OLED_Clear();
        }


      }
      if (num == 10)
      {
          OLED_ShowFloatNum(0,4,zuzhi,66,16);
          OLED_ShowChinese(0,0,"量程",16);
          OLED_ShowNum(32,0,100,3,16);
          OLED_ShowChinese(64,0,"Ω",16);
          OLED_ShowChinese(0,2,"电阻大小：",16);
          OLED_ShowFloatNum(64,2,zuzhi,21,16);
      }
      if (num == 11)
      {
          OLED_ShowFloatNum(0,4,zuzhi,66,16);
          zuzhi = zuzhi/10000;
          OLED_ShowChinese(0,0,"量程",16);
          OLED_ShowNum(48,0,1,1,16);
          OLED_ShowString(55,0,"k",16);
          OLED_ShowChinese(64,0,"Ω",16);
          OLED_ShowChinese(0,2,"电阻大小：",16);
          OLED_ShowNum(64,2,0,1,16);
          OLED_ShowFloatNum(70,2,zuzhi,03,16);
      }
      if (num == 12)
      {
          OLED_ShowFloatNum(0,4,zuzhi,66,16);
          zuzhi = zuzhi / 1000;
          OLED_ShowChinese(0,0,"量程",16);
          OLED_ShowNum(48,0,10,2,16);
          OLED_ShowString(70,0,"k",16);
          OLED_ShowChinese(80,0,"Ω",16);
          OLED_ShowChinese(0,2,"电阻大小：",16);
          OLED_ShowFloatNum(64,2,zuzhi,12,16);
      }
      if (num == 13)
      {
          OLED_ShowFloatNum(0,4,zuzhi,66,16);
          zuzhi = zuzhi / 1000;
          OLED_ShowChinese(0,0,"量程",16);
          OLED_ShowNum(48,0,100,3,16);
          OLED_ShowString(75,0,"k",16);
          OLED_ShowChinese(85,0,"Ω",16);
          OLED_ShowChinese(0,2,"电阻大小：",16);
          OLED_ShowFloatNum(64,2,zuzhi,21,16);
      }
      /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM1)//锟借定锟矫讹拷时锟斤拷10ms锟斤拷一锟斤拷锟叫讹拷
    {
        MatrixKey_Loop();
    }
    if (htim->Instance == TIM2)
    {
        Frec_Overflow_Handle();
    }
    if (htim->Instance == TIM3)
    {
        Frec_Trec_TIMer_Handle();
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
