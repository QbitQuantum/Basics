BOOL CALLBACK
vncPropertiesPoll::DialogProcPoll(HWND hwnd,
						  UINT uMsg,
						  WPARAM wParam,
						  LPARAM lParam )
{
	// We use the dialog-box's USERDATA to store a _this pointer
	// This is set only once WM_INITDIALOG has been recieved, though!
    vncPropertiesPoll *_this = helper::SafeGetWindowUserData<vncPropertiesPoll>(hwnd);

	switch (uMsg)
	{

	case WM_INITDIALOG:
		{
			// Retrieve the Dialog box parameter and use it as a pointer
			// to the calling vncPropertiesPoll object
            helper::SafeSetWindowUserData(hwnd, lParam);

			_this = (vncPropertiesPoll *) lParam;
			_this->m_dlgvisible = TRUE;

			if (_this->m_fUseRegistry)
			{
				_this->Load(_this->m_usersettings);

				// Set the dialog box's title to indicate which Properties we're editting
				if (_this->m_usersettings) {
					SetWindowText(hwnd, sz_ID_CURRENT_USER_PROP);
				} else {
					SetWindowText(hwnd, sz_ID_DEFAULT_SYST_PROP);
				}
			}
			else
			{
				//LoadFromIniFile();
			}

			// Modif sf@2002

		   SetDlgItemInt(hwnd, IDC_MAXCPU, _this->m_server->MaxCpu(), false);

		   HWND hTurboMode = GetDlgItem(hwnd, IDC_TURBOMODE);
           SendMessage(hTurboMode, BM_SETCHECK, _this->m_server->TurboMode(), 0);

			// Set the polling options
			HWND hDriver = GetDlgItem(hwnd, IDC_DRIVER);
			SendMessage(hDriver,
				BM_SETCHECK,
				_this->m_server->Driver(),0);

			HWND hHook = GetDlgItem(hwnd, IDC_HOOK);
			SendMessage(hHook,
				BM_SETCHECK,
				_this->m_server->Hook(),
				0);

			HWND hPollFullScreen = GetDlgItem(hwnd, IDC_POLL_FULLSCREEN);
			SendMessage(hPollFullScreen,
				BM_SETCHECK,
				_this->m_server->PollFullScreen(),
				0);

			HWND hPollForeground = GetDlgItem(hwnd, IDC_POLL_FOREGROUND);
			SendMessage(hPollForeground,
				BM_SETCHECK,
				_this->m_server->PollForeground(),
				0);

			HWND hPollUnderCursor = GetDlgItem(hwnd, IDC_POLL_UNDER_CURSOR);
			SendMessage(hPollUnderCursor,
				BM_SETCHECK,
				_this->m_server->PollUnderCursor(),
				0);

			HWND hPollConsoleOnly = GetDlgItem(hwnd, IDC_CONSOLE_ONLY);
			SendMessage(hPollConsoleOnly,
				BM_SETCHECK,
				_this->m_server->PollConsoleOnly(),
				0);
			EnableWindow(hPollConsoleOnly,
				_this->m_server->PollUnderCursor() || _this->m_server->PollForeground()
				);

			HWND hPollOnEventOnly = GetDlgItem(hwnd, IDC_ONEVENT_ONLY);
			SendMessage(hPollOnEventOnly,
				BM_SETCHECK,
				_this->m_server->PollOnEventOnly(),
				0);
			EnableWindow(hPollOnEventOnly,
				_this->m_server->PollUnderCursor() || _this->m_server->PollForeground()
				);

			// [v1.0.2-jp2 fix-->]
			HWND hSingleWindow = GetDlgItem(hwnd, IDC_SINGLE_WINDOW);
			SendMessage(hSingleWindow, BM_SETCHECK, _this->m_server->SingleWindow(), 0);

			HWND hWindowName = GetDlgItem(hwnd, IDC_NAME_APPLI);
			if ( _this->m_server->GetWindowName() != NULL){
			   SetDlgItemText(hwnd, IDC_NAME_APPLI,_this->m_server->GetWindowName());
			}
			EnableWindow(hWindowName, _this->m_server->SingleWindow());
			// [<--v1.0.2-jp2 fix]

			SetForegroundWindow(hwnd);

			return FALSE; // Because we've set the focus
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDOK:
		case IDC_APPLY:
			{
				

				int maxcpu = GetDlgItemInt(hwnd, IDC_MAXCPU, NULL, FALSE);
				_this->m_server->MaxCpu(maxcpu);

				// Modif sf@2002
				HWND hTurboMode = GetDlgItem(hwnd, IDC_TURBOMODE);
				_this->m_server->TurboMode(SendMessage(hTurboMode, BM_GETCHECK, 0, 0) == BST_CHECKED);

				// Handle the polling stuff
				HWND hDriver = GetDlgItem(hwnd, IDC_DRIVER);
				bool result=(SendMessage(hDriver, BM_GETCHECK, 0, 0) == BST_CHECKED);
				if (result)
				{
					_this->m_server->Driver(CheckVideoDriver(0));
				}
				else _this->m_server->Driver(false);
				HWND hHook = GetDlgItem(hwnd, IDC_HOOK);
				_this->m_server->Hook(
					SendMessage(hHook, BM_GETCHECK, 0, 0) == BST_CHECKED
					);
				HWND hPollFullScreen = GetDlgItem(hwnd, IDC_POLL_FULLSCREEN);
				_this->m_server->PollFullScreen(
					SendMessage(hPollFullScreen, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				HWND hPollForeground = GetDlgItem(hwnd, IDC_POLL_FOREGROUND);
				_this->m_server->PollForeground(
					SendMessage(hPollForeground, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				HWND hPollUnderCursor = GetDlgItem(hwnd, IDC_POLL_UNDER_CURSOR);
				_this->m_server->PollUnderCursor(
					SendMessage(hPollUnderCursor, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				HWND hPollConsoleOnly = GetDlgItem(hwnd, IDC_CONSOLE_ONLY);
				_this->m_server->PollConsoleOnly(
					SendMessage(hPollConsoleOnly, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				HWND hPollOnEventOnly = GetDlgItem(hwnd, IDC_ONEVENT_ONLY);
				_this->m_server->PollOnEventOnly(
					SendMessage(hPollOnEventOnly, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				// [v1.0.2-jp2 fix-->] Move to vncpropertiesPoll.cpp
				HWND hSingleWindow = GetDlgItem(hwnd, IDC_SINGLE_WINDOW);
				_this->m_server->SingleWindow(SendMessage(hSingleWindow, BM_GETCHECK, 0, 0) == BST_CHECKED);

				char szName[32];
				if (GetDlgItemText(hwnd, IDC_NAME_APPLI, (LPSTR) szName, 32) == 0){
					vnclog.Print(LL_INTINFO,VNCLOG("Error while reading Window Name %d \n"), GetLastError());
				}
				else{
					_this->m_server->SetSingleWindowName(szName);
				}
				// [<--v1.0.2-jp2 fix] Move to vncpropertiesPoll.cpp

				// Save the settings
				if (_this->m_fUseRegistry)
					_this->Save();
				else
					_this->SaveToIniFile();

				// Was ok pressed?
				if (LOWORD(wParam) == IDOK)
				{
					// Yes, so close the dialog
					vnclog.Print(LL_INTINFO, VNCLOG("enddialog (OK)\n"));

					_this->m_returncode_valid = TRUE;

					EndDialog(hwnd, IDOK);
					_this->m_dlgvisible = FALSE;
				}

				_this->m_server->SetHookings();

				return TRUE;
			}

		// [v1.0.2-jp2 fix-->] Move to vncpropertiesPoll.cpp
		 case IDC_SINGLE_WINDOW:
			 {
				 HWND hSingleWindow = GetDlgItem(hwnd, IDC_SINGLE_WINDOW);
				 BOOL fSingleWindow = (SendMessage(hSingleWindow, BM_GETCHECK,0, 0) == BST_CHECKED);
				 HWND hWindowName   = GetDlgItem(hwnd, IDC_NAME_APPLI);
				 EnableWindow(hWindowName, fSingleWindow);
			 }
			 return TRUE;
		// [<--v1.0.2-jp2 fix] Move to vncpropertiesPoll.cpp

		 case IDCANCEL:
			vnclog.Print(LL_INTINFO, VNCLOG("enddialog (CANCEL)\n"));

			_this->m_returncode_valid = TRUE;

			EndDialog(hwnd, IDCANCEL);
			_this->m_dlgvisible = FALSE;
			return TRUE;
		

		case IDC_POLL_FOREGROUND:
		case IDC_POLL_UNDER_CURSOR:
			// User has clicked on one of the polling mode buttons
			// affected by the pollconsole and pollonevent options
			{
				// Get the poll-mode buttons
				HWND hPollForeground = GetDlgItem(hwnd, IDC_POLL_FOREGROUND);
				HWND hPollUnderCursor = GetDlgItem(hwnd, IDC_POLL_UNDER_CURSOR);

				// Determine whether to enable the modifier options
				BOOL enabled = (SendMessage(hPollForeground, BM_GETCHECK, 0, 0) == BST_CHECKED) ||
					(SendMessage(hPollUnderCursor, BM_GETCHECK, 0, 0) == BST_CHECKED);

				HWND hPollConsoleOnly = GetDlgItem(hwnd, IDC_CONSOLE_ONLY);
				EnableWindow(hPollConsoleOnly, enabled);

				HWND hPollOnEventOnly = GetDlgItem(hwnd, IDC_ONEVENT_ONLY);
				EnableWindow(hPollOnEventOnly, enabled);
			}
			return TRUE;

		
		case IDC_CHECKDRIVER:
			{
				CheckVideoDriver(1);
			}
			return TRUE;
		



		}
		break;
	}
	return 0;
}