static BOOL OnCreate(HWND hWnd)
{
    HMENU   hMenu;
    HMENU   hEditMenu;
    HMENU   hViewMenu;
    HMENU   hUpdateSpeedMenu;
    HMENU   hCPUHistoryMenu;
    int     nActivePage;
    int     nParts[3];
    RECT    rc;
    TCITEMW item;

    static WCHAR wszApplications[255];
    static WCHAR wszProcesses[255];
    static WCHAR wszPerformance[255];

    LoadStringW(hInst, IDS_APPLICATIONS, wszApplications, sizeof(wszApplications)/sizeof(WCHAR));
    LoadStringW(hInst, IDS_PROCESSES, wszProcesses, sizeof(wszProcesses)/sizeof(WCHAR));
    LoadStringW(hInst, IDS_PERFORMANCE, wszPerformance, sizeof(wszPerformance)/sizeof(WCHAR));

    SendMessageW(hMainWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadIconW(hInst, MAKEINTRESOURCEW(IDI_TASKMANAGER)));
    SendMessageW(hMainWnd, WM_SETICON, ICON_SMALL,
                 (LPARAM)LoadImageW(hInst, MAKEINTRESOURCEW(IDI_TASKMANAGER), IMAGE_ICON,
                                    GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON),
                                    LR_SHARED));

    /* Initialize the Windows Common Controls DLL */
    InitCommonControls();

    /* Get the minimum window sizes */
    GetWindowRect(hWnd, &rc);
    nMinimumWidth = (rc.right - rc.left);
    nMinimumHeight = (rc.bottom - rc.top);

    /* Create the status bar */
    hStatusWnd = CreateStatusWindowW(WS_VISIBLE|WS_CHILD|WS_CLIPSIBLINGS|SBT_NOBORDERS, NULL, hWnd, STATUS_WINDOW);
    if(!hStatusWnd)
        return FALSE;

    /* Create the status bar panes */
    nParts[0] = 100;
    nParts[1] = 210;
    nParts[2] = 400;
    SendMessageW(hStatusWnd, SB_SETPARTS, 3, (LPARAM)nParts);

    /* Create tab pages */
    hTabWnd = GetDlgItem(hWnd, IDC_TAB);
#if 1
    hApplicationPage = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_APPLICATION_PAGE), hWnd, ApplicationPageWndProc);
    hProcessPage = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_PROCESS_PAGE), hWnd, ProcessPageWndProc);
    hPerformancePage = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_PERFORMANCE_PAGE), hWnd, PerformancePageWndProc);
#else
    hApplicationPage = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_APPLICATION_PAGE), hTabWnd, ApplicationPageWndProc);
    hProcessPage = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_PROCESS_PAGE), hTabWnd, ProcessPageWndProc);
    hPerformancePage = CreateDialogW(hInst, MAKEINTRESOURCEW(IDD_PERFORMANCE_PAGE), hTabWnd, PerformancePageWndProc);
#endif

    /* Insert tabs */
    memset(&item, 0, sizeof(TCITEMW));
    item.mask = TCIF_TEXT;
    item.pszText = wszApplications;
    SendMessageW(hTabWnd, TCM_INSERTITEMW, 0, (LPARAM)&item);
    memset(&item, 0, sizeof(TCITEMW));
    item.mask = TCIF_TEXT;
    item.pszText = wszProcesses;
    SendMessageW(hTabWnd, TCM_INSERTITEMW, 1, (LPARAM)&item);
    memset(&item, 0, sizeof(TCITEMW));
    item.mask = TCIF_TEXT;
    item.pszText = wszPerformance;
    SendMessageW(hTabWnd, TCM_INSERTITEMW, 2, (LPARAM)&item);

    /* Size everything correctly */
    GetClientRect(hWnd, &rc);
    nOldWidth = rc.right;
    nOldHeight = rc.bottom;
    /* nOldStartX = rc.left; */
    /*nOldStartY = rc.top;  */

#define PAGE_OFFSET_LEFT    17
#define PAGE_OFFSET_TOP     72
#define PAGE_OFFSET_WIDTH   (PAGE_OFFSET_LEFT*2)
#define PAGE_OFFSET_HEIGHT  (PAGE_OFFSET_TOP+32)

    if ((TaskManagerSettings.Left != 0) ||
        (TaskManagerSettings.Top != 0) ||
        (TaskManagerSettings.Right != 0) ||
        (TaskManagerSettings.Bottom != 0))
    {
        MoveWindow(hWnd, TaskManagerSettings.Left, TaskManagerSettings.Top, TaskManagerSettings.Right - TaskManagerSettings.Left, TaskManagerSettings.Bottom - TaskManagerSettings.Top, TRUE);
#ifdef __GNUC__TEST__
        MoveWindow(hApplicationPage, TaskManagerSettings.Left + PAGE_OFFSET_LEFT, TaskManagerSettings.Top + PAGE_OFFSET_TOP, TaskManagerSettings.Right - TaskManagerSettings.Left - PAGE_OFFSET_WIDTH, TaskManagerSettings.Bottom - TaskManagerSettings.Top - PAGE_OFFSET_HEIGHT, FALSE);
        MoveWindow(hProcessPage, TaskManagerSettings.Left + PAGE_OFFSET_LEFT, TaskManagerSettings.Top + PAGE_OFFSET_TOP, TaskManagerSettings.Right - TaskManagerSettings.Left - PAGE_OFFSET_WIDTH, TaskManagerSettings.Bottom - TaskManagerSettings.Top - PAGE_OFFSET_HEIGHT, FALSE);
        MoveWindow(hPerformancePage, TaskManagerSettings.Left + PAGE_OFFSET_LEFT, TaskManagerSettings.Top + PAGE_OFFSET_TOP, TaskManagerSettings.Right - TaskManagerSettings.Left - PAGE_OFFSET_WIDTH, TaskManagerSettings.Bottom - TaskManagerSettings.Top - PAGE_OFFSET_HEIGHT, FALSE);
#endif
    }
    if (TaskManagerSettings.Maximized)
        ShowWindow(hWnd, SW_MAXIMIZE);

    /* Set the always on top style */
    hMenu = GetMenu(hWnd);
    hEditMenu = GetSubMenu(hMenu, 1);
    hViewMenu = GetSubMenu(hMenu, 2);
    hUpdateSpeedMenu = GetSubMenu(hViewMenu, 1);
    hCPUHistoryMenu = GetSubMenu(hViewMenu, 7);

    /* Check or uncheck the always on top menu item */
    if (TaskManagerSettings.AlwaysOnTop) {
        CheckMenuItem(hEditMenu, ID_OPTIONS_ALWAYSONTOP, MF_BYCOMMAND|MF_CHECKED);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    } else {
        CheckMenuItem(hEditMenu, ID_OPTIONS_ALWAYSONTOP, MF_BYCOMMAND|MF_UNCHECKED);
        SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    }

    /* Check or uncheck the minimize on use menu item */
    if (TaskManagerSettings.MinimizeOnUse)
        CheckMenuItem(hEditMenu, ID_OPTIONS_MINIMIZEONUSE, MF_BYCOMMAND|MF_CHECKED);
    else
        CheckMenuItem(hEditMenu, ID_OPTIONS_MINIMIZEONUSE, MF_BYCOMMAND|MF_UNCHECKED);

    /* Check or uncheck the hide when minimized menu item */
    if (TaskManagerSettings.HideWhenMinimized)
        CheckMenuItem(hEditMenu, ID_OPTIONS_HIDEWHENMINIMIZED, MF_BYCOMMAND|MF_CHECKED);
    else
        CheckMenuItem(hEditMenu, ID_OPTIONS_HIDEWHENMINIMIZED, MF_BYCOMMAND|MF_UNCHECKED);

    /* Check or uncheck the show 16-bit tasks menu item */
    if (TaskManagerSettings.Show16BitTasks)
        CheckMenuItem(hEditMenu, ID_OPTIONS_SHOW16BITTASKS, MF_BYCOMMAND|MF_CHECKED);
    else
        CheckMenuItem(hEditMenu, ID_OPTIONS_SHOW16BITTASKS, MF_BYCOMMAND|MF_UNCHECKED);

    if (TaskManagerSettings.View_LargeIcons)
        CheckMenuRadioItem(hViewMenu, ID_VIEW_LARGE, ID_VIEW_DETAILS, ID_VIEW_LARGE, MF_BYCOMMAND);
    else if (TaskManagerSettings.View_SmallIcons)
        CheckMenuRadioItem(hViewMenu, ID_VIEW_LARGE, ID_VIEW_DETAILS, ID_VIEW_SMALL, MF_BYCOMMAND);
    else
        CheckMenuRadioItem(hViewMenu, ID_VIEW_LARGE, ID_VIEW_DETAILS, ID_VIEW_DETAILS, MF_BYCOMMAND);

    if (TaskManagerSettings.ShowKernelTimes)
        CheckMenuItem(hViewMenu, ID_VIEW_SHOWKERNELTIMES, MF_BYCOMMAND|MF_CHECKED);
    else
        CheckMenuItem(hViewMenu, ID_VIEW_SHOWKERNELTIMES, MF_BYCOMMAND|MF_UNCHECKED);

    if (TaskManagerSettings.UpdateSpeed == 1)
        CheckMenuRadioItem(hUpdateSpeedMenu, ID_VIEW_UPDATESPEED_HIGH, ID_VIEW_UPDATESPEED_PAUSED, ID_VIEW_UPDATESPEED_HIGH, MF_BYCOMMAND);
    else if (TaskManagerSettings.UpdateSpeed == 2)
        CheckMenuRadioItem(hUpdateSpeedMenu, ID_VIEW_UPDATESPEED_HIGH, ID_VIEW_UPDATESPEED_PAUSED, ID_VIEW_UPDATESPEED_NORMAL, MF_BYCOMMAND);
    else if (TaskManagerSettings.UpdateSpeed == 4)
        CheckMenuRadioItem(hUpdateSpeedMenu, ID_VIEW_UPDATESPEED_HIGH, ID_VIEW_UPDATESPEED_PAUSED, ID_VIEW_UPDATESPEED_LOW, MF_BYCOMMAND);
    else
        CheckMenuRadioItem(hUpdateSpeedMenu, ID_VIEW_UPDATESPEED_HIGH, ID_VIEW_UPDATESPEED_PAUSED, ID_VIEW_UPDATESPEED_PAUSED, MF_BYCOMMAND);

    if (TaskManagerSettings.CPUHistory_OneGraphPerCPU)
        CheckMenuRadioItem(hCPUHistoryMenu, ID_VIEW_CPUHISTORY_ONEGRAPHALL, ID_VIEW_CPUHISTORY_ONEGRAPHPERCPU, ID_VIEW_CPUHISTORY_ONEGRAPHPERCPU, MF_BYCOMMAND);
    else
        CheckMenuRadioItem(hCPUHistoryMenu, ID_VIEW_CPUHISTORY_ONEGRAPHALL, ID_VIEW_CPUHISTORY_ONEGRAPHPERCPU, ID_VIEW_CPUHISTORY_ONEGRAPHALL, MF_BYCOMMAND);

    nActivePage = TaskManagerSettings.ActiveTabPage;
    SendMessageW(hTabWnd, TCM_SETCURFOCUS, 0, 0);
    SendMessageW(hTabWnd, TCM_SETCURFOCUS, 1, 0);
    SendMessageW(hTabWnd, TCM_SETCURFOCUS, 2, 0);
    SendMessageW(hTabWnd, TCM_SETCURFOCUS, nActivePage, 0);

    if (TaskManagerSettings.UpdateSpeed == 1)
        SetTimer(hWnd, 1, 1000, NULL);
    else if (TaskManagerSettings.UpdateSpeed == 2)
        SetTimer(hWnd, 1, 2000, NULL);
    else if (TaskManagerSettings.UpdateSpeed == 4)
        SetTimer(hWnd, 1, 4000, NULL);

    /*
     * Refresh the performance data
     * Sample it twice so we can establish
     * the delta values & cpu usage
     */
    PerfDataRefresh();
    PerfDataRefresh();

    RefreshApplicationPage();
    RefreshProcessPage();
    RefreshPerformancePage();

    TrayIcon_ShellAddTrayIcon();

    return TRUE;
}