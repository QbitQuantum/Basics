//----------------------------------------------------------------------------
// Function: SystemInfo
//
// Description:
// Returns the resource information about the machine 
//
// Returns:
// EXIT_SUCCESS: On success
// EXIT_FAILURE: otherwise
int SystemInfo() 
{
  size_t vmemSize, vmemFree, memSize, memFree;
  PERFORMANCE_INFORMATION memInfo;
  SYSTEM_INFO sysInfo;
  FILETIME idleTimeFt, kernelTimeFt, userTimeFt;
  ULARGE_INTEGER idleTime, kernelTime, userTime;
  ULONGLONG cpuTimeMs;
  size_t size;
  LPBYTE pBuffer;
  PROCESSOR_POWER_INFORMATION const *ppi;
  ULONGLONG cpuFrequencyKhz;
  NTSTATUS status;

  ZeroMemory(&memInfo, sizeof(PERFORMANCE_INFORMATION));
  memInfo.cb = sizeof(PERFORMANCE_INFORMATION);
  if(!GetPerformanceInfo(&memInfo, sizeof(PERFORMANCE_INFORMATION)))
  {
    ReportErrorCode(L"GetPerformanceInfo", GetLastError());
    return EXIT_FAILURE;
  }
  vmemSize = memInfo.CommitLimit*memInfo.PageSize;
  vmemFree = vmemSize - memInfo.CommitTotal*memInfo.PageSize;
  memSize = memInfo.PhysicalTotal*memInfo.PageSize;
  memFree = memInfo.PhysicalAvailable*memInfo.PageSize;

  GetSystemInfo(&sysInfo);

  if(!GetSystemTimes(&idleTimeFt, &kernelTimeFt, &userTimeFt))
  {
    ReportErrorCode(L"GetSystemTimes", GetLastError());
    return EXIT_FAILURE;
  }
  idleTime.HighPart = idleTimeFt.dwHighDateTime;
  idleTime.LowPart = idleTimeFt.dwLowDateTime;
  kernelTime.HighPart = kernelTimeFt.dwHighDateTime;
  kernelTime.LowPart = kernelTimeFt.dwLowDateTime;
  userTime.HighPart = userTimeFt.dwHighDateTime;
  userTime.LowPart = userTimeFt.dwLowDateTime;

  cpuTimeMs = (kernelTime.QuadPart - idleTime.QuadPart + userTime.QuadPart)/10000;

  // allocate buffer to get info for each processor
  size = sysInfo.dwNumberOfProcessors * sizeof(PROCESSOR_POWER_INFORMATION);
  pBuffer = (BYTE*) LocalAlloc(LPTR, size);
  if(!pBuffer)
  {
    ReportErrorCode(L"LocalAlloc", GetLastError());
    return EXIT_FAILURE;
  }
  status = CallNtPowerInformation(ProcessorInformation, NULL, 0, pBuffer, (long)size);
  if(0 != status)
  {
    fwprintf_s(stderr, L"Error in CallNtPowerInformation. Err:%d\n", status);
    LocalFree(pBuffer);
    return EXIT_FAILURE;
  }
  ppi = (PROCESSOR_POWER_INFORMATION const *)pBuffer;
  cpuFrequencyKhz = ppi->MaxMhz*1000;
  LocalFree(pBuffer);

  fwprintf_s(stdout, L"%Iu,%Iu,%Iu,%Iu,%u,%I64u,%I64u\n", vmemSize, memSize,
    vmemFree, memFree, sysInfo.dwNumberOfProcessors, cpuFrequencyKhz, cpuTimeMs);

  return EXIT_SUCCESS;
}