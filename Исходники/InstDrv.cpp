bool _stdcall RemoveWinIoDriver()
{
  SC_HANDLE hSCManager;
  SC_HANDLE hService;
  bool bResult;

  StopWinIoDriver();

  hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

  if (hSCManager)
  {
    hService = OpenServiceA(hSCManager, "WinRing0_1_2_0", SERVICE_ALL_ACCESS);

    CloseServiceHandle(hSCManager);

    if (hService)
    {
      bResult = DeleteService(hService);
      
      CloseServiceHandle(hService);
    }
    else
      return false;
  }
  else
    return false;

  return bResult;
}