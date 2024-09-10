BOOL CALLBACK
vncProperties::DialogProc(HWND hwnd,
						  UINT uMsg,
						  WPARAM wParam,
						  LPARAM lParam )
{
	// We use the dialog-box's USERDATA to store a _this pointer
	// This is set only once WM_INITDIALOG has been recieved, though!
	vncProperties *_this = (vncProperties *) GetWindowLong(hwnd, GWL_USERDATA);

	switch (uMsg)
	{

	case WM_INITDIALOG:
		{
			// Retrieve the Dialog box parameter and use it as a pointer
			// to the calling vncProperties object
			SetWindowLong(hwnd, GWL_USERDATA, lParam);
			_this = (vncProperties *) lParam;
			_this->m_dlgvisible = TRUE;

			// Set the dialog box's title to indicate which Properties we're editting
			if (_this->m_usersettings) {
				SetWindowText(hwnd, "WinVNC: Current User Properties");
			} else {
				SetWindowText(hwnd, "WinVNC: Default Local System Properties");
			}

			// Initialise the properties controls
			HWND hConnectSock = GetDlgItem(hwnd, IDC_CONNECT_SOCK);
			SendMessage(hConnectSock,
				BM_SETCHECK,
				_this->m_server->SockConnected(),
				0);

			HWND hConnectHTTP = GetDlgItem(hwnd, IDC_CONNECT_HTTP);
			SendMessage(hConnectHTTP,
				BM_SETCHECK,
				_this->m_server->HTTPConnectEnabled(),
				0);

			HWND hConnectCorba = GetDlgItem(hwnd, IDC_CONNECT_CORBA);
			SendMessage(hConnectCorba,
				BM_SETCHECK,
				_this->m_server->CORBAConnected(),
				0);
#if(defined(_CORBA))
			ShowWindow(hConnectCorba, SW_SHOW);
#else
			ShowWindow(hConnectCorba, SW_HIDE);
#endif

			HWND hAutoPortNo = GetDlgItem(hwnd, IDC_AUTO_DISPLAY_NO);
			SendMessage(hAutoPortNo,
				BM_SETCHECK,
				_this->m_server->AutoPortSelect(),
				0);
			EnableWindow(hAutoPortNo, _this->m_server->SockConnected());

			HWND hPortNo = GetDlgItem(hwnd, IDC_PORTNO);
			SetDlgItemInt(hwnd, IDC_PORTNO, PORT_TO_DISPLAY(_this->m_server->GetPort()), FALSE);
			EnableWindow(hPortNo, _this->m_server->SockConnected()
				&& !_this->m_server->AutoPortSelect());

			HWND hPassword = GetDlgItem(hwnd, IDC_PASSWORD);
			EnableWindow(hPassword, _this->m_server->SockConnected());

			// Get the password
			{
				char plain[MAXPWLEN+1];
	      _this->m_server->GetPassword(plain);
	      {
	        vncPasswd::ToText plainpwd(plain);
          int length = strlen(plainpwd);
				  for (int i=0; i<length; i++) {
					  plain[i] = i+1;
				  }
				  plain[length]=0;
        }
			  SetDlgItemText(hwnd, IDC_PASSWORD, (const char *) plain);
			}

			// Remote input settings
			HWND hEnableRemoteInputs = GetDlgItem(hwnd, IDC_DISABLE_INPUTS);
			SendMessage(hEnableRemoteInputs,
				BM_SETCHECK,
				!(_this->m_server->RemoteInputsEnabled()),
				0);

			// Local input settings
			HWND hDisableLocalInputs = GetDlgItem(hwnd, IDC_DISABLE_LOCAL_INPUTS);
			SendMessage(hDisableLocalInputs,
				BM_SETCHECK,
				_this->m_server->LocalInputsDisabled(),
				0);

			// Remove the wallpaper
			HWND hRemoveWallpaper = GetDlgItem(hwnd, IDC_REMOVE_WALLPAPER);
			SendMessage(hRemoveWallpaper,
				BM_SETCHECK,
				_this->m_server->RemoveWallpaperEnabled(),
				0);

			// Lock settings
			HWND hLockSetting;
			switch (_this->m_server->LockSettings()) {
			case 1:
				hLockSetting = GetDlgItem(hwnd, IDC_LOCKSETTING_LOCK);
				break;
			case 2:
				hLockSetting = GetDlgItem(hwnd, IDC_LOCKSETTING_LOGOFF);
				break;
			default:
				hLockSetting = GetDlgItem(hwnd, IDC_LOCKSETTING_NOTHING);
			};
			SendMessage(hLockSetting,
				BM_SETCHECK,
				TRUE,
				0);

			// Set the polling options
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

			SetForegroundWindow(hwnd);

			return TRUE;
		}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case IDOK:
		case IDC_APPLY:
			{
				// Save the password
				char passwd[MAXPWLEN+1];
				if (GetDlgItemText(hwnd, IDC_PASSWORD, (LPSTR) &passwd, MAXPWLEN+1) == 0)
				{
				    vncPasswd::FromClear crypt;
				    _this->m_server->SetPassword(crypt);
				}
				else
				{
				  char current_pwd[MAXPWLEN+1];
	        _this->m_server->GetPassword(current_pwd);
          vncPasswd::ToText current(current_pwd);

				  BOOL password_changed = FALSE;
				  for (int i=0; i<MAXPWLEN; i++) {
            if (passwd[i] != i+1) password_changed = TRUE;
            if ((passwd[i] >= 1) && (passwd[i] <= MAXPWLEN)) passwd[i] = current[passwd[i]-1];
				  }
				  if (password_changed) {
					  vnclog.Print(LL_INTINFO, VNCLOG("password changed\n"));
					  vncPasswd::FromText crypt(passwd);
					  _this->m_server->SetPassword(crypt);
				  } 
				}

				// Save the new settings to the server
				HWND hAutoDisplayNo = GetDlgItem(hwnd, IDC_AUTO_DISPLAY_NO);
				_this->m_server->SetAutoPortSelect(
					SendMessage(hAutoDisplayNo, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				// only save the port number if we're not auto selecting!
				if (!_this->m_server->AutoPortSelect())
				{
					BOOL success;
					UINT portno = GetDlgItemInt(hwnd, IDC_PORTNO, &success, TRUE);
					if (success)
						_this->m_server->SetPort(DISPLAY_TO_PORT(portno));
				}
				
				HWND hConnectSock = GetDlgItem(hwnd, IDC_CONNECT_SOCK);
				_this->m_server->SockConnect(
					SendMessage(hConnectSock, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				HWND hConnectHTTP = GetDlgItem(hwnd, IDC_CONNECT_HTTP);
				_this->m_server->EnableHTTPConnect(
					SendMessage(hConnectHTTP, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				HWND hConnectCorba = GetDlgItem(hwnd, IDC_CONNECT_CORBA);
				_this->m_server->CORBAConnect(
					SendMessage(hConnectCorba, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				// Remote input stuff
				HWND hEnableRemoteInputs = GetDlgItem(hwnd, IDC_DISABLE_INPUTS);
				_this->m_server->EnableRemoteInputs(
					SendMessage(hEnableRemoteInputs, BM_GETCHECK, 0, 0) != BST_CHECKED
					);

				// Local input stuff
				HWND hDisableLocalInputs = GetDlgItem(hwnd, IDC_DISABLE_LOCAL_INPUTS);
				_this->m_server->DisableLocalInputs(
					SendMessage(hDisableLocalInputs, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				// Wallpaper handling
				HWND hRemoveWallpaper = GetDlgItem(hwnd, IDC_REMOVE_WALLPAPER);
				_this->m_server->EnableRemoveWallpaper(
					SendMessage(hRemoveWallpaper, BM_GETCHECK, 0, 0) == BST_CHECKED
					);

				// Lock settings handling
				if (SendMessage(GetDlgItem(hwnd, IDC_LOCKSETTING_LOCK), BM_GETCHECK, 0, 0)
					== BST_CHECKED) {
					_this->m_server->SetLockSettings(1);
				} else if (SendMessage(GetDlgItem(hwnd, IDC_LOCKSETTING_LOGOFF), BM_GETCHECK, 0, 0)
					== BST_CHECKED) {
					_this->m_server->SetLockSettings(2);
				} else {
					_this->m_server->SetLockSettings(0);
				}

				// Handle the polling stuff
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

				// And to the registry
				_this->Save();

				// Was ok pressed?
				if (LOWORD(wParam) == IDOK)
				{
					// Yes, so close the dialog
					vnclog.Print(LL_INTINFO, VNCLOG("enddialog (OK)\n"));

					_this->m_returncode_valid = TRUE;

					EndDialog(hwnd, IDOK);
					_this->m_dlgvisible = FALSE;
				}

				return TRUE;
			}

		case IDCANCEL:
			vnclog.Print(LL_INTINFO, VNCLOG("enddialog (CANCEL)\n"));

			_this->m_returncode_valid = TRUE;

			EndDialog(hwnd, IDCANCEL);
			_this->m_dlgvisible = FALSE;
			return TRUE;

		case IDC_CONNECT_SOCK:
			// The user has clicked on the socket connect tickbox
			{
				HWND hConnectSock = GetDlgItem(hwnd, IDC_CONNECT_SOCK);
				BOOL connectsockon =
					(SendMessage(hConnectSock, BM_GETCHECK, 0, 0) == BST_CHECKED);

				HWND hAutoDisplayNo = GetDlgItem(hwnd, IDC_AUTO_DISPLAY_NO);
				EnableWindow(hAutoDisplayNo, connectsockon);
			
				HWND hPortNo = GetDlgItem(hwnd, IDC_PORTNO);
				EnableWindow(hPortNo, connectsockon
					&& (SendMessage(hAutoDisplayNo, BM_GETCHECK, 0, 0) != BST_CHECKED));
			
				HWND hPassword = GetDlgItem(hwnd, IDC_PASSWORD);
				EnableWindow(hPassword, connectsockon);
			}
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

		case IDC_AUTO_DISPLAY_NO:
			// User has toggled the Auto Port Select feature.
			// If this is in use, then we don't allow the Display number field
			// to be modified!
			{
				// Get the auto select button
				HWND hPortNoAuto = GetDlgItem(hwnd, IDC_AUTO_DISPLAY_NO);

				// Should the portno field be modifiable?
				BOOL enable = SendMessage(hPortNoAuto, BM_GETCHECK, 0, 0) != BST_CHECKED;

				// Set the state
				HWND hPortNo = GetDlgItem(hwnd, IDC_PORTNO);
				EnableWindow(hPortNo, enable);
			}
			return TRUE;

		}

		break;
	}
	return 0;
}