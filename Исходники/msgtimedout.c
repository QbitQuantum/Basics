BOOL CALLBACK ErrorDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	struct ErrorWindowData *ewd = (struct ErrorWindowData *) GetWindowLong(hwndDlg, GWL_USERDATA);
	//if (ewd==NULL && msg!=WM_INITDIALOG) return FALSE;
	switch (msg) {
		case WM_INITDIALOG:
		{
			RECT rc, rcParent;
			char caption[2048];
			ewd = (struct ErrorWindowData *) lParam;
			SetWindowLong(hwndDlg, GWL_USERDATA, (LONG) ewd);
			TranslateDialogDefault(hwndDlg);
			if (ewd != NULL) {
				if (!ewd->szDescription) 
					ewd->szDescription = strdup(Translate("An unknown error has occured."));
				if (!ewd->szText) 
					ewd->szText = strdup("");
				if (!ewd->szName) 
					ewd->szName = strdup("");
				SetDlgItemTextA(hwndDlg, IDC_ERRORTEXT, ewd->szDescription);
		#if defined( _UNICODE )
				SetDlgItemTextW(hwndDlg, IDC_MSGTEXT, (TCHAR *)(ewd->szText + strlen(ewd->szText) + 1));
		#else
				SetDlgItemTextA(hwndDlg, IDC_MSGTEXT, ewd->szText);
		#endif
				sprintf(caption, "%s - %s", Translate("Send Error"), ewd->szName);
				SetWindowTextA(hwndDlg, caption);
				GetWindowRect(hwndDlg, &rc);
				GetWindowRect(ewd->hwndParent, &rcParent);
				SetWindowPos(hwndDlg, HWND_TOP, rcParent.left + (rcParent.right - rcParent.left - rc.right + rc.left) / 2, rcParent.top + (rcParent.bottom - rcParent.top - rc.bottom + rc.top), 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
			}
		}
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					SendMessage(ewd->hwndParent, DM_ERRORDECIDED, MSGERROR_RETRY, (LPARAM) ewd);
					DestroyWindow(hwndDlg);
					break;
				case IDCANCEL:
					SendMessage(ewd->hwndParent, DM_ERRORDECIDED, MSGERROR_CANCEL, (LPARAM) ewd);
					DestroyWindow(hwndDlg);
					break;
			}
			break;
		case WM_DESTROY:
			SetWindowLong(hwndDlg, GWL_USERDATA, (LONG) NULL);
			free(ewd->szName);
			free(ewd->szDescription);
			free(ewd->szText);
			free(ewd);
			break;

	}
	return FALSE;

}