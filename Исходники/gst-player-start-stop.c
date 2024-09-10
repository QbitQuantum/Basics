static BOOL 
SafeTerminateProcess(HANDLE hProcess, UINT uExitCode) 
{
  DWORD dwTID, dwCode, dwErr = 0;
  HANDLE hProcessDup = INVALID_HANDLE_VALUE;
  HANDLE hRT = NULL;
  HINSTANCE hKernel = GetModuleHandle("Kernel32");
  BOOL bSuccess = FALSE;

  BOOL bDup = DuplicateHandle(GetCurrentProcess(), hProcess, GetCurrentProcess(), &hProcessDup, PROCESS_ALL_ACCESS, FALSE, 0);

  if (GetExitCodeProcess((bDup) ? hProcessDup : hProcess, &dwCode) && (dwCode == STILL_ACTIVE)) {
    FARPROC pfnExitProc;
    pfnExitProc = GetProcAddress(hKernel, "ExitProcess");
    hRT = CreateRemoteThread((bDup) ? hProcessDup : hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pfnExitProc, (PVOID)uExitCode, 0, &dwTID);
    if (hRT == NULL)
      dwErr = GetLastError();
  } else {
    dwErr = ERROR_PROCESS_ABORTED;
  }

  if (hRT) {
    WaitForSingleObject((bDup) ? hProcessDup : hProcess, INFINITE);
    CloseHandle(hRT);
    bSuccess = TRUE;
  }

  if (bDup)
    CloseHandle(hProcessDup);

  if (!bSuccess)
    SetLastError(dwErr);

  return bSuccess;
}