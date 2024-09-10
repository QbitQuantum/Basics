void CSearchDlg::OnClose()
{
	SaveBarState(SEARCH_PARAMS_PROFILE);
	// MORPH leuk_he:run as ntservice v1.. workarround a mfc bug
	if (RunningAsService()) {
		DWORD dwProcessId;
		DWORD dwThreadId= GetWindowThreadProcessId(m_hWnd,&dwProcessId);
		EnumThreadWindows(dwThreadId, EnumProc,(LPARAM) dwThreadId);
	}
	// MORPH leuk_he:run as ntservice v1..

	CFrameWnd::OnClose();
}