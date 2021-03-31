#include "QMC5883L.h"
#include "util.h"

#define QMC_ADDRESS 0x0D
#define WHOIS_REGISTER 0x0D
#define XOUT_REGISTER 0x00
#define CR1_REGISTER 0x09
#define CR2_REGISTER 0x0A

void QMC5883L_Init(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c, uint8_t rateSetting)
{
	// 0000RR01 10:00 50:01 100:10 200:11
	writeOneByte(i2c, QMC_ADDRESS, CR1_REGISTER, 0b00000001 | (rateSetting << 2));

	  /*
	  35168 Bytes GOOD
	  35176 Bytes FAULT (2ledOns in main)
	  35420 Bytes FAULT (43 ledOns in main)
	  35428 Bytes GOOD
	  https://electronics.stackexchange.com/questions/498286/how-to-debug-this-i2c-hard-fault
	  https://interrupt.memfault.com/blog/cortex-m-fault-debug#registers-prior-to-exception
	  Check on other hardware
	  */
	/* Cause of the strangest bug ever. Program halting through this, but only when the program was a certain size.
	if (getWhoIs() != 0xFF)
	{
		print(uart, "QMC5883L Incorrect ID:");
		uint8_t val = getWhoIs();
		HAL_UART_Transmit(uart, (uint8_t*) &val, 1, 1000);
	}*/

	print(uart, "QMC5883L initialisation complete.\n");
}

void updateMagnetometer(I2C_HandleTypeDef *i2c)
{
	uint8_t data[6];
	readBytes(i2c, QMC_ADDRESS, XOUT_REGISTER, data, 6);

	float Lx = (data[1] << 8) | data[0];
	float Ly = (data[3] << 8) | data[2];
	float Lz = (data[5] << 8) | data[4];

	Mx = -Ly;
	My = Lx;
	Mz = Lz;
}

void adjustMagnetometer(struct MagCalibration *cal)
{
	Mx = 2 * (Mx - cal->MxMin) / (cal->MxMax - cal->MxMin) - 1;
	My = 2 * (My - cal->MyMin) / (cal->MyMax - cal->MyMin) - 1;
	Mz = 2 * (Mz - cal->MzMin) / (cal->MzMax - cal->MzMin) - 1;
}

void calibrateMagnetometer(UART_HandleTypeDef *uart, I2C_HandleTypeDef *i2c)
{
	while (1)
	{
		updateMagnetometer(i2c);
		printFloats(uart, "", 3, Mx, My, Mz);
		HAL_Delay(50);
	}
}

uint8_t getWhoIs(I2C_HandleTypeDef *i2c)
{
	uint8_t id;
	readBytes(i2c, QMC_ADDRESS, WHOIS_REGISTER, &id, 1);
	return id;
}
