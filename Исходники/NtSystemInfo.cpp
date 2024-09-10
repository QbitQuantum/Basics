BOOL CALLBACK SystemWindowInformation::EnumerateWindows( HWND hwnd, LPARAM lParam )
{
	SystemWindowInformation* _this = (SystemWindowInformation*)lParam;
	WINDOW_INFO wi;

	wi.hWnd = hwnd;
	GetWindowThreadProcessId(hwnd, &wi.ProcessId ) ;

	// Filtering by process ID
	if ( _this->m_processId == -1 || _this->m_processId == wi.ProcessId )
	{
		GetWindowText( hwnd, wi.Caption, MaxCaptionSize );

		// That is we are looking for
		if ( GetLastError() == 0 )
			_this->m_WindowInfos.AddTail( wi );
	}

	return TRUE;
};