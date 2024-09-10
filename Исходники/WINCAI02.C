int PASCAL
WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR CmdLine, int nCmdShow)
{
    MSG       msg;                      /* MSG structure to pass to windows proc */
    WNDCLASS  wndclass;
    char      *AppName;                 /* Name for the window */

    cbErrHandling (PRINTALL, STOPALL);  /* Set library's error handling */

    CmdLine = NULL;                     /* Not used */
    AppName = "WINCDEMO";               /* The name of this application */
    if(!hPrevInstance)
        {
        wndclass.style      = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc= MainMessageHandler;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance  = hInstance;
        wndclass.hIcon      = LoadIcon (hInstance, AppName);
        wndclass.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);
        wndclass.lpszMenuName   = AppName;
        wndclass.lpszClassName  = AppName;
        RegisterClass (&wndclass);
        }

    /* create application's Main window                                    */
    hWndMain = CreateWindow (AppName,                  /* Window class name          */
                             "AInScan Foreground",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,           /* Use default X, Y            */
                             CW_USEDEFAULT,           /* Use default X, Y            */
                             GetSystemMetrics(SM_CXSIZE) * 12,   /* x - fit text      */
                             GetSystemMetrics(SM_CYSIZE) * 20,  /* y - fit text      */
                             NULL,                    /* Parent window's handle      */
                             NULL,                    /* Default to Class Menu       */
                             hInstance,               /* Instance of window          */
                             NULL);                   /* Create struct for WM_CREATE */


    if (hWndMain == NULL)
        {
        MessageBox(NULL, "Could not create window in WinMain", NULL, MB_ICONEXCLAMATION);
        return (1);
        }

    ShowWindow(hWndMain, nCmdShow);     /* Display main window      */
    UpdateWindow(hWndMain);

    /* Start a 500ms timer to update display */
//    if(!SetTimer(hWndMain, TIMER_NUM, 500, NULL))
//        {
//        MessageBox(NULL, "Error starting Windows timer", NULL, MB_OK |
//                   MB_ICONEXCLAMATION);
 //       return (1);
 //       }                          
        
    while(GetMessage(&msg, NULL, 0, 0)) /* Main message loop */
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }

    UnregisterClass (AppName, hInstance);
    return (msg.wParam);
} 