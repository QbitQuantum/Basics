int8_t Magnetometer::readGauss(double * x, double * y, double * z)
{
    int16_t x_r, y_r, z_r;

    int8_t ret = readRaw(&x_r, &y_r, &z_r);

    // pass the error
    if (ret != 0)
        return ret;

    // convert reading to gauss
    int16_t divisor;
    switch (gain_)
    {
        case HMC5833L_GAIN_1370:
            divisor = 1370;
            break;
        case HMC5833L_GAIN_1090:
            divisor = 1090;
            break;
        case HMC5833L_GAIN_820:
            divisor = 820;
            break;
        case HMC5833L_GAIN_660:
            divisor = 660;
            break;
        case HMC5833L_GAIN_440:
            divisor = 440;
            break;
        case HMC5833L_GAIN_390:
            divisor = 390;
            break;
        case HMC5833L_GAIN_330:
            divisor = 330;
            break;
        case HMC5833L_GAIN_230:
            divisor = 230;
            break;

        default:
            return HMC5833L_ERROR_GAINOUTOFRANGE;
    }

    *x = (double)x_r / divisor;
    *y = (double)y_r / divisor;
    *z = (double)z_r / divisor;

    return 0;
}