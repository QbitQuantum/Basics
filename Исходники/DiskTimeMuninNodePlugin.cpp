int DiskTimeMuninNodePlugin::GetValues(char *buffer, int len)
{
  PDH_STATUS status;
  PDH_FMT_COUNTERVALUE diskTimeValue;
  int printCount;

  status = PdhCollectQueryData(m_PerfQuery);
  if (status != ERROR_SUCCESS)
    return -1;
  
  for (size_t i = 0; i < m_DiskTimeCounters.size(); i++) {
    // Get the formatted counter value    
    status = PdhGetFormattedCounterValue(m_DiskTimeCounters[i], PDH_FMT_DOUBLE, NULL, &diskTimeValue);
    if (status != ERROR_SUCCESS)
      return -1;
    printCount = _snprintf(buffer, len, "disktime_%i_.value %.2f\n", i, diskTimeValue.doubleValue);
    len -= printCount;
    buffer += printCount;
  }
  strncat(buffer, ".\n", len);
  return 0;
}