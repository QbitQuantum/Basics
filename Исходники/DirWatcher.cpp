BOOL CDirWatcher::StartWatch(HWND hNotifyWnd, LPCTSTR lpszPath)
{
	m_hNotifyWnd = hNotifyWnd;
	m_strPath = lpszPath;

	m_hFileHandle = CreateFile(m_strPath, 
		FILE_LIST_DIRECTORY,
		FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS|FILE_FLAG_OVERLAPPED,
		NULL); 
	if (m_hFileHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	m_hCompPort = CreateIoCompletionPort(m_hFileHandle, m_hCompPort, DWORD(this), 0);

	memset(&m_overlapped, 0, sizeof(OVERLAPPED));
	ReadDirectoryChangesW(m_hFileHandle, m_lpBuffer, 4096,
			FALSE, FILE_NOTIFY_CHANGE_FILE_NAME, &m_dwSize, &m_overlapped, NULL);
	
	m_hThread = CreateThread(NULL, 0, _WatchProc, (void*)this, 0, &m_dwThreadID);

	return TRUE;
}