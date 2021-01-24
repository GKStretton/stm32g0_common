#include "QMC5883L.h"
#include "util.h"

float MxMin = -40.0f;
float MxMax = 505.0f;
float MyMin = -113.0f;
float MyMax = 393.0f;
float MzMin = -73.0f;
float MzMax = 420.0f;


void QMC5883L_Init(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c)
{
	print(uart, "QMC5883L initialisation PLACEHOLDER.\n");
}

int updateMagnetometer(I2C_HandleTypeDef *i2c)
{
	return 0;
}

void adjustMagnetometer()
{

}
