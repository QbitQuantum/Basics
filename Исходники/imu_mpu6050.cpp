void imu_init()
{
		
	uint8_t count = 10;
	
    // initialize device
#ifdef __BOARD_YUN__
	Console.println(F("Initializing I2C devices..."));
#else
    Serial.println(F("Initializing I2C devices..."));
#endif
    mpu.initialize();

    // verify connection
#ifdef __BOARD_YUN__
    Console.println(F("Testing device connections..."));
    Console.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
#else
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
#endif
/*
    // wait for ready
    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
    while (Serial.available() && Serial.read()); // empty buffer
    while (!Serial.available());                 // wait for data
    while (Serial.available() && Serial.read()); // empty buffer again
*/
    // load and configure the DMP
#ifdef __BOARD_YUN__
    Console.println(F("Initializing DMP..."));
#else
    Serial.println(F("Initializing DMP..."));
#endif    
	do {
	
		devStatus = mpu.dmpInitialize();
		// Set some offset to the MEMS
		mpu.setXGyroOffset(220);
		mpu.setYGyroOffset(76);
		mpu.setZGyroOffset(-85);
		mpu.setZAccelOffset(1788);
		// make sure it worked (returns 0 if so)
		if (devStatus == 0) 
		{
			count = 10;
			// turn on the DMP, now that it's ready
#ifdef __BOARD_YUN__
			Console.println(F("Enabling DMP..."));
#else			
			Serial.println(F("Enabling DMP..."));
#endif
			mpu.setDMPEnabled(true);

			mpuIntStatus = mpu.getIntStatus();

			// set our DMP Ready flag so the main loop() function knows it's okay to use it
#ifdef __BOARD_YUN__
			Console.println(F("DMP ready! Waiting for first interrupt..."));
#else
			Serial.println(F("DMP ready! Waiting for first interrupt..."));
#endif
			dmpReady = true;

			// get expected DMP packet size for later comparison
			packetSize = mpu.dmpGetFIFOPacketSize();
			return;
		} 
		else {
			// ERROR!
			// 1 = initial memory load failed
			// 2 = DMP configuration updates failed
			// (if it's going to break, usually the code will be 1)
#ifdef __BOARD_YUN__
			Console.print(F("DMP Initialization failed (code"));
			Console.print(devStatus);
			Console.println(F(")"));
			// New attempt message
			Console.println(F("Trying again"));
#else
			Serial.print(F("DMP Initialization failed (code "));
			Serial.print(devStatus);
			Serial.println(F(")"));
			// New attempt message
			Serial.println(F("Trying again"));
#endif
		}
	}
	while (--count);
	
	// configure LED for output	
	pinMode(SOL_LED, OUTPUT);
	
	// Check if the configuration has failed
//	if (!count) 
	{	
#ifdef __BOARD_YUN__
		Console.println(F("DMP initializaion failed"));
#else
		Serial.println(F("DMP initialization failed"));
#endif
		while (true) 
		{
			// Locks in infinite loop
			digitalWrite(SOL_LED, HIGH);
			delay(300);
			digitalWrite(SOL_LED, LOW);
			delay(300);
		}
	}
	
}