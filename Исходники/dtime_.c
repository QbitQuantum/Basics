double
dtime_ (real tarray[2])
{
#if defined (_WIN32)
  static int win32_platform = -1;

  if (win32_platform == -1)
    {
      OSVERSIONINFO osv;
      osv.dwOSVersionInfoSize = sizeof (osv);
      GetVersionEx (&osv);
      win32_platform = osv.dwPlatformId;
    }

  /* We need to use this hack on non-NT platforms, where the first call
     returns 0.0 and subsequent ones return the correct value. */
  if (win32_platform != VER_PLATFORM_WIN32_NT)
    {
      static unsigned long long clock_freq;
      static unsigned long long old_count;
      unsigned long long count;
      double delta;
      LARGE_INTEGER counter_val;

      if (clock_freq == 0)
	{
	  LARGE_INTEGER freq;
	  if (!QueryPerformanceFrequency (&freq))
	    {
	      errno = ENOSYS;
	      return 0.0;
	    }
	  else
	    {
	      clock_freq = ((unsigned long long) freq.HighPart << 32)
		+ ((unsigned) freq.LowPart);
	    }
	}

      if (!QueryPerformanceCounter (&counter_val))
	return -1.0;

      count = ((unsigned long long) counter_val.HighPart << 32)
	+ (unsigned) counter_val.LowPart;
      delta = ((double) (count - old_count)) / clock_freq;
      tarray[0] = (float) delta;
      tarray[1] = 0.0;
      old_count = count;
    }
  else
    {
      static unsigned long long old_utime, old_stime;
      unsigned long long utime, stime;
      FILETIME creation_time, exit_time, kernel_time, user_time;

      GetProcessTimes (GetCurrentProcess (), &creation_time, &exit_time,
		       &kernel_time, &user_time);
      utime = ((unsigned long long) user_time.dwHighDateTime << 32)
	+ (unsigned) user_time.dwLowDateTime;
      stime = ((unsigned long long) kernel_time.dwHighDateTime << 32)
	+ (unsigned) kernel_time.dwLowDateTime;

      tarray[0] = (utime - old_utime) / 1.0e7;
      tarray[1] = (stime - old_stime) / 1.0e7;
      old_utime = utime;
      old_stime = stime;
    }
  return tarray[0] + tarray[1];

#elif defined (HAVE_GETRUSAGE) || defined (HAVE_TIMES)
  /* The getrusage version is only the default for convenience. */
#ifdef HAVE_GETRUSAGE
  float utime, stime;
  static float old_utime = 0.0, old_stime = 0.0;
  struct rusage rbuff;

  if (getrusage (RUSAGE_SELF, &rbuff) != 0)
    abort ();
  utime = (float) (rbuff.ru_utime).tv_sec +
    (float) (rbuff.ru_utime).tv_usec / 1000000.0;
  tarray[0] = utime - (float) old_utime;
  stime = (float) (rbuff.ru_stime).tv_sec +
    (float) (rbuff.ru_stime).tv_usec / 1000000.0;
  tarray[1] = stime - old_stime;
#else /* HAVE_GETRUSAGE */
  /* For dtime, etime we store the clock tick parameter (clk_tck) the
     first time either of them is invoked rather than each time.  This
     approach probably speeds up each invocation by avoiding a system
     call each time, but means that the overhead of the first call is
     different to all others. */
  static long clk_tck = 0;
  time_t utime, stime;
  static time_t old_utime = 0, old_stime = 0;
  struct tms buffer;

/* NeXTStep seems to define _SC_CLK_TCK but not to have sysconf;
   fixme: does using _POSIX_VERSION help? */
#  if defined _SC_CLK_TCK && defined _POSIX_VERSION
  if (!clk_tck)
    clk_tck = sysconf (_SC_CLK_TCK);
#  elif defined CLOCKS_PER_SECOND
  if (!clk_tck)
    clk_tck = CLOCKS_PER_SECOND;
#  elif defined CLK_TCK
  if (!clk_tck)
    clk_tck = CLK_TCK;
#  elif defined HZ
  if (!clk_tck)
    clk_tck = HZ;
#  elif defined HAVE_GETRUSAGE
#  else
#error Dont know clock tick length
#  endif
  if (times (&buffer) == (clock_t) - 1)
    return -1.0;
  utime = buffer.tms_utime;
  stime = buffer.tms_stime;
  tarray[0] = ((float) (utime - old_utime)) / (float) clk_tck;
  tarray[1] = ((float) (stime - old_stime)) / (float) clk_tck;
#endif /* HAVE_GETRUSAGE */
  old_utime = utime;
  old_stime = stime;
  return (tarray[0] + tarray[1]);
#else /* ! HAVE_GETRUSAGE && ! HAVE_TIMES */
  errno = ENOSYS;
  return 0.0;
#endif /* ! HAVE_GETRUSAGE && ! HAVE_TIMES */
}