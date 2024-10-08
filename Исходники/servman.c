int WINAPI
_tWinMain(HINSTANCE hThisInstance,
          HINSTANCE hPrevInstance,
          LPTSTR lpCmdLine,
          int nCmdShow)
{
    LPTSTR lpAppName;
    HWND hMainWnd;
    MSG Msg;
    int Ret = 1;
    INITCOMMONCONTROLSEX icex;
    
    switch (GetUserDefaultUILanguage())
  {
    case MAKELANGID(LANG_HEBREW, SUBLANG_DEFAULT):
      SetProcessDefaultLayout(LAYOUT_RTL);
      break;

    default:
      break;
  }
    
    hInstance = hThisInstance;
    ProcessHeap = GetProcessHeap();

    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_BAR_CLASSES | ICC_COOL_CLASSES;
    InitCommonControlsEx(&icex);

    if (!AllocAndLoadString(&lpAppName,
                            hInstance,
                            IDS_APPNAME))
    {
        return 1;
    }

    if (InitMainWindowImpl())
    {
        hMainWnd = CreateMainWindow(lpAppName,
                                    nCmdShow);
        if (hMainWnd != NULL)
        {
            /* pump the message queue */
            while( GetMessage( &Msg, NULL, 0, 0 ) )
            {
                //if ( !hProgDlg || !IsWindow(hProgDlg) || !IsDialogMessage(hProgDlg, &Msg) )
                //{
                    TranslateMessage(&Msg);
                    DispatchMessage(&Msg);
                //}
            }

            Ret = 0;
        }

        UninitMainWindowImpl();
    }

    LocalFree((HLOCAL)lpAppName);

    return Ret;
}