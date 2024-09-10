//PROGRAM FUNCTIONS
void setup_mpu6050(){
	clear_i2c();
	Wire.begin();
	SERIAL_OUT.println("Initializing gyro...");
	accelgyro.initialize();
	//accelgyro.reset();
    accelgyro.setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!

	// verify connection
	SERIAL_OUT.println("Testing device connections...");
	SERIAL_OUT.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

	SERIAL_OUT.println(F("Setting clock source to Z Gyro..."));
	accelgyro.setClockSource(MPU6050_CLOCK_PLL_ZGYRO);
	//SERIAL_OUT.println(accelgyro.getClockSource(MPU6050_CLOCK_PLL_ZGYRO);

	SERIAL_OUT.println(F("Setting sample rate to 200Hz..."));
	accelgyro.setRate(0); // 1khz / (1 + 4) = 200 Hz

// *          |   ACCELEROMETER    |           GYROSCOPE
// * DLPF_CFG | Bandwidth | Delay  | Bandwidth | Delay  | Sample Rate
// * ---------+-----------+--------+-----------+--------+-------------
// * 0        | 260Hz     | 0ms    | 256Hz     | 0.98ms | 8kHz
// * 1        | 184Hz     | 2.0ms  | 188Hz     | 1.9ms  | 1kHz
// * 2        | 94Hz      | 3.0ms  | 98Hz      | 2.8ms  | 1kHz
// * 3        | 44Hz      | 4.9ms  | 42Hz      | 4.8ms  | 1kHz
// * 4        | 21Hz      | 8.5ms  | 20Hz      | 8.3ms  | 1kHz
// * 5        | 10Hz      | 13.8ms | 10Hz      | 13.4ms | 1kHz
// * 6        | 5Hz       | 19.0ms | 5Hz       | 18.6ms | 1kHz
// * 7        |   -- Reserved --   |   -- Reserved --   | Reserved

	SERIAL_OUT.println(F("Setting DLPF bandwidth"));
	accelgyro.setDLPFMode(MPU6050_DLPF_BW_42);

	SERIAL_OUT.println(F("Setting gyro sensitivity to +/- 250 deg/sec..."));
	accelgyro.setFullScaleGyroRange(0);
	//accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
	//accelgyro.setFullScaleGyroRange(0);  // 0=250, 1=500, 2=1000, 3=2000 deg/sec

	//SERIAL_OUT.println(F("Resetting FIFO..."));
	//accelgyro.resetFIFO();

	// use the code below to change accel/gyro offset values
	accelgyro.setXGyroOffset(XGYROOFFSET);
	accelgyro.setYGyroOffset(YGYROOFFSET);
	accelgyro.setZGyroOffset(ZGYROOFFSET);
	SERIAL_OUT.print(accelgyro.getXAccelOffset()); SERIAL_OUT.print("\t"); // 
	SERIAL_OUT.print(accelgyro.getYAccelOffset()); SERIAL_OUT.print("\t"); // 
	SERIAL_OUT.print(accelgyro.getZAccelOffset()); SERIAL_OUT.print("\t"); // 
	SERIAL_OUT.print(accelgyro.getXGyroOffset()); SERIAL_OUT.print("\t"); // 
	SERIAL_OUT.print(accelgyro.getYGyroOffset()); SERIAL_OUT.print("\t"); // 
	SERIAL_OUT.print(accelgyro.getZGyroOffset()); SERIAL_OUT.print("\t"); // 
	SERIAL_OUT.print("\n");
		
	SERIAL_OUT.println(F("Enabling FIFO..."));
	accelgyro.setFIFOEnabled(true);
	accelgyro.setZGyroFIFOEnabled(true);
	accelgyro.setXGyroFIFOEnabled(false);
	accelgyro.setYGyroFIFOEnabled(false);
	accelgyro.setAccelFIFOEnabled(false);
	SERIAL_OUT.print("Z axis enabled?\t"); SERIAL_OUT.println(accelgyro.getZGyroFIFOEnabled());
	SERIAL_OUT.print("x axis enabled?\t"); SERIAL_OUT.println(accelgyro.getXGyroFIFOEnabled());
	SERIAL_OUT.print("y axis enabled?\t"); SERIAL_OUT.println(accelgyro.getYGyroFIFOEnabled());
	SERIAL_OUT.print("accel enabled?\t"); SERIAL_OUT.println(accelgyro.getAccelFIFOEnabled());
	accelgyro.resetFIFO();
	return ;
}