static INT_PTR CALLBACK DlgProcMsnConnOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	DBVARIANT dbv;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		{
			SetWindowLongPtr(hwndDlg, GWLP_USERDATA, lParam);
			CMsnProto* proto = (CMsnProto*)lParam;

			if (!proto->getString("DirectServer", &dbv)) {
				SetDlgItemTextA(hwndDlg, IDC_DIRECTSERVER, dbv.pszVal);
				db_free(&dbv);
			}
			else SetDlgItemTextA(hwndDlg, IDC_DIRECTSERVER, MSN_DEFAULT_LOGIN_SERVER);

			if (!proto->getString("GatewayServer", &dbv)) {
				SetDlgItemTextA(hwndDlg, IDC_GATEWAYSERVER, dbv.pszVal);
				db_free(&dbv);
			}
			else SetDlgItemTextA(hwndDlg, IDC_GATEWAYSERVER, MSN_DEFAULT_GATEWAY);

			CheckDlgButton(hwndDlg, IDC_SLOWSEND, proto->getByte("SlowSend", 0) ? BST_CHECKED : BST_UNCHECKED);

			SendDlgItemMessage(hwndDlg, IDC_HOSTOPT, CB_ADDSTRING, 0, (LPARAM)TranslateT("Automatically obtain host/port"));
			SendDlgItemMessage(hwndDlg, IDC_HOSTOPT, CB_ADDSTRING, 0, (LPARAM)TranslateT("Manually specify host/port"));
			SendDlgItemMessage(hwndDlg, IDC_HOSTOPT, CB_ADDSTRING, 0, (LPARAM)TranslateT("Disable"));

			unsigned gethst = proto->getByte("AutoGetHost", 1);
			if (gethst < 2) gethst = !gethst;

			char ipaddr[256] = "";
			if (gethst == 1)
				if (db_get_static(NULL, proto->m_szModuleName, "YourHost", ipaddr, sizeof(ipaddr)))
					gethst = 0;

			if (gethst == 0)
				strncpy_s(ipaddr, (proto->msnLoggedIn ? proto->MyConnection.GetMyExtIPStr() : ""), _TRUNCATE);

			SendDlgItemMessage(hwndDlg, IDC_HOSTOPT, CB_SETCURSEL, gethst, 0);
			if (ipaddr[0])
				SetDlgItemTextA(hwndDlg, IDC_YOURHOST, ipaddr);
			else
				SetDlgItemText(hwndDlg, IDC_YOURHOST, TranslateT("IP info available only after login"));
			EnableWindow(GetDlgItem(hwndDlg, IDC_YOURHOST), gethst == 1);
		}
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RESETSERVER:
			SetDlgItemTextA(hwndDlg, IDC_DIRECTSERVER, MSN_DEFAULT_LOGIN_SERVER);
			SetDlgItemTextA(hwndDlg, IDC_GATEWAYSERVER, MSN_DEFAULT_GATEWAY);
			SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
			break;
		}

		if (HIWORD(wParam) == EN_CHANGE && (HWND)lParam == GetFocus())
			switch (LOWORD(wParam)) {
			case IDC_DIRECTSERVER:
			case IDC_GATEWAYSERVER:
			case IDC_YOURHOST:
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		}

		if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_HOSTOPT) {
			unsigned gethst = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
			EnableWindow(GetDlgItem(hwndDlg, IDC_YOURHOST), gethst == 1);
			SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		}

		if (HIWORD(wParam) == BN_CLICKED) {
			switch (LOWORD(wParam)) {
			case IDC_SLOWSEND:
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;
			}
		}
		break;

	case WM_NOTIFY:
		if (((LPNMHDR)lParam)->code == (UINT)PSN_APPLY) {
			char str[MAX_PATH];

			CMsnProto* proto = (CMsnProto*)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

			GetDlgItemTextA(hwndDlg, IDC_DIRECTSERVER, str, _countof(str));
			if (mir_strcmp(str, MSN_DEFAULT_LOGIN_SERVER))
				proto->setString("DirectServer", str);
			else
				proto->delSetting("DirectServer");

			GetDlgItemTextA(hwndDlg, IDC_GATEWAYSERVER, str, _countof(str));
			if (mir_strcmp(str, MSN_DEFAULT_GATEWAY))
				proto->setString("GatewayServer", str);
			else
				proto->delSetting("GatewayServer");

			proto->setByte("SlowSend", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_SLOWSEND));
			if (proto->getByte("SlowSend", FALSE)) {
				if (db_get_dw(NULL, "SRMsg", "MessageTimeout", 60000) < 60000 ||
					db_get_dw(NULL, "SRMM", "MessageTimeout", 60000) < 60000) {
					MessageBox(NULL, TranslateT("MSN Protocol requires message timeout to be not less then 60 sec. Correct the timeout value."),
						TranslateT("MSN Protocol"), MB_OK | MB_ICONINFORMATION);
				}
			}
			
#ifdef OBSOLETE
			unsigned gethst2 = proto->getByte("AutoGetHost", 1);

#endif
			unsigned gethst = SendDlgItemMessage(hwndDlg, IDC_HOSTOPT, CB_GETCURSEL, 0, 0);
			if (gethst < 2) gethst = !gethst;
			proto->setByte("AutoGetHost", (BYTE)gethst);

			if (gethst == 0) {
				GetDlgItemTextA(hwndDlg, IDC_YOURHOST, str, _countof(str));
				proto->setString("YourHost", str);
			}
			else proto->delSetting("YourHost");

#ifdef OBSOLETE
			if (gethst != gethst2)
				proto->ForkThread(&CMsnProto::MSNConnDetectThread, NULL);
#endif

			proto->LoadOptions();
			return TRUE;
		}
	}

	return FALSE;
}