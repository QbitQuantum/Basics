BOOL CExportDlg::OnInitDialog()
{
    CResizableStandAloneDialog::OnInitDialog();
    CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

    ExtendFrameIntoClientArea(IDC_REVISIONGROUP);
    m_aeroControls.SubclassOkCancelHelp(this);

    m_sExportDirOrig = m_strExportDirectory;
    m_bAutoCreateTargetName = !(PathIsDirectoryEmpty(m_sExportDirOrig) || !PathFileExists(m_sExportDirOrig));

    AdjustControlSize(IDC_NOEXTERNALS);
    AdjustControlSize(IDC_IGNOREKEYWORDS);
    AdjustControlSize(IDC_REVISION_HEAD);
    AdjustControlSize(IDC_REVISION_N);

    AddAnchor(IDC_REPOGROUP, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_REPOLABEL, TOP_LEFT);
    AddAnchor(IDC_URLCOMBO, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_BROWSE, TOP_RIGHT);
    AddAnchor(IDC_EXPORT_CHECKOUTDIR, TOP_LEFT);
    AddAnchor(IDC_CHECKOUTDIRECTORY, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_CHECKOUTDIRECTORY_BROWSE, TOP_RIGHT);
    AddAnchor(IDC_DEPTH, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_NOEXTERNALS, TOP_LEFT);
    AddAnchor(IDC_IGNOREKEYWORDS, TOP_LEFT);
    AddAnchor(IDC_EOLLABEL, TOP_LEFT);
    AddAnchor(IDC_EOLCOMBO, TOP_LEFT);

    AddAnchor(IDC_REVISIONGROUP, TOP_LEFT, BOTTOM_RIGHT);
    AddAnchor(IDC_REVISION_HEAD, TOP_LEFT);
    AddAnchor(IDC_REVISION_N, TOP_LEFT);
    AddAnchor(IDC_REVISION_NUM, TOP_LEFT);
    AddAnchor(IDC_SHOW_LOG, TOP_LEFT);

    AddAnchor(IDOK, BOTTOM_RIGHT);
    AddAnchor(IDCANCEL, BOTTOM_RIGHT);
    AddAnchor(IDHELP, BOTTOM_RIGHT);

    // save the provided url since the url combo
    // will change that below
    CString origurl = m_URL;
    m_URLCombo.SetURLHistory(true, true);
    m_URLCombo.LoadHistory(L"Software\\TortoiseSVN\\History\\repoURLS", L"url");
    m_URLCombo.SetCurSel(0);

    m_depthCombo.AddString(CString(MAKEINTRESOURCE(IDS_SVN_DEPTH_INFINITE)));
    m_depthCombo.AddString(CString(MAKEINTRESOURCE(IDS_SVN_DEPTH_IMMEDIATE)));
    m_depthCombo.AddString(CString(MAKEINTRESOURCE(IDS_SVN_DEPTH_FILES)));
    m_depthCombo.AddString(CString(MAKEINTRESOURCE(IDS_SVN_DEPTH_EMPTY)));
    m_depthCombo.SetCurSel(0);

    // set radio buttons according to the revision
    SetRevision(Revision);

    m_editRevision.SetWindowText(L"");

    if (!origurl.IsEmpty())
        m_URLCombo.SetWindowText(origurl);
    else
    {
        // if there is an url on the clipboard, use that url as the default.
        CAppUtils::AddClipboardUrlToWindow(m_URLCombo.GetSafeHwnd());
    }
    GetDlgItem(IDC_BROWSE)->EnableWindow(!m_URLCombo.GetString().IsEmpty());

    m_tooltips.AddTool(IDC_CHECKOUTDIRECTORY, IDS_CHECKOUT_TT_DIR);
    m_tooltips.AddTool(IDC_EOLCOMBO, IDS_EXPORT_TT_EOL);

    SHAutoComplete(GetDlgItem(IDC_CHECKOUTDIRECTORY)->m_hWnd, SHACF_FILESYSTEM);

    // fill the combobox with the choices of eol styles
    m_eolCombo.AddString(L"default");
    m_eolCombo.AddString(L"CRLF");
    m_eolCombo.AddString(L"LF");
    m_eolCombo.AddString(L"CR");
    m_eolCombo.SelectString(0, L"default");

    if (!Revision.IsHead())
    {
        // if the revision is not HEAD, change the radio button and
        // fill in the revision in the edit box
        CString temp;
        temp.Format(L"%ld", (LONG)Revision);
        m_editRevision.SetWindowText(temp);
        CheckRadioButton(IDC_REVISION_HEAD, IDC_REVISION_N, IDC_REVISION_N);
    }

    DialogEnableWindow(IDOK, !m_strExportDirectory.IsEmpty());

    if ((m_pParentWnd==NULL)&&(GetExplorerHWND()))
        CenterWindow(CWnd::FromHandle(GetExplorerHWND()));
    EnableSaveRestore(L"ExportDlg");
    return TRUE;
}