BOOL CProgressDlg::OnInitDialog()
{
	CResizableStandAloneDialog::OnInitDialog();

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
	m_pTaskbarList.Release();
	if (FAILED(m_pTaskbarList.CoCreateInstance(CLSID_TaskbarList)))
		m_pTaskbarList = nullptr;

	AddAnchor(IDC_TITLE_ANIMATE, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_RUN_PROGRESS, TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_LOG, TOP_LEFT,BOTTOM_RIGHT);

	AddAnchor(IDOK,BOTTOM_RIGHT);
	AddAnchor(IDCANCEL,BOTTOM_RIGHT);
	AddAnchor(IDC_PROGRESS_BUTTON1,BOTTOM_LEFT);
	AddAnchor(IDC_CURRENT,TOP_LEFT);

	this->GetDlgItem(IDC_PROGRESS_BUTTON1)->ShowWindow(SW_HIDE);
	m_Animate.Open(IDR_DOWNLOAD);

	CFont m_logFont;
	CAppUtils::CreateFontForLogs(m_logFont);
	//GetDlgItem(IDC_CMD_LOG)->SetFont(&m_logFont);
	m_Log.SetFont(&m_logFont);

	CString InitialText;
	if ( !m_PreText.IsEmpty() )
	{
		InitialText = m_PreText + _T("\r\n");
	}
#if 0
	if (m_bShowCommand && (!m_GitCmd.IsEmpty() ))
	{
		InitialText += m_GitCmd+_T("\r\n\r\n");
	}
#endif
	m_Log.SetWindowTextW(InitialText);
	m_CurrentWork.SetWindowTextW(_T(""));

	if (!m_PreFailText.IsEmpty())
		InsertColorText(this->m_Log, m_PreFailText, RGB(255, 0, 0));

	EnableSaveRestore(_T("ProgressDlg"));

	m_pThread = AfxBeginThread(ProgressThreadEntry, this, THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);
	if (!m_pThread)
	{
		CMessageBox::Show(this->m_hWnd, IDS_ERR_THREADSTARTFAILED, IDS_APPNAME, MB_OK | MB_ICONERROR);
		DialogEnableWindow(IDCANCEL, TRUE);
	}
	else
	{
		m_pThread->m_bAutoDelete = FALSE;
		m_pThread->ResumeThread();
	}

	CString sWindowTitle;
	GetWindowText(sWindowTitle);
	CAppUtils::SetWindowTitle(m_hWnd, m_Git->m_CurrentDir, sWindowTitle);

	// Make sure this dialog is shown in foreground (see issue #1536)
	SetForegroundWindow();

	return TRUE;
}