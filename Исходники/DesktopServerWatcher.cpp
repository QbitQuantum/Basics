void DesktopServerWatcher::doXPTrick()
{
  m_log->info(_T("Trying to do WindowsXP trick to start process on separate session"));

  try {
    WinStaLibrary winSta;

    WCHAR password[1];
    memset(password, 0, sizeof(password));

    if (winSta.WinStationConnectW(NULL, 0, WTS::getActiveConsoleSessionId(m_log),
      password, 0) == FALSE) {
      throw SystemException(_T("Failed to call WinStationConnectW"));
    }

    // Get path to tvnserver binary.
    StringStorage pathToBinary;
    Environment::getCurrentModulePath(&pathToBinary);

     // Start current console process that will lock workstation (not using Xp Trick).
    CurrentConsoleProcess lockWorkstation(m_log, pathToBinary.getString(),
      _T("-lockworkstation"));
    lockWorkstation.start();
    lockWorkstation.waitForExit();

     // Check exit code (exit code is GetLastError() value in case of system error,
     // LockWorkstation() in child process failed, or 0 if workstation is locked).
    DWORD exitCode = lockWorkstation.getExitCode();

    if (exitCode != 0) {
      throw SystemException(exitCode);
    }
  } catch (SystemException &ex) {
    m_log->error(ex.getMessage());
    throw;
  }
}