int gettimeofday(struct timeval* tv, struct timezone* tz)
{
   // define tzinit flag (whether or not the timezone has been initialized)
   static bool tzinit = false;

   // NOTE: use FileTimeToSystemTime to convert a FILETIME to a SYSTEMTIME
   // that has years, months, days, hours, seconds, milliseconds, etc
   if(tv != NULL)
   {
//      // get the system time as a file time (a UTC time object)
//      FILETIME ft;
//      GetSystemTimeAsFileTime(&ft);
//
//      // use a large integer to combine the time into a 64-bit long
//      LARGE_INTEGER li;
//      li.LowPart = ft.dwLowDateTime;
//      li.HighPart = ft.dwHighDateTime;
//
//      // get the 64-bit long in
//      // the time is in 100-nanosecond intervals (1000 nanoseconds in
//      // a microsecond, so this is really just microseconds / 10)
//      __int64 time = li.QuadPart;

      // get the system time as a file time (a UTC time object),
      // interpretable as a 64-bit integer
      union now
      {
         FILETIME ft;
         __int64 time;
      };

      GetSystemTimeAsFileTime(&now.ft);

      // eliminate time between 01/01/1601 (UTC) and 01/01/1970 (epoch)
      now.time -= EPOCH_UTC_TENTHMICROSECS_DELTA;

      // get time in microseconds
      now.time /= UINT64_C(10);

      // store time in seconds and microseconds (1 microsecond = 1000000 sec)
      tv->tv_sec  = (uint64_t)(now.time / UINT64_C(1000000));
      tv->tv_usec = (uint64_t)(now.time % UINT64_C(1000000));
   }

   // populate timezone
   if(tz != NULL)
   {
      if(!tzinit)
      {
         // initialize timezone
         _tzset();
         tzinit = true;
      }

      // set timezone information:

      // get the number of minutes west (tz_dsttime is supposedly obsolete)
      tz->tz_minuteswest = gGetTimeZoneMinutesWest();
      tz->tz_dsttime = _daylight;
   }

   // success
   return 0;
}