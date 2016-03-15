// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LSM330
// This code is designed to work with the LSM330_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=LSM330_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LSM330
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LSM330 GYRO I2C address is 0x6A(106)
		I2CDevice device_gyro = bus.getDevice(0x6A);

		// Select control register1
		// X, Y and Z axis enabled, power on mode, o/p data rate 95 Hz
		device_gyro.write(0x20 ,(byte)0x0F);
		Thread.sleep(300);

		// Read 6 bytes of data
		// xGyro lsb, xGyro msb, yGyro lsb, yGyro msb, zGyro lsb, zGyro msb
		byte[] data = new byte[6];
		data[0] = (byte)device_gyro.read(0x28);
		data[1] = (byte)device_gyro.read(0x29);
		data[2] = (byte)device_gyro.read(0x2A);
		data[3] = (byte)device_gyro.read(0x2B);
		data[4] = (byte)device_gyro.read(0x2C);
		data[5] = (byte)device_gyro.read(0x2D);

		// Convert the data
		int xGyro = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF)) ;
		if(xGyro > 32767)
		{
			xGyro -= 65536;
		}	

		int yGyro = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yGyro > 32767)
		{
			yGyro -= 65536;
		}

		int zGyro = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zGyro > 32767)
		{
			zGyro -= 65536;
		}

		// Get I2C device, LSM330 ACCELERO I2C address is 0x1D(29)
		I2CDevice device_acc = bus.getDevice(0x1D);
		
		// Select control register1
		// X, Y and Z axis enabled, power on mode, o/p data rate 100 Hz
		device_acc.write(0x20, (byte)0x67);
		Thread.sleep(300);
		
		// Read 6 bytes of data
		// xAccl lsb, xAccl msb, yAccl lsb, yAccl msb, zAccl lsb, zAccl msb
		data[0] = (byte)device_acc.read(0x28);
		data[1] = (byte)device_acc.read(0x29);
		data[2] = (byte)device_acc.read(0x2A);
		data[3] = (byte)device_acc.read(0x2B);
		data[4] = (byte)device_acc.read(0x2C);
		data[5] = (byte)device_acc.read(0x2D);

		// Convert the data
		int xAccl = ((data[1] & 0xFF) * 256 + (data[0] & 0xFF)) ;
		if(xAccl > 32767)
		{
			xAccl -= 65536;
		}	
		
		int yAccl = ((data[3] & 0xFF) * 256 + (data[2] & 0xFF)) ;
		if(yAccl > 32767)
		{
			yAccl -= 65536;
		}
		
		int zAccl = ((data[5] & 0xFF) * 256 + (data[4] & 0xFF)) ;
		if(zAccl > 32767)
		{
			zAccl -= 65536;
		}
		
		// Output data to screen
		System.out.printf("Rotation in X-Axis : %d %n", xGyro);
		System.out.printf("Rotation in Y-Axis : %d %n", yGyro);
		System.out.printf("Rotation in Z-Axis : %d %n", zGyro);
		System.out.printf("Acceleration in X-Axis : %d %n", xAccl);
		System.out.printf("Acceleration in Y-Axis : %d %n", yAccl);
		System.out.printf("Acceleration in Z-Axis : %d %n", zAccl);
	}
}
