static int
_map(long double in_value, long double in_min, long double in_max, long double out_min, long double out_max, long double out_step, double *out_value)
{
    long double result;

    result = (in_value - in_min) * (out_max - out_min) /
             (in_max - in_min) + out_min;

    errno = 0;
    result -= fmodl((result - out_min), out_step);
    if (errno > 0)
        return -errno;

    *out_value = result;

    return 0;
}