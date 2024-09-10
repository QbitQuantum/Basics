BOOL CEditPropExternals::OnInitDialog()
{
    CResizableStandAloneDialog::OnInitDialog();
    CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

    ExtendFrameIntoClientArea(IDC_EXTERNALSLIST);
    m_aeroControls.SubclassControl(this, IDC_ADD);
    m_aeroControls.SubclassControl(this, IDC_EDIT);
    m_aeroControls.SubclassControl(this, IDC_REMOVE);
    m_aeroControls.SubclassControl(this, IDC_FINDHEAD);
    m_aeroControls.SubclassOkCancelHelp(this);

    ATLASSERT(m_pathList.GetCount() == 1);

    SVN svn;
    m_url = CTSVNPath(svn.GetURLFromPath(m_pathList[0]));
    m_repoRoot = CTSVNPath(svn.GetRepositoryRoot(m_pathList[0]));

    m_externals.Add(m_pathList[0], m_PropValue, false);

    DWORD exStyle = LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER;
    m_ExtList.SetExtendedStyle(exStyle);

    SetWindowTheme(m_ExtList.GetSafeHwnd(), L"Explorer", NULL);

    m_ExtList.SetRedraw(false);
    m_ExtList.DeleteAllItems();

    int c = m_ExtList.GetHeaderCtrl()->GetItemCount()-1;
    while (c>=0)
        m_ExtList.DeleteColumn(c--);
    CString temp;
    temp.LoadString(IDS_STATUSLIST_COLFILE);
    m_ExtList.InsertColumn(0, temp);
    temp.LoadString(IDS_STATUSLIST_COLURL);
    m_ExtList.InsertColumn(1, temp);
    temp.LoadString(IDS_EXTERNALS_PEG);
    m_ExtList.InsertColumn(2, temp);
    temp.LoadString(IDS_EXTERNALS_OPERATIVE);
    m_ExtList.InsertColumn(3, temp);
    temp.LoadString(IDS_EXTERNALS_HEADREV);
    m_ExtList.InsertColumn(4, temp);
    m_ExtList.SetItemCountEx((int)m_externals.size());

    CRect rect;
    m_ExtList.GetClientRect(&rect);
    m_ExtList.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
    int cx = (rect.Width()-240-m_ExtList.GetColumnWidth(0));
    m_ExtList.SetColumnWidth(1, cx);
    m_ExtList.SetColumnWidth(2, 80);
    m_ExtList.SetColumnWidth(3, 80);
    m_ExtList.SetColumnWidth(4, 80);

    m_ExtList.SetRedraw(true);

    CString sWindowTitle;
    GetWindowText(sWindowTitle);
    CAppUtils::SetWindowTitle(m_hWnd, m_pathList.GetCommonRoot().GetUIPathString(), sWindowTitle);

    AddAnchor(IDC_EXTERNALSLIST, TOP_LEFT, BOTTOM_RIGHT);
    AddAnchor(IDC_ADD, BOTTOM_LEFT);
    AddAnchor(IDC_EDIT, BOTTOM_LEFT);
    AddAnchor(IDC_REMOVE, BOTTOM_LEFT);
    AddAnchor(IDC_FINDHEAD, BOTTOM_LEFT);
    AddAnchor(IDOK, BOTTOM_RIGHT);
    AddAnchor(IDCANCEL, BOTTOM_RIGHT);
    AddAnchor(IDHELP, BOTTOM_RIGHT);
    EnableSaveRestore(L"EditPropsExternals");

    return TRUE;
}