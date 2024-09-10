void MPLSensor::calcOrientationSensor(float *R, float *values)
{
    float tmp;

    //Azimuth
    if ((R[7] > 0.7071067f) || ((R[8] < 0) && (fabs(R[7]) > fabs(R[6])))) {
        values[0] = (float) atan2f(-R[3], R[0]);
    } else {
        values[0] = (float) atan2f(R[1], R[4]);
    }
    values[0] *= 57.295779513082320876798154814105f;
    if (values[0] < 0) {
        values[0] += 360.0f;
    }
    //Pitch
    tmp = R[7];
    if (tmp > 1.0f)
        tmp = 1.0f;
    if (tmp < -1.0f)
        tmp = -1.0f;
    values[1] = -asinf(tmp) * 57.295779513082320876798154814105f;
    if (R[8] < 0) {
        values[1] = 180.0f - values[1];
    }
    if (values[1] > 180.0f) {
        values[1] -= 360.0f;
    }
    //Roll
    if ((R[7] > 0.7071067f)) {
        values[2] = (float) atan2f(R[6], R[7]);
    } else {
        values[2] = (float) atan2f(R[6], R[8]);
    }

    values[2] *= 57.295779513082320876798154814105f;
    if (values[2] > 90.0f) {
        values[2] = 180.0f - values[2];
    }
    if (values[2] < -90.0f) {
        values[2] = -180.0f - values[2];
    }
}