struct tm *
ACE_OS::localtime_r (const time_t *t, struct tm *res)
{
  ACE_OS_TRACE ("ACE_OS::localtime_r");
#if defined (ACE_HAS_REENTRANT_FUNCTIONS)
# if defined (DIGITAL_UNIX)
  ACE_OSCALL_RETURN (::_Plocaltime_r (t, res), struct tm *, 0);
# else
  ACE_OSCALL_RETURN (::localtime_r (t, res), struct tm *, 0);
# endif /* DIGITAL_UNIX */
#elif defined (ACE_HAS_TR24731_2005_CRT)
  ACE_SECURECRTCALL (localtime_s (res, t), struct tm *, 0, res);
  return res;
#elif !defined (ACE_HAS_WINCE)
  ACE_OS_GUARD

  ACE_UNUSED_ARG (res);
  struct tm * res_ptr = 0;
  ACE_OSCALL (::localtime (t), struct tm *, 0, res_ptr);
  if (res_ptr == 0)
    return 0;
  else
    {
      *res = *res_ptr;
      return res;
    }
#elif defined (ACE_HAS_WINCE)
  // This is really stupid, converting FILETIME to timeval back and
  // forth.  It assumes FILETIME and DWORDLONG are the same structure
  // internally.

  TIME_ZONE_INFORMATION pTz;

  const unsigned short int __mon_yday[2][13] =
  {
    /* Normal years.  */
    { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    /* Leap years.  */
    { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
  };

  ULARGE_INTEGER _100ns;
  ::GetTimeZoneInformation (&pTz);

  _100ns.QuadPart = (DWORDLONG) *t * 10000 * 1000 + ACE_Time_Value::FILETIME_to_timval_skew;
  FILETIME file_time;
  file_time.dwLowDateTime = _100ns.LowPart;
  file_time.dwHighDateTime = _100ns.HighPart;

  FILETIME localtime;
  SYSTEMTIME systime;
  FileTimeToLocalFileTime (&file_time, &localtime);
  FileTimeToSystemTime (&localtime, &systime);

  res->tm_hour = systime.wHour;

  if(pTz.DaylightBias!=0)
    res->tm_isdst = 1;
  else
    res->tm_isdst = 1;

   int iLeap;
   iLeap = (res->tm_year % 4 == 0 && (res->tm_year% 100 != 0 || res->tm_year % 400 == 0));
   // based on leap select which group to use

   res->tm_mday = systime.wDay;
   res->tm_min = systime.wMinute;
   res->tm_mon = systime.wMonth - 1;
   res->tm_sec = systime.wSecond;
   res->tm_wday = systime.wDayOfWeek;
   res->tm_yday = __mon_yday[iLeap][systime.wMonth] + systime.wDay;
   res->tm_year = systime.wYear;// this the correct year but bias the value to start at the 1900
   res->tm_year = res->tm_year - 1900;

   return res;
#else
  // @@ Same as ACE_OS::localtime (), you need to implement it
  //    yourself.
  ACE_UNUSED_ARG (t);
  ACE_UNUSED_ARG (res);
  ACE_NOTSUP_RETURN (0);
#endif /* ACE_HAS_REENTRANT_FUNCTIONS */
}