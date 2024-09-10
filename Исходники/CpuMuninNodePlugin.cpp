void CpuMuninNodePlugin::CalculateCpuLoad()
{
  if (NtQuerySystemInformation != NULL && GetSystemTimes != NULL) {
    LONG status;
    SYSTEM_TIME_INFORMATION SysTimeInfo;
    SYSTEM_BASIC_INFORMATION SysBaseInfo;

    // get number of processors in the system
    status = NtQuerySystemInformation(SystemBasicInformation, &SysBaseInfo, sizeof(SysBaseInfo), NULL);
    if (status != NO_ERROR) {
      printf("Querying SystemBasicInformation failed: 0x%x\n", status);
      return;
    }

    // get new system time
    status = NtQuerySystemInformation(SystemTimeInformation, &SysTimeInfo, sizeof(SysTimeInfo), NULL);
    if (status!=NO_ERROR) {
      printf("Querying SystemTimeInformation failed: 0x%x\n", status);
      return;
    }

    // get new CPU times
    // http://www.codeproject.com/Articles/9113/Get-CPU-Usage-with-GetSystemTimes
    FILETIME ftIdleTime;
    FILETIME ftKernelTime;
    FILETIME ftUserTime;
    BOOL result = GetSystemTimes((LPFILETIME)&ftIdleTime, (LPFILETIME)&ftKernelTime, (LPFILETIME)&ftUserTime);
    if (result == FALSE) {
      printf("GetSystemTimes failed\n");
      return;
    }
    unsigned long long systemTime = FileTimeToInt64(ftKernelTime) + FileTimeToInt64(ftUserTime);
    unsigned long long idleTime = FileTimeToInt64(ftIdleTime);

    // if it's a first call - skip it
    if (liOldIdleTime != 0)
    {
      // CurrentValue = NewValue - OldValue
      __int64 diffIdleTime = idleTime - liOldIdleTime;
      __int64 diffSystemTime = systemTime - liOldSystemTime;

      dbCpuTimePercent = (1.0f - ((diffSystemTime > 0) ? ((float)diffIdleTime) / diffSystemTime : 0)) * 100;
    }

    // store new times
    liOldIdleTime = idleTime;
    liOldSystemTime = systemTime;
  }
  else {
    printf("NtQuerySystemInformation or GetSystemTimes functions not available\n");
  }
}