// copied and modified from NewStatusNotify
INT_PTR CALLBACK DlgPopupOpts(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	int ID;
	TCHAR str[512];
	HMENU hMenu, hMenu1;
	RECT pos;
	HWND button;
	MCONTACT hContact;

	switch (msg) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hdlg);
		SaveOptions();

		// click actions
		hMenu  = LoadMenu(hInst, MAKEINTRESOURCE(IDR_PMENU));
		hMenu1 = GetSubMenu(hMenu, 0);
		GetMenuString(hMenu1, opt.LeftClickAction, str, sizeof(str), MF_BYCOMMAND);
		SetDlgItemText(hdlg, IDC_LeftClick, TranslateTS(str));
		GetMenuString(hMenu1, opt.RightClickAction, str, sizeof(str), MF_BYCOMMAND);
		SetDlgItemText(hdlg, IDC_RightClick, TranslateTS(str));
		DestroyMenu(hMenu);

		// other options
		CheckDlgButton(hdlg, IDC_E, opt.UsePopup);
		CheckDlgButton(hdlg, IDC_POP2, opt.AlertPopup);
		CheckDlgButton(hdlg, IDC_POP1, opt.UpdatePopup);
		CheckDlgButton(hdlg, IDC_CH, opt.PopupOnChange);
		CheckDlgButton(hdlg, IDC_W, opt.ShowWarnings);
		SetDlgItemText(hdlg,IDC_PText, opt.pText);
		SetDlgItemText(hdlg,IDC_PTitle, opt.pTitle);
		// setting popup delay option
		_ltot(opt.pDelay, str, 10);
		SetDlgItemText(hdlg,IDC_DELAY, str);
		if (opt.pDelay == -1)
			CheckRadioButton(hdlg, IDC_PD1, IDC_PD3, IDC_PD2);
		else if (opt.pDelay == 0)
			CheckRadioButton(hdlg, IDC_PD1, IDC_PD3, IDC_PD1);
		else
			CheckRadioButton(hdlg, IDC_PD1, IDC_PD3, IDC_PD3);
		//Colours. First step is configuring the colours.
		SendDlgItemMessage(hdlg,IDC_BGCOLOUR,CPM_SETCOLOUR,0,opt.BGColour);
		SendDlgItemMessage(hdlg,IDC_TEXTCOLOUR,CPM_SETCOLOUR,0,opt.TextColour);
		//Second step is disabling them if we want to use default Windows ones.
		CheckDlgButton(hdlg, IDC_USEWINCOLORS,opt.UseWinColors?BST_CHECKED:BST_UNCHECKED);
		EnableWindow(GetDlgItem(hdlg, IDC_BGCOLOUR), !opt.UseWinColors);
		EnableWindow(GetDlgItem(hdlg, IDC_TEXTCOLOUR), !opt.UseWinColors);

		// buttons
		SendMessage(GetDlgItem(hdlg,IDC_PREVIEW), BUTTONSETASFLATBTN, TRUE, 0);
		SendMessage(GetDlgItem(hdlg,IDC_PDEF), BUTTONSETASFLATBTN, TRUE, 0);
		SendMessage(GetDlgItem(hdlg,IDC_LeftClick), BUTTONSETASFLATBTN, TRUE, 0);
		SendMessage(GetDlgItem(hdlg,IDC_RightClick), BUTTONSETASFLATBTN, TRUE, 0);
		SendMessage(GetDlgItem(hdlg,IDC_VAR3), BUTTONSETASFLATBTN, TRUE, 0);
		return TRUE;

	case WM_COMMAND:
		// enable the "apply" button 
		if (HIWORD(wParam) == BN_CLICKED && GetFocus() == (HWND)lParam)
			SendMessage(GetParent(hdlg),PSM_CHANGED,0,0);
		if ( !((LOWORD(wParam) == IDC_UPDATE || LOWORD(wParam) == IDC_DEGREE) && 
			(HIWORD(wParam) != EN_CHANGE || (HWND)lParam != GetFocus())))
			SendMessage(GetParent(hdlg),PSM_CHANGED,0,0);
		//These are simple clicks: we don't save, but we tell the Options Page to enable the "Apply" button.
		switch(LOWORD(wParam)) {
		case IDC_BGCOLOUR: //Fall through
		case IDC_TEXTCOLOUR:
			// select new colors
			if (HIWORD(wParam) == CPN_COLOURCHANGED)
				SendMessage(GetParent(hdlg), PSM_CHANGED, 0, 0);
			break;

		case IDC_USEWINCOLORS:
			// use window color - enable/disable color selection controls
			EnableWindow(GetDlgItem(hdlg, IDC_BGCOLOUR), !(opt.UseWinColors));
			EnableWindow(GetDlgItem(hdlg, IDC_TEXTCOLOUR), !(opt.UseWinColors));
			SendMessage(GetParent(hdlg), PSM_CHANGED, 0, 0);
			break;

		case IDC_E:
		case IDC_CH:
			SendMessage(GetParent(hdlg), PSM_CHANGED, 0, 0);
			break;

		case IDC_RightClick:
			// right click action selection menu
			button = GetDlgItem(hdlg, IDC_RightClick);
			GetWindowRect(button, &pos); 

			hMenu  = LoadMenu(hInst, MAKEINTRESOURCE(IDR_PMENU));
			hMenu1 = GetSubMenu(hMenu, 0);
			TranslateMenu(hMenu1);
			SelectMenuItem(hMenu1, opt.RightClickAction);
			ID = TrackPopupMenu(hMenu1, TPM_LEFTBUTTON|TPM_RETURNCMD, pos.left, pos.bottom, 0, hdlg, NULL);
			if (ID)   opt.RightClickAction = ID;
			DestroyMenu(hMenu);

			hMenu  = LoadMenu(hInst, MAKEINTRESOURCE(IDR_PMENU));
			hMenu1 = GetSubMenu(hMenu, 0);
			GetMenuString(hMenu1, opt.RightClickAction, str, sizeof(str), MF_BYCOMMAND);
			SetDlgItemText(hdlg, IDC_RightClick, TranslateTS(str));
			DestroyMenu(hMenu);
			break;

		case IDC_LeftClick:
			// left click action selection menu
			button = GetDlgItem(hdlg, IDC_LeftClick);
			GetWindowRect(button, &pos); 

			hMenu  = LoadMenu(hInst, MAKEINTRESOURCE(IDR_PMENU));
			hMenu1 = GetSubMenu(hMenu, 0);
			TranslateMenu(hMenu1);
			SelectMenuItem(hMenu1, opt.LeftClickAction);
			ID = TrackPopupMenu(hMenu1, TPM_LEFTBUTTON|TPM_RETURNCMD, pos.left, pos.bottom, 0, hdlg, NULL);
			if (ID)   opt.LeftClickAction = ID;
			DestroyMenu(hMenu);

			hMenu  = LoadMenu(hInst, MAKEINTRESOURCE(IDR_PMENU));
			hMenu1 = GetSubMenu(hMenu, 0);
			GetMenuString(hMenu1, opt.LeftClickAction, str, sizeof(str), MF_BYCOMMAND);
			SetDlgItemText(hdlg, IDC_LeftClick, TranslateTS(str));
			DestroyMenu(hMenu);
			break;

		case IDC_PD1:
			// Popup delay setting from Popup plugin
			SetDlgItemText(hdlg, IDC_DELAY, _T("0"));
			CheckRadioButton(hdlg, IDC_PD1, IDC_PD3, IDC_PD1);
			break;

		case IDC_PD2:
			// Popup delay = permanent
			SetDlgItemText(hdlg, IDC_DELAY, _T("-1"));
			CheckRadioButton(hdlg, IDC_PD1, IDC_PD3, IDC_PD2);
			break;

		case IDC_DELAY:
			// if text is edited
			CheckRadioButton(hdlg, IDC_PD1, IDC_PD3, IDC_PD3);
			break;

		case IDC_PDEF:
			// set the default value for popup texts
			SetTextDefault("Pp");
			SetDlgItemText(hdlg,IDC_PText, opt.pText);
			SetDlgItemText(hdlg,IDC_PTitle, opt.pTitle);
			wfree(&opt.pText);
			wfree(&opt.pTitle);
			break;

		case IDC_VAR3:
			// display variable list
			_tcscpy(str, _T("                                                            \n"));		// to make the message box wider
			_tcscat(str, TranslateT("%c\tcurrent condition\n%d\tcurrent date\n%e\tdewpoint\n%f\tfeel-like temperature\n%h\ttoday's high\n%i\twind direction\n%l\ttoday's low\n%m\thumidity\n%n\tstation name\n%p\tpressure\n%r\tsunrise time\n%s\tstation ID\n%t\ttemperature\n%u\tupdate time\n%v\tvisibility\n%w\twind speed\n%y\tsun set"));
			_tcscat(str, _T("\n"));
			_tcscat(str, TranslateT("%[..]\tcustom variables"));
			MessageBox(NULL, str, TranslateT("Variable List"), MB_OK|MB_ICONASTERISK|MB_TOPMOST);
			break;

		case IDC_PREVIEW:
			// popup preview
			hContact = opt.DefStn;
			ReadPopupOpt(hdlg);	// read new options to memory
			WeatherPopup((WPARAM)opt.DefStn, (BOOL)TRUE);	// display popup using new opt
			DestroyOptions();
			LoadOptions();		// restore old option in memory
			opt.DefStn = hContact;
			break;
		}
		break;
	
	case WM_NOTIFY: //Here we have pressed either the OK or the APPLY button.
		switch (((LPNMHDR)lParam)->code) {
			case PSN_APPLY: {
				ReadPopupOpt(hdlg);

				// save the options, and update main menu
				SaveOptions();
				UpdatePopupMenu(opt.UsePopup);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}