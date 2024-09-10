bool CWin32PowerStateWorker::PowerManagement(PowerState State)
{
  static bool gotShutdownPrivileges = false;
  if (!gotShutdownPrivileges)
  {
    HANDLE hToken;
    // Get a token for this process.
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
      // Get the LUID for the shutdown privilege.
      TOKEN_PRIVILEGES tkp = {};
      if (LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
      {
        tkp.PrivilegeCount = 1;  // one privilege to set
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        // Get the shutdown privilege for this process.
        if (AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0))
          gotShutdownPrivileges = true;
      }
      CloseHandle(hToken);
    }

    if (!gotShutdownPrivileges)
      return false;
  }

  switch (State)
  {
  case POWERSTATE_HIBERNATE:
    CLog::Log(LOGINFO, "Asking Windows to hibernate...");
    return SetSuspendState(true, true, false) == TRUE;
  case POWERSTATE_SUSPEND:
    CLog::Log(LOGINFO, "Asking Windows to suspend...");
    return SetSuspendState(false, true, false) == TRUE;
  case POWERSTATE_SHUTDOWN:
    CLog::Log(LOGINFO, "Shutdown Windows...");
    if (g_sysinfo.IsWindowsVersionAtLeast(CSysInfo::WindowsVersionWin8))
      return InitiateShutdownW(NULL, NULL, 0, SHUTDOWN_HYBRID | SHUTDOWN_INSTALL_UPDATES | SHUTDOWN_POWEROFF,
                               SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED) == ERROR_SUCCESS;
    return InitiateShutdownW(NULL, NULL, 0, SHUTDOWN_INSTALL_UPDATES | SHUTDOWN_POWEROFF,
                             SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED) == ERROR_SUCCESS;
  case POWERSTATE_REBOOT:
    CLog::Log(LOGINFO, "Rebooting Windows...");
    if (g_sysinfo.IsWindowsVersionAtLeast(CSysInfo::WindowsVersionWin8))
      return InitiateShutdownW(NULL, NULL, 0, SHUTDOWN_INSTALL_UPDATES | SHUTDOWN_RESTART,
                               SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED) == ERROR_SUCCESS;
    return InitiateShutdownW(NULL, NULL, 0, SHUTDOWN_INSTALL_UPDATES | SHUTDOWN_RESTART,
                             SHTDN_REASON_MAJOR_APPLICATION | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED) == ERROR_SUCCESS;
  default:
    CLog::Log(LOGERROR, "Unknown PowerState called.");
    return false;
  }
}