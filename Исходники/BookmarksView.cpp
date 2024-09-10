LRESULT CBookmarksView::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
    SetMsgHandled(false);
    DlgResize_Init(false, false);

    CRect rc(0, 0, 0, 0);
    CWindow wndPlaceholder = GetDlgItem(IDC_BOOKMARKS_PLACEHOLDER);
    wndPlaceholder.GetWindowRect(rc);
    ScreenToClient(rc);
    wndPlaceholder.DestroyWindow();

    const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SORTASCENDING | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    if (!m_list.Create(dwViewStyle, rc, CWnd::FromHandle(m_hWnd), IDC_BOOKMARKS_PLACEHOLDER))
    {
        TRACE0("Failed to create Class View\n");
        return -1;      // fail to create
    }
    m_list.SetOwner(CWnd::FromHandle(m_hWnd));

    m_list.m_sortedCol = 0;
    m_list.m_sortAscending = false;

    m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    m_list.EnableMultipleSort(true);

    int col = 0;
    m_list.InsertColumn(col++, _T("Line"));
    m_list.InsertColumn(col++, _T("Type"));
    m_list.InsertColumn(col++, _T("User"));
    m_list.InsertColumn(col++, _T("Module"));
    m_list.InsertColumn(col++, _T("Attribute"));
    m_list.InsertColumn(col++, _T("Attr Type"));
    m_list.InsertColumn(col++, _T("Description"));

    for (int i = 0; i < col; ++i)
    {
        m_list.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
    }

    if (!m_listMaster.Create(dwViewStyle, rc, CWnd::FromHandle(m_hWnd), IDC_BOOKMARKS_PLACEHOLDER))
    {
        TRACE0("Failed to create Class View\n");
        return -1;      // fail to create
    }
    col = 0;
    m_listMaster.InsertColumn(col++, _T("Line"));
    m_listMaster.InsertColumn(col++, _T("Type"));
    m_listMaster.InsertColumn(col++, _T("User"));
    m_listMaster.InsertColumn(col++, _T("Module"));
    m_listMaster.InsertColumn(col++, _T("Attribute"));
    m_listMaster.InsertColumn(col++, _T("Attr Type"));
    m_listMaster.InsertColumn(col++, _T("Description"));

    boost::filesystem::path iniPath;
    GetIniPath(iniPath);
    CComPtr<IConfig> iniFile = CreateIConfig(QUERYBUILDER_INI, iniPath);

    m_checkMine = iniFile->Get(GLOBAL_BOOKMARKS_SHOWMINE);
    m_checkTodos = iniFile->Get(GLOBAL_BOOKMARKS_SHOWTODOS);
    m_checkHacks = iniFile->Get(GLOBAL_BOOKMARKS_SHOWHACKS);

    m_list.m_sortedCol = iniFile->Get(GLOBAL_BOOKMARKS_SORTCOLUMN);
    m_list.m_sortAscending = iniFile->Get(GLOBAL_BOOKMARKS_SORTASCENDING);

    DoDataExchange();

    return 0;
}