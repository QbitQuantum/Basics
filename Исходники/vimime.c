EXPORT LONG
SetIME(LPCSTR pwszKLID) {
  HMODULE hDllUser32;

  hDllUser32 = LoadLibrary("user32");
  if (hDllUser32)
  {
    HKL (WINAPI *pfnLoadKeyboardLayout)(LPCSTR, UINT);

    pfnLoadKeyboardLayout = (HKL (WINAPI *)(LPCSTR, UINT)) GetProcAddress(hDllUser32, "LoadKeyboardLayoutW");

    if (pfnLoadKeyboardLayout)
    {
      HWND hTop = NULL;
      DWORD dwThreadID;

      dwThreadID = GetCurrentThreadId();
      EnumThreadWindows(dwThreadID, FindWindowProc, (LPARAM)&hTop);

      if (hTop)
      {
        HKL kLayout = NULL;
        SetWindowLong(hTop, GWL_EXSTYLE, GetWindowLong(hTop, GWL_EXSTYLE) | WS_EX_LAYERED);
        kLayout = pfnLoadKeyboardLayout(pwszKLID, 1);
        SendMessage(hTop, WM_INPUTLANGCHANGEREQUEST, SC_RESTORE, (LPARAM)&kLayout);
      }
    }
    FreeLibrary(hDllUser32);
  }
  return GetLastError();
}