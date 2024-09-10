// この関数もMtlWin.hの中で浮いていたので隔離した
// もしかしたら作ったの自分かも
HWND _CreateSimpleReBarCtrl(HWND hWndParent, DWORD dwStyle, UINT nID)
{
	// Ensure style combinations for proper rebar painting
	if (dwStyle & CCS_NODIVIDER && dwStyle & WS_BORDER)
		dwStyle &= ~WS_BORDER;
	else if ( !(dwStyle & WS_BORDER) && !(dwStyle & CCS_NODIVIDER) )
		dwStyle |= CCS_NODIVIDER;

	// Create rebar window
	HWND	  hWndReBar = ::CreateWindowEx(
								0,
								REBARCLASSNAME,
								NULL,
								dwStyle,
								0,
								0,
								100,
								100,
								hWndParent,
								(HMENU) LongToHandle(nID),
								_Module.GetModuleInstance(),
								NULL );

	if (hWndReBar == NULL) {
		ATLTRACE2( atlTraceUI, 0, _T("Failed to create rebar.\n") );
		return NULL;
	}

	// Initialize and send the REBARINFO structure
	REBARINFO rbi;
	rbi.cbSize = sizeof (REBARINFO);
	rbi.fMask  = 0;

	if ( !::SendMessage(hWndReBar, RB_SETBARINFO, 0, (LPARAM) &rbi) ) {
		ATLTRACE2( atlTraceUI, 0, _T("Failed to initialize rebar.\n") );
		::DestroyWindow(hWndReBar);
		return NULL;
	}

	return hWndReBar;
}