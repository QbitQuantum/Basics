LRESULT CDlgAddItem::OnCaptureLBtnUp( WPARAM wParam, LPARAM lParam )
{
	// 根据坐标获取窗体 [7/10/2014 Brilliance]
	POINT pot;
	GetCursorPos(&pot);
	CWnd* pWnd = WindowFromPoint(pot);
	// 获取标题 [7/10/2014 Brilliance]
	pWnd->GetWindowText(m_csTitle);	
	// 获取类名 [7/10/2014 Brilliance]
	TCHAR sClass[128] = {0};
	GetClassName(pWnd->GetSafeHwnd(), sClass, sizeof(sClass)/sizeof(TCHAR));
	m_csClass = sClass;
	// 获取大小 [7/10/2014 Brilliance]
	CRect rt;
	pWnd->GetClientRect(&rt);
	ClientToScreen(&rt);
	//m_csRect.Format(_T("(%d,%d),%d*%d"), rt.left, rt.top, rt.Width(), rt.Height());
	m_csRect.Format(_T("%d,%d"), rt.Width(), rt.Height());
	// 获取进程ID [7/10/2014 Brilliance]
	DWORD dwProcessId = 0;
	GetWindowThreadProcessId(pWnd->GetSafeHwnd(), &dwProcessId);
	m_csProcessId.Format(_T("%d"), dwProcessId);
	// 获取进程名 [7/10/2014 Brilliance]
	HANDLE hProcess =  OpenProcess(/*PROCESS_ALL_ACCESS*/PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, dwProcessId);
	TCHAR sProcessName[MAX_PATH] = {0};
	TCHAR sProcessPath[MAX_PATH] = {0};
	if (NULL != hProcess )
	{
		HMODULE hMod;
		DWORD cbNeeded;
		if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
		{
			GetModuleBaseName( hProcess, hMod, sProcessName, sizeof(sProcessName)/sizeof(TCHAR) );
			GetModuleFileName(hMod, sProcessPath, sizeof(sProcessPath)/sizeof(TCHAR));
		}
	}	
	m_csProcessName = sProcessName;
	m_csProcessPath = sProcessPath;
	// 获取线程ID [7/10/2014 Brilliance]
// 	DWORD dwThreadId = 0;
// 	dwThreadId = GetThreadId(pWnd->m_hWnd);
	
	CString csText;
	csText.Format(_T("左键弹起,x=%d,y=%d,Title:%s,Class:%s\r\n"), pot.x, pot.y, m_csTitle, m_csClass);
	TRACE(csText);
	//m_csOutput = m_csOutput + csText;
	//UpdateData(FALSE);

	UpdateData(FALSE);
	return 0;
}