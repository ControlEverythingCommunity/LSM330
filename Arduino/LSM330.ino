// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM330
// This code is designed to work with the LSM330_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM330_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// LSM330 Gyro I2C address is 0x6A(106)
#define Addr_Gyro 0x6A
// LSM330 Accl I2C address is 0x1D(29)
#define Addr_Accl 0x1D

void setup() 
{
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
  unsigned data[6];

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
  int xGyro = data[1] * 256 + data[0];
  int yGyro = data[3] * 256 + data[2];
  int zGyro = data[5] * 256 + data[4];

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
  int xAccl = data[1] * 256 + data[0];
  int yAccl = data[3] * 256 + data[2];
  int zAccl = data[5] * 256 + data[4];

  // Output data to Serial Monitor
  Serial.print("X-Axis of Rotation :");
  Serial.println(xGyro);
  Serial.print("Y-Axis of Rotation :");
  Serial.println(yGyro);
  Serial.print("Z-Axis of Rotation :");
  Serial.println(zGyro);
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis : ");
  Serial.println(yAccl);
  Serial.print("Acceleration in Z-Axis : ");
  Serial.println(zAccl);
  delay(500);
}
