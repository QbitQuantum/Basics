static BOOL VariantTimeToSystemTimeWithMsec(const double ft, SYSTEMTIME* st)
{
    BOOL rc = FALSE;

    double halfsecond = MSFT_FLOAT_1000MILLISECONDS / 2.0; // a half of 1000 msec

    if ( VariantTimeToSystemTime(ft - halfsecond, st) != FALSE )
    {
        double fraction = ft - (unsigned long)ft; // extracts the fraction part

        double hours;
        hours = fraction = (fraction - (int)fraction) * 24;
        double minutes;
        minutes = (hours - (int)hours) * 60;
        double seconds;
        seconds = (minutes - (int)minutes) * 60;
        double milliseconds;
        milliseconds = (seconds - (int)seconds) * 1000;
        milliseconds = milliseconds + 0.5; // rounding off millisecond to the nearest millisecond

        if ( milliseconds < 1.0 || milliseconds > 999.0 ) //Fractional calculations may yield in results like
            milliseconds = 0; // 0.00001 or 999.9999 which should actually be zero (slightly above or below limits are actually zero)

        if ( milliseconds )
        {
            st->wMilliseconds = (WORD) milliseconds;
            rc = TRUE;
        }
        else
        {
            rc = VariantTimeToSystemTime(ft, st); //if there is 0 milliseconds, then we don't have the problem
        }
    }

    return rc;
}