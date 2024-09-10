void setup_IMU() 
{
	tmObjectInit(&lagedatalogsync_tmup);
	I2CInitialize();
	mpu.initialize();
	devStatus = mpu.dmpInitialize();
	if (devStatus == 0) 
	{
		//chThdCreateStatic(LageSyncThreadWorkingArea, sizeof(LageSyncThreadWorkingArea), NORMALPRIO, LageSyncthread, NULL);
		mpu.setDMPEnabled(true);
		mpuIntStatus = mpu.getIntStatus();
		dmpReady = true;
		packetSize = mpu.dmpGetFIFOPacketSize();
	} 
}