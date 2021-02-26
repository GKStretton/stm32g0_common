#include "QMC5883L.h"
#include "util.h"

#define QMC_ADDRESS 0x0D
#define WHOIS_REGISTER 0x0D
#define XOUT_REGISTER 0x00
#define CR1_REGISTER 0x09
#define CR2_REGISTER 0x0A

void QMC5883L_Init(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c)
{
	// 0000RR01 10:00 50:01 100:10 200:11
	writeOneByte(i2c, QMC_ADDRESS, CR1_REGISTER, 0b00000001);
	if (getWhoIs() != 0xFF)
	{
		print(uart, "QMC5883L Incorrect ID:");
		uint8_t val = getWhoIs();
		HAL_UART_Transmit(uart, (uint8_t*) &val, 1, 1000);
	}

	print(uart, "QMC5883L initialisation complete.\n");
}

void updateMagnetometer(I2C_HandleTypeDef *i2c)
{
	uint8_t data[6];
	readBytes(i2c, QMC_ADDRESS, XOUT_REGISTER, data, 6);

	Mx = (data[1] << 8) | data[0];
	My = (data[3] << 8) | data[2];
	Mz = (data[5] << 8) | data[4];
}

void adjustMagnetometer(struct MagCalibration *cal)
{

}

uint8_t getWhoIs(I2C_HandleTypeDef *i2c)
{
	uint8_t id;
	readBytes(i2c, QMC_ADDRESS, WHOIS_REGISTER, &id, 1);
	return id;
}
