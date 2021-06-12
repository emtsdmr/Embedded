/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int indx1=0;
int indx2=0;

//Structure definition
typedef struct {
	char *str;
	int counter;
	uint16_t large_value;
} my_struct;

//Task Handlers
xTaskHandle Sender1_Task_Handler;
xTaskHandle Sender2_Task_Handler;
xTaskHandle Receiver_Task_Handler;

//Queue Handler
xQueueHandle St_Queue_Handler;

//Task Functions
void Sender1_Task (void *argument);
void Sender2_Task (void *argument);
void Receiver_Task (void *argument);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  //Create Queue
  St_Queue_Handler = xQueueCreate(2, sizeof(my_struct));

  if (St_Queue_Handler == 0)
	  HAL_UART_Transmit(&huart2,(uint8_t *) "Unable to Create Structure Queue\n\n",33,100);
  else
	  HAL_UART_Transmit(&huart2,(uint8_t *) "Structure Queue created successfully\n\n",40,1000);

  //Create Tasks

  xTaskCreate(Sender1_Task,"SENDER1", 128, NULL, 2, &Sender1_Task_Handler);
  xTaskCreate(Sender2_Task,"SENDER2", 128, NULL, 2, &Sender2_Task_Handler);
  xTaskCreate(Receiver_Task,"RECEIVER", 128, NULL, 1, &Receiver_Task_Handler);

  //HAL_UART_Receive_IT(&huart2, &Rx_data, 1);

  vTaskStartScheduler();
  /* USER CODE END 2 */

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Sender1_Task (void *argument)
{
	my_struct *ptrtostruct;
	uint32_t TickDelay = pdMS_TO_TICKS(2000);

	while(1)
	{
		char *str0="Entered Sender1_Task, About to send to the queue\n";
	    HAL_UART_Transmit(&huart2,(uint8_t *)str0, strlen(str0), HAL_MAX_DELAY);

		//Allocate memory to the ptr
		ptrtostruct = pvPortMalloc(sizeof(my_struct));

		//Load the Data
		ptrtostruct->counter=1+indx1;
		ptrtostruct->large_value=1000+indx1*100;
		ptrtostruct->str="Hello from SENDER1!";

		if(xQueueSend(St_Queue_Handler, &ptrtostruct, portMAX_DELAY) == pdPASS)
		{
			char *str1="Successfully sent to the queue, Leaving Sender1_Task\n\n";
			HAL_UART_Transmit(&huart2,(uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);
		}
		
		indx1++;
		vTaskDelay(TickDelay);
	}
}
void Sender2_Task (void *argument)
{
	my_struct *ptrtostruct;
	uint32_t TickDelay = pdMS_TO_TICKS(2000);

	while(1)
	{
		char *str0="Entered Sender2_Task, About to send to the queue\n";
	    HAL_UART_Transmit(&huart2,(uint8_t *)str0, strlen(str0), HAL_MAX_DELAY);

		//Allocate memory to the ptr
		ptrtostruct = pvPortMalloc(sizeof(my_struct));

		//Load the Data
		ptrtostruct->counter=1+indx2;
		ptrtostruct->large_value=2000+indx2*200;
		ptrtostruct->str="Hello from SENDER2!";

		if(xQueueSend(St_Queue_Handler, &ptrtostruct, portMAX_DELAY) == pdPASS)
		{
			char *str1="Successfully sent to the queue, Leaving Sender2_Task\n\n";
			HAL_UART_Transmit(&huart2,(uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);
		}
		
		indx2++;
		vTaskDelay(TickDelay);
	}
}

void Receiver_Task (void *argument)
{
	my_struct *Rptrtostruct;
	uint32_t TickDelay = pdMS_TO_TICKS(3000);
	char *str1;

	while(1)
	{
		char *str0="Entered Receiver Task, About to receive from the queue\n";
	    HAL_UART_Transmit(&huart2,(uint8_t *)str0, strlen(str0), HAL_MAX_DELAY);

		if(xQueueReceive(St_Queue_Handler, &Rptrtostruct, portMAX_DELAY) == pdPASS)
		{
			str1 = pvPortMalloc(100 * sizeof(char));
			sprintf(str1,"Received from queue!\nCounter: %d\n Large value:%u\n String: %s\n\n",Rptrtostruct->counter,Rptrtostruct->large_value,Rptrtostruct->str);
			HAL_UART_Transmit(&huart2,(uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);
			vPortFree(str1);
		}
		vPortFree(Rptrtostruct);

		vTaskDelay(TickDelay);
	}
}

/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(huart, &Rx_data, 1);
	int toSend=2017;
	if (Rx_data == 'r')
	{
		BaseType_t xHigherPriorityTaskWoken=pdFALSE;

		if(xQueueSendToFrontFromISR(SimpleQueue, &toSend, &xHigherPriorityTaskWoken) == pdPASS)
		{
			char *str1="\n\nSent from ISR\n\n";
			HAL_UART_Transmit(&huart2,(uint8_t *)str1, strlen(str1), 500);
		}

		portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
	}

}*/
/* USER CODE END 4 */



 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
