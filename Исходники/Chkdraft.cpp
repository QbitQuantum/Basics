bool Chkdraft::CreateSubWindows()
{
    HWND hWnd = getHandle();
    if ( hWnd != NULL )
    {
        DragAcceptFiles(hWnd, TRUE);
        int statusWidths[] = { 130, 205, 350, 450, 600, -1 };

        return mainMenu.FindThis(hWnd) &&
            mainToolbar.CreateThis(hWnd, IDR_MAIN_TOOLBAR) &&
            statusBar.CreateThis(sizeof(statusWidths) / sizeof(int), statusWidths, 0,
                WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, hWnd, (HMENU)IDR_MAIN_STATUS) &&
            mainPlot.CreateThis(hWnd, IDR_MAIN_PLOT) &&
            BecomeMDIFrame(maps, GetSubMenu(GetMenu(hWnd), 6), ID_MDI_FIRSTCHILD,
                WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
                0, 0, 0, 0, (HMENU)IDR_MAIN_MDI);
    }
    else
        return false;
}