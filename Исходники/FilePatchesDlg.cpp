BOOL CFilePatchesDlg::Init(GitPatch * pPatch, CPatchFilesDlgCallBack * pCallBack, CString sPath, CWnd * pParent)
{
	if (!pCallBack || !pPatch)
	{
		m_cFileList.DeleteAllItems();
		return FALSE;
	}
	m_arFileStates.RemoveAll();
	m_pPatch = pPatch;
	m_pCallBack = pCallBack;
	m_sPath = sPath;
	if (m_sPath.IsEmpty())
	{
		CString title(MAKEINTRESOURCE(IDS_DIFF_TITLE));
		SetWindowText(title);
	}
	else
	{
		CRect rect;
		GetClientRect(&rect);
		SetTitleWithPath(rect.Width());
		m_sPath.TrimRight(L'\\');
		m_sPath += L'\\';
	}

	SetWindowTheme(m_cFileList.GetSafeHwnd(), L"Explorer", nullptr);
	m_cFileList.SetExtendedStyle(LVS_EX_INFOTIP | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	m_cFileList.DeleteAllItems();
	int c = m_cFileList.GetHeaderCtrl()->GetItemCount() - 1;
	while (c>=0)
		m_cFileList.DeleteColumn(c--);
	m_cFileList.InsertColumn(0, CString(MAKEINTRESOURCE(IDS_PATH)));
	m_cFileList.InsertColumn(1, CString(MAKEINTRESOURCE(IDS_STATE)));

	m_cFileList.SetRedraw(false);

	for(int i=0; i<m_pPatch->GetNumberOfFiles(); i++)
	{
		CString sFile = CPathUtils::GetFileNameFromPath(m_pPatch->GetStrippedPath(i));

		int state;
		if (m_sPath.IsEmpty())
			state = 0;
		else
		{
			state = m_pPatch->GetFailedHunks(i);
		}
		if (m_pPatch->GetHasConflict(i))
			state = FPDLG_FILESTATE_CONFLICT;
		if (state > 0)
			state = FPDLG_FILESTATE_ERROR;
		m_arFileStates.Add(state);
		CString sFileName = GetFullPath(i);
		sFileName = CPathUtils::GetFileNameFromPath(sFileName);
		m_cFileList.InsertItem(i, sFile, SYS_IMAGE_LIST().GetPathIconIndex(sFileName));
		SetStateText(i, state);
	}
	int mincol = 0;
	int maxcol = m_cFileList.GetHeaderCtrl()->GetItemCount() - 1;
	int col;
	for (col = mincol; col <= maxcol; col++)
	{
		m_cFileList.SetColumnWidth(col,LVSCW_AUTOSIZE_USEHEADER);
	}

	m_cFileList.SetImageList(&SYS_IMAGE_LIST(), LVSIL_SMALL);
	m_cFileList.SetRedraw(true);

	RECT parentrect;
	pParent->GetWindowRect(&parentrect);
	RECT windowrect;
	GetWindowRect(&windowrect);

	int width = windowrect.right - windowrect.left;
	int height = windowrect.bottom - windowrect.top;
	windowrect.right = parentrect.left;
	windowrect.left = windowrect.right - width;
	windowrect.top = parentrect.top;
	windowrect.bottom = windowrect.top + height;
	auto hMonitor = MonitorFromRect(&windowrect, MONITOR_DEFAULTTONULL);
	if (hMonitor)
		SetWindowPos(nullptr, windowrect.left, windowrect.top, width, height, SWP_NOACTIVATE | SWP_NOZORDER);

	m_nWindowHeight = windowrect.bottom - windowrect.top;
	m_pMainFrame = pParent;
	return TRUE;
}