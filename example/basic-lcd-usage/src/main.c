#include "main.h"

#include "LCD_PCF8574.h"

static LCD2004_I2C lcd;
I2C_HandleTypeDef hi2c1;

static void LCD_I2C_TransmitHAL(void *context, uint16_t address, const uint8_t *data, uint16_t length)
{
	I2C_HandleTypeDef *hi2c = (I2C_HandleTypeDef *) context;
	if (HAL_I2C_Master_Transmit(hi2c, address, (uint8_t *) data, length, HAL_MAX_DELAY) != HAL_OK)
	{
		Error_Handler();
	}
}

static void LCD_DelayHAL(void *context, uint32_t delayMs)
{
	(void) context;
	HAL_Delay(delayMs);
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_I2C1_Init();

	LCD_Init(&lcd, LCD_DEFAULT_ADDR, LCD_I2C_TransmitHAL, LCD_DelayHAL, &hi2c1);
	LCD_Clear(&lcd);
	LCD_DisplayStringLineCentered2(&lcd, "STM32F401CCU6", 0);
	LCD_DisplayStringLineCentered2(&lcd, "I2C1 LCD demo", 1);

	while (1)
	{
	}
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}
}

void MX_I2C1_Init(void)
{
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}
}

void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}
}

void assert_failed(uint8_t *file, uint32_t line)
{
	(void) file;
	(void) line;
	Error_Handler();
}
