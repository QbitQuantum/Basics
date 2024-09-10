float CCPUInfo::getCPUFrequency()
{
  // Get CPU frequency, scaled to MHz.
#if defined(TARGET_DARWIN)
  long long hz = 0;
  size_t len = sizeof(hz);
  if (sysctlbyname("hw.cpufrequency", &hz, &len, NULL, 0) == -1)
    return 0.f;
  return hz / 1000000.0;
#elif defined TARGET_WINDOWS
  if (m_cpuFreqCounter && PdhCollectQueryData(m_cpuQueryFreq) == ERROR_SUCCESS)
  {
    PDH_RAW_COUNTER cnt;
    DWORD cntType;
    if (PdhGetRawCounterValue(m_cpuFreqCounter, &cntType, &cnt) == ERROR_SUCCESS &&
        (cnt.CStatus == PDH_CSTATUS_VALID_DATA || cnt.CStatus == PDH_CSTATUS_NEW_DATA))
    {
      return float(cnt.FirstValue);
    }
  }
  
  if (!m_cores.empty())
    return float(m_cores.begin()->second.m_fSpeed);
  else
    return 0.f;
#elif defined(TARGET_FREEBSD)
  int hz = 0;
  size_t len = sizeof(hz);
  if (sysctlbyname("dev.cpu.0.freq", &hz, &len, NULL, 0) != 0)
    hz = 0;
  return (float)hz;
#else
  int value = 0;
  if (m_fCPUFreq && !m_cpuInfoForFreq)
  {
    rewind(m_fCPUFreq);
    fflush(m_fCPUFreq);
    fscanf(m_fCPUFreq, "%d", &value);
    value /= 1000.0;
  }
  if (m_fCPUFreq && m_cpuInfoForFreq)
  {
    rewind(m_fCPUFreq);
    fflush(m_fCPUFreq);
    float mhz, avg=0.0;
    int n, cpus=0;
    while(EOF!=(n=fscanf(m_fCPUFreq," MHz : %f ", &mhz)))
    {
      if (n>0) {
        cpus++;
        avg += mhz;
      }
      fscanf(m_fCPUFreq,"%*s");
    }

    if (cpus > 0)
      value = avg/cpus;
  }
  return value;
#endif
}