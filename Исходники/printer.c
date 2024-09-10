static HDC chooseprinter(void)
{
    PRINTDLG pd;
    HDC dc;
    DWORD rc;
    char cwd[MAX_PATH];

    GetCurrentDirectory(MAX_PATH,cwd);

    pd.lStructSize = sizeof( PRINTDLG );
    pd.hwndOwner = NULL;
    pd.hDevMode = (HANDLE)NULL;
    pd.hDevNames = (HANDLE)NULL;
    pd.Flags = PD_RETURNDC | PD_NOSELECTION | PD_NOPAGENUMS |
	PD_USEDEVMODECOPIES;
    pd.nFromPage = 0;
    pd.nToPage = 0;
    pd.nMinPage = 0;
    pd.nMaxPage = 0;
    pd.nCopies = 1;
    pd.hInstance = (HINSTANCE)NULL;
    pd.lCustData = (LPARAM)0;
    pd.lpfnPrintHook = 0;
    pd.lpfnSetupHook = 0;
    pd.lpPrintTemplateName = (LPCSTR) 0;
    pd.lpSetupTemplateName = (LPCSTR) 0;
    pd.hPrintTemplate = (HGLOBAL)0;
    pd.hSetupTemplate = (HGLOBAL)0;

    dc = PrintDlg( &pd ) ? pd.hDC : NULL;
    SetCurrentDirectory(cwd);
    if (!dc) {
	rc = CommDlgExtendedError(); /* 0 means user cancelled */
	if (rc) R_ShowMessage(_("Unable to choose printer"));
    }
    return dc;
}