
#pragma once

#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_uart.h"
#include "stm32g0xx_hal_i2c.h"

#define PI 3.141592653f

void printFloats(UART_HandleTypeDef *huart, char* str, int n, ...);
void print(UART_HandleTypeDef *huart, char* str);
void printTimer(UART_HandleTypeDef *huart, uint16_t i);
void printTimerInv(UART_HandleTypeDef *huart, uint16_t i);
float arctan2(float a, float b);
float boundOne(float a);

void readBytes(I2C_HandleTypeDef *i2c, uint8_t address, uint8_t subaddress, uint8_t *data, uint8_t size);
void writeOneByte(I2C_HandleTypeDef *i2c, uint8_t address, uint8_t subaddress, uint8_t data);
