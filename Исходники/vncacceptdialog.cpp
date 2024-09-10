BOOL CALLBACK vncAcceptDialog::vncAcceptDlgProc(HWND hwnd,
											UINT uMsg,
											WPARAM wParam,
											LPARAM lParam) {
	// This is a static method, so we don't know which instantiation we're
	// dealing with. But we can get a pseudo-this from the parameter to
	// WM_INITDIALOG, which we therafter store with the window and retrieve
	// as follows:
	 static HBITMAP hbmBkGnd = NULL;
     vncAcceptDialog *_this = helper::SafeGetWindowUserData<vncAcceptDialog>(hwnd);
	switch (uMsg) {
		// Dialog has just been created
	case WM_INITDIALOG:
		{
			// Save the lParam into our user data so that subsequent calls have
			// access to the parent C++ object
            helper::SafeSetWindowUserData(hwnd, lParam);
            vncAcceptDialog *_this = (vncAcceptDialog *) lParam;

			// Set the IP-address string
			char accept_reject_mesg[512];
			IniFile myIniFile;
			myIniFile.ReadString("admin", "accept_reject_mesg", accept_reject_mesg,512);
			if (strlen(accept_reject_mesg)==0) strcpy(accept_reject_mesg,"WinVNC has received an incoming connection from");
			SetDlgItemText(hwnd, IDC_STATIC_TEXT1, accept_reject_mesg);
			SetDlgItemText(hwnd, IDC_ACCEPT_IP, _this->m_ipAddress);

			{
			char WORKDIR[MAX_PATH];
			char mycommand[MAX_PATH];
			if (GetModuleFileName(NULL, WORKDIR, MAX_PATH))
				{
				char* p = strrchr(WORKDIR, '\\');
				if (p == NULL) return 0;
				*p = '\0';
			}
			strcpy(mycommand,WORKDIR);
			strcat(mycommand,"\\mylogo.bmp");
			hbmBkGnd = (HBITMAP)LoadImage(NULL, mycommand, IMAGE_BITMAP, 0, 0,LR_LOADFROMFILE);
			}
			SendMessage(GetDlgItem(hwnd, IDC_ACCEPTLOGO),STM_SETIMAGE,IMAGE_BITMAP,(LPARAM)(HBITMAP)hbmBkGnd);

			if (SetTimer(hwnd, 1, 1000, NULL) == 0)
			{
				if (_this->m_acceptOnTimeout)
					EndDialog(hwnd, IDACCEPT);
				else
				EndDialog(hwnd, IDREJECT);
			}
			_this->m_timeoutCount = _this->m_timeoutSecs;

			char temp[256];
			if (_this->m_acceptOnTimeout)
				sprintf(temp, "AutoAccept:%u", (_this->m_timeoutCount));
			else
				sprintf(temp, "AutoReject:%u", (_this->m_timeoutCount));
			SetDlgItemText(hwnd, IDC_ACCEPT_TIMEOUT, temp);

			// Attempt to mimic Win98/2000 dialog behaviour
			if ((vncService::IsWinNT() && (vncService::VersionMajor() <= 4)) ||
				(vncService::IsWin95() && (vncService::VersionMinor() == 0)))
			{
				// Perform special hack to display the dialog safely
				if (GetWindowThreadProcessId(GetForegroundWindow(), NULL) != GetCurrentProcessId())
				{
					// We can't set our dialog as foreground if the foreground window
					// doesn't belong to us - it's unsafe!
					SetActiveWindow(hwnd);
					_this->m_foreground_hack = TRUE;
					_this->m_flash_state = FALSE;
				}
			}
			if (!_this->m_foreground_hack) {
				SetForegroundWindow(hwnd);
			}

			// Beep
			MessageBeep(MB_ICONEXCLAMATION);

            // Return success!
			return TRUE;
		}

		// Timer event
	case WM_TIMER:
		if ((_this->m_timeoutCount) == 0)
			{
				if ( _this->m_acceptOnTimeout )
					{
						EndDialog(hwnd, IDACCEPT);
					}
				else
					{
						EndDialog(hwnd, IDREJECT);
					}
			}
		_this->m_timeoutCount--;

		// Flash if necessary
		if (_this->m_foreground_hack) {
			if (GetWindowThreadProcessId(GetForegroundWindow(), NULL) != GetCurrentProcessId())
			{
				_this->m_flash_state = !_this->m_flash_state;
				FlashWindow(hwnd, _this->m_flash_state);
			} else {
				_this->m_foreground_hack = FALSE;
			}
		}

		// Update the displayed count
		char temp[256];
		if ( _this->m_acceptOnTimeout )
			sprintf(temp, "AutoAccept: %u", (_this->m_timeoutCount));
		else
			sprintf(temp, "AutoReject: %u", (_this->m_timeoutCount));
		SetDlgItemText(hwnd, IDC_ACCEPT_TIMEOUT, temp);
		break;

		// Dialog has just received a command
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			// User clicked Accept or pressed return
		case IDACCEPT:
		case IDOK:
			EndDialog(hwnd, IDACCEPT);
			return TRUE;

		case IDREJECT:
		case IDCANCEL:
			EndDialog(hwnd, IDREJECT);
			return TRUE;
		};

		break;

		// Window is being destroyed!  (Should never happen)
	case WM_DESTROY:
		DeleteObject(hbmBkGnd);
		EndDialog(hwnd, IDREJECT);
		return TRUE;
	}
	return 0;
}