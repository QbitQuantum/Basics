INT_PTR CALLBACK CConfig::ChatDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char buf[128];

	switch (uMsg) {
	case WM_INITDIALOG:
		{
			m_bInitializingDialog = true;

			// Translate the dialog
			TranslateDialogDefault(hwndDlg);

			CheckDlgButton(hwndDlg, IDC_MAXIMIZED_TITLE, m_abBoolSettings[MAXIMIZED_TITLE] ? BST_UNCHECKED : BST_CHECKED);
			CheckDlgButton(hwndDlg, IDC_MAXIMIZED_LABELS, m_abBoolSettings[MAXIMIZED_LABELS] ? BST_UNCHECKED : BST_CHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_REPLY_MAXIMIZED, m_abBoolSettings[SESSION_REPLY_MAXIMIZED] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_SCROLL_MAXIMIZED, m_abBoolSettings[SESSION_SCROLL_MAXIMIZED] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_SHOWTYPING, m_abBoolSettings[SESSION_SHOWTYPING] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_SENDTYPING, m_abBoolSettings[SESSION_SENDTYPING] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_LOADDB, m_abBoolSettings[SESSION_LOADDB] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_MARKREAD, m_abBoolSettings[SESSION_MARKREAD] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_SYMBOLS, m_abBoolSettings[SESSION_SYMBOLS] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_TIMESTAMPS, m_abBoolSettings[SESSION_TIMESTAMPS] ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_CLOSE, m_abBoolSettings[SESSION_CLOSE] ? BST_CHECKED : BST_UNCHECKED);

			CheckDlgButton(hwndDlg, IDC_SESSION_SENDRETURN, m_abBoolSettings[SESSION_SENDRETURN] ? BST_CHECKED : BST_UNCHECKED);

			CheckDlgButton(hwndDlg, IDC_SESSION_SCROLLNONE, m_aiIntSettings[SESSION_AUTOSCROLL] == SESSION_AUTOSCROLL_NONE ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_SCROLLFIRST, m_aiIntSettings[SESSION_AUTOSCROLL] == SESSION_AUTOSCROLL_FIRST ? BST_CHECKED : BST_UNCHECKED);
			CheckDlgButton(hwndDlg, IDC_SESSION_SCROLLLAST, m_aiIntSettings[SESSION_AUTOSCROLL] == SESSION_AUTOSCROLL_LAST ? BST_CHECKED : BST_UNCHECKED);

			_itoa_s(m_aiIntSettings[SESSION_LOGSIZE], buf, _countof(buf), 10);
			SetDlgItemTextA(hwndDlg, IDC_SESSION_LOGSIZE, buf);

			_itoa_s(m_aiIntSettings[SESSION_CLOSETIMER], buf, _countof(buf), 10);
			SetDlgItemTextA(hwndDlg, IDC_SESSION_CLOSETIMER, buf);

			m_bInitializingDialog = false;
			break;
		}
	case WM_NOTIFY:
		{
			switch (((LPNMHDR)lParam)->code) {
			case PSN_APPLY:
				{
					m_abBoolSettings[SESSION_SCROLL_MAXIMIZED] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_SCROLL_MAXIMIZED) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_REPLY_MAXIMIZED] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_REPLY_MAXIMIZED) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_SHOWTYPING] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_SHOWTYPING) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_SENDTYPING] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_SENDTYPING) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_LOADDB] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_LOADDB) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_SENDRETURN] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_SENDRETURN) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_MARKREAD] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_MARKREAD) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_SYMBOLS] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_SYMBOLS) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_TIMESTAMPS] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_TIMESTAMPS) == BST_CHECKED ? true : false;
					m_abBoolSettings[SESSION_CLOSE] = IsDlgButtonChecked(hwndDlg, IDC_SESSION_CLOSE) == BST_CHECKED ? true : false;

					if (IsDlgButtonChecked(hwndDlg, IDC_SESSION_SCROLLNONE) == BST_CHECKED)
						m_aiIntSettings[SESSION_AUTOSCROLL] = SESSION_AUTOSCROLL_NONE;
					else if (IsDlgButtonChecked(hwndDlg, IDC_SESSION_SCROLLFIRST) == BST_CHECKED)
						m_aiIntSettings[SESSION_AUTOSCROLL] = SESSION_AUTOSCROLL_FIRST;
					else
						m_aiIntSettings[SESSION_AUTOSCROLL] = SESSION_AUTOSCROLL_LAST;

					m_abBoolSettings[MAXIMIZED_TITLE] = IsDlgButtonChecked(hwndDlg, IDC_MAXIMIZED_TITLE) == BST_UNCHECKED ? true : false;
					m_abBoolSettings[MAXIMIZED_LABELS] = IsDlgButtonChecked(hwndDlg, IDC_MAXIMIZED_LABELS) == BST_UNCHECKED ? true : false;

					GetDlgItemTextA(hwndDlg, IDC_SESSION_LOGSIZE, buf, _countof(buf));
					m_aiIntSettings[SESSION_LOGSIZE] = atoi(buf) > 0 ? atoi(buf) : 1;

					GetDlgItemTextA(hwndDlg, IDC_SESSION_CLOSETIMER, buf, _countof(buf));
					m_aiIntSettings[SESSION_CLOSETIMER] = atoi(buf) >= 0 ? atoi(buf) : 1;

					CConfig::SaveSettings();
					SendMessage(hwndDlg, WM_INITDIALOG, 0, 0);
					break;
				}
			}
			break;
		}
	case WM_COMMAND:
		{
			// Activate the apply button
			if (!m_bInitializingDialog && ((HIWORD(wParam) == EN_CHANGE) || (HIWORD(wParam) == BN_CLICKED)))
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);

			break;
		}
	}
	return 0;
}