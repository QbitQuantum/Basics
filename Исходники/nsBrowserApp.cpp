static void Output(const char *fmt, ... )
{
  va_list ap;
  va_start(ap, fmt);

#ifndef XP_WIN
  vfprintf(stderr, fmt, ap);
#ifdef XP_OS2
  char msg[2048];
  vsnprintf(msg, sizeof(msg), fmt, ap);
  HAB hab = WinInitialize(0);
  WinCreateMsgQueue(hab, 0);
  WinMessageBox(HWND_DESKTOP, 0, msg, "Firefox", 0,
                MB_OK | MB_ERROR | MB_MOVEABLE);
#endif
#else
  char msg[2048];
  vsnprintf_s(msg, _countof(msg), _TRUNCATE, fmt, ap);

  wchar_t wide_msg[2048];
  MultiByteToWideChar(CP_UTF8,
                      0,
                      msg,
                      -1,
                      wide_msg,
                      _countof(wide_msg));
#if MOZ_WINCONSOLE
  fwprintf_s(stderr, wide_msg);
#else
  MessageBoxW(NULL, wide_msg, L"Firefox", MB_OK
                                        | MB_ICONERROR
                                        | MB_SETFOREGROUND);
#endif
#endif

  va_end(ap);
}