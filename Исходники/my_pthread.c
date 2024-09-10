struct tm* gmtime_r(const time_t* clock, struct tm* res)
{
    gmtime_s(res, clock);
    return res;
}