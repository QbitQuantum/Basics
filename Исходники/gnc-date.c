long int
gnc_timezone (const struct tm *tm)
{
    g_return_val_if_fail (tm != NULL, 0);

#ifdef HAVE_STRUCT_TM_GMTOFF
    /* tm_gmtoff is seconds *east* of UTC and is
     * already adjusted for daylight savings time. */
    return -(tm->tm_gmtoff);
#else
    {
        long tz_seconds;
        /* timezone is seconds *west* of UTC and is
         * not adjusted for daylight savings time.
         * In Spring, we spring forward, wheee! */
# if COMPILER(MSVC)
        _get_timezone(&tz_seconds);
# else
        tz_seconds = timezone;
# endif
        return (long int)(tz_seconds - (tm->tm_isdst > 0 ? 3600 : 0));
    }
#endif
}