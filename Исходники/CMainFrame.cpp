LRESULT CMainFrame::EnableDisableCloseItem(bool bActivate)
{
    HMENU hMenu = ::GetMenu(m_hwnd);

    UINT EnableFlag;
    if (bActivate)
    {
        EnableFlag = MF_ENABLED;
    }
    else
    {
        EnableFlag = MF_GRAYED;
    }

    EnableMenuItem(hMenu, 1, MF_BYPOSITION | EnableFlag);

    HMENU hFileMenu = ::GetSubMenu(hMenu, 0);

    ::EnableMenuItem(hFileMenu, IDM_FILE_CLOSE, MF_BYCOMMAND | EnableFlag);
    ::EnableMenuItem(hFileMenu, IDM_WINDOW_CLOSE_ALL, MF_BYCOMMAND | EnableFlag);

    DrawMenuBar();
    return 0;
}