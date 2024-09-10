CmcDateTime CmcDateTime::GetTimeNow ()
  {
static bool bFirstTime = true;

static CmcDateTime last_date;
static LARGE_INTEGER last_time;
static LONGLONG iCounterFrequency = 0;

  if (bFirstTime)
    {
    bFirstTime = false;
    LARGE_INTEGER large_int_frequency;
    if (QueryPerformanceFrequency (&large_int_frequency))
      {
      iCounterFrequency = large_int_frequency.QuadPart;
      QueryPerformanceCounter (&last_time);
      }
    }

  double secs = 0;
  LARGE_INTEGER time_now;

  if (iCounterFrequency)
    {
    QueryPerformanceCounter (&time_now);

    LONGLONG offset = time_now.QuadPart - last_time.QuadPart;
    secs = (double) offset / (double) iCounterFrequency;
//    TRACE ("Secs = %10.4f\n", secs);
    }
  else
    {
    time_now.QuadPart = 0;
    time_now.QuadPart = 0;
    }


  // if no high-performance counter, just query the time each time
  if (iCounterFrequency == 0 || 
      last_date.m_dt == 0 ||
      secs > RESYNC_EVERY_SECS)
    {
    SYSTEMTIME systime;
    GetLocalTime (&systime);
 	  last_date = CmcDateTime(systime.wYear, systime.wMonth,
		                  systime.wDay, systime.wHour, systime.wMinute,
		                  (double) systime.wSecond + ( (double) systime.wMilliseconds / 1000.0) );
    secs = 0;
    last_time = time_now;
    }

  CmcDateTime this_date (last_date);

  this_date.m_dt += secs / SECS_IN_DAY;

  // ---- debugging
#if 0
    {
    SYSTEMTIME systime;
    GetSystemTime (&systime);
 	  CmcDateTime test = CmcDateTime(systime.wYear, systime.wMonth,
		                  systime.wDay, systime.wHour, systime.wMinute,
		                  (double) systime.wSecond + ( (double) systime.wMilliseconds / 1000.0) );
    double diff = test.m_dt - this_date.m_dt;

    TRACE1 ("Time difference = %10.8f\n", diff);
    }

#endif
  // --- end debugging

  return this_date; 

  }