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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "BackupRegister.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum{
	Nenhuma = 0, EscreverNoBKUPReg, LerBKUPReg, ApagarTudo, ApagarEnderecoEspecifico
}Acao;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MSG_CLEAR_SCREEN "\033[0H\033[0J"
#define MSG_ASK_NEW_VALUE "\n\n\r Selecione uma das acoes:"\
                          "\n\r ED - Escreve dado (ED DRNN XXXX)"\
						  "\n\r AD - Apagar dado  (AD DRNN)"\
						  "\n\r AT - Apagar Tudo  (AT)\n\r"
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  BKPREG_iniciar();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */


  uint32_t Valor = 0;
  BkpregID EnderecoAlvo = 0;
  Acao AcaoRecebida = Nenhuma;

  void EnviarValoresDeBKPREGPelaSerial(void);
  Acao ReceberOperacaoDeBKPREGPelaSerial(BkpregID *EnderecoAlvo, uint32_t *ValorQueSeraArmazenado);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  EnviarValoresDeBKPREGPelaSerial();

  while (1)
  {
	  AcaoRecebida = ReceberOperacaoDeBKPREGPelaSerial(&EnderecoAlvo, &Valor);

	  if (AcaoRecebida == EscreverNoBKUPReg){
		  BKPREG_escrever((BkpregID)EnderecoAlvo, Valor);
		  EnviarValoresDeBKPREGPelaSerial();
	  }
	  else if (AcaoRecebida == ApagarTudo){
		  BKPREG_apagar_tudo();
		  EnviarValoresDeBKPREGPelaSerial();
	  }
	  else if (AcaoRecebida == ApagarEnderecoEspecifico){
		  BKPREG_apaga(EnderecoAlvo);
		  EnviarValoresDeBKPREGPelaSerial();
	  }
	  else
		  ;
  }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 57600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void EnviarValoresDeBKPREGPelaSerial(void){
	uint8_t DadoTX[250] = {0};

	// organiza os valores dos backup registers dentro da string DadoTX
	sprintf((char *)DadoTX,"\n\r Backup registers values:"
			  	  	  	  	 "\n\r DR01: 0x%04lX"
			  	  	  	     "\n\r DR02: 0x%04lX"
	 	  	     	 	 	 "\n\r DR03: 0x%04lX"
	 	  	     	 	 	 "\n\r DR04: 0x%04lX"
	 	  	     	 	 	 "\n\r DR05: 0x%04lX"
	 	  	     	 	 	 "\n\r DR06: 0x%04lX"
			  	  	  	     "\n\r DR07: 0x%04lX"
			   	  	     	 "\n\r DR08: 0x%04lX"
			   	  	     	 "\n\r DR09: 0x%04lX"
			  	  	  	  	 "\n\r DR10: 0x%04lX",
							 BKPREG_ler(DR1),
							 BKPREG_ler(DR2),
							 BKPREG_ler(DR3),
							 BKPREG_ler(DR4),
							 BKPREG_ler(DR5),
							 BKPREG_ler(DR6),
							 BKPREG_ler(DR7),
							 BKPREG_ler(DR8),
							 BKPREG_ler(DR9),
							 BKPREG_ler(DR10));

	  // Limpa tela do RealTerm
	  HAL_UART_Transmit(&huart1, MSG_CLEAR_SCREEN, strlen((const char *)MSG_CLEAR_SCREEN), 100);

	  // Envia os valores dos BKPRegs para monitor serial
	  HAL_UART_Transmit(&huart1, DadoTX, strlen((const char *)DadoTX), 100);

	  // Envia mensagem solicitando novo dado
	  HAL_UART_Transmit(&huart1, MSG_ASK_NEW_VALUE, strlen((const char *)MSG_ASK_NEW_VALUE), 100);
}

Acao ReceberOperacaoDeBKPREGPelaSerial(BkpregID *EnderecoAlvo, uint32_t *ValorQueSeraArmazenado){
	uint8_t DadoRX[12] = {0};
	uint8_t OperacaoRX[3] = {0};
	HAL_StatusTypeDef UARTStatus;

	*EnderecoAlvo = *ValorQueSeraArmazenado = 0;
	uint8_t Deslocamento = 12;

	// Le dado na porta serial UART1 - polling
	UARTStatus = HAL_UART_Receive(&huart1, DadoRX, 12, 100);

	OperacaoRX[0] = DadoRX[0];
	OperacaoRX[1] = DadoRX[1];
	OperacaoRX[2] = NULL;

	if (!strcmp(OperacaoRX,"ED")){
		*EnderecoAlvo = ((DadoRX[5] - 48) * 10) + (DadoRX[6] - 48);
		for (uint8_t i = 8; i < 12 ; i++){
			if (DadoRX[i] > 47 && DadoRX[i] < 58)
				*ValorQueSeraArmazenado += ((DadoRX[i] - 48) << Deslocamento);
			else if (DadoRX[i] > 64 && DadoRX[i] < 71)
				*ValorQueSeraArmazenado += ((DadoRX[i] - 55) << Deslocamento);
			else
				return Nenhuma;

			Deslocamento -= 4;
		}
		return EscreverNoBKUPReg;
	}
	else if (!strcmp(OperacaoRX,"AT")){
		return ApagarTudo;
	}
	else if (!strcmp(OperacaoRX,"AD")){
		*EnderecoAlvo = ((DadoRX[5] - 48) * 10) + (DadoRX[6] - 48);
		if (*EnderecoAlvo > 10)
			return Nenhuma;
		else
			return ApagarEnderecoEspecifico;
	}
	else
		return Nenhuma;

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
