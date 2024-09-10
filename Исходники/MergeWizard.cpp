BOOL CMergeWizard::OnInitDialog()
{
    BOOL bResult = CResizableSheetEx::OnInitDialog();
    CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    SVN svn;
    url = svn.GetURLFromPath(wcPath);
    sUUID = svn.GetUUIDFromPath(wcPath);

    MARGINS margs;
    margs.cxLeftWidth = 0;
    margs.cyTopHeight = 0;
    margs.cxRightWidth = 0;
    margs.cyBottomHeight = BOTTOMMARG;

    if ((DWORD)CRegDWORD(L"Software\\TortoiseSVN\\EnableDWMFrame", TRUE))
    {
        HIGHCONTRAST hc = { sizeof(HIGHCONTRAST) };
        SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(HIGHCONTRAST), &hc, FALSE);
        BOOL bEnabled = FALSE;
        if (((hc.dwFlags & HCF_HIGHCONTRASTON) == 0) && SUCCEEDED(DwmIsCompositionEnabled(&bEnabled)) && bEnabled)
        {
            DwmExtendFrameIntoClientArea(m_hWnd, &margs);
            ShowGrip(false);
        }
        m_aeroControls.SubclassOkCancelHelp(this);
        m_aeroControls.SubclassControl(this, ID_WIZFINISH);
        m_aeroControls.SubclassControl(this, ID_WIZBACK);
        m_aeroControls.SubclassControl(this, ID_WIZNEXT);
    }

    if ((m_pParentWnd == NULL) && (GetExplorerHWND()))
        CenterWindow(CWnd::FromHandle(GetExplorerHWND()));
    EnableSaveRestore(L"MergeWizard");

    return bResult;
}