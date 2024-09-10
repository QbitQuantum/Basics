bool Gyro_init(void)
{  
    Wire.begin();
    mpu.initialize();

    if (mpu.testConnection() == false) {
      return false;
    }
    devStatus = mpu.dmpInitialize();
    
    if (devStatus == 0) {
        mpu.setXGyroOffset(X_GYRO_OFFSET);
        mpu.setYGyroOffset(Y_GYRO_OFFSET);
        mpu.setZGyroOffset(Z_GYRO_OFFSET);
        mpu.setXAccelOffset(X_ACCEL_OFFSET);
        mpu.setYAccelOffset(Y_ACCEL_OFFSET);
        mpu.setZAccelOffset(Z_ACCEL_OFFSET);
    
        mpu.setDMPEnabled(true);
        dmpReady = true;

        attachInterrupt(0, dmp_data_ready, RISING);

        mpuIntStatus = mpu.getIntStatus();
        packetSize = mpu.dmpGetFIFOPacketSize();
        
        return true;
    }
    else {
        return false;
    }
}