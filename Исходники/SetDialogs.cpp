// CSetDialogs message handlers
BOOL CSetDialogs::OnInitDialog()
{
    CMFCFontComboBox::m_bDrawUsingFont = true;

    ISettingsPropPage::OnInitDialog();

    EnableToolTips();

    int ind = m_cAutoClose.AddString(CString(MAKEINTRESOURCE(IDS_PROGRS_CLOSE_MANUAL)));
    m_cAutoClose.SetItemData(ind, CLOSE_MANUAL);
    ind = m_cAutoClose.AddString(CString(MAKEINTRESOURCE(IDS_PROGRS_CLOSE_NOMERGES)));
    m_cAutoClose.SetItemData(ind, CLOSE_NOMERGES);
    ind = m_cAutoClose.AddString(CString(MAKEINTRESOURCE(IDS_PROGRS_CLOSE_NOCONFLICTS)));
    m_cAutoClose.SetItemData(ind, CLOSE_NOCONFLICTS);
    ind = m_cAutoClose.AddString(CString(MAKEINTRESOURCE(IDS_PROGRS_CLOSE_NOERROR)));
    m_cAutoClose.SetItemData(ind, CLOSE_NOERRORS);

    m_dwAutoClose = m_regAutoClose;
    m_bAutoCloseLocal = m_regAutoCloseLocal;
    m_bShortDateFormat = m_regShortDateFormat;
    m_bUseSystemLocaleForDates = m_regUseSystemLocaleForDates;
    m_sFontName = m_regFontName;
    m_dwFontSize = m_regFontSize;
    m_bUseWCURL = m_regUseWCURL;
    m_sDefaultCheckoutPath = m_regDefaultCheckoutPath;
    m_sDefaultCheckoutUrl = m_regDefaultCheckoutUrl;
    m_bDiffByDoubleClick = m_regDiffByDoubleClick;
    m_bUseRecycleBin = m_regUseRecycleBin;

    SHAutoComplete(GetDlgItem(IDC_CHECKOUTPATH)->m_hWnd, SHACF_FILESYSTEM);
    SHAutoComplete(GetDlgItem(IDC_CHECKOUTURL)->m_hWnd, SHACF_URLALL);

    for (int i=0; i<m_cAutoClose.GetCount(); ++i)
        if (m_cAutoClose.GetItemData(i)==m_dwAutoClose)
            m_cAutoClose.SetCurSel(i);

    CString temp;
    temp.Format(L"%ld", (DWORD)m_regDefaultLogs);
    m_sDefaultLogs = temp;

    m_tooltips.AddTool(IDC_SHORTDATEFORMAT, IDS_SETTINGS_SHORTDATEFORMAT_TT);
    m_tooltips.AddTool(IDC_SYSTEMLOCALEFORDATES, IDS_SETTINGS_USESYSTEMLOCALEFORDATES_TT);
    m_tooltips.AddTool(IDC_AUTOCLOSECOMBO, IDS_SETTINGS_AUTOCLOSE_TT);
    m_tooltips.AddTool(IDC_WCURLFROM, IDS_SETTINGS_USEWCURL_TT);
    m_tooltips.AddTool(IDC_CHECKOUTPATHLABEL, IDS_SETTINGS_CHECKOUTPATH_TT);
    m_tooltips.AddTool(IDC_CHECKOUTPATH, IDS_SETTINGS_CHECKOUTPATH_TT);
    m_tooltips.AddTool(IDC_CHECKOUTURLLABEL, IDS_SETTINGS_CHECKOUTURL_TT);
    m_tooltips.AddTool(IDC_CHECKOUTURL, IDS_SETTINGS_CHECKOUTURL_TT);
    m_tooltips.AddTool(IDC_DIFFBYDOUBLECLICK, IDS_SETTINGS_DIFFBYDOUBLECLICK_TT);
    m_tooltips.AddTool(IDC_USERECYCLEBIN, IDS_SETTINGS_USERECYCLEBIN_TT);

    int count = 0;
    for (int i=6; i<32; i=i+2)
    {
        temp.Format(L"%d", i);
        m_cFontSizes.AddString(temp);
        m_cFontSizes.SetItemData(count++, i);
    }
    BOOL foundfont = FALSE;
    for (int i=0; i<m_cFontSizes.GetCount(); i++)
    {
        if (m_cFontSizes.GetItemData(i) == m_dwFontSize)
        {
            m_cFontSizes.SetCurSel(i);
            foundfont = TRUE;
        }
    }
    if (!foundfont)
    {
        temp.Format(L"%lu", m_dwFontSize);
        m_cFontSizes.SetWindowText(temp);
    }

    m_cFontNames.Setup(DEVICE_FONTTYPE|RASTER_FONTTYPE|TRUETYPE_FONTTYPE, 1, FIXED_PITCH);
    m_cFontNames.SelectFont(m_sFontName);

    UpdateData(FALSE);
    return TRUE;
}