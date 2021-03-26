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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "lib_lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
static rgb_lcd lcdData;
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
uint8_t rx_buffer[1];
char input_string[40];
char input_raw[100];
char old_input_string[40];
char old_input_string2[40];
char input_buffer[40];
int input_i = 0;
int flag=0; input_complete=0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	input_raw[input_i] = (char*)rx_buffer[0];

	input_buffer[input_i] = (char*)rx_buffer[0];
	if(input_buffer[input_i] == '\n' ){
		input_complete = 1;//activa el flag 2
		input_i = 0;//reinicia el indice del input string

		for(int i = 0; i < 40; i++){
			input_string[i] = input_buffer[i];
			input_buffer[i]=0;//reinicia el input buffer
		}
		HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
		return 0;
	}
	input_i++;
	//si el buffer no trae ni \n ni \r entonces guarda el elemento del  buffer en el indice de input string
	HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
}
void wifi_init(){
	  /*if(input_string == "WIFI GOT IP\r\n"){
		  clearlcd();
		  lcd_position(&hi2c1,0,0);//cositas
		  lcd_print(&hi2c1, "wifi state:");
		  lcd_position(&hi2c1,0,1);//cositas
		  lcd_print(&hi2c1, "connected");
		  reglagecouleur(0,255,0);
	  }*/

}
void print_lcd2(char line_1[16], char line_2[16], int R, int G, int B){
	  clearlcd();
	  lcd_position(&hi2c1,0,0);//cositas
	  lcd_print(&hi2c1, line_1);
	  lcd_position(&hi2c1,0,1);//cositas
	  lcd_print(&hi2c1, line_2);
	  reglagecouleur(R, G, B);

}
void show_plate(char *input, char *commande){
	//find :
	int start, start2, length, new = 0; ;
	char string[40];
	length = strlen((char*)input);
	for(int i = 0; i < length; i++){
		if(input[i] == ':')
			start = i;
		if(input[i] == ';')
			start2 = i;
	}

	for(int i = start + 1; i < length - 12; i++){

		string[new] = input[i];
		new++;
	}
	new = 0;
	for(int i = start2 + 1; i < length - 10; i++){
		commande[new] = input[i];
		new++;
	}
	lcd_print(&hi2c1, string);

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	//int buffer_lenght = 40;
	char commande[2];
	uint8_t cmd[40], request[40], screen_text[40];


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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, rx_buffer, 1);
  lcd_init(&hi2c1, &lcdData); // initialise le lcd
  ATCommand("ATE1");

  print_lcd2("system:", "Starting", 0,0,255);
  // --------------- wifi init ---------------
  //ATCommand("AT+RST");
  print_lcd2("WiFi state:", "connecting", 0, 255, 255);
  HAL_Delay(3000);
  //input_string;
  print_lcd2("WiFi state:", "connected", 0, 255, 0);
  print_lcd2("Server state:", "starting", 0, 255, 255);
  ATCommand("AT+CWMODE=3");
  ATCommand("AT+CIPMUX=1");
  ATCommand("AT+CIPSERVER=1");
  ATCommand("AT+CIPSTATUS");

  print_lcd2("Server state:", "started", 0, 255, 255);

  print_lcd2("Waiting for new", "commandes", 0, 255, 0);
  __HAL_UART_FLUSH_DRREGISTER(&huart1);
  commande[0] = '0';
  commande[1] = '0';

  ATCommand("AT+CIPSERVER=0");
  ATCommand("AT+CIPMUX=0");
  ATCommand("AT+CIPSTART=\"TCP\",\"debian\",8000");
  sprintf((char*)request,
		  "GET /api/%c%c HTTP/1.1\r\nHost:debian",
		  commande[0],
		  commande[1]
		  );
  sprintf((char*)cmd,
		  "AT+CIPSEND=%i",
		  strlen((char*)request)
		  );

  ATCommand(cmd);
  ATCommand(request);
  ATCommand("AT+CIPCLOSE");
  ATCommand("AT+CIPMUX=1");
  ATCommand("AT+CIPSERVER=1");
  __HAL_UART_FLUSH_DRREGISTER(&huart1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	  //HAL_Delay(2000);
	  //while(!input_complete);
	  if(input_complete){
		  strcpy((char*)screen_text, input_buffer);
		  clearlcd();
		  if(input_string == "waiting--------;00")
			  reglagecouleur(0, 255, 0);
		  else{
		  reglagecouleur(255, 0, 0);}
		  lcd_position(&hi2c1,0,0);//cositas
		  show_plate(input_string, commande);
		  lcd_position(&hi2c1,0,1);//cositas
		  lcd_print(&hi2c1, commande);
		  __HAL_UART_FLUSH_DRREGISTER(&huart1);
		  input_complete = 0;
	  }
	  if(!HAL_GPIO_ReadPin (GPIOB, GPIO_PIN_5)){
		  ATCommand("AT+CIPSERVER=0");
		  ATCommand("AT+CIPMUX=0");
		  ATCommand("AT+CIPSTART=\"TCP\",\"debian\",8000");
		  //strcpy((char*)request, "GET /api/67 HTTP/1.1\r\nHost:debian");
		  sprintf((char*)request,
				  "GET /api/%c%c HTTP/1.1\r\nHost:debian",
				  commande[0],
				  commande[1]
				  );
		  sprintf((char*)cmd,
				  "AT+CIPSEND=%i",
				  strlen((char*)request)
				  );

		  ATCommand(cmd);
		  ATCommand(request);
		  ATCommand("AT+CIPCLOSE");
		  ATCommand("AT+CIPMUX=1");
		  ATCommand("AT+CIPSERVER=1");
		  __HAL_UART_FLUSH_DRREGISTER(&huart1);
		  }
	  //print_lcd2("Waiting for new", "commandes", 0, 255, 0);


	  /*



	  if(input_complete){
		  strcpy((char*)screen_text, input_string);
		  clearlcd();
		  lcd_position(&hi2c1,0,0);//cositas
		  lcd_print(&hi2c1, screen_text);
	  }
	  HAL_Delay(50);*/
	  //HAL_Delay(7000);


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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
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
}

/* USER CODE BEGIN 4 */
void ATCommand(uint8_t cmd[40]){
	//uint8_t cmd_;
	//strcpy((char*)cmd, command);
	HAL_UART_Transmit(&huart1, cmd, strlen((char*)cmd), 20000);
	HAL_UART_Transmit(&huart1, "\r\n", 2, 20000);
	HAL_Delay(500);
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
