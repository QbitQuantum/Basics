PDH_STATUS PerformanceCounter::NextValue(DWORD format,
                                         PDH_FMT_COUNTERVALUE* value) {
  auto status = PdhCollectQueryData(query_);
  if (status != ERROR_SUCCESS)
    return status;

  return PdhGetFormattedCounterValue(counter_, format | PDH_FMT_NOCAP100,
                                     nullptr, value);
}