#include "accelerometer.h"
#include "i2c.h"

void accelerometer_init(void)
{
	  I2C_Init();
    I2C_WriteReg(0x1D, 0x2A, 1); // Set ACTIVE bit in CTRL_REG1 in MMA8451
}

accelerometer_vector accelerometer_read(void)
{
	  uint8_t arrayXYZ[6];
    accelerometer_vector result;
		for (int i = 0; i < 3; i++) {
				I2C_ReadRegBlock(0x1D, 0x01, 6, arrayXYZ);
		}
		result.x = ((float)((int16_t)((arrayXYZ[0] << 8) | arrayXYZ[1]) >> 2) / 4096);
		result.y = ((float)((int16_t)((arrayXYZ[2] << 8) | arrayXYZ[3]) >> 2) / 4096);
		result.z = ((float)((int16_t)((arrayXYZ[4] << 8) | arrayXYZ[5]) >> 2) / 4096);
    return result;
}
