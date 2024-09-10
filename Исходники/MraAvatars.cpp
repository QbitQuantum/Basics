INT_PTR CALLBACK MraAvatarsQueueDlgProcOpts(HWND hWndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CMraProto *ppro = (CMraProto*)GetWindowLongPtr(hWndDlg, GWLP_USERDATA);

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hWndDlg);
		SetWindowLongPtr(hWndDlg, GWLP_USERDATA, lParam);
		ppro = (CMraProto*)lParam;
		{
			CheckDlgButton(hWndDlg, IDC_ENABLE, db_get_b(NULL, MRA_AVT_SECT_NAME, "Enable", MRA_AVT_DEFAULT_ENABLE));

			CMStringW szServer;
			if (DB_GetStringW(NULL, MRA_AVT_SECT_NAME, "Server", szServer))
				SetDlgItemText(hWndDlg, IDC_SERVER, szServer.c_str());
			else
				SetDlgItemTextA(hWndDlg, IDC_SERVER, MRA_AVT_DEFAULT_SERVER);

			SetDlgItemInt(hWndDlg, IDC_SERVERPORT, db_get_dw(NULL, MRA_AVT_SECT_NAME, "ServerPort", MRA_AVT_DEFAULT_SERVER_PORT), FALSE);
			CheckDlgButton(hWndDlg, IDC_USE_KEEPALIVE_CONN, db_get_b(NULL, MRA_AVT_SECT_NAME, "UseKeepAliveConn", MRA_AVT_DEFAULT_USE_KEEPALIVE_CONN));
			SetDlgItemInt(hWndDlg, IDC_UPD_CHECK_INTERVAL, db_get_dw(NULL, MRA_AVT_SECT_NAME, "CheckInterval", MRA_AVT_DEFAULT_CHK_INTERVAL), FALSE);
			CheckDlgButton(hWndDlg, IDC_RETURN_ABC_PATH, db_get_b(NULL, MRA_AVT_SECT_NAME, "ReturnAbsolutePath", MRA_AVT_DEFAULT_RET_ABC_PATH));
			CheckDlgButton(hWndDlg, IDC_DELETE_AVT_ON_CONTACT_DELETE, db_get_b(NULL, MRA_AVT_SECT_NAME, "DeleteAvtOnContactDelete", MRA_DELETE_AVT_ON_CONTACT_DELETE));

			EnableControlsArray(hWndDlg, (WORD*)&wMraAvatarsControlsList, SIZEOF(wMraAvatarsControlsList), IsDlgButtonChecked(hWndDlg, IDC_ENABLE));
		}
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_ENABLE)
			EnableControlsArray(hWndDlg, (WORD*)&wMraAvatarsControlsList, SIZEOF(wMraAvatarsControlsList), IsDlgButtonChecked(hWndDlg, IDC_ENABLE));

		if (LOWORD(wParam) == IDC_BUTTON_DEFAULT) {
			SetDlgItemTextA(hWndDlg, IDC_SERVER, MRA_AVT_DEFAULT_SERVER);
			SetDlgItemInt(hWndDlg, IDC_SERVERPORT, MRA_AVT_DEFAULT_SERVER_PORT, FALSE);
		}

		if ((LOWORD(wParam) == IDC_SERVER || LOWORD(wParam) == IDC_SERVERPORT || LOWORD(wParam) == IDC_UPD_CHECK_INTERVAL) && (HIWORD(wParam) != EN_CHANGE || (HWND)lParam != GetFocus())) return FALSE;
		SendMessage(GetParent(hWndDlg), PSM_CHANGED, 0, 0);
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case PSN_APPLY:
			db_set_b(NULL, MRA_AVT_SECT_NAME, "Enable", IsDlgButtonChecked(hWndDlg, IDC_ENABLE));
			db_set_b(NULL, MRA_AVT_SECT_NAME, "DeleteAvtOnContactDelete", IsDlgButtonChecked(hWndDlg, IDC_DELETE_AVT_ON_CONTACT_DELETE));
			db_set_b(NULL, MRA_AVT_SECT_NAME, "ReturnAbsolutePath", IsDlgButtonChecked(hWndDlg, IDC_RETURN_ABC_PATH));
			db_set_dw(NULL, MRA_AVT_SECT_NAME, "CheckInterval", GetDlgItemInt(hWndDlg, IDC_UPD_CHECK_INTERVAL, NULL, FALSE));
			db_set_b(NULL, MRA_AVT_SECT_NAME, "UseKeepAliveConn", IsDlgButtonChecked(hWndDlg, IDC_USE_KEEPALIVE_CONN));
			db_set_dw(NULL, MRA_AVT_SECT_NAME, "ServerPort", GetDlgItemInt(hWndDlg, IDC_SERVERPORT, NULL, FALSE));

			TCHAR szServer[MAX_PATH];
			GetDlgItemText(hWndDlg, IDC_SERVER, szServer, SIZEOF(szServer));
			db_set_ts(NULL, MRA_AVT_SECT_NAME, "Server", szServer);
			return TRUE;
		}
		break;
	}
	return FALSE;
}