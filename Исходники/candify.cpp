VOID Candify::RunMessageLoop()
{
	DWORD dwEvent;
	HANDLE hEvents[2];
	BOOL bConnectionState;
    int next_timeout = 0;
	int iPlaylistCount = 0;

	hEvents[0] = m_hSpotifyEvent;
	hEvents[1] = m_hWnd;

	// Handle events
	bConnectionState = FALSE;
    while (TRUE) {
		dwEvent = MsgWaitForMultipleObjectsEx(2, hEvents, FALSE, next_timeout > 0 ? next_timeout : INFINITE, 0xFFFF);

		next_timeout = m_lpSpotify->handleEvents();

		if (!bConnectionState && m_lpSpotify->isConnected()) {
			PostMessage(m_hDialogWnd, WM_DLGLOGGEDIN, 0, 0);
			bConnectionState = TRUE;
		}

		if (m_lpSpotify->hasFailedLogin()) {
			PostMessage(m_hDialogWnd, WM_DLGLOGINFAILED, 0, 0);
		}

		if (m_lpSpotify->hasNewPlaylists()) {
			PostMessage(m_hDialogWnd, WM_DLGUPDATEPLAYLISTS, 0, 0);
		}

		MSG msg;
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){ 
			if (msg.message == WM_QUIT) {
				return;
			}
			if (IsWindow(m_hDialogWnd) && IsDialogMessage(m_hDialogWnd, &msg)) {
				continue;
			}
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
    }
}