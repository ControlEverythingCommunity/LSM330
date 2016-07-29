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
    // lsb first
    // Read xGyro lsb data from register(0x28)
    char reg[1] = {0x28};
    write(file, reg, 1);
    char data[1] = {0};
    if(read(file, data, 1) != 1)
    {
        printf("Error : Input/Output error \n");
        exit(1);
    }
    char data_0 = data[0];
    
    // Read xGyro msb data from register(0x29)
    reg[0] = 0x29;
    write(file, reg, 1);
    read(file, data, 1);
    char data_1 = data[0];
    
    // Read yGyro lsb data from register(0x2A)
    reg[0] = 0x2A;
    write(file, reg, 1);
    read(file, data, 1);
    char data_2 = data[0];
    
    // Read yGyro msb data from register(0x2B)
    reg[0] = 0x2B;
    write(file, reg, 1);
    read(file, data, 1);
    char data_3 = data[0];
    
    // Read zGyro lsb data from register(0x2C)
    reg[0] = 0x2C;
    write(file, reg, 1);
    read(file, data, 1);
    char data_4 = data[0];
    
    // Read zGyro msb data from register(0x2D)
    reg[0] = 0x2D;
    write(file, reg, 1);
    read(file, data, 1);
    char data_5 = data[0];
    
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
    sleep(0.5);
    
    // Read 6 bytes of data
    // lsb first
    // Read xAccl lsb data from register(0x28)
    char reg1[1] = {0x28};
    write(file, reg1, 1);
    char data1[1] = {0};
    if(read(file, data1, 1) != 1)
    {
        printf("Error : Input/Output error \n");
        exit(1);
    }
    char data1_0 = data1[0];
    
    // Read xAccl msb data from register(0x29)
    reg1[0] = 0x29;
    write(file, reg1, 1);
    read(file, data1, 1);
    char data1_1 = data1[0];
    
    // Read yAccl lsb data from register(0x2A)
    reg1[0] = 0x2A;
    write(file, reg1, 1);
    read(file, data1, 1);
    char data1_2 = data1[0];
    
    // Read yAccl msb data from register(0x2B)
    reg1[0] = 0x2B;
    write(file, reg1, 1);
    read(file, data1, 1);
    char data1_3 = data1[0];
    
    // Read zAccl lsb data from register(0x2C)
    reg1[0] = 0x2C;
    write(file, reg1, 1);
    read(file, data1, 1);
    char data1_4 = data1[0];
    
    // Read zAccl msb data from register(0x2D)
    reg1[0] = 0x2D;
    write(file, reg1, 1);
    read(file, data1, 1);
    char data1_5 = data1[0];
    
    // Convert the data
    int xAccl = (data1_1 * 256 + data1_0);
    if(xAccl > 32767)
    {
        xAccl -= 65536;
    }
    
    int yAccl = (data1_3 * 256 + data1_2);
    if(yAccl > 32767)
    {
        yAccl -= 65536;
    }
    
    int zAccl = (data1_5 * 256 + data1_4);
    if(zAccl > 32767)
    {
        zAccl -= 65536;
    }
    
    // Output data to screen
    printf("Acceleration in X-Axis : %d \n", xAccl);
    printf("Acceleration in Y-Axis : %d \n", yAccl);
    printf("Acceleration in Z-Axis : %d \n", zAccl);
    printf("Rotation in X-axis : %d \n", xGyro);
    printf("Rotation in Y-axis : %d \n", yGyro);
    printf("Rotation in Z-axis : %d \n", zGyro);
}
