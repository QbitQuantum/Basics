time_t
timegm (struct tm *tm)
{
#ifdef HAVE_W32_SYSTEM
  /* This one is thread safe.  */
  SYSTEMTIME st;
  FILETIME ft;
  unsigned long long cnsecs;

  st.wYear   = tm->tm_year + 1900;
  st.wMonth  = tm->tm_mon  + 1;
  st.wDay    = tm->tm_mday;
  st.wHour   = tm->tm_hour;
  st.wMinute = tm->tm_min;
  st.wSecond = tm->tm_sec;
  st.wMilliseconds = 0; /* Not available.  */
  st.wDayOfWeek = 0;    /* Ignored.  */

  /* System time is UTC thus the conversion is pretty easy.  */
  if (!SystemTimeToFileTime (&st, &ft))
    {
      jnlib_set_errno (EINVAL);
      return (time_t)(-1);
    }

  cnsecs = (((unsigned long long)ft.dwHighDateTime << 32)
            | ft.dwLowDateTime);
  cnsecs -= 116444736000000000ULL; /* The filetime epoch is 1601-01-01.  */
  return (time_t)(cnsecs / 10000000ULL);

#else /* (Non thread safe implementation!) */

  time_t answer;
  char *zone;

  zone=getenv("TZ");
  putenv("TZ=UTC");
  tzset();
  answer=mktime(tm);
  if(zone)
    {
      static char *old_zone;

      if (!old_zone)
        {
          old_zone = malloc(3+strlen(zone)+1);
          if (old_zone)
            {
              strcpy(old_zone,"TZ=");
              strcat(old_zone,zone);
            }
	}
      if (old_zone)
        putenv (old_zone);
    }
  else
    gnupg_unsetenv("TZ");

  tzset();
  return answer;
#endif
}