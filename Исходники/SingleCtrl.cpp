BOOL CSingleCtrl::Check()
{
	CWnd *pPrevWnd = CWnd::GetDesktopWindow()->GetWindow(GW_CHILD);

	::CreateMutex(NULL, TRUE, m_sExeName.GetString());
	if (GetLastError() != ERROR_ALREADY_EXISTS)
		return TRUE;

	while (pPrevWnd)
	{
		if (::GetProp(pPrevWnd->GetSafeHwnd(), m_sExeName.GetString()))
		{
			TRACE("Check: %s found\r\n", m_sExeName.GetString());
			if (pPrevWnd->IsIconic()) {
				TRACE("Check: show it now\r\n");
				pPrevWnd->ShowWindow(SW_RESTORE);
			} else
				pPrevWnd->ShowWindow(SW_NORMAL);
			pPrevWnd->SetForegroundWindow();
			pPrevWnd->GetLastActivePopup()->SetForegroundWindow();
			return FALSE;
		}

		pPrevWnd = pPrevWnd->GetWindow(GW_HWNDNEXT);
	}

	TRACE("Could not find previous instance main window!\r\n");
	return FALSE;
}