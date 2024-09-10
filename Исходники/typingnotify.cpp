static INT_PTR CALLBACK DlgProcOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int i;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);

		if (ColorMode == COLOR_WINDOWS) {
			CheckDlgButton(hwndDlg, IDC_USEWINCOLORS, BST_CHECKED);
			Utils::enableDlgControl(hwndDlg, IDC_USEPOPUPCOLORS, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_USEWINCOLORS, TRUE);
			CheckDlgButton(hwndDlg, IDC_USEPOPUPCOLORS, BST_UNCHECKED);
		}
		else if (ColorMode == COLOR_POPUP) {
			CheckDlgButton(hwndDlg, IDC_USEWINCOLORS, BST_UNCHECKED);
			Utils::enableDlgControl(hwndDlg, IDC_USEWINCOLORS, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_USEPOPUPCOLORS, TRUE);
			CheckDlgButton(hwndDlg, IDC_USEPOPUPCOLORS, BST_CHECKED);
		}

		for (i=0; i < SIZEOF(colorPicker); i++) {
			SendDlgItemMessage(hwndDlg, colorPicker[i].res, CPM_SETCOLOUR, 0, colorPicker[i].color);
			Utils::enableDlgControl(hwndDlg, colorPicker[i].res, (ColorMode == COLOR_OWN));
		}

		CheckDlgButton(hwndDlg, IDC_TIMEOUT_PERMANENT, (TimeoutMode == TIMEOUT_PERMANENT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_TIMEOUT_POPUP, (TimeoutMode == TIMEOUT_POPUP) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_TIMEOUT_PROTO, (TimeoutMode == TIMEOUT_PROTO) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_TIMEOUT_CUSTOM, (TimeoutMode == TIMEOUT_CUSTOM) ? BST_CHECKED : BST_UNCHECKED);
		SetDlgItemInt(hwndDlg, IDC_TIMEOUT_VALUE, Timeout, 0);
		Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE, TimeoutMode == TIMEOUT_CUSTOM);

		CheckDlgButton(hwndDlg, IDC_TIMEOUT_PERMANENT2, (TimeoutMode2 == TIMEOUT_PERMANENT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_TIMEOUT_POPUP2, (TimeoutMode2 == TIMEOUT_POPUP) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_TIMEOUT_CUSTOM2, (TimeoutMode2 == TIMEOUT_CUSTOM) ? BST_CHECKED : BST_UNCHECKED);
		SetDlgItemInt(hwndDlg, IDC_TIMEOUT_VALUE2, Timeout2, 0);
		Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE2, TimeoutMode2 == TIMEOUT_CUSTOM);

		CheckDlgButton(hwndDlg, IDC_START, (StartDisabled) ? BST_UNCHECKED : BST_CHECKED);
		CheckDlgButton(hwndDlg, IDC_STOP, (StopDisabled) ? BST_UNCHECKED : BST_CHECKED);

		CheckDlgButton(hwndDlg, IDC_ONEPOPUP, (OnePopup) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_SHOWMENU, (ShowMenu) ? BST_CHECKED : BST_UNCHECKED);

		Utils::enableDlgControl(hwndDlg, IDC_ONEPOPUP, PluginConfig.g_PopupAvail);
		Utils::enableDlgControl(hwndDlg, IDC_SHOWMENU, PluginConfig.g_PopupAvail);
		Utils::enableDlgControl(hwndDlg, IDC_PREVIEW, PluginConfig.g_PopupAvail/*&&!ServiceExists(MS_POPUP_REGISTERNOTIFICATION)*/);

		newTimeout = Timeout;
		newTimeoutMode = TimeoutMode;
		newTimeout2 = Timeout2;
		newTimeoutMode2 = TimeoutMode2;
		newColorMode = ColorMode;
		break;

	case WM_COMMAND:
		{
			WORD idCtrl = LOWORD(wParam), wNotifyCode = HIWORD(wParam);

			if (wNotifyCode == CPN_COLOURCHANGED) {
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				return TRUE;
			}

			switch (idCtrl) {
			case IDC_USEWINCOLORS:
				if (wNotifyCode == BN_CLICKED) {
					BOOL bEnableOthers;

					if (IsDlgButtonChecked(hwndDlg, IDC_USEWINCOLORS)) {
						newColorMode = COLOR_WINDOWS;
						bEnableOthers = FALSE;
					}
					else {
						newColorMode = COLOR_OWN;
						bEnableOthers = TRUE;
					}

					for (i=0; i < SIZEOF(colorPicker); i++)
						Utils::enableDlgControl(hwndDlg, colorPicker[i].res, bEnableOthers);

					Utils::enableDlgControl(hwndDlg, IDC_USEPOPUPCOLORS, bEnableOthers);

					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				}
				break;

			case IDC_USEPOPUPCOLORS:
				if (wNotifyCode == BN_CLICKED) {
					BOOL bEnableOthers;

					if (IsDlgButtonChecked(hwndDlg, IDC_USEPOPUPCOLORS)) {
						newColorMode = COLOR_POPUP;
						bEnableOthers = FALSE;
					}
					else {
						newColorMode = COLOR_OWN;
						bEnableOthers = TRUE;
					}

					for (i=0; i < sizeof(colorPicker) / sizeof(colorPicker[0]); i++)
						Utils::enableDlgControl(hwndDlg, colorPicker[i].res, bEnableOthers);

					Utils::enableDlgControl(hwndDlg, IDC_USEWINCOLORS, bEnableOthers);

					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				}
				break;

			case IDC_ONEPOPUP:
			case IDC_CLIST:
			case IDC_DISABLED:
			case IDC_SHOWMENU:
			case IDC_START:
			case IDC_STOP:
			case IDC_WOCL:
				if (wNotifyCode == BN_CLICKED)
					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_PREVIEW:
				if (PluginConfig.g_PopupAvail) {
					POPUPDATAT ppd = { 0 };
					for (i=0; i < 2; i++) {
						int notyping;
						if (i == PROTOTYPE_CONTACTTYPING_OFF) {
							lstrcpy(ppd.lptzContactName, TranslateT("Contact"));
							lstrcpyn(ppd.lptzText, szStop, MAX_SECONDLINE);
							notyping = 1;
						}
						else {
							lstrcpy(ppd.lptzContactName, TranslateT("Contact"));
							lstrcpyn(ppd.lptzText, szStart, MAX_SECONDLINE);
							notyping = 0;
						}

						switch (newColorMode) {
						case COLOR_OWN:
							ppd.colorText = SendDlgItemMessage(hwndDlg, colorPicker[2*notyping + 1].res, CPM_GETCOLOUR, 0, 0);
							ppd.colorBack = SendDlgItemMessage(hwndDlg, colorPicker[2*notyping ].res, CPM_GETCOLOUR, 0, 0);
							break;
						case COLOR_WINDOWS:
							ppd.colorBack = GetSysColor(COLOR_BTNFACE);
							ppd.colorText = GetSysColor(COLOR_WINDOWTEXT);
							break;
						case COLOR_POPUP:
						default:
							ppd.colorBack = ppd.colorText = 0;
							break;
						}

						if (notyping)
							switch (newTimeoutMode2) {
							case TIMEOUT_CUSTOM:
								ppd.iSeconds = newTimeout2;
								break;
							case TIMEOUT_PERMANENT:
								ppd.iSeconds = -1;
								break;
							case TIMEOUT_POPUP:
							default:
								ppd.iSeconds = 0;
								break;
						}
						else
							switch (newTimeoutMode) {
							case TIMEOUT_CUSTOM:
								ppd.iSeconds = newTimeout;
								break;
							case TIMEOUT_PROTO:
								ppd.iSeconds = 10;
								break;
							case TIMEOUT_PERMANENT:
								ppd.iSeconds = -1;
								break;
							case TIMEOUT_POPUP:
							default:
								ppd.iSeconds = 0;
								break;
						}

						ppd.lchIcon = PluginConfig.g_buttonBarIcons[ICON_DEFAULT_TYPING];
						ppd.lchContact = (HANDLE)wParam;
						ppd.PluginWindowProc = NULL;
						ppd.PluginData = NULL;
						PUAddPopupT(&ppd);
					}
				}
				break;

			case IDC_TIMEOUT_POPUP2:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode2 = TIMEOUT_POPUP;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE2, 0);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_CUSTOM2:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode2 = TIMEOUT_CUSTOM;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE2, 1);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_POPUP:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode = TIMEOUT_POPUP;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE, 0);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_PERMANENT:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode = TIMEOUT_PERMANENT;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE, 0);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_PERMANENT2:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode2 = TIMEOUT_PERMANENT;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE2, 0);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_CUSTOM:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode = TIMEOUT_CUSTOM;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE, 1);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_PROTO:
				if (wNotifyCode != BN_CLICKED)
					break;
				newTimeoutMode = TIMEOUT_PROTO;
				Utils::enableDlgControl(hwndDlg, IDC_TIMEOUT_VALUE, 0);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				break;

			case IDC_TIMEOUT_VALUE:
			case IDC_TIMEOUT_VALUE2:
				{
					int newValue = GetDlgItemInt(hwndDlg, idCtrl, NULL, 0);

					if (wNotifyCode == EN_KILLFOCUS) {
						int oldValue;

						if (idCtrl == IDC_TIMEOUT_VALUE)
							oldValue = newTimeout;
						else
							oldValue = newTimeout2;

						if (newValue != oldValue)
							SetDlgItemInt(hwndDlg, idCtrl, oldValue, 0);
						return TRUE;
					}
					if (wNotifyCode != EN_CHANGE || (HWND) lParam != GetFocus())
						return TRUE;

					if (newValue > TIMEOUT_MAXVALUE)
						newValue = TIMEOUT_MAXVALUE;
					else if (newValue < TIMEOUT_MINVALUE)
						newValue = TIMEOUT_MINVALUE;

					if (idCtrl == IDC_TIMEOUT_VALUE)
						newTimeout = newValue;
					else
						newTimeout2 = newValue;

					SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
				}
			}
		}
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom) {
		case 0:
			switch (((LPNMHDR) lParam)->code) {
			case PSN_APPLY:
				for (i=0; i < sizeof(colorPicker) / sizeof(colorPicker[0]); i++) {
					colorPicker[i].color = SendDlgItemMessage(hwndDlg, colorPicker[i].res, CPM_GETCOLOUR, 0, 0);
					db_set_dw(0, Module, colorPicker[i].desc, colorPicker[i].color);
				}

				Timeout = newTimeout;   TimeoutMode = newTimeoutMode;
				Timeout2 = newTimeout2; TimeoutMode2 = newTimeoutMode2;
				ColorMode = newColorMode;

				if (Disabled != IsDlgButtonChecked(hwndDlg, IDC_DISABLED))
					EnableDisableMenuCommand(0, 0);

				StartDisabled = IsDlgButtonChecked(hwndDlg, IDC_START) ? 0 : 2;
				StopDisabled = IsDlgButtonChecked(hwndDlg, IDC_STOP) ? 0 : 4;
				OnePopup = IsDlgButtonChecked(hwndDlg, IDC_ONEPOPUP);
				ShowMenu = IsDlgButtonChecked(hwndDlg, IDC_SHOWMENU);

				db_set_b(0, Module, SET_ONEPOPUP, OnePopup);
				db_set_b(0, Module, SET_SHOWDISABLEMENU, ShowMenu);
				db_set_b(0, Module, SET_DISABLED, (BYTE) (StartDisabled | StopDisabled));
				db_set_b(0, Module, SET_COLOR_MODE, ColorMode);
				db_set_b(0, Module, SET_TIMEOUT_MODE, TimeoutMode);
				db_set_b(0, Module, SET_TIMEOUT, (BYTE) Timeout);
				db_set_b(0, Module, SET_TIMEOUT_MODE2, TimeoutMode2);
				db_set_b(0, Module, SET_TIMEOUT2, (BYTE) Timeout2);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}