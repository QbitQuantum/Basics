/* Display Applet */
static LONG APIENTRY
DisplayApplet(HWND hwnd, UINT uMsg, LPARAM wParam, LPARAM lParam)
{
    HPROPSHEETPAGE hpsp[MAX_DESK_PAGES];
    PROPSHEETHEADER psh;
    HPSXA hpsxa;
    TCHAR Caption[1024];
    LONG ret;
    UINT i;

    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(uMsg);
    UNREFERENCED_PARAMETER(hwnd);

    g_GlobalData.desktop_color = GetSysColor(COLOR_DESKTOP);

    LoadString(hApplet, IDS_CPLNAME, Caption, sizeof(Caption) / sizeof(TCHAR));

    ZeroMemory(&psh, sizeof(PROPSHEETHEADER));
    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_USECALLBACK | PSH_PROPTITLE;
    psh.hwndParent = hCPLWindow;
    psh.hInstance = hApplet;
    psh.hIcon = LoadIcon(hApplet, MAKEINTRESOURCE(IDC_DESK_ICON));
    psh.pszCaption = Caption;
    psh.nPages = 0;
    psh.nStartPage = 0;
    psh.phpage = hpsp;

    /* Allow shell extensions to replace the background page */
    hpsxa = SHCreatePropSheetExtArray(HKEY_LOCAL_MACHINE, REGSTR_PATH_CONTROLSFOLDER TEXT("\\Desk"), MAX_DESK_PAGES - psh.nPages);

    for (i = 0; i != sizeof(PropPages) / sizeof(PropPages[0]); i++)
    {
        /* Override the background page if requested by a shell extension */
        if (PropPages[i].idDlg == IDD_BACKGROUND && hpsxa != NULL &&
            SHReplaceFromPropSheetExtArray(hpsxa, CPLPAGE_DISPLAY_BACKGROUND, PropSheetAddPage, (LPARAM)&psh) != 0)
        {
            /* The shell extension added one or more pages to replace the background page.
               Don't create the built-in page anymore! */
            continue;
        }

        InitPropSheetPage(&psh, PropPages[i].idDlg, PropPages[i].DlgProc, PropPages[i].Callback);
    }

    /* NOTE: Don't call SHAddFromPropSheetExtArray here because this applet only allows
             replacing the background page but not extending the applet by more pages */

    ret = (LONG)(PropertySheet(&psh) != -1);

    if (hpsxa != NULL)
        SHDestroyPropSheetExtArray(hpsxa);

    return ret;
}