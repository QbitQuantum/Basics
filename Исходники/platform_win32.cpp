int gettimeofday(struct timeval *_tv, struct timezone *_tz)
{
    FILETIME        ft;
    LARGE_INTEGER   li;
    __int64         t;
    static int      tzflag;

    if (_tv)
    {
        GetSystemTimeAsFileTime(&ft);
        li.LowPart  = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        t  = li.QuadPart;       /* In 100-nanosecond intervals */
        t -= EPOCHFILETIME;     /* Offset to the Epoch time */
        t /= 10;                /* In microseconds */
        _tv->tv_sec  = (long)(t / 1000000);
        _tv->tv_usec = (long)(t % 1000000);
    }

    if (_tz) 
    {
        if (!tzflag) 
        {
            _tzset();
            tzflag++;
        }

         _get_timezone(&_tz->tz_minuteswest);
         _tz->tz_minuteswest /= 60;
         _get_daylight(&_tz->tz_dsttime);
    }

    return 0;
}