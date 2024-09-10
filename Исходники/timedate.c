static LONG APIENTRY
Applet(HWND hwnd, UINT uMsg, LPARAM wParam, LPARAM lParam)
{
    PROPSHEETHEADER psh;
    PROPSHEETPAGEW psp[3];
    WCHAR Caption[256];
    LONG Ret = 0;

    UNREFERENCED_PARAMETER(uMsg);
    UNREFERENCED_PARAMETER(wParam);
    UNREFERENCED_PARAMETER(lParam);

    if (RegisterMonthCalControl(hApplet) &&
        RegisterClockControl())
    {
        LoadStringW(hApplet, IDS_CPLNAME, Caption, sizeof(Caption) / sizeof(WCHAR));

        ZeroMemory(&psh, sizeof(PROPSHEETHEADERW));
        psh.dwSize = sizeof(PROPSHEETHEADERW);
        psh.dwFlags =  PSH_PROPSHEETPAGE | PSH_PROPTITLE;
        psh.hwndParent = hwnd;
        psh.hInstance = hApplet;
        psh.hIcon = LoadIcon(hApplet, MAKEINTRESOURCEW(IDC_CPLICON));
        psh.pszCaption = Caption;
        psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGEW);
        psh.nStartPage = 0;
        psh.ppsp = psp;

        InitPropSheetPage(&psp[0], IDD_DATETIMEPAGE, (DLGPROC) DateTimePageProc);
        InitPropSheetPage(&psp[1], IDD_TIMEZONEPAGE, (DLGPROC) TimeZonePageProc);
        InitPropSheetPage(&psp[2], IDD_INETTIMEPAGE, (DLGPROC) InetTimePageProc);

        Ret = (LONG)(PropertySheetW(&psh) != -1);

        UnregisterMonthCalControl(hApplet);
        UnregisterClockControl();
    }

    return Ret;
}