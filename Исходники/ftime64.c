_CRTIMP errno_t __cdecl _ftime64_s (
        struct __timeb64 *tp
        )
{
        FT nt_time;
        __time64_t t;
        TIME_ZONE_INFORMATION tzinfo;
        DWORD tzstate;
        long timezone = 0;

        _VALIDATE_RETURN_ERRCODE( ( tp != NULL ), EINVAL )

        __tzset();

        _ERRCHECK(_get_timezone(&timezone));
        tp->timezone = (short)(timezone / 60);

        GetSystemTimeAsFileTime( &(nt_time.ft_struct) );

        /*
         * Obtain the current DST status. Note the status is cached and only
         * updated once per minute, if necessary.
         */
        if ( (t = (__time64_t)(nt_time.ft_scalar / 600000000i64))
             != elapsed_minutes_cache )
        {
            if ( (tzstate = GetTimeZoneInformation( &tzinfo )) != 0xFFFFFFFF )
            {
                /*
                 * Must be very careful in determining whether or not DST is
                 * really in effect.
                 */
                if ( (tzstate == TIME_ZONE_ID_DAYLIGHT) &&
                     (tzinfo.DaylightDate.wMonth != 0) &&
                     (tzinfo.DaylightBias != 0) )
                    dstflag_cache = DAYLIGHT_TIME;
                else
                    /*
                     * When in doubt, assume standard time
                     */
                    dstflag_cache = STANDARD_TIME;
            }
            else
                dstflag_cache = UNKNOWN_TIME;

            elapsed_minutes_cache = t;
        }

        tp->dstflag = (short)dstflag_cache;

        tp->millitm = (unsigned short)((nt_time.ft_scalar / 10000i64) %
                      1000i64);

        tp->time = (__time64_t)((nt_time.ft_scalar - EPOCH_BIAS) / 10000000i64);

        return 0;
}