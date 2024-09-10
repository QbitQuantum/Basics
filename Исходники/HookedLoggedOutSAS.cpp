		/* static */
		INT_PTR HookedLoggedOutSAS::MicrosoftDialogProcWrapper(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			if(s_hookedDlgProc == 0)
			{
				pERROR(L"HookedLoggedOutSAS::MicrosoftDialogProcWrapper: Dialog wrapper called before we know who we're hooking!");
				return 0;	// Nothin we can do!
			}

			// Fall through if hooking is not enabled
			if(!s_hookingEnabled)
				return s_hookedDlgProc(hwnd, msg, wparam, lparam);

			// Hooking is on, so we let msgina do its thing
			INT_PTR msginaResult = s_hookedDlgProc(hwnd, msg, wparam, lparam);

			// If we're init'ing, then we set username, password and queue a message to login
			if(msg == WM_INITDIALOG)
			{
				std::wstring domainUsername = s_loginResult.Domain();
				domainUsername += L"\\";
				domainUsername += s_loginResult.Username();

				pDEBUG(L"HookedLoggedOutSAS::MicrosoftDialogProcWrapper: Hooked dialog, setting username/password and submitting for user: %s", domainUsername.c_str());
				SetDlgItemText(hwnd, IDC_MSGINA_USERNAME, domainUsername.c_str());
				SetDlgItemText(hwnd, IDC_MSGINA_PASSWORD, s_loginResult.Password().c_str());			
				SendMessage(hwnd, WM_COMMAND, 1, 1);
			}

			return msginaResult;
		}