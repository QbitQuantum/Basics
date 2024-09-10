BOOL CGitProgressDlg::OnInitDialog()
{
	__super::OnInitDialog();

	// Let the TaskbarButtonCreated message through the UIPI filter. If we don't
	// do this, Explorer would be unable to send that message to our window if we
	// were running elevated. It's OK to make the call all the time, since if we're
	// not elevated, this is a no-op.
	CHANGEFILTERSTRUCT cfs = { sizeof(CHANGEFILTERSTRUCT) };
	typedef BOOL STDAPICALLTYPE ChangeWindowMessageFilterExDFN(HWND hWnd, UINT message, DWORD action, PCHANGEFILTERSTRUCT pChangeFilterStruct);
	CAutoLibrary hUser = AtlLoadSystemLibraryUsingFullPath(_T("user32.dll"));
	if (hUser)
	{
		ChangeWindowMessageFilterExDFN *pfnChangeWindowMessageFilterEx = (ChangeWindowMessageFilterExDFN*)GetProcAddress(hUser, "ChangeWindowMessageFilterEx");
		if (pfnChangeWindowMessageFilterEx)
		{
			pfnChangeWindowMessageFilterEx(m_hWnd, WM_TASKBARBTNCREATED, MSGFLT_ALLOW, &cfs);
		}
	}
	m_ProgList.m_pTaskbarList.Release();
	if (FAILED(m_ProgList.m_pTaskbarList.CoCreateInstance(CLSID_TaskbarList)))
		m_ProgList.m_pTaskbarList = nullptr;

	UpdateData(FALSE);

	AddAnchor(IDC_SVNPROGRESS, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_TITLE_ANIMATE, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PROGRESSLABEL, BOTTOM_LEFT, BOTTOM_CENTER);
	AddAnchor(IDC_PROGRESSBAR, BOTTOM_CENTER, BOTTOM_RIGHT);
	AddAnchor(IDC_INFOTEXT, BOTTOM_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_NONINTERACTIVE, BOTTOM_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDCANCEL, BOTTOM_RIGHT);
	AddAnchor(IDOK, BOTTOM_RIGHT);
	AddAnchor(IDC_LOGBUTTON, BOTTOM_RIGHT);
	//SetPromptParentWindow(this->m_hWnd);

	m_Animate.Open(IDR_DOWNLOAD);
	m_ProgList.m_pAnimate = &m_Animate;
	m_ProgList.m_pProgControl = &m_ProgCtrl;
	m_ProgList.m_pProgressLabelCtrl = &m_ProgLableCtrl;
	m_ProgList.m_pInfoCtrl = &m_InfoCtrl;
	m_ProgList.m_pPostWnd = this;
	m_ProgList.m_bSetTitle = true;

	if (hWndExplorer)
		CenterWindow(CWnd::FromHandle(hWndExplorer));
	EnableSaveRestore(_T("GITProgressDlg"));

	m_background_brush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
	m_ProgList.Init();

	return TRUE;
}