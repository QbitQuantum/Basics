static INT_PTR CALLBACK MainDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bTranslated = FALSE;
	static bool loading = true;
	switch (uMsg) {
	case WM_INITDIALOG:
		loading = true;
		TranslateDialogDefault(hwndDlg);
		CheckDlgButton(hwndDlg, IDC_EVERYBODY, Config.TalkWithEverybody ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_NOTINLIST, Config.TalkWithNotInList ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_AUTOAWAY, Config.TalkEveryoneWhileAway ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_WARN, Config.TalkWarnContacts ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_MARKREAD, Config.MarkAsRead ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_PAUSEDEPENDS, Config.PauseDepends ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_PAUSERANDOM, Config.PauseRandom ? BST_CHECKED : BST_UNCHECKED);
		SendDlgItemMessage(hwndDlg, IDC_WAITTIME, EM_SETLIMITTEXT, 3, 0);
		SetDlgItemInt(hwndDlg, IDC_WAITTIME, Config.AnswerPauseTime, FALSE);
		SendDlgItemMessage(hwndDlg, IDC_THINKTIME, EM_SETLIMITTEXT, 3, 0);
		SetDlgItemInt(hwndDlg, IDC_THINKTIME, Config.AnswerThinkTime, FALSE);
		SendDlgItemMessage(hwndDlg, IDC_WARNTXT, EM_SETLIMITTEXT, MAX_WARN_TEXT, 0);
		SetDlgItemText(hwndDlg, IDC_WARNTXT, Config.WarnText);
		UpdateEverybodyCheckboxes(hwndDlg);
		loading = false;
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_EVERYBODY && HIWORD(wParam) == BN_CLICKED)
			UpdateEverybodyCheckboxes(hwndDlg);
		if (!loading) {
			bool notify = true;
			switch (LOWORD(wParam)) {
			case IDC_WARNTXT:
			case IDC_WAITTIME:
			case IDC_THINKTIME:
				if (HIWORD(wParam) != EN_CHANGE)
					notify = false;
				break;
			}
			if (notify)
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		}
		break;
	case WM_NOTIFY:
		{
			NMHDR* nmhdr = (NMHDR*)lParam;
			switch (nmhdr->code) {
			case PSN_APPLY:
			case PSN_KILLACTIVE:
				{
					Config.TalkWithEverybody = IsDlgButtonChecked(hwndDlg, IDC_EVERYBODY) == BST_CHECKED ? TRUE : FALSE;
					Config.TalkWithNotInList = IsDlgButtonChecked(hwndDlg, IDC_NOTINLIST) == BST_CHECKED ? TRUE : FALSE;
					Config.TalkEveryoneWhileAway = IsDlgButtonChecked(hwndDlg, IDC_AUTOAWAY) == BST_CHECKED ? TRUE : FALSE;
					Config.TalkWarnContacts = IsDlgButtonChecked(hwndDlg, IDC_WARN) == BST_CHECKED ? TRUE : FALSE;
					Config.MarkAsRead = IsDlgButtonChecked(hwndDlg, IDC_MARKREAD) == BST_CHECKED ? TRUE : FALSE;
					Config.PauseDepends = IsDlgButtonChecked(hwndDlg, IDC_PAUSEDEPENDS) == BST_CHECKED ? TRUE : FALSE;
					Config.PauseRandom = IsDlgButtonChecked(hwndDlg, IDC_PAUSERANDOM) == BST_CHECKED ? TRUE : FALSE;
					Config.AnswerPauseTime = GetDlgItemInt(hwndDlg, IDC_WAITTIME, &bTranslated, FALSE);
					if (!bTranslated)
						Config.AnswerPauseTime = 2;
					Config.AnswerThinkTime = GetDlgItemInt(hwndDlg, IDC_THINKTIME, &bTranslated, FALSE);
					if (!bTranslated)
						Config.AnswerThinkTime = 4;
					TCHAR c[MAX_WARN_TEXT];
					bTranslated = GetDlgItemText(hwndDlg, IDC_WARNTXT, c, _countof(c));
					if (bTranslated)
						Config.WarnText = c;
					else
						Config.WarnText = TranslateTS(DEFAULT_WARN_TEXT);
				}
				return TRUE;
			}
			break;
		}
		break;
	}
	return 0;
}