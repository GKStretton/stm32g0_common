#pragma once
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_i2c.h"
#include "stm32g0xx_hal_uart.h"


float Mx, My, Mz;

void QMC5883L_Init(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c);
struct MagCalibration {
	float MxMin;
	float MxMax;
	float MyMin;
	float MyMax;
	float MzMin;
	float MzMax;
};


void updateMagnetometer(I2C_HandleTypeDef *i2c);
void adjustMagnetometer(struct MagCalibration *cal);

uint8_t getWhoIs();
