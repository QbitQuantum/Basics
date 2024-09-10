/**
 * Returns the current system time in milliseconds. The value is only useful
 * to measure the elapsed time between subsequent calls of the function. The
 * absolute time value depends on the system.
 *
 * @return The system time in milliseconds.
 */
UINT64 dlp_time()
{
  time_t nTime;
  time(&nTime);
  nTime*=1000;

  {
    #if defined __GNUC__ || defined __TMS
      nTime += (time_t)(clock()/(time_t)((FLOAT64)CLOCKS_PER_SEC/1000.));
    #else
      MMTIME rNow; timeGetSystemTime(&rNow,sizeof(MMTIME));
      nTime += (time_t)rNow.u.ms%1000;
    #endif
  }

  return (UINT64)nTime;
}