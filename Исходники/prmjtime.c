JSInt64
PRMJ_Now(void)
{
#ifdef XP_OS2
    JSInt64 s, us, ms2us, s2us;
    struct timeb b;
#endif
#ifdef XP_WIN
    JSInt64 s, us,
    win2un = JSLL_INIT(0x19DB1DE, 0xD53E8000),
    ten = JSLL_INIT(0, 10);
    FILETIME time, midnight;
#endif
#if defined(XP_UNIX) || defined(XP_BEOS)
    struct timeval tv;
    JSInt64 s, us, s2us;
#endif /* XP_UNIX */

#ifdef XP_OS2
    ftime(&b);
    JSLL_UI2L(ms2us, PRMJ_USEC_PER_MSEC);
    JSLL_UI2L(s2us, PRMJ_USEC_PER_SEC);
    JSLL_UI2L(s, b.time);
    JSLL_UI2L(us, b.millitm);
    JSLL_MUL(us, us, ms2us);
    JSLL_MUL(s, s, s2us);
    JSLL_ADD(s, s, us);
    return s;
#endif
#ifdef XP_WIN
    /* The windows epoch is around 1600. The unix epoch is around 1970.
       win2un is the difference (in windows time units which are 10 times
       more precise than the JS time unit) */
    GetSystemTimeAsFileTime(&time);
    /* Win9x gets confused at midnight
       http://support.microsoft.com/default.aspx?scid=KB;en-us;q224423
       So if the low part (precision <8mins) is 0 then we get the time
       again. */
    if (!time.dwLowDateTime) {
        GetSystemTimeAsFileTime(&midnight);
        time.dwHighDateTime = midnight.dwHighDateTime;
    }
    JSLL_UI2L(s, time.dwHighDateTime);
    JSLL_UI2L(us, time.dwLowDateTime);
    JSLL_SHL(s, s, 32);
    JSLL_ADD(s, s, us);
    JSLL_SUB(s, s, win2un);
    JSLL_DIV(s, s, ten);
    return s;
#endif

#if defined(XP_UNIX) || defined(XP_BEOS)
#ifdef _SVID_GETTOD   /* Defined only on Solaris, see Solaris <sys/types.h> */
    gettimeofday(&tv);
#else
    gettimeofday(&tv, 0);
#endif /* _SVID_GETTOD */
    JSLL_UI2L(s2us, PRMJ_USEC_PER_SEC);
    JSLL_UI2L(s, tv.tv_sec);
    JSLL_UI2L(us, tv.tv_usec);
    JSLL_MUL(s, s, s2us);
    JSLL_ADD(s, s, us);
    return s;
#endif /* XP_UNIX */
}