bool CWSWindow::GetWindowFromProcID()
{
	m_hWnd = NULL;
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, m_dwProcID);
	if (hProc == NULL)
	{
		LOG_WS_ERROR(_T("OpenProcess failed"));
		return false;
	}
	WaitForInputIdle(hProc, INFINITE);
	EnumWindows(&EnumWindowsProc, reinterpret_cast<LPARAM>(this));

	return (m_hWnd != NULL);
}