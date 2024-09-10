void* gyro_acc(void*)
{
    int i = 0;
    // initialize device
    printf("Initializing I2C devices...\n");
    mpu.initialize();
    
    // verify connection
    printf("Testing device connections...\n");
    printf(mpu.testConnection() ? "MPU6050 connection successful\n" : "MPU6050 connection failed\n");
    mpu.setI2CMasterModeEnabled(false);
    mpu.setI2CBypassEnabled(true);
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
        printf("DMP ready!\n");
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        printf("DMP Initialization failed (code %d)\n", devStatus);
        return 0;
    }
    /*****************************************************/
    while(1)
    {
        if (START_FLAG == 0)
        {
            delay(200);
        }
        if (START_FLAG == 1)
        {
            break;
        }
    }
    delay(50);
    for(;;)
    {
        if (!dmpReady) return 0;
        // get current FIFO count
        fifoCount = mpu.getFIFOCount();

        if (fifoCount == 1024) 
        {
            // reset so we can continue cleanly
            mpu.resetFIFO();
            printf("FIFO overflow!\n");

            // otherwise, check for DMP data ready interrupt (this should happen frequently)
        } 
        else if (fifoCount >= 42) 
        {
            // read a packet from FIFO
            mpu.getFIFOBytes(fifoBuffer, packetSize);
            
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            //printf("ypr  %7.2f %7.2f %7.2f  ", ypr[0] * 180/M_PI, ypr[1] * 180/M_PI, ypr[2] * 180/M_PI);
            Angle[2] = ypr[0] * 180/M_PI;
            Angle[1] = ypr[1] * 180/M_PI;//此为Pitch
            Angle[0] = ypr[2] * 180/M_PI;//此为Roll
            
            // display initial world-frame acceleration, adjusted to remove gravity
            // and rotated based on known orientation from quaternion
            /*
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            //printf("aworld %6d %6d %6d    ", aaWorld.x, aaWorld.y, aaWorld.z);
            //AngleSpeed[0] =  aaWorld.x;
            //AngleSpeed[1] =  aaWorld.y;
            //AngleSpeed[2] =  aaWorld.z;
            */
            /****************************读取完毕*********************************/
            if (Inital <= 300)
            {
                Inital ++;
                if (Inital % 98 == 1)
                {
                Inital_Roll[i] = Angle[0];
                Inital_Pitch[i] = Angle[1];
                Inital_Yaw[i] = Angle[2];
                printf("Roll:%.2f Pitch:%.2f Yaw:%.2f",Inital_Roll[i],Inital_Pitch[i],Inital_Yaw[i]);
                i++;
                printf("%d\n",Inital);
                fflush(stdout);
                if (i == 3)
                {
                    Inital_Yaw[3] = (Inital_Yaw[0] + Inital_Yaw[1] + Inital_Yaw[2]) / 3;
                    Inital_Roll[3] =(Inital_Roll[0] + Inital_Roll[1] + Inital_Roll[2]) / 3;
                    Inital_Pitch[3] = (Inital_Pitch[0] + Inital_Pitch[1] + Inital_Pitch[2]) / 3;
                }
                }
            }
            else
            {
                Pid_Roll = Pid_Calc_R(Roll_Suit,Angle[0]);
                Pid_Pitch = Pid_Calc_P(Pitch_Suit,Angle[1]);
                Pid_Yaw = Pid_Calc_Y(Yaw_Suit,Angle[2],Inital_Yaw[3]);
                All_Count = All_Count + 1;
                DutyCycle[0] = Default_Acc  - Pid_Roll - Pid_Pitch; //- Pid_Yaw;
                DutyCycle[1] = Default_Acc  - Pid_Roll + Pid_Pitch; //+ Pid_Yaw;
                //DutyCycle[0] = Default_Acc;
                //DutyCycle[1] = Default_Acc;
                DutyCycle[2] = Default_Acc  + Pid_Roll - Pid_Pitch; //+ Pid_Yaw;
                DutyCycle[3] = Default_Acc  + Pid_Roll + Pid_Pitch; //- Pid_Yaw;
                //DutyCycle[2] = Default_Acc;
                //DutyCycle[3] = Default_Acc;
            
                PWMOut(PinNumber1,DutyCycle[0]);
                PWMOut(PinNumber2,DutyCycle[1]);
                PWMOut(PinNumber3,DutyCycle[2]);
                PWMOut(PinNumber4,DutyCycle[3]);
            }
        }
    }
}