BOOL CALLBACK 
DoCommonCalls (
		HWND	hDlg, 
		UINT	uMsg, 
		WPARAM	wParam,
		LPARAM	lParam) 
{
	GPP *gpp;

	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			CPGPPassphraseDialogOptions *options;

			SetWindowLong (hDlg, GWL_USERDATA, lParam);
			gpp=(GPP *)lParam;

			options = (CPGPPassphraseDialogOptions *)gpp->options;

			if(options->mWindowTitle)
				SetWindowText(hDlg,options->mWindowTitle);

			if(options->mPrompt)
				SetDlgItemText (hDlg, IDC_PROMPTSTRING, options->mPrompt);

			gpp->bHideText = TRUE;
			CheckDlgButton (hDlg, IDC_HIDETYPING, BST_CHECKED);

			SetCapsLockMessageState(hDlg);

			SetForegroundWindow (hDlg);

			// Force focus to passphrase box
			SetFocus(GetDlgItem(hDlg, IDC_PHRASE1));
			break;
		}

		case WM_KEYUP:
		{
			SetCapsLockMessageState(hDlg);
			break;
		}

		case WM_HELP:
		{
			char szHelpFile[MAX_PATH+1];

			GetHelpDir(szHelpFile);

			WinHelp ((HWND)(((LPHELPINFO) lParam)->hItemHandle), szHelpFile, 
			 HELP_WM_HELP, (DWORD) (LPSTR) aIds); 
			break; 
		}

		case WM_CONTEXTMENU:
		{
			char szHelpFile[MAX_PATH+1];

			GetHelpDir(szHelpFile);

			WinHelp ((HWND) wParam, szHelpFile, HELP_CONTEXTMENU, 
				(DWORD) (LPVOID) aIds); 
			break; 
		}

		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY: 
		{
			HWND hwndPhrase1,hwndPhrase2;

			gpp=(GPP *)GetWindowLong (hDlg, GWL_USERDATA);

			ClearPassphrases(hDlg,gpp);

			hwndPhrase1=GetDlgItem(hDlg, IDC_PHRASE1);
			hwndPhrase2=GetDlgItem(hDlg, IDC_PHRASE2);

			if(hwndPhrase1)
			{
				SetWindowLong (hwndPhrase1,
					   GWL_WNDPROC, 
					   (LONG)gpp->wpOrigPhrase1Proc);
			}

			if(hwndPhrase2)
			{
				SetWindowLong (hwndPhrase2, 
					   GWL_WNDPROC, 
					   (LONG)gpp->wpOrigPhrase2Proc);
			}

			EndDialog(hDlg,kPGPError_UserAbort);
			break;
		}

		case WM_CTLCOLOREDIT:
		{
			HWND hwndPhrase1,hwndPhrase2;

			gpp=(GPP *)GetWindowLong (hDlg, GWL_USERDATA);

			hwndPhrase1=GetDlgItem(hDlg, IDC_PHRASE1);
			hwndPhrase2=GetDlgItem(hDlg, IDC_PHRASE2);

			if(lParam==0)
				break;

			if (((HWND)lParam == hwndPhrase1) ||
				((HWND)lParam == hwndPhrase2)) 
			{
				SetBkColor ((HDC)wParam, GetSysColor (COLOR_WINDOW));
				if (gpp->bHideText) 
					SetTextColor ((HDC)wParam, GetSysColor (COLOR_WINDOW));
				else 
					SetTextColor ((HDC)wParam, 
							  GetSysColor (COLOR_WINDOWTEXT));
				return (BOOL)CreateSolidBrush (GetSysColor (COLOR_WINDOW));
			}
			break;
		}

		case WM_COMMAND:
		{
			gpp=(GPP *)GetWindowLong (hDlg, GWL_USERDATA);

			switch(LOWORD (wParam)) 
			{
				case IDCANCEL:
					EndDialog (hDlg, kPGPError_UserAbort);
					break;

				case IDC_HIDETYPING :
				{
					HWND hwndPhrase1,hwndPhrase2;
	
					hwndPhrase1=GetDlgItem(hDlg, IDC_PHRASE1);
					hwndPhrase2=GetDlgItem(hDlg, IDC_PHRASE2);

					if (IsDlgButtonChecked (hDlg, IDC_HIDETYPING)
							== BST_CHECKED) 
						gpp->bHideText = TRUE;
					else 
						gpp->bHideText = FALSE;

					if(hwndPhrase1!=NULL)
						InvalidateRect (hwndPhrase1, NULL, TRUE);

					if(hwndPhrase2!=NULL)
						InvalidateRect (hwndPhrase2, NULL, TRUE);
					break;
				}
			}
			break;	
		}
	}

	return FALSE;
}