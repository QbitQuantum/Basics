pid_t getppid(void)
{
 PROCESS_BASIC_INFORMATION pbiInfo;
 NTSTATUS                  nErrCode;

 nErrCode = NtQueryInformationProcess
 (
  NtCurrentProcess(),
  ProcessBasicInformation,
  &pbiInfo,
  sizeof(pbiInfo),
  NULL
 );

 if(!NT_SUCCESS(nErrCode))
 {
  errno = __status_to_errno(nErrCode);
  return (0);
 }

 return (pbiInfo.InheritedFromUniqueProcessId);
}