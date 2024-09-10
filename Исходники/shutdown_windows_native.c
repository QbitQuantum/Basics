int system_shutdown() {
  grantPrivileges();
  if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))
    return -1;

  return 0;
}