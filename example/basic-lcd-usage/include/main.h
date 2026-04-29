#pragma once

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
void MX_I2C1_Init(void);
void Error_Handler(void);
