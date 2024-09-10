INT_PTR CALLBACK DlgProcText(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rc, pos;
	HWND button;
	HMENU hMenu, hMenu1;
	TCHAR str[4096];
	switch (msg) {
	case WM_INITDIALOG:
		opt_startup = TRUE;
		// set windows position, make it top-most
		GetWindowRect(hdlg, &rc);
		SetWindowPos(hdlg, HWND_TOPMOST, rc.left, rc.top, 0, 0, SWP_NOSIZE);
		TranslateDialogDefault(hdlg);
		// generate the display text for variable list
		_tcsncpy(str, VAR_LIST_OPT, _countof(str) - 1);
		SetDlgItemText(hdlg, IDC_VARLIST, str);

		// make the more variable and other buttons flat
		SendDlgItemMessage(hdlg, IDC_MORE, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM1, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM2, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM3, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM4, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM5, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM6, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM7, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_TM8, BUTTONSETASFLATBTN, TRUE, 0);
		SendDlgItemMessage(hdlg, IDC_RESET, BUTTONSETASFLATBTN, TRUE, 0);
		// load the settings
		LoadTextSettings(hdlg);
		opt_startup = FALSE;
		return TRUE;

	case WM_COMMAND:
		if (opt_startup)	return TRUE;
		switch (LOWORD(wParam)) {
		case IDC_CTEXT:
		case IDC_BTITLE:
		case IDC_BTEXT:
		case IDC_NTEXT:
		case IDC_XTEXT:
		case IDC_ETEXT:
		case IDC_HTEXT:
		case IDC_BTITLE2:
			if (HIWORD(wParam) == EN_CHANGE)
				SendMessage(GetParent(hdlg), PSM_CHANGED, 0, 0);
			break;

		case IDC_MORE:
			// display custom variables list
			MoreVarList();
			break;

		case IDC_TM1:
		case IDC_TM2:
		case IDC_TM3:
		case IDC_TM4:
		case IDC_TM5:
		case IDC_TM6:
		case IDC_TM7:
		case IDC_TM8:
			// display the menu
			button = GetDlgItem(hdlg, LOWORD(wParam));
			GetWindowRect(button, &pos);
			hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_TMMENU));
			hMenu1 = GetSubMenu(hMenu, 0);
			TranslateMenu(hMenu1);
			switch (TrackPopupMenu(hMenu1, TPM_LEFTBUTTON | TPM_RETURNCMD, pos.left, pos.bottom, 0, hdlg, NULL)) {
			case ID_MPREVIEW:
				{
					// show the preview in a message box, using the weather data from the default station
					WEATHERINFO winfo = LoadWeatherInfo(opt.DefStn);
					GetDisplay(&winfo, *var[LOWORD(wParam) - IDC_TM1], str);
					MessageBox(NULL, str, TranslateT("Weather Protocol Text Preview"), MB_OK | MB_TOPMOST);
					break;
				}
			case ID_MRESET:
				unsigned varo = LOWORD(wParam) - IDC_TM1;
				// remove the old setting from db and free memory
				TCHAR* vartmp = *var[varo];
				wfree(&vartmp);
				SetTextDefault(varname[varo]);
				SetDlgItemText(hdlg, cname[varo], *var[varo]);
				break;
			}
			DestroyMenu(hMenu);
			break;

		case IDC_RESET:
			// left click action selection menu
			button = GetDlgItem(hdlg, IDC_RESET);
			GetWindowRect(button, &pos);
			hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_TMENU));
			hMenu1 = GetSubMenu(hMenu, 0);
			TranslateMenu(hMenu1);
			switch (TrackPopupMenu(hMenu1, TPM_LEFTBUTTON | TPM_RETURNCMD, pos.left, pos.bottom, 0, hdlg, NULL)) {
			case ID_T1:
				// reset to the strings in memory, discard all changes
				LoadTextSettings(hdlg);
				break;

			case ID_T2:
				// reset to the default setting
				FreeTextVar();
				SetTextDefault("CbBENHX");
				LoadTextSettings(hdlg);
				break;
			}
			DestroyMenu(hMenu);
			break;
		}
		return TRUE;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case PSN_APPLY:
			// save the option
			TCHAR textstr[MAX_TEXT_SIZE];
			// free memory for old settings
			FreeTextVar();
			// save new settings to memory
			GetDlgItemText(hdlg, IDC_CTEXT, textstr, _countof(textstr));
			wSetData(&opt.cText, textstr);
			GetDlgItemText(hdlg, IDC_BTEXT, textstr, _countof(textstr));
			wSetData(&opt.bText, textstr);
			GetDlgItemText(hdlg, IDC_BTITLE, textstr, _countof(textstr));
			wSetData(&opt.bTitle, textstr);
			GetDlgItemText(hdlg, IDC_ETEXT, textstr, _countof(textstr));
			wSetData(&opt.eText, textstr);
			GetDlgItemText(hdlg, IDC_NTEXT, textstr, _countof(textstr));
			wSetData(&opt.nText, textstr);
			GetDlgItemText(hdlg, IDC_HTEXT, textstr, _countof(textstr));
			wSetData(&opt.hText, textstr);
			GetDlgItemText(hdlg, IDC_XTEXT, textstr, _countof(textstr));
			wSetData(&opt.xText, textstr);
			GetDlgItemText(hdlg, IDC_BTITLE2, textstr, _countof(textstr));
			wSetData(&opt.sText, textstr);
			SaveOptions();
			UpdateAllInfo(0, 0);
			break;
		}
		break;
	}
	return FALSE;
}