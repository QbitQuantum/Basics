static HWND
GetVimWindow() {
  if (hTopWindow) {
    return hTopWindow;
  }

  HMODULE hDllKernel32 = LoadLibrary("kernel32");
  if (hDllKernel32) {
    HWND (WINAPI *pfnGetConsoleWindow)();
    pfnGetConsoleWindow
      = (HWND (WINAPI *)())
          GetProcAddress(hDllKernel32, "GetConsoleWindow");
    if (pfnGetConsoleWindow && (hTopWindow = (HWND) pfnGetConsoleWindow())) {
      ShowWindow(hTopWindow, SW_SHOW);
      return hTopWindow;
    }
  }
  DWORD dwThreadID = GetCurrentThreadId();
  EnumThreadWindows(dwThreadID, FindWindowProc, (LPARAM)&hTopWindow);
  return hTopWindow;
}