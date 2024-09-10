INT_PTR CALLBACK DlgProcOptsConnections(HWND hWndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMraProto *ppro = (CMraProto*)GetWindowLongPtr(hWndDlg, GWLP_USERDATA);
	CMStringW szBuff;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hWndDlg);
		SetWindowLongPtr(hWndDlg, GWLP_USERDATA, lParam);
		ppro = (CMraProto*)lParam;

		if (ppro->mraGetStringW(NULL, "Server", szBuff))
			SetDlgItemText(hWndDlg, IDC_SERVER, szBuff.c_str());
		else
			SetDlgItemTextA(hWndDlg, IDC_SERVER, MRA_DEFAULT_SERVER);

		SetDlgItemInt(hWndDlg, IDC_SERVERPORT, ppro->getWord("ServerPort", MRA_DEFAULT_SERVER_PORT), FALSE);
		// if set SSL proxy, setting will ignored

		//CheckDlgButton(hWndDlg, IDC_KEEPALIVE, getByte("keepalive", 0));
		CheckDlgButton(hWndDlg, IDC_AUTO_ADD_CONTACTS_TO_SERVER, ppro->getByte("AutoAddContactsToServer", MRA_DEFAULT_AUTO_ADD_CONTACTS_TO_SERVER));
		CheckDlgButton(hWndDlg, IDC_AUTO_AUTH_REQ_ON_LOGON, ppro->getByte("AutoAuthRequestOnLogon", MRA_DEFAULT_AUTO_AUTH_REQ_ON_LOGON));
		CheckDlgButton(hWndDlg, IDC_AUTO_AUTH_GRAND_IN_CLIST, ppro->getByte("AutoAuthGrandUsersInCList", MRA_DEFAULT_AUTO_AUTH_GRAND_IN_CLIST));
		CheckDlgButton(hWndDlg, IDC_AUTO_AUTH_GRAND_NEW_USERS, ppro->getByte("AutoAuthGrandNewUsers", MRA_DEFAULT_AUTO_AUTH_GRAND_NEW_USERS));

		CheckDlgButton(hWndDlg, IDC_SLOWSEND, ppro->getByte("SlowSend", MRA_DEFAULT_SLOW_SEND));
		CheckDlgButton(hWndDlg, IDC_INCREMENTAL_NEW_MAIL_NOTIFY, ppro->getByte("IncrementalNewMailNotify", MRA_DEFAULT_INC_NEW_MAIL_NOTIFY));
		CheckDlgButton(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY, ppro->getByte("TrayIconNewMailNotify", MRA_DEFAULT_TRAYICON_NEW_MAIL_NOTIFY));
		CheckDlgButton(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY_CLICK_TO_INBOX, ppro->getByte("TrayIconNewMailClkToInbox", MRA_DEFAULT_TRAYICON_NEW_MAIL_CLK_TO_INBOX));
		EnableWindow(GetDlgItem(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY_CLICK_TO_INBOX), ppro->getByte("TrayIconNewMailNotify", MRA_DEFAULT_TRAYICON_NEW_MAIL_NOTIFY));

		CheckDlgButton(hWndDlg, IDC_RTF_RECEIVE_ENABLE, ppro->getByte("RTFReceiveEnable", MRA_DEFAULT_RTF_RECEIVE_ENABLE));

		CheckDlgButton(hWndDlg, IDC_RTF_SEND_ENABLE, ppro->getByte("RTFSendEnable", MRA_DEFAULT_RTF_SEND_ENABLE));
		EnableWindow(GetDlgItem(hWndDlg, IDC_RTF_SEND_SMART), ppro->getByte("RTFSendEnable", MRA_DEFAULT_RTF_SEND_ENABLE));
		EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON_FONT), ppro->getByte("RTFSendEnable", MRA_DEFAULT_RTF_SEND_ENABLE));
		EnableWindow(GetDlgItem(hWndDlg, IDC_RTF_BGCOLOUR), ppro->getByte("RTFSendEnable", MRA_DEFAULT_RTF_SEND_ENABLE));
		SendDlgItemMessage(hWndDlg, IDC_RTF_BGCOLOUR, CPM_SETCOLOUR, 0, ppro->getDword("RTFBackgroundColour", MRA_DEFAULT_RTF_BACKGROUND_COLOUR));
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_DEFAULT:
			SetDlgItemTextA(hWndDlg, IDC_SERVER, MRA_DEFAULT_SERVER);
			SetDlgItemInt(hWndDlg, IDC_SERVERPORT, MRA_DEFAULT_SERVER_PORT, FALSE);
			break;
		case IDC_TRAYICON_NEW_MAIL_NOTIFY:
			EnableWindow(GetDlgItem(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY_CLICK_TO_INBOX), IsDlgButtonChecked(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY));
			break;
		case IDC_RTF_SEND_ENABLE:
			EnableWindow(GetDlgItem(hWndDlg, IDC_RTF_SEND_SMART), IsDlgButtonChecked(hWndDlg, IDC_RTF_SEND_ENABLE));
			EnableWindow(GetDlgItem(hWndDlg, IDC_BUTTON_FONT), IsDlgButtonChecked(hWndDlg, IDC_RTF_SEND_ENABLE));
			EnableWindow(GetDlgItem(hWndDlg, IDC_RTF_BGCOLOUR), IsDlgButtonChecked(hWndDlg, IDC_RTF_SEND_ENABLE));
			break;
		case IDC_BUTTON_FONT:
			{
				LOGFONT lf = {0};
				CHOOSEFONT cf = {0};

				cf.lStructSize = sizeof(cf);
				cf.lpLogFont = &lf;
				cf.rgbColors = ppro->getDword("RTFFontColour", MRA_DEFAULT_RTF_FONT_COLOUR);
				cf.Flags = (CF_SCREENFONTS|CF_EFFECTS|CF_FORCEFONTEXIST|CF_INITTOLOGFONTSTRUCT);
				if (ppro->mraGetContactSettingBlob(NULL, "RTFFont", &lf, sizeof(LOGFONT), NULL) == FALSE) {
					HDC hDC = GetDC(NULL);// kegl
					lf.lfCharSet = MRA_DEFAULT_RTF_FONT_CHARSET;
					lf.lfHeight = -MulDiv(MRA_DEFAULT_RTF_FONT_SIZE, GetDeviceCaps(hDC, LOGPIXELSY), 72);
					lstrcpyn(lf.lfFaceName, MRA_DEFAULT_RTF_FONT_NAME, LF_FACESIZE);
					ReleaseDC(NULL, hDC);
				}

				if (ChooseFont(&cf)) {
					ppro->mraWriteContactSettingBlob(NULL, "RTFFont", &lf, sizeof(LOGFONT));
					ppro->setDword("RTFFontColour", cf.rgbColors);
				}
			}
			break;
		}

		if ((LOWORD(wParam) == IDC_SERVER || LOWORD(wParam) == IDC_SERVERPORT) && (HIWORD(wParam) != EN_CHANGE || (HWND)lParam != GetFocus())) return FALSE;
		SendMessage(GetParent(hWndDlg), PSM_CHANGED, 0, 0);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case PSN_APPLY:
			TCHAR szBuff[MAX_PATH];
			GetDlgItemText(hWndDlg, IDC_SERVER, szBuff, SIZEOF(szBuff));
			ppro->mraSetStringW(NULL, "Server", szBuff);
			ppro->setWord("ServerPort", (WORD)GetDlgItemInt(hWndDlg, IDC_SERVERPORT, NULL, FALSE));
			ppro->setByte("AutoAddContactsToServer", IsDlgButtonChecked(hWndDlg, IDC_AUTO_ADD_CONTACTS_TO_SERVER));
			ppro->setByte("AutoAuthRequestOnLogon", IsDlgButtonChecked(hWndDlg, IDC_AUTO_AUTH_REQ_ON_LOGON));
			ppro->setByte("AutoAuthGrandUsersInCList", IsDlgButtonChecked(hWndDlg, IDC_AUTO_AUTH_GRAND_IN_CLIST));
			ppro->setByte("AutoAuthGrandNewUsers", IsDlgButtonChecked(hWndDlg, IDC_AUTO_AUTH_GRAND_NEW_USERS));

			ppro->setByte("SlowSend", IsDlgButtonChecked(hWndDlg, IDC_SLOWSEND));
			ppro->setByte("IncrementalNewMailNotify", IsDlgButtonChecked(hWndDlg, IDC_INCREMENTAL_NEW_MAIL_NOTIFY));
			ppro->setByte("TrayIconNewMailNotify", IsDlgButtonChecked(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY));
			ppro->setByte("TrayIconNewMailClkToInbox", IsDlgButtonChecked(hWndDlg, IDC_TRAYICON_NEW_MAIL_NOTIFY_CLICK_TO_INBOX));

			ppro->setByte("RTFReceiveEnable", IsDlgButtonChecked(hWndDlg, IDC_RTF_RECEIVE_ENABLE));
			ppro->setByte("RTFSendEnable", IsDlgButtonChecked(hWndDlg, IDC_RTF_SEND_ENABLE));
			ppro->setDword("RTFBackgroundColour", SendDlgItemMessage(hWndDlg, IDC_RTF_BGCOLOUR, CPM_GETCOLOUR, 0, 0));
			return TRUE;
		}
		break;
	}
	return FALSE;
}