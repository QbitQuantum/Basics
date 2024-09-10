unsigned int WINAPI DirChangeNotifier::task() {
	m_hChangeDir = FindFirstChangeNotification(
		m_path,                        // directory to watch
		FALSE,                         // do not watch subtree
		FILE_NOTIFY_CHANGE_FILE_NAME); // watch for file names

	if (m_hChangeDir == INVALID_HANDLE_VALUE) {
		OutputDebugStringW(L"ERROR: FindFirstChangeNotification");
		_endthreadex(0);
		return 0;
	}

	while (TRUE) {
		DWORD dwWaitStatus = WaitForSingleObject(m_hChangeDir, INFINITE);
		if (dwWaitStatus == WAIT_OBJECT_0) {
			if (m_fTerminate) {
				break;
			}
			// A file was created, renamed, or deleted in the directory.
			// Refresh this directory and restart the notification.
			if (isChecked()) {
				::Info.AdvControl(&MainGuid, ACTL_SYNCHRO, 0, (void*)m_hPanel);
			}

			if (!FindNextChangeNotification(m_hChangeDir)) {
				OutputDebugStringW(L"ERROR: FindNextChangeNotification");
				break;
			}
		}
		else {
			OutputDebugStringW(L"WaitForSingleObject");
			break;
		}
	}
	if (!m_fTerminate)
		FindCloseChangeNotification(m_hChangeDir);
	m_hChangeDir = INVALID_HANDLE_VALUE;
	_endthreadex(0);
	return 0;
}