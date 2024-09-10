tm* gmtime_r(const time_t *clock, tm *result)
{
    return gmtime_s(result, clock) == 0 ? result : 0;
}