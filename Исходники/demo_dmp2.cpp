void* gyro_acc(void*)
{
    //float kp = 0.00375,ki = 0.0000,kd = 0.00076;
    float kp = 0.0068,ki = 0.000,kd = 0.0018;
    //0030 0088 0014 有偏角 p0.0031偏角更大 0.0029也是 i=0 小偏角 p0.00305 d0.00143 不错 i0.0005 偏角变大
    //0032 0017
    float pregyro =0;
    float desired = 0;
    //double error;
    float integ=0;//integral积分参数
    float iLimit =8 ;
    float deriv=0;//derivative微分参数 
    float prevError=0;
    float lastoutput=0;
    //float Piddeadband=0.3;
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
        
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetAccel(&aa, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
        //printf("aworld %6d %6d %6d    ", aaWorld.x, aaWorld.y, aaWorld.z);
        AngleSpeed[0] =  aaWorld.x;
        AngleSpeed[1] =  aaWorld.y;
        AngleSpeed[2] =  aaWorld.z;
        
        /****************************读取完毕*********************************/
        error = desired - Angle[0];//偏差：期望-测量值
        All_Count = All_Count + 1;
        error = error * 0.88 + prevError * 0.12;
        /*
        if (fabs(prevError - error ) > 12)
        {
            error = prevError;
        }*/
        
        integ += error * IMU_UPDATE_DT;//偏差积分，IMU_UPDATE_DT也就是每调整漏斗大小的步辐
        
        if (integ >= iLimit)//作积分限制
        {
          integ = iLimit;
        }
        else if (integ < -iLimit)
        {
          integ = -iLimit;
        }
        
        deriv = (error - prevError) / IMU_UPDATE_DT;//微分     应该可用陀螺仪角速度代替
        
        AngleSpeed[0] = deriv;
        if (fabs(deriv) < 20 )
        {
            if (fabs(deriv) < 10 )
            {
                deriv = deriv * 0.8;
            }
            else
            {
                deriv = deriv * 0.9;
            }
        }
        //if(deriv
        //roll.deriv = -gyro;//注意是否跟自己的参数方向相反，不然会加剧振荡
        
        //deriv = -AngleSpeed[0];
        /*
        if (fabs(pregyro - deriv) > 20)
        {
            deriv = deriv * 0.5 + pregyro * 0.5;
        }
        */
        output = (kp * error) + (ki * integ) + (kd * deriv);
        
        
        prevError = error;//更新前一次偏差
        pregyro = deriv;
        if (output >  0.16)
        {
            output = 0.16;
        }
        if (output <  -0.16)
        {
            output = -0.16;
        }
        Pid_Roll = output;
        //output = output * 0.9 + lastoutput * 0.1;
        if (fabs(error) < 0.3 )
        {
            output = lastoutput * 0.5;
        }
        lastoutput = output;
        
        DutyCycle[0] = Default_Acc  - output;
        DutyCycle[1] = Default_Acc  - output;
        //DutyCycle[0] = Default_Acc;
        
        //DutyCycle[1] = Default_Acc;
        DutyCycle[2] = Default_Acc  + output;
        DutyCycle[3] = Default_Acc  + output;
        //DutyCycle[2] = Default_Acc;
        //DutyCycle[3] = Default_Acc;
        
        PWMOut(PinNumber1,DutyCycle[0]);
        PWMOut(PinNumber2,DutyCycle[1]);
        PWMOut(PinNumber3,DutyCycle[2]);
        PWMOut(PinNumber4,DutyCycle[3]);
        
        }
    }
}