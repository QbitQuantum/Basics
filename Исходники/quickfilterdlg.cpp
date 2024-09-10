LRESULT CQuickFilterDlg::OnInitDialog(HWND /*hwndFocus*/, LPARAM /*lp*/)
{
	DlgResize_Init(false);

	m_comboLevel = GetDlgItem(IDC_QF_LEVEL);
	m_editTags = GetDlgItem(IDC_QF_TAGS);
	m_frame = GetTopLevelParent();
	m_tagSelector.Create(m_hWnd);
	m_tagSelector.AssignWindow(m_editTags);

	m_brsHasFilter.CreateSolidBrush(RGB(128,255,128));
	m_brsNormal.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));

	m_internalUpdatingUI = true;
	SyncLevels();
	SyncTags();
	UpdateUI();
	m_internalUpdatingUI = false;
	::PostMessage(GetTopLevelParent(), WM_FILTER_CHANGE, 0, 0);

	m_hook = SetWindowsHookExW(WH_CALLWNDPROC, (HOOKPROC)&CQuickFilterDlg::CallWndProc, NULL, GetCurrentThreadId());

	SetTimer(IDT_REFRESH, 1000, NULL);

	g_dlg = this;
	m_initing = false;
	return FALSE;
}