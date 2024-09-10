void InstallSignalHandlers(const char *ProgramName)
{
  gFPEPreviousFilter = SetUnhandledExceptionFilter(FpeHandler);
}