/***************************
 * CreateDlg
 ***************************/
SHVBool SHVMainThreadEventDispatcherConsole::CreateDlg()
{
SHVString16C title(SHVString16C::FromWin32(L"SHIVA Console"));
int titleLength = title.GetLength();
HLOCAL templateHandle;
void* dlgTemplate;
char* buffer;
int len = AlignDWord( sizeof(DLGTEMPLATE) + sizeof(WORD) * 4
	+ ((titleLength) ? ((titleLength+1)*2 + sizeof(WORD)) : 0)
	);

	HWND oldWindow = FindWindowW(NULL,title.GetSafeBufferWin32());
	///\todo add code to make sure the window is created with the same application as us
	if (oldWindow) 
	{
		// set focus to foremost child window
		// The "| 0x01" is used to bring any owned windows to the foreground and
		// activate them.
		SetForegroundWindow((HWND)((ULONG) oldWindow | 0x00000001));
		return SHVBool::False;
	}

	templateHandle = LocalAlloc(LHND, len);

	dlgTemplate = LocalLock(templateHandle);
	
	memset(dlgTemplate,0,len);

	LPDLGTEMPLATE temp = (LPDLGTEMPLATE)dlgTemplate;
	temp->x  = 0;
	temp->y  = 0;
	temp->cx = 240;
	temp->cy = 180;
	temp->cdit  = 0; // number of controls
	temp->style = WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_OVERLAPPED;
	temp->dwExtendedStyle = WS_EX_DLGMODALFRAME;

	// skip the dlgtemplate data from buffer
	buffer = (char*)dlgTemplate;
	buffer += sizeof(DLGTEMPLATE);

	// set menu and skip
	*(WORD*)buffer = 0;
	buffer += sizeof(WORD);

	// set class and skip
	*(WORD*)buffer = 0;
	buffer += sizeof(WORD);

	// set title and skip
	if (titleLength)
	{
	WCHAR* titleWChar = (WCHAR*)buffer;

		wcscpy(titleWChar,title.GetSafeBufferWin32());
	}
	else
	{
		*(WORD*)buffer = 0;
		buffer += sizeof(WORD);
	}

#ifdef __SHIVA_POCKETPC
	memset (&s_sai, 0, sizeof(s_sai));
	s_sai.cbSize = sizeof(s_sai);
#endif

	wndConsole = CreateDialogIndirectW(GetModuleHandle(NULL), (LPDLGTEMPLATE)dlgTemplate, NULL, &SHVMainThreadEventDispatcherConsole::WinceDlgProc);

	LocalUnlock(templateHandle);
	LocalFree(templateHandle);


	SetWindowLongPtr(wndConsole,GWLP_USERDATA,(LONG_PTR)this);

#ifdef __SHIVA_POCKETPC
	{
	SHMENUBARINFO mbi;

		memset(&mbi, 0, sizeof(SHMENUBARINFO));
		mbi.cbSize     = sizeof(SHMENUBARINFO);
		mbi.hwndParent = wndConsole;
		mbi.nToolBarId = 100;
		mbi.hInstRes   = GetModuleHandle(NULL);
		mbi.nBmpId     = 0;
		mbi.cBmpImages = 0;
		mbi.dwFlags    = SHCMBF_EMPTYBAR;

		SHCreateMenuBar(&mbi);
		if (mbi.hwndMB)
		{
		RECT menubarRect, winRect;
			GetWindowRect(wndConsole, &winRect);
			GetWindowRect(mbi.hwndMB, &menubarRect);
			winRect.bottom -= (menubarRect.bottom - menubarRect.top);
			MoveWindow(wndConsole, winRect.left, winRect.top, winRect.right, winRect.bottom, FALSE);
		}
	}
#endif

	// font stuff
	{
	HDC dc = ::GetDC(NULL);
	int dcBackup = ::SaveDC(dc);
	SIZE sz;
	LOGFONTW lf;

#if defined(__SHIVA_WINCE) && (_WIN32_WCE < 500)
		///\todo Implement a way to get the real message font from the system on windows CE
		memset(&lf, 0, sizeof(LOGFONT));
		lf.lfWeight = FW_NORMAL;
		lf.lfHeight = 15; // reasonable size
#else
	HFONT stockFont = (HFONT)::GetStockObject(SYSTEM_FONT);

		///\todo Test if this method works for older wince's
	
		// do something!
		SHVVERIFY(::GDIGetObject(stockFont, sizeof(LOGFONT), &lf));
#endif
		lf.lfPitchAndFamily = FIXED_PITCH|FF_MODERN;
		wcscpy(lf.lfFaceName, L"MS Shell Dlg");
		Font = ::CreateFontIndirect(&lf);
		::SendMessage(wndConsole,WM_SETFONT,(WPARAM)Font,0);

		::SelectObject(dc,Font);
		
		SHVVERIFY(::GetTextExtentPointW(dc,L" ",1,&sz));
		fontHeight = sz.cy + 2;
		fontWidth = sz.cx;

		::RestoreDC(dc,dcBackup);
		::ReleaseDC(NULL,dc);

	}

	// edit box
	edtConsole = ::CreateWindowExW(0,L"EDIT", L"", ES_LEFT|ES_AUTOHSCROLL|WS_TABSTOP|WS_CHILD|WS_VISIBLE,
			0, 0, 0, fontHeight, wndConsole, NULL, GetModuleHandle(NULL), NULL);
	edtProc = (WNDPROC)GetWindowLongPtr(edtConsole,GWLP_WNDPROC);
	SetWindowLongPtr(edtConsole,GWLP_WNDPROC,(LONG_PTR)&SHVMainThreadEventDispatcherConsole::WinceEditProc);

	::SendMessage(edtConsole,WM_SETFONT,(WPARAM)Font,0);

	Resize();
	::ShowWindow(wndConsole,SW_SHOW);
	::UpdateWindow(wndConsole);

	return SHVBool::True;
}