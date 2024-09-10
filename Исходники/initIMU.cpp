int setup() {
    // initialize device
    printf("Initializing MPU ...\n");
    mpu.initialize();

    // verify connection
    printf("Testing connection ...\n");
    if (!mpu.testConnection()) { printf("MPU6050 connection failed\n"); return 1; }

    // load and configure the DMP
    printf("Flashing DMP ...\n");
    devStatus = mpu.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        //attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
        printf("DMP ready\n");
        printf("MPU6050 initialized!\n");
        return 0;
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
        return 1;
    }
}