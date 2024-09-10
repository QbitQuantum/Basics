Bool
TimeUtil_UTCTimeToSystemTime(const __time64_t utcTime,   // IN
                             SYSTEMTIME *systemTime)     // OUT
{
   int atmYear;
   int atmMonth;

   struct tm *atm;

   /*
    * _localtime64 support years up through 3000.  At least it says
    * so.  I'm getting garbage only after reaching year 4408.
    */

   if (utcTime < 0 || utcTime > (60LL * 60 * 24 * 365 * (3000 - 1970))) {
      return FALSE;
   }

   atm = _localtime64(&utcTime);
   if (atm == NULL) {
      return FALSE;
   }

   atmYear = atm->tm_year + 1900;
   atmMonth = atm->tm_mon + 1;

   /*
    * Windows's SYSTEMTIME documentation says that these are limits...
    * Main reason for this test is to cut out negative values _localtime64
    * likes to return for some inputs.
    */

   if (atmYear < 1601 || atmYear > 30827 ||
       atmMonth < 1 || atmMonth > 12 ||
       atm->tm_wday < 0 || atm->tm_wday > 6 ||
       atm->tm_mday < 1 || atm->tm_mday > 31 ||
       atm->tm_hour < 0 || atm->tm_hour > 23 ||
       atm->tm_min < 0 || atm->tm_min > 59 ||
       /* Allow leap second, just in case... */
       atm->tm_sec < 0 || atm->tm_sec > 60) {
      return FALSE;
   }

   systemTime->wYear         = (WORD) atmYear;
   systemTime->wMonth        = (WORD) atmMonth;
   systemTime->wDayOfWeek    = (WORD) atm->tm_wday;
   systemTime->wDay          = (WORD) atm->tm_mday;
   systemTime->wHour         = (WORD) atm->tm_hour;
   systemTime->wMinute       = (WORD) atm->tm_min;
   systemTime->wSecond       = (WORD) atm->tm_sec;
   systemTime->wMilliseconds = 0;

   return TRUE;
}