void Gyro_getADC(void)
{
    // range: +/- 8192; +/- 2000 deg/sec
    gyro.read(gyroADC);
    gyro.align(gyroADC);

    GYRO_Common();
}