HWND
otIdleServiceWin::GetHWND()
{
  HINSTANCE hInst;
  WNDCLASS wc;
  
  if (myHWND)
    return myHWND;
  
  hInst = GetModuleHandle(NULL);
  
  memset(&wc, 0, sizeof(wc));
  wc.style = CS_NOCLOSE | CS_GLOBALCLASS;
  wc.lpfnWndProc = WinProc;
  wc.hInstance = hInst;
  wc.lpszClassName = TEXT("otIdleHandlerClass");
  myWinClass = RegisterClass(&wc);

  if (!myWinClass)
    return NULL;

  myHWND = CreateWindow((LPCSTR)myWinClass, TEXT(""),
                        WS_MINIMIZE, 0, 0, 0, 0,
                        GetDesktopWindow(), NULL, hInst, NULL);
  
  if (!myHWND)
    UnregisterClass((LPCSTR)myWinClass, hInst);

  WTSRegisterSessionNotification(myHWND, NOTIFY_FOR_THIS_SESSION);
  
  return myHWND;
}