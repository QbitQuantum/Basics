bool i2cSetupGyro()
{
    //wake up gyro
	//return I2Cdev::writeBit( gyroAddr, 0x6b, 6, 0b0);
	gyroscope.initialize();
	return gyroscope.testConnection();
}