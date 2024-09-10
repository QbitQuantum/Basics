static void addDebugLine(_In_z_ _Printf_format_string_ TCHAR const * const format, ...) {
  static Semaphore gate;
  static TCHAR *mode = _T("w");
  gate.wait();
  FILE *f = FOPEN(_T("c:\\temp\\semaphore.log"),mode);
  mode = _T("a");
  va_list argptr;
  va_start(argptr,format);
  _vftprintf(f, format, argptr);
  va_end(argptr);
  fclose(f);
  gate.signal();
}