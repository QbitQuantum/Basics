HWND CFifa2AutoLauncher::StartLauncherWindow()
{

	if(FALSE == StartLauncherProcess()) {
		return NULL;
	}

	m_hMainWindow = NULL;
	int iCount = 0;

	while (iCount < m_iTimeoutCount && UNKNOWN == m_state) {

		EnumWindows(CFifa2AutoLauncher::EnumWindowsProc, (LPARAM)this);
		::Sleep(m_iTimeoutSeconds);

	}

	return m_hMainWindow;
}