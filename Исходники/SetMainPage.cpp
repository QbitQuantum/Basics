BOOL CSetMainPage::OnInitDialog()
{
    ISettingsPropPage::OnInitDialog();

    EnableToolTips();

    m_sTempExtensions = m_regExtensions;
    m_dwLanguage = m_regLanguage;
    m_bUseAero = m_regUseAero;
    HIGHCONTRAST hc = { sizeof(HIGHCONTRAST) };
    SystemParametersInfo(SPI_GETHIGHCONTRAST, sizeof(HIGHCONTRAST), &hc, FALSE);
    BOOL bEnabled = FALSE;
    DialogEnableWindow(IDC_AERODWM, ((hc.dwFlags & HCF_HIGHCONTRASTON) == 0) && SUCCEEDED(DwmIsCompositionEnabled(&bEnabled)) && bEnabled);
    if (IsWindows10OrGreater())
        GetDlgItem(IDC_AERODWM)->ShowWindow(SW_HIDE);
    CString temp;
    temp = m_regLastCommitTime;
    m_bLastCommitTime = (temp.CompareNoCase(L"yes")==0);

    m_tooltips.AddTool(IDC_TEMPEXTENSIONSLABEL, IDS_SETTINGS_TEMPEXTENSIONS_TT);
    m_tooltips.AddTool(IDC_TEMPEXTENSIONS, IDS_SETTINGS_TEMPEXTENSIONS_TT);
    m_tooltips.AddTool(IDC_COMMITFILETIMES, IDS_SETTINGS_COMMITFILETIMES_TT);
    m_tooltips.AddTool(IDC_CREATELIB, IDS_SETTINGS_CREATELIB_TT);

    DialogEnableWindow(IDC_CREATELIB, IsWindows7OrGreater());

    // set up the language selecting combobox
    TCHAR buf[MAX_PATH] = { 0 };
    GetLocaleInfo(1033, LOCALE_SNATIVELANGNAME, buf, _countof(buf));
    m_LanguageCombo.AddString(buf);
    m_LanguageCombo.SetItemData(0, 1033);
    CString path = CPathUtils::GetAppParentDirectory();
    path = path + L"Languages\\";
    CSimpleFileFind finder(path, L"*.dll");
    int langcount = 1;
    while (finder.FindNextFileNoDirectories())
    {
        CString file = finder.GetFilePath();
        CString filename = finder.GetFileName();
        if (filename.Left(12).CompareNoCase(L"TortoiseProc")==0)
        {
            CString sVer = _T(STRPRODUCTVER);
            sVer = sVer.Left(sVer.ReverseFind('.'));
            CString sFileVer = CPathUtils::GetVersionFromFile(file);
            sFileVer = sFileVer.Left(sFileVer.ReverseFind('.'));
            if (sFileVer.Compare(sVer)!=0)
                continue;
            CString sLoc = filename.Mid(12);
            sLoc = sLoc.Left(sLoc.GetLength()-4);   // cut off ".dll"
            if ((sLoc.Left(2) == L"32")&&(sLoc.GetLength() > 5))
                continue;
            DWORD loc = _tstoi(filename.Mid(12));
            GetLocaleInfo(loc, LOCALE_SNATIVELANGNAME, buf, _countof(buf));
            CString sLang = buf;
            GetLocaleInfo(loc, LOCALE_SNATIVECTRYNAME, buf, _countof(buf));
            if (buf[0])
            {
                sLang += L" (";
                sLang += buf;
                sLang += L")";
            }
            m_LanguageCombo.AddString(sLang);
            m_LanguageCombo.SetItemData(langcount++, loc);
        }
    }

    for (int i=0; i<m_LanguageCombo.GetCount(); i++)
    {
        if (m_LanguageCombo.GetItemData(i) == m_dwLanguage)
            m_LanguageCombo.SetCurSel(i);
    }

    UpdateData(FALSE);
    return TRUE;
}