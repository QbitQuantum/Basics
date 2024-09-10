int ControlApplication::checkServicePasswords(bool isRunAsRequested)
{
  // FIXME: code duplication.
  if (IsUserAnAdmin() == FALSE) {
    // If admin rights already requested and application still don't have them,
    // then show error message and exit.
    if (isRunAsRequested) {
      MessageBox(0,
        StringTable::getString(IDS_ADMIN_RIGHTS_NEEDED),
        StringTable::getString(IDS_MBC_TVNCONTROL),
        MB_OK | MB_ICONERROR);
      return 1;
    }
    // Path to tvnserver binary.
    StringStorage pathToBinary;
    // Command line for child process.
    StringStorage childCommandLine;

    // Get path to tvnserver binary.
    Environment::getCurrentModulePath(&pathToBinary);
    // Set -dontelevate flag to tvncontrol know that admin rights already requested.
    childCommandLine.format(_T("%s -dontelevate"), m_commandLine.getString());

    // Start child.
    try {
      Shell::runAsAdmin(pathToBinary.getString(), childCommandLine.getString());
      return 0;
    } catch (SystemException &sysEx) {
      if (sysEx.getErrorCode() != ERROR_CANCELLED) {
        MessageBox(0,
          sysEx.getMessage(),
          StringTable::getString(IDS_MBC_TVNCONTROL),
          MB_OK | MB_ICONERROR);
      }
      return 1;
    } // try / catch.
    return 0;
  }
  checkServicePasswords();
  return 0;
}