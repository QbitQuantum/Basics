static BOOL CALLBACK TlenAdvOptDlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char text[256];
	BOOL bChecked;

	switch (msg) {
	case WM_INITDIALOG:
		{
			DBVARIANT dbv;
			TranslateDialogDefault(hwndDlg);
			if (!DBGetContactSetting(NULL, jabberProtoName, "LoginServer", &dbv)) {
				SetDlgItemText(hwndDlg, IDC_EDIT_LOGIN_SERVER, dbv.pszVal);
				DBFreeVariant(&dbv);
			} else {
				SetDlgItemText(hwndDlg, IDC_EDIT_LOGIN_SERVER, "tlen.pl");
			}

			CheckDlgButton(hwndDlg, IDC_USE_SSL, DBGetContactSettingByte(NULL, jabberProtoName, "UseSSL", FALSE));

			EnableWindow(GetDlgItem(hwndDlg, IDC_HOST), TRUE);
			EnableWindow(GetDlgItem(hwndDlg, IDC_HOSTPORT), TRUE);

			if (!DBGetContactSetting(NULL, jabberProtoName, "ManualHost", &dbv)) {
				SetDlgItemText(hwndDlg, IDC_HOST, dbv.pszVal);
				DBFreeVariant(&dbv);
			}
			else
				SetDlgItemText(hwndDlg, IDC_HOST, "s1.tlen.pl");
			SetDlgItemInt(hwndDlg, IDC_HOSTPORT, DBGetContactSettingWord(NULL, jabberProtoName, "ManualPort", TLEN_DEFAULT_PORT), FALSE);

			CheckDlgButton(hwndDlg, IDC_KEEPALIVE, DBGetContactSettingByte(NULL, jabberProtoName, "KeepAlive", TRUE));
			CheckDlgButton(hwndDlg, IDC_VISIBILITY_SUPPORT, DBGetContactSettingByte(NULL, jabberProtoName, "VisibilitySupport", FALSE));
			// File transfer options
			bChecked = FALSE;
			if (DBGetContactSettingByte(NULL, jabberProtoName, "UseFileProxy", FALSE) == TRUE) {
			    bChecked = TRUE;
				CheckDlgButton(hwndDlg, IDC_FILE_USE_PROXY, TRUE);
			}
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_TYPE_LABEL), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_TYPE), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_HOST_LABEL), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_HOST), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PORT_LABEL), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PORT), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_USE_AUTH), bChecked);
			if (DBGetContactSettingByte(NULL, jabberProtoName, "FileProxyAuth", FALSE) == TRUE) {
				CheckDlgButton(hwndDlg, IDC_FILE_PROXY_USE_AUTH, TRUE);
			} else {
			    bChecked = FALSE;
			}
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_USER_LABEL), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_USER), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PASSWORD_LABEL), bChecked);
			EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PASSWORD), bChecked);

			SendDlgItemMessage(hwndDlg, IDC_FILE_PROXY_TYPE, CB_ADDSTRING, 0, (LPARAM)Translate("Forwarding"));
            SendDlgItemMessage(hwndDlg, IDC_FILE_PROXY_TYPE, CB_ADDSTRING, 0, (LPARAM)Translate("SOCKS4"));
            SendDlgItemMessage(hwndDlg, IDC_FILE_PROXY_TYPE, CB_ADDSTRING, 0, (LPARAM)Translate("SOCKS5"));
			SendDlgItemMessage(hwndDlg, IDC_FILE_PROXY_TYPE, CB_SETCURSEL, DBGetContactSettingWord(NULL, jabberProtoName, "FileProxyType", 0), 0);
			if (!DBGetContactSetting(NULL, jabberProtoName, "FileProxyHost", &dbv)) {
				SetDlgItemText(hwndDlg, IDC_FILE_PROXY_HOST, dbv.pszVal);
				DBFreeVariant(&dbv);
			}
			SetDlgItemInt(hwndDlg, IDC_FILE_PROXY_PORT, DBGetContactSettingWord(NULL, jabberProtoName, "FileProxyPort", 0), FALSE);
			if (!DBGetContactSetting(NULL, jabberProtoName, "FileProxyUsername", &dbv)) {
				SetDlgItemText(hwndDlg, IDC_FILE_PROXY_USER, dbv.pszVal);
				DBFreeVariant(&dbv);
			}
			if (!DBGetContactSetting(NULL, jabberProtoName, "FileProxyPassword", &dbv)) {
				CallService(MS_DB_CRYPT_DECODESTRING, strlen(dbv.pszVal)+1, (LPARAM) dbv.pszVal);
				SetDlgItemText(hwndDlg, IDC_FILE_PROXY_PASSWORD, dbv.pszVal);
				DBFreeVariant(&dbv);
			}
			return TRUE;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
			case IDC_FILE_PROXY_TYPE:
				if (HIWORD(wParam) == CBN_SELCHANGE)
					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;
			case IDC_EDIT_LOGIN_SERVER:
			case IDC_HOST:
			case IDC_HOSTPORT:
			case IDC_FILE_PROXY_HOST:
			case IDC_FILE_PROXY_PORT:
			case IDC_FILE_PROXY_USER:
			case IDC_FILE_PROXY_PASSWORD:
				if ((HWND)lParam==GetFocus() && HIWORD(wParam)==EN_CHANGE)
					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;
			case IDC_FILE_USE_PROXY:
				bChecked = IsDlgButtonChecked(hwndDlg, IDC_FILE_USE_PROXY);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_TYPE_LABEL), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_TYPE), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_HOST_LABEL), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_HOST), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PORT_LABEL), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PORT), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_USE_AUTH), bChecked);
			case IDC_FILE_PROXY_USE_AUTH:
				bChecked = IsDlgButtonChecked(hwndDlg, IDC_FILE_PROXY_USE_AUTH) & IsDlgButtonChecked(hwndDlg, IDC_FILE_USE_PROXY);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_USER_LABEL), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_USER), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PASSWORD_LABEL), bChecked);
				EnableWindow(GetDlgItem(hwndDlg, IDC_FILE_PROXY_PASSWORD), bChecked);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;
			case IDC_KEEPALIVE:
			case IDC_VISIBILITY_SUPPORT:
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;
			default:
//				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;
			}
		}
		break;
	case WM_NOTIFY:
		{
			switch (((LPNMHDR) lParam)->code) {
			case PSN_APPLY:
				{
					WORD port;
					BOOL reconnectRequired = FALSE;
					DBVARIANT dbv;
					GetDlgItemText(hwndDlg, IDC_EDIT_LOGIN_SERVER, text, sizeof(text));
					if (DBGetContactSetting(NULL, jabberProtoName, "LoginServer", &dbv) || strcmp(text, dbv.pszVal))
						reconnectRequired = TRUE;
					if (dbv.pszVal != NULL)	DBFreeVariant(&dbv);
					DBWriteContactSettingString(NULL, jabberProtoName, "LoginServer", strlwr(text));

					DBWriteContactSettingByte(NULL, jabberProtoName, "UseSSL", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_USE_SSL));

					GetDlgItemText(hwndDlg, IDC_HOST, text, sizeof(text));
					if (DBGetContactSetting(NULL, jabberProtoName, "ManualHost", &dbv) || strcmp(text, dbv.pszVal))
						reconnectRequired = TRUE;
					if (dbv.pszVal != NULL)	DBFreeVariant(&dbv);
					DBWriteContactSettingString(NULL, jabberProtoName, "ManualHost", text);

					port = (WORD) GetDlgItemInt(hwndDlg, IDC_HOSTPORT, NULL, FALSE);
					if (DBGetContactSettingWord(NULL, jabberProtoName, "ManualPort", TLEN_DEFAULT_PORT) != port)
						reconnectRequired = TRUE;
					DBWriteContactSettingWord(NULL, jabberProtoName, "ManualPort", port);
					DBWriteContactSettingByte(NULL, jabberProtoName, "KeepAlive", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_KEEPALIVE));
					jabberSendKeepAlive = IsDlgButtonChecked(hwndDlg, IDC_KEEPALIVE);
					DBWriteContactSettingByte(NULL, jabberProtoName, "VisibilitySupport", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_VISIBILITY_SUPPORT));
					// File transfer options
					DBWriteContactSettingByte(NULL, jabberProtoName, "UseFileProxy", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_FILE_USE_PROXY));
					DBWriteContactSettingWord(NULL, jabberProtoName, "FileProxyType", (WORD) SendDlgItemMessage(hwndDlg, IDC_FILE_PROXY_TYPE, CB_GETCURSEL, 0, 0));
					GetDlgItemText(hwndDlg, IDC_FILE_PROXY_HOST, text, sizeof(text));
					DBWriteContactSettingString(NULL, jabberProtoName, "FileProxyHost", text);
					DBWriteContactSettingWord(NULL, jabberProtoName, "FileProxyPort", (WORD) GetDlgItemInt(hwndDlg, IDC_FILE_PROXY_PORT, NULL, FALSE));
					DBWriteContactSettingByte(NULL, jabberProtoName, "FileProxyAuth", (BYTE) IsDlgButtonChecked(hwndDlg, IDC_FILE_PROXY_USE_AUTH));
					GetDlgItemText(hwndDlg, IDC_FILE_PROXY_USER, text, sizeof(text));
					DBWriteContactSettingString(NULL, jabberProtoName, "FileProxyUsername", text);
					GetDlgItemText(hwndDlg, IDC_FILE_PROXY_PASSWORD, text, sizeof(text));
					CallService(MS_DB_CRYPT_ENCODESTRING, sizeof(text), (LPARAM) text);
					DBWriteContactSettingString(NULL, jabberProtoName, "FileProxyPassword", text);
					if (reconnectRequired && jabberConnected)
						MessageBox(hwndDlg, Translate("These changes will take effect the next time you connect to the Tlen network."), Translate("Tlen Protocol Option"), MB_OK|MB_SETFOREGROUND);
					return TRUE;
				}
			}
		}
		break;
	case WM_DESTROY:
		break;
	}

	return FALSE;
}