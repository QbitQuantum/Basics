void NaClTimeInternalInit(struct NaClTimeState *ntsp) {
  TIMECAPS    tc;
  SYSTEMTIME  st;
  FILETIME    ft;
  LARGE_INTEGER qpc_freq;

  /*
   * Maximize timer/Sleep resolution.
   */
  timeGetDevCaps(&tc, sizeof tc);

  if (ntsp->allow_low_resolution) {
    /* Set resolution to max so we don't over-promise. */
    ntsp->wPeriodMin = tc.wPeriodMax;
  } else {
    ntsp->wPeriodMin = tc.wPeriodMin;
    timeBeginPeriod(ntsp->wPeriodMin);
    NaClLog(4, "NaClTimeInternalInit: timeBeginPeriod(%u)\n", ntsp->wPeriodMin);
  }
  ntsp->time_resolution_ns = ntsp->wPeriodMin * NACL_NANOS_PER_MILLI;

  /*
   * Compute Unix epoch start; calibrate high resolution clock.
   */
  st.wYear = 1970;
  st.wMonth = 1;
  st.wDay = 1;
  st.wHour = 0;
  st.wMinute = 0;
  st.wSecond = 0;
  st.wMilliseconds = 0;
  SystemTimeToFileTime(&st, &ft);
  ntsp->epoch_start_ms = NaClFileTimeToMs(&ft);
  NaClLog(4, "Unix epoch start is  %"NACL_PRIu64"ms in Windows epoch time\n",
          ntsp->epoch_start_ms);

  NaClMutexCtor(&ntsp->mu);

  /*
   * We don't actually grab the lock, since the module initializer
   * should be called before going threaded.
   */
  ntsp->can_use_qpc = 0;
  if (!ntsp->allow_low_resolution) {
    ntsp->can_use_qpc = QueryPerformanceFrequency(&qpc_freq);
    /*
     * On Athlon X2 CPUs (e.g. model 15) QueryPerformanceCounter is
     * unreliable.  Fallback to low-res clock.
     */
    if (strstr(CPU_GetBrandString(), "AuthenticAMD") && (CPU_GetFamily() == 15))
        ntsp->can_use_qpc = 0;

    NaClLog(4,
            "CPU_GetBrandString->[%s] ntsp->can_use_qpc=%d\n",
            CPU_GetBrandString(),
            ntsp->can_use_qpc);

    if (ntsp->can_use_qpc) {
      ntsp->qpc_frequency = qpc_freq.QuadPart;
      NaClLog(4, "qpc_frequency = %"NACL_PRId64" (counts/s)\n",
              ntsp->qpc_frequency);
      if (!NaClCalibrateWindowsClockQpc(ntsp))
        ntsp->can_use_qpc = 0;
    }
    if (!ntsp->can_use_qpc)
      NaClCalibrateWindowsClockMu(ntsp);
  }
}