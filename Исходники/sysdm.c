/* First Applet */
LONG CALLBACK
SystemApplet(VOID)
{
    HPROPSHEETPAGE hpsp[MAX_SYSTEM_PAGES];
    PROPSHEETHEADER psh;
    HMODULE hNetIdDll;
    HPSXA hpsxa = NULL;
    LONG Ret;
    static INITCOMMONCONTROLSEX icc = {sizeof(INITCOMMONCONTROLSEX), ICC_LINK_CLASS};

    if (!InitCommonControlsEx(&icc))
        return 0;

    ZeroMemory(&psh, sizeof(PROPSHEETHEADER));
    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags =  PSH_PROPTITLE;
    psh.hwndParent = hCPLWindow;
    psh.hInstance = hApplet;
    psh.hIcon = LoadIcon(hApplet, MAKEINTRESOURCE(IDI_CPLSYSTEM));
    psh.pszCaption = MAKEINTRESOURCE(IDS_CPLSYSTEMNAME);
    psh.nPages = 0;
    psh.nStartPage = 0;
    psh.phpage = hpsp;
    psh.pfnCallback = NULL;

    InitPropSheetPage(&psh, IDD_PROPPAGEGENERAL, (DLGPROC) GeneralPageProc);
    hNetIdDll = AddNetIdPage(&psh);
    InitPropSheetPage(&psh, IDD_PROPPAGEHARDWARE, (DLGPROC) HardwarePageProc);
    InitPropSheetPage(&psh, IDD_PROPPAGEADVANCED, (DLGPROC) AdvancedPageProc);

    /* Load additional pages provided by shell extensions */
    hpsxa = SHCreatePropSheetExtArray(HKEY_LOCAL_MACHINE, REGSTR_PATH_CONTROLSFOLDER TEXT("\\System"), MAX_SYSTEM_PAGES - psh.nPages);
    if (hpsxa != NULL)
    {
        SHAddFromPropSheetExtArray(hpsxa, PropSheetAddPage, (LPARAM)&psh);
    }

    Ret = (LONG)(PropertySheet(&psh) != -1);

    if (hpsxa != NULL)
    {
        SHDestroyPropSheetExtArray(hpsxa);
    }

    if (hNetIdDll != NULL)
        FreeLibrary(hNetIdDll);

    return Ret;
}