BOOL CCopyDlg::OnInitDialog()
{
    CResizableStandAloneDialog::OnInitDialog();
    CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

    ExtendFrameIntoClientArea(IDC_EXTGROUP);
    m_aeroControls.SubclassControl(this, IDC_DOSWITCH);
    m_aeroControls.SubclassControl(this, IDC_MAKEPARENTS);
    m_aeroControls.SubclassOkCancelHelp(this);
    m_bCancelled = false;

    DWORD exStyle = LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_CHECKBOXES;
    m_ExtList.SetExtendedStyle(exStyle);
    SetWindowTheme(m_ExtList.GetSafeHwnd(), L"Explorer", NULL);
    m_ExtList.ShowText(CString(MAKEINTRESOURCE(IDS_COPY_WAITFOREXTERNALS)));

    AdjustControlSize(IDC_COPYHEAD);
    AdjustControlSize(IDC_COPYREV);
    AdjustControlSize(IDC_COPYWC);
    AdjustControlSize(IDC_DOSWITCH);
    AdjustControlSize(IDC_MAKEPARENTS);

    CTSVNPath path(m_path);
    CString sWindowTitle;
    GetWindowText(sWindowTitle);
    CAppUtils::SetWindowTitle(m_hWnd, path.GetUIPathString(), sWindowTitle);

    m_History.SetMaxHistoryItems((LONG)CRegDWORD(L"Software\\TortoiseSVN\\MaxHistoryItems", 25));

    SetRevision(m_CopyRev);

    m_tooltips.AddTool(IDC_HISTORY, IDS_COMMITDLG_HISTORY_TT);

    if (SVN::PathIsURL(path))
    {
        DialogEnableWindow(IDC_COPYWC, FALSE);
        DialogEnableWindow(IDC_DOSWITCH, FALSE);
        SetDlgItemText(IDC_COPYSTARTLABEL, CString(MAKEINTRESOURCE(IDS_COPYDLG_FROMURL)));
    }

    SVN svn;
    CString sUUID;
    m_repoRoot = svn.GetRepositoryRootAndUUID(path, true, sUUID);
    m_repoRoot.TrimRight('/');
    m_wcURL = svn.GetURLFromPath(path);
    if (m_wcURL.IsEmpty() || (!path.IsUrl() && !path.Exists()))
    {
        CString Wrong_URL=path.GetSVNPathString();
        CString temp;
        temp.Format(IDS_ERR_NOURLOFFILE, (LPCTSTR)Wrong_URL);
        ::MessageBox(this->m_hWnd, temp, L"TortoiseSVN", MB_ICONERROR);
        this->EndDialog(IDCANCEL);      //exit
    }
    m_URLCombo.LoadHistory(L"Software\\TortoiseSVN\\History\\repoPaths\\"+sUUID, L"url");
    m_URLCombo.SetCurSel(0);
    CString relPath = m_wcURL.Mid(m_repoRoot.GetLength());
    if (!m_URL.IsEmpty())
    {
        // allow the use of urls relative to the repo root
        if (m_URL[0] != '^')
            relPath = m_URL.Mid(m_repoRoot.GetLength());
        else
            relPath = m_URL.Mid(1);
    }
    CTSVNPath r = CTSVNPath(relPath);
    relPath = r.GetUIPathString();
    relPath.Replace('\\', '/');
    m_URLCombo.AddString(relPath, 0);
    m_URLCombo.SelectString(-1, relPath);
    m_URL = m_wcURL;
    SetDlgItemText(IDC_DESTURL, CPathUtils::CombineUrls(m_repoRoot, relPath));
    SetDlgItemText(IDC_FROMURL, m_wcURL);

    CString reg;
    reg.Format(L"Software\\TortoiseSVN\\History\\commit%s", (LPCTSTR)sUUID);
    m_History.Load(reg, L"logmsgs");

    m_ProjectProperties.ReadProps(m_path);
    if (CRegDWORD(L"Software\\TortoiseSVN\\AlwaysWarnIfNoIssue", FALSE))
        m_ProjectProperties.bWarnIfNoIssue = TRUE;

    m_cLogMessage.Init(m_ProjectProperties);
    m_cLogMessage.SetFont((CString)CRegString(L"Software\\TortoiseSVN\\LogFontName", L"Courier New"), (DWORD)CRegDWORD(L"Software\\TortoiseSVN\\LogFontSize", 8));

    GetDlgItem(IDC_BUGTRAQBUTTON)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BUGTRAQBUTTON)->EnableWindow(FALSE);
    CBugTraqAssociations bugtraq_associations;
    bugtraq_associations.Load(m_ProjectProperties.GetProviderUUID(), m_ProjectProperties.sProviderParams);

    if (bugtraq_associations.FindProvider(CTSVNPathList(m_path), &m_bugtraq_association))
    {
        CComPtr<IBugTraqProvider> pProvider;
        HRESULT hr = pProvider.CoCreateInstance(m_bugtraq_association.GetProviderClass());
        if (SUCCEEDED(hr))
        {
            m_BugTraqProvider = pProvider;
            ATL::CComBSTR temp;
            ATL::CComBSTR parameters;
            parameters.Attach(m_bugtraq_association.GetParameters().AllocSysString());
            hr = pProvider->GetLinkText(GetSafeHwnd(), parameters, &temp);
            if (SUCCEEDED(hr))
            {
                SetDlgItemText(IDC_BUGTRAQBUTTON, temp == 0 ? L"" : temp);
                GetDlgItem(IDC_BUGTRAQBUTTON)->EnableWindow(TRUE);
                GetDlgItem(IDC_BUGTRAQBUTTON)->ShowWindow(SW_SHOW);
            }
        }

        GetDlgItem(IDC_LOGMESSAGE)->SetFocus();
    }
    if (m_ProjectProperties.sMessage.IsEmpty())
    {
        GetDlgItem(IDC_BUGID)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUGIDLABEL)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LOGMESSAGE)->SetFocus();
    }
    else
    {
        GetDlgItem(IDC_BUGID)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_BUGIDLABEL)->ShowWindow(SW_SHOW);
        if (!m_ProjectProperties.sLabel.IsEmpty())
            SetDlgItemText(IDC_BUGIDLABEL, m_ProjectProperties.sLabel);
        GetDlgItem(IDC_BUGID)->SetFocus();
    }

    if (!m_sLogMessage.IsEmpty())
        m_cLogMessage.SetText(m_sLogMessage);
    else
        m_cLogMessage.SetText(m_ProjectProperties.GetLogMsgTemplate(PROJECTPROPNAME_LOGTEMPLATEBRANCH));

    OnEnChangeLogmessage();

    m_linkControl.ConvertStaticToLink(m_hWnd, IDC_CHECKALL);
    m_linkControl.ConvertStaticToLink(m_hWnd, IDC_CHECKNONE);

    // line up all controls and adjust their sizes.
#define LINKSPACING 9
    RECT rc = AdjustControlSize(IDC_SELECTLABEL);
    rc.right -= 15; // AdjustControlSize() adds 20 pixels for the checkbox/radio button bitmap, but this is a label...
    rc = AdjustStaticSize(IDC_CHECKALL, rc, LINKSPACING);
    rc = AdjustStaticSize(IDC_CHECKNONE, rc, LINKSPACING);

    CAppUtils::SetAccProperty(m_cLogMessage.GetSafeHwnd(), PROPID_ACC_ROLE, ROLE_SYSTEM_TEXT);
    CAppUtils::SetAccProperty(m_cLogMessage.GetSafeHwnd(), PROPID_ACC_HELP, CString(MAKEINTRESOURCE(IDS_INPUT_ENTERLOG)));
    CAppUtils::SetAccProperty(m_cLogMessage.GetSafeHwnd(), PROPID_ACC_KEYBOARDSHORTCUT, L"Alt+"+CString(CAppUtils::FindAcceleratorKey(this, IDC_INVISIBLE)));

    CAppUtils::SetAccProperty(GetDlgItem(IDC_CHECKALL)->GetSafeHwnd(), PROPID_ACC_ROLE, ROLE_SYSTEM_LINK);
    CAppUtils::SetAccProperty(GetDlgItem(IDC_CHECKNONE)->GetSafeHwnd(), PROPID_ACC_ROLE, ROLE_SYSTEM_LINK);

    CAppUtils::SetAccProperty(m_URLCombo.GetSafeHwnd(), PROPID_ACC_KEYBOARDSHORTCUT, L"Alt+"+CString(CAppUtils::FindAcceleratorKey(this, IDC_TOURLLABEL)));
    CAppUtils::SetAccProperty(GetDlgItem(IDC_FROMURL)->GetSafeHwnd(), PROPID_ACC_KEYBOARDSHORTCUT, L"Alt+"+CString(CAppUtils::FindAcceleratorKey(this, IDC_COPYSTARTLABEL)));
    CAppUtils::SetAccProperty(GetDlgItem(IDC_DESTURL)->GetSafeHwnd(), PROPID_ACC_KEYBOARDSHORTCUT, L"Alt+"+CString(CAppUtils::FindAcceleratorKey(this, IDC_DESTLABEL)));

    AddAnchor(IDC_REPOGROUP, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_COPYSTARTLABEL, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_FROMURL, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_TOURLLABEL, TOP_LEFT);
    AddAnchor(IDC_URLCOMBO, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_BROWSE, TOP_RIGHT);
    AddAnchor(IDC_DESTLABEL, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_DESTURL, TOP_LEFT, TOP_RIGHT);
    AddAnchor(IDC_MSGGROUP, TOP_LEFT, MIDDLE_RIGHT);
    AddAnchor(IDC_HISTORY, TOP_LEFT);
    AddAnchor(IDC_BUGTRAQBUTTON, TOP_LEFT);
    AddAnchor(IDC_BUGIDLABEL, TOP_RIGHT);
    AddAnchor(IDC_BUGID, TOP_RIGHT);
    AddAnchor(IDC_INVISIBLE, TOP_RIGHT);
    AddAnchor(IDC_LOGMESSAGE, TOP_LEFT, MIDDLE_RIGHT);
    AddAnchor(IDC_FROMGROUP, MIDDLE_LEFT, MIDDLE_RIGHT);
    AddAnchor(IDC_COPYHEAD, MIDDLE_LEFT);
    AddAnchor(IDC_COPYREV, MIDDLE_LEFT);
    AddAnchor(IDC_COPYREVTEXT, MIDDLE_RIGHT);
    AddAnchor(IDC_BROWSEFROM, MIDDLE_RIGHT);
    AddAnchor(IDC_COPYWC, MIDDLE_LEFT);
    AddAnchor(IDC_EXTGROUP, MIDDLE_LEFT, BOTTOM_RIGHT);
    AddAnchor(IDC_SELECTLABEL, MIDDLE_LEFT);
    AddAnchor(IDC_CHECKALL, MIDDLE_LEFT);
    AddAnchor(IDC_CHECKNONE, MIDDLE_LEFT);
    AddAnchor(IDC_EXTERNALSLIST, MIDDLE_LEFT, BOTTOM_RIGHT);
    AddAnchor(IDC_DOSWITCH, BOTTOM_LEFT);
    AddAnchor(IDC_MAKEPARENTS, BOTTOM_LEFT);
    AddAnchor(IDOK, BOTTOM_RIGHT);
    AddAnchor(IDCANCEL, BOTTOM_RIGHT);
    AddAnchor(IDHELP, BOTTOM_RIGHT);

    if ((m_pParentWnd==NULL)&&(GetExplorerHWND()))
        CenterWindow(CWnd::FromHandle(GetExplorerHWND()));
    EnableSaveRestore(L"CopyDlg");

    m_bSettingChanged = false;
    if (!m_path.IsUrl())
    {
        // start a thread to obtain the highest revision number of the working copy
        // without blocking the dialog
        if ((m_pThread = AfxBeginThread(FindRevThreadEntry, this))==NULL)
        {
            OnCantStartThread();
        }
    }

    return TRUE;
}