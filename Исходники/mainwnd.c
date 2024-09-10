static BOOL
InitMainWnd(PMAIN_WND_INFO Info)
{
    if (!pCreateToolbar(Info))
    {
        DisplayString(_T("error creating toolbar"));
        return FALSE;
    }

    if (!CreateListView(Info))
    {
        DisplayString(_T("error creating list view"));
        return FALSE;
    }

    if (!CreateStatusBar(Info))
        DisplayString(_T("error creating status bar"));

    /* Create Popup Menu */
    Info->hShortcutMenu = LoadMenu(hInstance,
                                   MAKEINTRESOURCE(IDR_POPUP));

    Info->bIsUserAnAdmin = IsUserAnAdmin();
    if (Info->bIsUserAnAdmin)
    {
        HMENU hMainMenu = GetMenu(Info->hMainWnd);

        SendMessage(Info->hTool,
                    TB_SETSTATE,
                    ID_CREATE,
                    (LPARAM)MAKELONG(TBSTATE_ENABLED, 0));
        if (hMainMenu)
        {
            EnableMenuItem(hMainMenu,
                           ID_CREATE,
                           MF_ENABLED);
        }
        EnableMenuItem(GetSubMenu(Info->hShortcutMenu, 0),
                       ID_CREATE,
                       MF_ENABLED);
    }

    return TRUE;
}