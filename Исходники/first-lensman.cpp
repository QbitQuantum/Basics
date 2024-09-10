static void setup() {
	// initialize device
	printf("Initializing I2C devices...\n");
	mpu.initialize();

	// verify connection
	printf("Testing device connections...\n");
	printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");

	// load and configure the DMP
	printf("Initializing DMP...\n");
	devStatus = mpu.dmpInitialize();

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		printf("Enabling DMP...\n");
		mpu.setDMPEnabled(true);

		// enable Arduino interrupt detection
		//Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
		//attachInterrupt(0, dmpDataReady, RISING);
		mpuIntStatus = mpu.getIntStatus();

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		printf("DMP ready! Waiting for first interrupt...\n");
		dmpReady = true;

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
	}
	else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		printf("DMP Initialization failed (code %d)\n", devStatus);
	}

	/*
	adjAccel[0] = adjAccel[1] = adjAccel[2] = 0;
	adjGyro[0] = adjGyro[1] = adjGyro[2] = 0;
	for (int i = 0; i < 20; i++)
	{
		readFIFO();
		mpu.dmpGetAccel(accel, fifoBuffer);
		mpu.dmpGetGyro(gyro, fifoBuffer);
		adjAccel[0] += accel[0];
		adjAccel[1] += accel[1];
		adjAccel[2] += accel[2];
		adjGyro[0] += gyro[0];
		adjGyro[1] += gyro[1];
		adjGyro[2] += gyro[2];
	}
	adjAccel[0] /= 20;
	adjAccel[1] /= 20;
	adjAccel[2] /= 20;
	adjGyro[0] /= 20;
	adjGyro[1] /= 20;
	adjGyro[2] /= 20;
	printf("ADJUST: %d, %d, %d\n", adjAccel[0], adjAccel[1], adjAccel[2]);
	*/

	measurement.setTo(cv::Scalar(0));
	kalman.transitionMatrix =
		*(cv::Mat_<float>(4, 4) <<
		1, 0, 1, 0,
		0, 1, 0, 1,
		0, 0, 1, 0,
		0, 0, 0, 1);
	readFIFO();
	mpu.dmpGetAccel(accel, fifoBuffer);
	kalman.statePre.at<float>(0) = accel[0];
	kalman.statePre.at<float>(1) = accel[1];
	kalman.statePre.at<float>(2) = accel[2];
	kalman.statePre.at<float>(3) = 0.0;
	setIdentity(kalman.measurementMatrix);
	setIdentity(kalman.processNoiseCov, cv::Scalar::all(1e-4));
	setIdentity(kalman.measurementNoiseCov, cv::Scalar::all(10));
	setIdentity(kalman.errorCovPost, cv::Scalar::all(.1));
}