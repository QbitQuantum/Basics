HWND CreatePropSheet(HINSTANCE hInstance, HWND hwndOwner, LPCTSTR lpszTitle)
{
    HWND hPropSheet;
    PROPSHEETHEADERW psh;
    PROPSHEETPAGEW   psp[7];
    unsigned int nPages = 0;

    /* Header */
    psh.dwSize      = sizeof(psh);
    psh.dwFlags     = PSH_PROPSHEETPAGE | PSH_MODELESS | /*PSH_USEICONID |*/ PSH_HASHELP | /*PSH_NOCONTEXTHELP |*/ PSH_USECALLBACK;
    psh.hInstance   = hInstance;
    psh.hwndParent  = hwndOwner;
    // psh.pszIcon     = MAKEINTRESOURCEW(IDI_APPICON); // Disabled because it only sets the small icon; the big icon is a stretched version of the small one.
    psh.pszCaption  = lpszTitle;
    psh.nStartPage  = 0;
    psh.ppsp        = psp;
    psh.pfnCallback = PropSheetCallback;

    /* General page */
    psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
    psp[nPages].dwFlags     = PSP_HASHELP;
    psp[nPages].hInstance   = hInstance;
    psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_GENERAL_PAGE);
    psp[nPages].pfnDlgProc  = GeneralPageWndProc;
    ++nPages;

    // if (bIsOSVersionLessThanVista)
    {
        /* SYSTEM.INI page */
        if (MyFileExists(lpszSystemIni, NULL))
        {
            psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
            psp[nPages].dwFlags     = PSP_HASHELP | PSP_USETITLE;
            psp[nPages].hInstance   = hInstance;
            psp[nPages].pszTitle    = MAKEINTRESOURCEW(IDS_TAB_SYSTEM);
            psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_SYSTEM_PAGE);
            psp[nPages].pfnDlgProc  = SystemPageWndProc;
            psp[nPages].lParam      = (LPARAM)lpszSystemIni;
            ++nPages;

            BackupIniFile(lpszSystemIni);
        }

        /* WIN.INI page */
        if (MyFileExists(lpszWinIni, NULL))
        {
            psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
            psp[nPages].dwFlags     = PSP_HASHELP | PSP_USETITLE;
            psp[nPages].hInstance   = hInstance;
            psp[nPages].pszTitle    = MAKEINTRESOURCEW(IDS_TAB_WIN);
            psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_SYSTEM_PAGE);
            psp[nPages].pfnDlgProc  = WinPageWndProc;
            psp[nPages].lParam      = (LPARAM)lpszWinIni;
            ++nPages;

            BackupIniFile(lpszWinIni);
        }
    }

    /* FreeLdr page */
    // TODO: Program the interface for Vista: "light" BCD editor...
    if (!bIsWindows || (bIsWindows && bIsOSVersionLessThanVista))
    {
        LPCWSTR lpszLoaderIniFile = NULL;
        DWORD   dwTabNameId       = 0;
        if (bIsWindows)
        {
            lpszLoaderIniFile = lpszBootIni;
            dwTabNameId       = IDS_TAB_BOOT;
        }
        else
        {
            lpszLoaderIniFile = lpszFreeLdrIni;
            dwTabNameId       = IDS_TAB_FREELDR;
        }

        if (MyFileExists(lpszLoaderIniFile, NULL))
        {
            psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
            psp[nPages].dwFlags     = PSP_HASHELP | PSP_USETITLE;
            psp[nPages].hInstance   = hInstance;
            psp[nPages].pszTitle    = MAKEINTRESOURCEW(dwTabNameId);
            psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_FREELDR_PAGE);
            psp[nPages].pfnDlgProc  = FreeLdrPageWndProc;
            psp[nPages].lParam      = (LPARAM)lpszLoaderIniFile;
            ++nPages;

            BackupIniFile(lpszLoaderIniFile);
        }
    }

    /* Services page */
    psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
    psp[nPages].dwFlags     = PSP_HASHELP;
    psp[nPages].hInstance   = hInstance;
    psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_SERVICES_PAGE);
    psp[nPages].pfnDlgProc  = ServicesPageWndProc;
    ++nPages;

#if 0
    /* Startup page */
    psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
    psp[nPages].dwFlags     = PSP_HASHELP;
    psp[nPages].hInstance   = hInstance;
    psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_STARTUP_PAGE);
    psp[nPages].pfnDlgProc  = StartupPageWndProc;
    ++nPages;
#endif

    /* Tools page */
    psp[nPages].dwSize      = sizeof(PROPSHEETPAGEW);
    psp[nPages].dwFlags     = PSP_HASHELP;
    psp[nPages].hInstance   = hInstance;
    psp[nPages].pszTemplate = MAKEINTRESOURCEW(IDD_TOOLS_PAGE);
    psp[nPages].pfnDlgProc  = ToolsPageWndProc;
    ++nPages;

    /* Set the total number of created pages */
    psh.nPages = nPages;

    /* Create the property sheet */
    hPropSheet = (HWND)PropertySheetW(&psh);
    if (hPropSheet)
    {
        /* Center the property sheet on the desktop and show it */
        ClipOrCenterWindowToMonitor(hPropSheet, MONITOR_WORKAREA | MONITOR_CENTER);
        ShowWindow(hPropSheet, SW_SHOWNORMAL);
    }

    return hPropSheet;
}