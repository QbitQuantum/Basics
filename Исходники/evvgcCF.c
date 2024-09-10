void getOrientation(float *smoothAcc, float *orient, float *accData, float *gyroData, float dt)
{
    float accAngle[3];
    float gyroRate[3];

    if (evvgcCFinitialized == false)
    {
        initOrientation();

        evvgcCFinitialized = true;
    }

    //-------------------------------------------

    if (evvgcCFinitialized == true)
    {
        accAngle[ROLL ] = atan2f(-accData[YAXIS], -accData[ZAXIS]);
        accAngle[PITCH] = atan2f(accData[XAXIS], -accData[ZAXIS]);

        smoothAcc[ROLL]  = ((smoothAcc[ROLL ] * 99.0f) + accAngle[ROLL ]) / 100.0f;
        smoothAcc[PITCH] = ((smoothAcc[PITCH] * 99.0f) + accAngle[PITCH]) / 100.0f;

        gyroRate[PITCH] =  gyroData[PITCH];
        orient[PITCH]   = (orient[PITCH] + gyroRate[PITCH] * dt) + 0.0002f * (smoothAcc[PITCH] - orient[PITCH]);

        gyroRate[ROLL]  =  gyroData[ROLL] * cosf(fabsf(orient[PITCH])) + gyroData[YAW] * sinf(orient[PITCH]);
        orient[ROLL]    = (orient[ROLL] + gyroRate[ROLL] * dt) + 0.0002f * (smoothAcc[ROLL] - orient[ROLL]);

        gyroRate[YAW]   =  gyroData[YAW] * cosf(fabsf(orient[PITCH])) - gyroData[ROLL] * sinf(orient[PITCH]);
        orient[YAW]     = (orient[YAW] + gyroRate[YAW] * dt);
    }
}