void PrintCommand(const wchar_t *path, const wchar_t * cmd) {
  if (path && *path && cmd && *cmd) {
    FILE *f = CreateLogFile(path, L"at, ccs=UNICODE");
    if (f) {
      MyPrintFunc(f, L"\r\nCommand > %s\r\n", cmd);
      ::fclose(f);
    }
    else
      wprintf_s(L"PrintCommand failed to PrintCommand cmd (%s) to log file (%s)\r\n", cmd, path);
  }
}