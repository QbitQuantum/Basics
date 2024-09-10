bool my_utime (const TCHAR *name, struct mytimeval *tv)
{
        int tolocal;
        int days, mins, ticks;
        struct mytimeval tv2;

        if (!tv) {
                struct timeb time;
                ftime (&time);
                tv2.tv_sec = time.time;
                tv2.tv_usec = time.millitm * 1000;
                tolocal = 0;
        } else {
                tv2.tv_sec = tv->tv_sec;
                tv2.tv_usec = tv->tv_usec;
                tolocal = 1;
        }
        timeval_to_amiga (&tv2, &days, &mins, &ticks);
        if (setfiletime (name, days, mins, ticks, tolocal))
                return true;

        return false;
}