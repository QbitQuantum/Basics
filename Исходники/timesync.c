int
settimeofday(
    struct timeval *tv,
    struct timezone *tz
    )
{
    SYSTEMTIME systime;
    struct tm *newtime;

    newtime = gmtime((time_t *)&(tv->tv_sec));
    systime.wYear = 1900+newtime->tm_year;
    systime.wMonth = 1+newtime->tm_mon;
    systime.wDay = newtime->tm_mday;
    systime.wHour = newtime->tm_hour;
    systime.wMinute = newtime->tm_min;
    systime.wSecond = newtime->tm_sec;
    systime.wMilliseconds = 0;
    return SetSystemTime(&systime);
}