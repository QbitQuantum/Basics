HWND GetMainWindowHandle(DWORD processId) {
  if (!HeXModule()/* && !DesktopWidget()*/) {
    return FindWindow(GetMainWindowClassName(processId), NULL);
  }

  /*if (DesktopWidget()) {
    HWND desktop = FindWindow(L"Progman", NULL);
    desktop = GetWindow(desktop, GW_CHILD);
    HWND main_window = FindWindowEx(desktop, NULL,
        GetMainWindowClassName(processId), NULL);
    return main_window;
  }*/

  seekedHandle = NULL;  
  HWND topWindow = GetTopWindow(NULL);
  while (topWindow){
    DWORD pid = 0;
    DWORD threadId = GetWindowThreadProcessId(topWindow, &pid);
    if (threadId != 0 && pid == processId) {
      EnumChildWindows(topWindow, EnumChildBrowserProc, (LPARAM)pid);
      if (seekedHandle) {
        return GetAncestor(seekedHandle, GA_ROOT);
      }
    }
    topWindow = GetNextWindow(topWindow, GW_HWNDNEXT);
  }
  return NULL;
}