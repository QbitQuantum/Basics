static HWND
CreateApplicationWindow(VOID)
{
    HWND hWnd;

    PMIXER_WINDOW MixerWindow = HeapAlloc(hAppHeap,
                                          HEAP_ZERO_MEMORY,
                                          sizeof(MIXER_WINDOW));
    if (MixerWindow == NULL)
    {
        return NULL;
    }

    if (mixerGetNumDevs() > 0)
    {
        hWnd = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT,
                              SZ_APP_CLASS,
                              lpAppTitle,
                              WS_DLGFRAME | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 
                              0, 0, 300, 315,
                              NULL,
                              LoadMenu(hAppInstance,
                                       MAKEINTRESOURCE(IDM_MAINMENU)),
                              hAppInstance,
                              MixerWindow);
    }
    else
    {
        LPTSTR lpErrMessage;

        /*
         * no mixer devices are available!
         */

        hWnd = NULL;
        if (AllocAndLoadString(&lpErrMessage,
                               hAppInstance,
                               IDS_NOMIXERDEVICES))
        {
            MessageBox(NULL,
                       lpErrMessage,
                       lpAppTitle,
                       MB_ICONINFORMATION);
            LocalFree(lpErrMessage);
        }
    }

    if (hWnd == NULL)
    {
        HeapFree(hAppHeap,
                 0,
                 MixerWindow);
    }

    return hWnd;
}