int main(int argc, char const *argv[])
{
    AccelVector gravity;
    MPU6050 accelgyro;
    accelgyro.initialize();
    accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    int16_t 
        x=-3940,
        y=-0110,
        z=00326;
    int16_t 
        gx,
        gy,
        gz;
    // accelgyro.getAcceleration(&x, &y,&z);
    gravity.x = x; gravity.y = y; gravity.z = z;
    float alpha = 0.5f, gyralpha = 0.9f;
    // for(int i=0; i<100; i++){
    //     accelgyro.getAcceleration(&x, &y,&z);
    //     gravity.x = gravity.x * alpha + x * (1 - alpha);
    //     gravity.y = gravity.y * alpha + y * (1 - alpha);
    //     gravity.z = gravity.z * alpha + z * (1 - alpha);
    //     usleep(50000);
    // }
    AccelVector vec, gyr;

        accelgyro.getMotion6(&x, &y,&z, &gx, &gy, &gz);
    gyr.x = gx; gyr.y = gy; gyr.z = gz;
    while(1)
    {
        accelgyro.getMotion6(&x, &y,&z, &gx, &gy, &gz);
        //accelgyro.getAcceleration(&x, &y,&z,);
        vec.x = vec.x * alpha + x * (1 - alpha);
        vec.y = vec.y * alpha + y * (1 - alpha);
        vec.z = vec.z * alpha + z * (1 - alpha);

        gyr.x = gyr.x * gyralpha + gx * (1 - gyralpha);
        gyr.y = gyr.y * gyralpha + gy * (1 - gyralpha);
        gyr.z = gyr.z * gyralpha + gz * (1 - gyralpha);
        
        printf("Total gforce now %.3f g's gyro len %.3f | Now: %05.0f %05.0f %05.0f Gyro: %05.0f %05.0f %05.0f\n", 
            vec.getMagnitude()/16000, gyr.getMagnitude(), vec.x, vec.y, vec.z, gyr.x, gyr.y, gyr.z);

        usleep(50000);
    }

        // MPU control/status vars
	/*bool dmpReady = false;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

	// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorInt16 aa;         // [x, y, z]            accel sensor measurements
	VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
	VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
	VectorFloat gravity;    // [x, y, z]            gravity vector
	float euler[3];         // [psi, theta, phi]    Euler angle container
	float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
	MPU6050 accelgyro;
    accelgyro.initialize();
    // load and configure the DMP
    printf("Initializing DMP...\n");
    devStatus = accelgyro.dmpInitialize();
    
    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        printf("Enabling DMP...\n");
        accelgyro.setDMPEnabled(true);

        // enable Arduino interrupt detection
        //Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        //attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = accelgyro.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        printf("DMP ready!\n");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = accelgyro.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
        return 0;
    }

    while(1){
        fifoCount = accelgyro.getFIFOCount();

        if (fifoCount == 1024) {
            // reset so we can continue cleanly
            accelgyro.resetFIFO();
            printf("FIFO overflow!\n");

        // otherwise, check for DMP data ready interrupt (this should happen frequently)
        } else if (fifoCount >= 42) {
            // read a packet from FIFO
            accelgyro.getFIFOBytes(fifoBuffer, packetSize);
            // display Euler angles in degrees
            accelgyro.dmpGetQuaternion(&q, fifoBuffer);
            accelgyro.dmpGetGravity(&gravity, &q);
            accelgyro.dmpGetYawPitchRoll(ypr, &q, &gravity);
            printf("ypr  %7.2f %7.2f %7.2f    \n", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
        }
    }        */
	return 0;
}