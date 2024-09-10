/* Initialize the IMU and I2C communication */
void IMUInit(){

    /* Intialize communication I2C */
    Wire.begin();
    
    /* Initialize IMU. Default resolution is set to minimum, no offsets */
    IMU.initialize();

    /* Get first values for accel and gyro */
    IMU.getMotion6(&accel[0], &accel[1], &accel[2], &gyro[0], &gyro[1], &gyro[2]);
}