/**
 * ダイアログのプロシージャ。
 * @param [in] hDlg ダイアログボックスのハンドルが格納されています
 * @param [in] uMsg メッセージが格納されています
 * @param [in] wParam メッセージの追加情報が格納されています
 * @param [in] lParam メッセージの追加情報が格納されています
 * @return メッセージを処理した場合は 0 以外(TRUE)、そうでなければ 0(FALSE)
 */
static BOOL CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hwndComboBox = NULL;
	static HWND hwndEdit = NULL;
	static LRESULT selectedIndex = CB_ERR;
	static int length = 0;
	char *imeControl = NULL;
	switch (uMsg) {
	case WM_INITDIALOG:
		center_window(hDlg);

		hwndComboBox = GetDlgItem(hDlg, IDC_COMBO1);
		SendMessage(hwndComboBox, CB_LIMITTEXT, 0, 0);
		hwndEdit = GetWindow(hwndComboBox, GW_CHILD);
		SetFocus(hwndComboBox);

		SetFocus(GetDlgItem(hDlg, IDC_COMBO1));

		for (unsigned int i = 0; i < history.size(); i++) {
			SendMessage(hwndComboBox, CB_INSERTSTRING, i, (LPARAM)history[i].c_str());
		}

		CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, selectedRadioButton);
		CheckDlgButton(hDlg, IDC_CHECK1, selectedCheckBox);
		if (selectedRadioButton == IDC_RADIO1 || selectedRadioButton == IDC_RADIO2) {
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), FALSE);
		}

		if (selectedText.size() != 0) {
			SetWindowText(hwndEdit, selectedText.c_str());
		}

		if ((imeControl = iniFile->read("IME", "control")) && strcmp(imeControl, "1") == 0) {
			HIMC hImc;
			DWORD dwConv, dwSent;
			
			hImc = ImmGetContext(hDlg);

			ImmGetConversionStatus(hImc, &dwConv, &dwSent);

			if (ImmGetOpenStatus(hImc)) {
				ImmSetOpenStatus(hImc, false);
			}
			ImmReleaseContext(hDlg, hImc);
		}

		// SetFocus でフォーカス移動を行った場合は FALSE を返さなければならない
		return FALSE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
			return TRUE;

		case IDOK:
			if (IsDlgButtonChecked(hDlg, IDC_RADIO1)) {
				selectedRadioButton = IDC_RADIO1;
			} else 	if (IsDlgButtonChecked(hDlg, IDC_RADIO2)) {
				selectedRadioButton = IDC_RADIO2;
			} else 	if (IsDlgButtonChecked(hDlg, IDC_RADIO3)) {
				selectedRadioButton = IDC_RADIO3;
			} else 	if (IsDlgButtonChecked(hDlg, IDC_RADIO4)) {
				selectedRadioButton = IDC_RADIO4;
			}
			selectedCheckBox = IsDlgButtonChecked(hDlg, IDC_CHECK1);

			// 設定ファイルに状態を書き出す
			switch (selectedRadioButton) {
			case IDC_RADIO1:
				iniFile->write("Config", "radio", "1");
				break;

			case IDC_RADIO2:
				iniFile->write("Config", "radio", "2");
				break;

			case IDC_RADIO3:
				iniFile->write("Config", "radio", "3");
				break;

			case IDC_RADIO4:
				iniFile->write("Config", "radio", "4");
				break;

			default:
				iniFile->write("Config", "radio", "1");
				break;
			}

			if (selectedCheckBox) {
				iniFile->write("Config", "check", "TRUE");
			} else {
				iniFile->write("Config", "check", "FALSE");
			}

			// 履歴を保存
			length = GetWindowTextLength(hwndEdit);

			if (length != 0) {
				char *buf = new char[length + 1];
				buf[length] = '\0';
				GetWindowText(hwndEdit, buf, length + 1);

				std::string temp = buf;

				delete[] buf;
				history.insert(history.begin(), temp);

				for (unsigned int i = 0; i < history.size() - 1; i++) {
					for (unsigned int j = i + 1; j < history.size(); j++) {
						std::string str1 = history[i];
						std::string str2 = history[j];
						if (str1 == str2) {
							history[j] = "";
						}
					}
				}
				int index = 0;
				for (unsigned int i = 0; i < MAX_HISTORY && i < history.size(); i++) {
					if (history[i] != "") {
						std::string key = "history";
						char num[3] = {0};
						sprintf_s(num, "%d", index);
						key += num;

						iniFile->write("History", key.c_str(), history[i].c_str());
						index++;
					}
				}
			}

			if (length != 0) {
	            EndDialog(hDlg, IDOK);
			} else {
				EndDialog(hDlg, IDCANCEL);
			}
			return TRUE;

		case IDC_RADIO1:
		case IDC_RADIO2:
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, LOWORD(wParam));
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), FALSE);
			return TRUE;

		case IDC_RADIO3:
		case IDC_RADIO4:
			CheckRadioButton(hDlg, IDC_RADIO1, IDC_RADIO4, LOWORD(wParam));
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK1), TRUE);
			return TRUE;

		case IDC_COMBO1:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE: // 選択項目が変更されたとき
			case CBN_EDITUPDATE: // 直接入力で内容が変更されたとき。変更内容が表示される前に呼ばれる
			case CBN_EDITCHANGE: // 直接入力で内容が変更されたとき。変更内容が表示された後に呼ばれる
				selectedIndex = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
				break;
			}
		
			break;

		default:
			break;
		}
		return FALSE;

	case WM_TIMER:
		return FALSE;

	case WM_CLOSE:
		EndDialog(hDlg, WM_CLOSE);
		return TRUE;

	default:
		break;
	}

	return FALSE;
}