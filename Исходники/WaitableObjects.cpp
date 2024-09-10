BOOL NktIsMultiProcessor()
{
  if (nProcessorsCount == 0)
  {
    SYSTEM_BASIC_INFORMATION sBasicInfo;
    LONG nTemp;
    NTSTATUS nNtStatus;

    nNtStatus = NktRtlGetNativeSystemInformation(SystemBasicInformation, &sBasicInfo, sizeof(sBasicInfo), NULL);
    if (nNtStatus == STATUS_NOT_IMPLEMENTED)
      nNtStatus = NktNtQuerySystemInformation(SystemBasicInformation, &sBasicInfo, sizeof(sBasicInfo), NULL);
    nTemp = 1;
    if (NT_SUCCESS(nNtStatus) && sBasicInfo.NumberOfProcessors > 1)
      nTemp = (LONG)(sBasicInfo.NumberOfProcessors);
    _InterlockedExchange(&nProcessorsCount, nTemp);
  }
  return (nProcessorsCount > 1) ? TRUE : FALSE;
}