local int FileTime2utime(FILETIME *pft, time_t *ut)
{
#ifndef NO_INT64
    ULLNG64 NTtime;

    NTtime = ((ULLNG64)pft->dwLowDateTime +
              ((ULLNG64)pft->dwHighDateTime << 32));

    /* underflow and overflow handling */
#ifdef CHECK_UTIME_SIGNED_UNSIGNED
    if ((time_t)0x80000000L < (time_t)0L)
    {
        if (NTtime < ((ULLNG64)UNIX_TIME_SMIN_LO +
                      ((ULLNG64)UNIX_TIME_SMIN_HI << 32))) {
            *ut = (time_t)LONG_MIN;
            return FALSE;
        }
        if (NTtime > ((ULLNG64)UNIX_TIME_SMAX_LO +
                      ((ULLNG64)UNIX_TIME_SMAX_HI << 32))) {
            *ut = (time_t)LONG_MAX;
            return FALSE;
        }
    }
    else
#endif /* CHECK_UTIME_SIGNED_UNSIGNED */
    {
        if (NTtime < ((ULLNG64)UNIX_TIME_ZERO_LO +
                      ((ULLNG64)UNIX_TIME_ZERO_HI << 32))) {
            *ut = (time_t)0;
            return FALSE;
        }
        if (NTtime > ((ULLNG64)UNIX_TIME_UMAX_LO +
                      ((ULLNG64)UNIX_TIME_UMAX_HI << 32))) {
            *ut = (time_t)ULONG_MAX;
            return FALSE;
        }
    }

    NTtime -= ((ULLNG64)UNIX_TIME_ZERO_LO +
               ((ULLNG64)UNIX_TIME_ZERO_HI << 32));
    *ut = (time_t)(NTtime / (unsigned long)NT_QUANTA_PER_UNIX);
    return TRUE;
#else /* NO_INT64 (64-bit integer arithmetics may not be supported) */
    /* nonzero if `y' is a leap year, else zero */
#   define leap(y) (((y)%4 == 0 && (y)%100 != 0) || (y)%400 == 0)
    /* number of leap years from 1970 to `y' (not including `y' itself) */
#   define nleap(y) (((y)-1969)/4 - ((y)-1901)/100 + ((y)-1601)/400)
    /* daycount at the end of month[m-1] */
    static ZCONST ush ydays[] =
      { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

    time_t days;
    SYSTEMTIME w32tm;

    /* underflow and overflow handling */
#ifdef CHECK_UTIME_SIGNED_UNSIGNED
    if ((time_t)0x80000000L < (time_t)0L)
    {
        if ((pft->dwHighDateTime < UNIX_TIME_SMIN_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_SMIN_HI) &&
             (pft->dwLowDateTime < UNIX_TIME_SMIN_LO))) {
            *ut = (time_t)LONG_MIN;
            return FALSE;
        if ((pft->dwHighDateTime > UNIX_TIME_SMAX_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_SMAX_HI) &&
             (pft->dwLowDateTime > UNIX_TIME_SMAX_LO))) {
            *ut = (time_t)LONG_MAX;
            return FALSE;
        }
    }
    else
#endif /* CHECK_UTIME_SIGNED_UNSIGNED */
    {
        if ((pft->dwHighDateTime < UNIX_TIME_ZERO_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_ZERO_HI) &&
             (pft->dwLowDateTime < UNIX_TIME_ZERO_LO))) {
            *ut = (time_t)0;
            return FALSE;
        }
        if ((pft->dwHighDateTime > UNIX_TIME_UMAX_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_UMAX_HI) &&
             (pft->dwLowDateTime > UNIX_TIME_UMAX_LO))) {
            *ut = (time_t)ULONG_MAX;
            return FALSE;
        }
    }

    FileTimeToSystemTime(pft, &w32tm);

    /* set `days' to the number of days into the year */
    days = w32tm.wDay - 1 + ydays[w32tm.wMonth-1] +
           (w32tm.wMonth > 2 && leap (w32tm.wYear));

    /* now set `days' to the number of days since 1 Jan 1970 */
    days += 365 * (time_t)(w32tm.wYear - 1970) +
            (time_t)(nleap(w32tm.wYear));

    *ut = (time_t)(86400L * days + 3600L * (time_t)w32tm.wHour +
                   (time_t)(60 * w32tm.wMinute + w32tm.wSecond));
    return TRUE;
#endif /* ?NO_INT64 */
} /* end function FileTime2utime() */
#endif /* USE_EF_UT_TIME || NT_TZBUG_WORKAROUND */


#if (defined(NT_TZBUG_WORKAROUND) && defined(W32_STAT_BANDAID))

local int VFatFileTime2utime(const FILETIME *pft, time_t *ut)
{
    FILETIME lft;
    SYSTEMTIME w32tm;
    struct tm ltm;

    FileTimeToLocalFileTime(pft, &lft);
    FileTimeToSystemTime(&lft, &w32tm);
    /* underflow and overflow handling */
    /* TODO: The range checks are not accurate, the actual limits may
     *       be off by one daylight-saving-time shift (typically 1 hour),
     *       depending on the current state of "is_dst".
     */
#ifdef CHECK_UTIME_SIGNED_UNSIGNED
    if ((time_t)0x80000000L < (time_t)0L)
    {
        if ((pft->dwHighDateTime < UNIX_TIME_SMIN_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_SMIN_HI) &&
             (pft->dwLowDateTime < UNIX_TIME_SMIN_LO))) {
            *ut = (time_t)LONG_MIN;
            return FALSE;
        if ((pft->dwHighDateTime > UNIX_TIME_SMAX_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_SMAX_HI) &&
             (pft->dwLowDateTime > UNIX_TIME_SMAX_LO))) {
            *ut = (time_t)LONG_MAX;
            return FALSE;
        }
    }
    else
#endif /* CHECK_UTIME_SIGNED_UNSIGNED */
    {
        if ((pft->dwHighDateTime < UNIX_TIME_ZERO_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_ZERO_HI) &&
             (pft->dwLowDateTime < UNIX_TIME_ZERO_LO))) {
            *ut = (time_t)0;
            return FALSE;
        }
        if ((pft->dwHighDateTime > UNIX_TIME_UMAX_HI) ||
            ((pft->dwHighDateTime == UNIX_TIME_UMAX_HI) &&
             (pft->dwLowDateTime > UNIX_TIME_UMAX_LO))) {
            *ut = (time_t)ULONG_MAX;
            return FALSE;
        }
    }
    ltm.tm_year = w32tm.wYear - 1900;
    ltm.tm_mon = w32tm.wMonth - 1;
    ltm.tm_mday = w32tm.wDay;
    ltm.tm_hour = w32tm.wHour;
    ltm.tm_min = w32tm.wMinute;
    ltm.tm_sec = w32tm.wSecond;
    ltm.tm_isdst = -1;  /* let mktime determine if DST is in effect */
    *ut = mktime(&ltm);

    /* a cheap error check: mktime returns "(time_t)-1L" on conversion errors.
     * Normally, we would have to apply a consistency check because "-1"
     * could also be a valid time. But, it is quite unlikely to read back odd
     * time numbers from file systems that store time stamps in DOS format.
     * (The only known exception is creation time on VFAT partitions.)
     */
    return (*ut != (time_t)-1L);

} /* end function VFatFileTime2utime() */
#endif /* NT_TZBUG_WORKAROUND && W32_STAT_BANDAID */


#if 0           /* Currently, this is not used at all */

long GetTheFileTime(char *name, iztimes *z_ut)
{
HANDLE h;
FILETIME Modft, Accft, Creft, lft;
WORD dh, dl;
#ifdef __RSXNT__        /* RSXNT/EMX C rtl uses OEM charset */
  char *ansi_name = (char *)alloca(strlen(name) + 1);

  OemToAnsi(name, ansi_name);
  name = ansi_name;
#endif

  h = CreateFile(name, FILE_READ_ATTRIBUTES, FILE_SHARE_READ,
                 NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
  if ( h != INVALID_HANDLE_VALUE ) {
    BOOL ftOK = GetFileTime(h, &Creft, &Accft, &Modft);
    CloseHandle(h);
#ifdef USE_EF_UT_TIME
    if (ftOK && (z_ut != NULL)) {
      FileTime2utime(&Modft, &(z_ut->mtime));
      if (Accft.dwLowDateTime != 0 || Accft.dwHighDateTime != 0)
          FileTime2utime(&Accft, &(z_ut->atime));
      else
          z_ut->atime = z_ut->mtime;
      if (Creft.dwLowDateTime != 0 || Creft.dwHighDateTime != 0)
          FileTime2utime(&Creft, &(z_ut->ctime));
      else
          z_ut->ctime = z_ut->mtime;
    }
#endif
    FileTimeToLocalFileTime(&ft, &lft);
    FileTimeToDosDateTime(&lft, &dh, &dl);
    return(dh<<16) | dl;
  }
  else
    return 0L;
}