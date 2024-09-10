void
ForwardToWindow(HWND wnd) {
  // For WinCE, we're stuck with providing our own argv[0] for the remote
  // command-line.
  WCHAR wPath[MAX_PATH] = L"dummy ";
  WCHAR *wCmd = ::GetCommandLineW();
  WCHAR wCwd[MAX_PATH];
  _wgetcwd(wCwd, MAX_PATH);

  // Construct a narrow UTF8 buffer <path> <commandline>\0<workingdir>\0
  size_t len = wcslen(wPath) + wcslen(wCmd) + wcslen(wCwd) + 2;
  WCHAR *wMsg = (WCHAR *)malloc(len * sizeof(*wMsg));
  wcscpy(wMsg, wPath);
  wcscpy(wMsg + wcslen(wPath), wCmd);                // The command line
  wcscpy(wMsg + wcslen(wPath) + wcslen(wCmd) + 1, wCwd); // Working dir

  // Then convert to UTF-8, assuming worst-case explosion of characters
  char *msg = (char *)malloc(len * 4);
  WideCharToMultiByte(CP_UTF8, 0, wMsg, len, msg, len * 4, NULL, NULL);

  // We used to set dwData to zero, when we didn't send the working dir.
  // Now we're using it as a version number.
  COPYDATASTRUCT cds = { 1, len, (void *)msg };

  // Bring the already running Mozilla process to the foreground.
  // nsWindow will restore the window (if minimized) and raise it.
  // for activating the existing window on wince we need "| 0x01"
  // see http://msdn.microsoft.com/en-us/library/ms940024.aspx for details
  ::SetForegroundWindow((HWND)(((ULONG) wnd) | 0x01));
  ::SendMessage(wnd, WM_COPYDATA, 0, (LPARAM)&cds);
  free(wMsg);
  free(msg);
}