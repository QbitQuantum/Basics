/**
 * Initialise monotonic seconds counter.
 */
void
MHD_monotonic_sec_counter_init (void)
{
#ifdef HAVE_CLOCK_GET_TIME
  mach_timespec_t cur_time;
#endif /* HAVE_CLOCK_GET_TIME */
  enum _MHD_mono_clock_source mono_clock_source = _MHD_CLOCK_NO_SOURCE;
#ifdef HAVE_CLOCK_GETTIME
  struct timespec ts;

  mono_clock_id = _MHD_UNWANTED_CLOCK;
#endif /* HAVE_CLOCK_GETTIME */
#ifdef HAVE_CLOCK_GET_TIME
  mono_clock_service = _MHD_INVALID_CLOCK_SERV;
#endif /* HAVE_CLOCK_GET_TIME */

  /* just a little syntactic trick to get the
     various following ifdef's to work out nicely */
  if (0)
    {
    }
  else
#ifdef HAVE_CLOCK_GETTIME
#ifdef CLOCK_MONOTONIC_COARSE
  /* Linux-specific fast value-getting clock */
  /* Can be affected by frequency adjustment and don't count time in suspend, */
  /* but preferred since it's fast */
  if (0 == clock_gettime (CLOCK_MONOTONIC_COARSE,
                          &ts))
    {
      mono_clock_id = CLOCK_MONOTONIC_COARSE;
      mono_clock_start = ts.tv_sec;
      mono_clock_source = _MHD_CLOCK_GETTIME;
    }
  else
#endif /* CLOCK_MONOTONIC_COARSE */
#ifdef CLOCK_MONOTONIC_FAST
  /* FreeBSD/DragonFly fast value-getting clock */
  /* Can be affected by frequency adjustment, but preferred since it's fast */
  if (0 == clock_gettime (CLOCK_MONOTONIC_FAST,
                          &ts))
    {
      mono_clock_id = CLOCK_MONOTONIC_FAST;
      mono_clock_start = ts.tv_sec;
      mono_clock_source = _MHD_CLOCK_GETTIME;
    }
  else
#endif /* CLOCK_MONOTONIC_COARSE */
#ifdef CLOCK_MONOTONIC_RAW
  /* Linux-specific clock */
  /* Not affected by frequency adjustment, but don't count time in suspend */
  if (0 == clock_gettime (CLOCK_MONOTONIC_RAW,
                          &ts))
    {
      mono_clock_id = CLOCK_MONOTONIC_RAW;
      mono_clock_start = ts.tv_sec;
      mono_clock_source = _MHD_CLOCK_GETTIME;
    }
  else
#endif /* CLOCK_MONOTONIC_RAW */
#ifdef CLOCK_BOOTTIME
  /* Linux-specific clock */
  /* Count time in suspend so it's real monotonic on Linux, */
  /* but can be slower value-getting than other clocks */
  if (0 == clock_gettime (CLOCK_BOOTTIME,
                          &ts))
    {
      mono_clock_id = CLOCK_BOOTTIME;
      mono_clock_start = ts.tv_sec;
      mono_clock_source = _MHD_CLOCK_GETTIME;
    }
  else
#endif /* CLOCK_BOOTTIME */
#ifdef CLOCK_MONOTONIC
  /* Monotonic clock */
  /* Widely supported, may be affected by frequency adjustment */
  /* On Linux it's not truly monotonic as it doesn't count time in suspend */
  if (0 == clock_gettime (CLOCK_MONOTONIC,
                          &ts))
    {
      mono_clock_id = CLOCK_MONOTONIC;
      mono_clock_start = ts.tv_sec;
      mono_clock_source = _MHD_CLOCK_GETTIME;
    }
  else
#endif /* CLOCK_BOOTTIME */
#endif /* HAVE_CLOCK_GETTIME */
#ifdef HAVE_CLOCK_GET_TIME
  /* Darwin-specific monotonic clock */
  /* Should be monotonic as clock_set_time function always unconditionally */
  /* failed on latest kernels */
  if ( (KERN_SUCCESS == host_get_clock_service (mach_host_self(),
                                                SYSTEM_CLOCK,
                                                &mono_clock_service)) &&
       (KERN_SUCCESS == clock_get_time (mono_clock_service,
                                        &cur_time)) )
    {
      mono_clock_start = cur_time.tv_sec;
      mono_clock_source = _MHD_CLOCK_GET_TIME;
    }
  else
#endif /* HAVE_CLOCK_GET_TIME */
#ifdef _WIN32
#if _WIN32_WINNT >= 0x0600
  /* W32 Vista or later specific monotonic clock */
  /* Available since Vista, ~15ms accuracy */
  if (1)
    {
      tick_start = GetTickCount64 ();
      mono_clock_source = _MHD_CLOCK_GETTICKCOUNT64;
    }
  else
#else  /* _WIN32_WINNT < 0x0600 */
  /* W32 specific monotonic clock */
  /* Available on Windows 2000 and later */
  if (1)
    {
      LARGE_INTEGER freq;
      LARGE_INTEGER perf_counter;

      QueryPerformanceFrequency (&freq); /* never fail on XP and later */
      QueryPerformanceCounter (&perf_counter); /* never fail on XP and later */
      perf_freq = freq.QuadPart;
      perf_start = perf_counter.QuadPart;
      mono_clock_source = _MHD_CLOCK_PERFCOUNTER;
    }
  else
#endif /* _WIN32_WINNT < 0x0600 */
#endif /* _WIN32 */
#ifdef HAVE_CLOCK_GETTIME
#ifdef CLOCK_HIGHRES
  /* Solaris-specific monotonic high-resolution clock */
  /* Not preferred due to be potentially resource-hungry */
  if (0 == clock_gettime (CLOCK_HIGHRES,
                          &ts))
    {
      mono_clock_id = CLOCK_HIGHRES;
      mono_clock_start = ts.tv_sec;
      mono_clock_source = _MHD_CLOCK_GETTIME;
    }
  else
#endif /* CLOCK_HIGHRES */
#endif /* HAVE_CLOCK_GETTIME */
#ifdef HAVE_GETHRTIME
  /* HP-UX and Solaris monotonic clock */
  /* Not preferred due to be potentially resource-hungry */
  if (1)
    {
      hrtime_start = gethrtime ();
      mono_clock_source = _MHD_CLOCK_GETHRTIME;
    }
  else
#endif /* HAVE_GETHRTIME */
    {
      /* no suitable clock source was found */
      mono_clock_source = _MHD_CLOCK_NO_SOURCE;
    }

#ifdef HAVE_CLOCK_GET_TIME
  if ( (_MHD_CLOCK_GET_TIME != mono_clock_source) &&
       (_MHD_INVALID_CLOCK_SERV != mono_clock_service) )
    {
      /* clock service was initialised but clock_get_time failed */
      mach_port_deallocate (mach_task_self(),
                            mono_clock_service);
      mono_clock_service = _MHD_INVALID_CLOCK_SERV;
    }
#else
  (void) mono_clock_source; /* avoid compiler warning */
#endif /* HAVE_CLOCK_GET_TIME */

  sys_clock_start = time (NULL);
}