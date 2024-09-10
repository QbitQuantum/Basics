void time_to_tfdt64(__time64_t t, struct tf_datetime *dt)
{
    int y, m, d, k, mjd;
    struct tm *tm = _localtime64(&t);

    y = tm->tm_year;
    m = tm->tm_mon + 1;
    d = tm->tm_mday;

    if((m == 1) || (m == 2))
    {
        k = 1;
    }
    else
    {
        k = 0;
    }

    mjd = 14956 + d +
        ((int) ((y - k) * 365.25)) + ((int) ((m + 1 + k * 12) * 30.6001));
    put_u16(&dt->mjd, (__u16) mjd);
    dt->hour = (__u8) tm->tm_hour;
    dt->minute = (__u8) tm->tm_min;
    dt->second = (__u8) tm->tm_sec;
}