// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM330
// This code is designed to work with the LSM330_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM330_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// LSM330 Gyro I2C address is 0x6A(106)
#define Addr_Gyro 0x6A
// LSM330 Accl I2C address is 0x1D(29)
#define Addr_Accl 0x1D

int xGyro = 0, yGyro = 0, zGyro = 0, xAccl = 0, yAccl =  0, zAccl = 0;
void setup() 
{
    // Set variable
    Particle.variable("i2cdevice", "LSM330");
    Particle.variable("xAccl", xAccl);
    Particle.variable("yAccl", yAccl);
    Particle.variable("zAccl", zAccl);
    Particle.variable("xGyro", xGyro);
    Particle.variable("yGyro", yGyro);
    Particle.variable("zGyro", zGyro);
    
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise serial communication, set baud rate = 9600
    Serial.begin(9600);
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Gyro);
    // Select control register 1
    Wire.write(0x20);
    // X, Y and Z axis enabled, power on mode, output data rate 95 Hz
    Wire.write(0x0F);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr_Accl);
    // Select control register1
    Wire.write(0x20);
    // X, Y and Z axis enabled, power on mode, output data rate 100 Hz
    Wire.write(0x67);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay(300);
}

void loop()
{
    unsigned int data[6];
    
    for(int i = 0; i < 6; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(Addr_Gyro);
        // Select data register
        Wire.write((40 + i));
        // Stop I2C transmission
        Wire.endTransmission();
        
        // Request 1 byte of data
        Wire.requestFrom(Addr_Gyro, 1);
        
        // Read 6 bytes of data
        // xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
        if(Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }
    
    // Convert the data
    xGyro = ((data[1] * 256) + data[0]);
    if (xGyro > 32767)
    {
        xGyro -= 65536;
    }
    yGyro = ((data[3] * 256) + data[2]);
    if (yGyro > 32767)
    {
        yGyro -= 65536;
    }
    zGyro = ((data[5] * 256) + data[4]);
    if (zGyro > 32767)
    {
        zGyro -= 65536;
    }

    delay(500);
    
    for(int i = 0; i < 6; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(Addr_Accl);
        // Select data register
        Wire.write((40 + i));
        // Stop I2C transmission
        Wire.endTransmission();
        
        // Request 1 byte of data
        Wire.requestFrom(Addr_Accl, 1);
        
        // Read 6 bytes of data
        // xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
        if(Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }
    
    // Convert the data
    xAccl = ((data[1] * 256) + data[0]);
    if(xAccl > 32767)
    {
        xAccl -= 65536;
    }
    yAccl = ((data[3] * 256) + data[2]);
    if(yAccl > 32767)
    {
        yAccl -= 65536;
    }
    zAccl = ((data[5] * 256) + data[4]);
    if(zAccl > 32767)
    {
        zAccl -= 65536;
    }

    // Output data to dashboard
    Particle.publish("X-Axis of Rotation :", String(xGyro));
    delay(1000);
    Particle.publish("Y-Axis of Rotation :", String(yGyro));
    delay(1000);
    Particle.publish("Z-Axis of Rotation :", String(zGyro));
    delay(1000);
    Particle.publish("Acceleration in X-Axis : ", String(xAccl));
    delay(1000);
    Particle.publish("Acceleration in Y-Axis : ", String(yAccl));
    delay(1000);
    Particle.publish("Acceleration in Z-Axis : ", String(zAccl));
    delay(1000);
}
