#pragma once
#include <stdint.h>
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_i2c.h"
#include "stm32g0xx_hal_uart.h"

#define MPU6050_ADDRESS 0x68
#define PWR_MGMT_1 0x6B
#define USER_CTRL 0x6A
#define WHO_AM_I 0x75
#define ACCEL_CONFIG 0x1C
#define GYRO_CONFIG 0x1B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

float Ax, Ay, Az;
float Gx, Gy, Gz;

struct GyroCalibration {
	float GxOff;
	float GyOff;
	float GzOff;
};

struct AccCalibration {
	float AxMin;
	float AxMax;
	float AyMin;
	float AyMax;
	float AzMin;
	float AzMax;
};

void MPU6050_Init(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c);

void updateAccelerometer(I2C_HandleTypeDef *i2c);
void updateGyro(I2C_HandleTypeDef *i2c);
void adjustAccelerometer(struct AccCalibration *accCal);
void adjustGyro(struct GyroCalibration *gyroCal);
void calibrateGyro(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c);
void calibrateAccelerometer(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c);

// 0x68
uint8_t getWHOAMI(I2C_HandleTypeDef *i2c);

