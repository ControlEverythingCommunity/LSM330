// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM330
// This code is designed to work with the LSM330_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM330_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file, i = 0;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, LSM330 GYRO I2C address is 0x6A(106)
	ioctl(file, I2C_SLAVE, 0x6A);
	
	// Select control register1
	// X, Y and Z axis enabled, power on mode, o/p data rate 95 Hz
	char config[2] = {0};
	config[0] = 0x20;
	config[1] = 0x0F;
	write(file, config, 2);
	sleep(0.5);
	
	// Read 6 bytes of data
	// xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
	char data[6] = {0};
	char input[1] = {0};
	char reg[1] = {0};
	
	for(i = 0; i < 6; i++)
	{
		reg = (0x28 + i);
		write(file, reg, 1);
		if(read(file, input, 1) != 1)
		{
			printf("Erorr : Input/output Erorr \n");
			exit(1);
		}
		data[i] = input[0];
	}
	
	// Convert the data
    int xGyro = (data[1] * 256 + data[0]);
    if(xGyro > 32767)
    {
        xGyro -= 65536;
    }
    
    int yGyro = (data[3] * 256 + data[2]);
    if(yGyro > 32767)
    {
        yGyro -= 65536;
    }
    
    int zGyro = (data[5] * 256 + data[4]);
    if(zGyro > 32767)
    {
        zGyro -= 65536;
    }
	
	// Get I2C device, LSM330 ACCELERO I2C address is 0x1D(29)
	ioctl(file, I2C_SLAVE, 0x1D);
	
	// Select control register1
	// X, Y and Z axis enabled, power on mode, o/p data rate 100 Hz
	config[0] = 0x20;
	config[1] = 0x67;
	write(file, config, 2);
	sleep(0.5)
	
	// Read 6 bytes of data
	// xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
	for(i = 0; i < 6; i++)
	{
		reg = (0x28 + i);
		write(file, reg, 1);
		if(read(file, input, 1) != 1)
		{
			printf("Erorr : Input/output Erorr \n");
			exit(1);
		}
		data[i] = input[0];
	}
	
	// Convert the data
    int xAccl = (data[1] * 256 + data[0]);
    if(xAccl > 32767)
    {
        xAccl -= 65536;
    }
    
    int yAccl = (data[3] * 256 + data[2]);
    if(yAccl > 32767)
    {
        yAccl -= 65536;
    }
    
    int zAccl = (data[5] * 256 + data[4]);
    if(zAccl > 32767)
    {
        zAccl -= 65536;
    }
	
	// Output data to screen
    printf("Rotation in X-axis : %d \n", xGyro);
    printf("Rotation in Y-axis : %d \n", yGyro);
    printf("Rotation in Z-axis : %d \n", zGyro);
    printf("Acceleration in X-axis : %d \n", xAccl);
    printf("Acceleration in Y-axis : %d \n", yAccl);
    printf("Acceleration in Z-axis : %d \n", zAccl);
}	