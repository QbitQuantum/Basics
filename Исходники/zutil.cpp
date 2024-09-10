int gettimeofday(struct timeval *tv, struct timezone *tz)
{
   FILETIME ft;
   unsigned __int64 tmpres = 0;
   static int tzflag = 0;

   if (NULL != tv)
   {
      GetSystemTimeAsFileTime(&ft);

      tmpres |= ft.dwHighDateTime;
      tmpres <<= 32;
      tmpres |= ft.dwLowDateTime;

      ULARGE_INTEGER test = { ft.dwLowDateTime, ft.dwHighDateTime };

      /*converting file time to unix epoch*/
      tmpres -= DELTA_EPOCH_IN_MICROSECS;
      tmpres /= 10;  /*convert into microseconds*/
      tv->tv_sec = (long)(tmpres / 1000000UL);
      tv->tv_usec = (long)(tmpres % 1000000UL);
   }

   if (NULL != tz)
   {
      if (!tzflag)
      {
         _tzset();
         tzflag++;
      }

      long tztmp = 0;
      _get_timezone(&tztmp);
      tz->tz_minuteswest = tztmp / 60;
      _get_daylight(&tz->tz_dsttime);
   }

   return 0;
}