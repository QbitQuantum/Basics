    // the unavoidable A/W versions. Don't forget to keep them in sync!
    bool trayMessageA( DWORD msg )
    {
		NOTIFYICONDATAA tnd;
		ZeroMemory( &tnd, sizeof(NOTIFYICONDATAA) );
		tnd.cbSize		= sizeof(NOTIFYICONDATAA);
 		tnd.hWnd		= winId();
		tnd.uID = 1; // michalj

 		if ( msg != NIM_DELETE ) {
 			tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
			tnd.uCallbackMessage= WM_NOTIFYICON;
 			tnd.hIcon		= hIcon;
 			if ( !iconObject->toolTip().isNull() ) {
				// Tip is limited to 63 + NULL; lstrcpyn appends a NULL terminator.
				QString tip = iconObject->toolTip().left( 63 ) + QChar();
				lstrcpynA(tnd.szTip, (const char*)tip.local8Bit(), QMIN( tip.length()+1, 64 ) );
 			}
 		}

		return Shell_NotifyIconA(msg, &tnd);
    }