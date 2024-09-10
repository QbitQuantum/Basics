INT_PTR CALLBACK DlgProcSBarOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	StatusBarProtocolOptions *dat = (StatusBarProtocolOptions*)GetWindowLongPtr(GetDlgItem(hwndDlg,IDC_STATUSBAR_PROTO_LIST),GWLP_USERDATA);
	LOGFONTA lf;
	BOOL perProto = IsDlgButtonChecked(hwndDlg, IDC_STATUSBAR_PER_PROTO);
	HWND hwndComboBox = GetDlgItem( hwndDlg, IDC_STATUSBAR_PROTO_LIST );
	int curSelProto = SendMessage(hwndComboBox, CB_GETITEMDATA, SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0), NULL) - 1; //first entry is the combo box is a constant.
	if (curSelProto < 0)
		perProto = FALSE;

	switch (msg) {
	case WM_INITDIALOG:
		perProto = (BOOL)db_get_b(NULL,"CLUI","SBarPerProto",SETTING_SBARPERPROTO_DEFAULT);

		TranslateDialogDefault(hwndDlg);

		CheckDlgButton(hwndDlg, IDC_SHOWSBAR, db_get_b(NULL,"CLUI","ShowSBar",SETTING_SHOWSBAR_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_STATUSBAR_PER_PROTO, perProto ? BST_CHECKED : BST_UNCHECKED);
		{
			// populate per-proto list box.
			char *szName;
			char buf[256];
			int count;

			SendMessage(hwndComboBox, CB_RESETCONTENT, 0, 0);

			PROTOACCOUNT **accs;
			ProtoEnumAccounts( &count, &accs );

			dat = (StatusBarProtocolOptions*)mir_alloc(sizeof(StatusBarProtocolOptions)*count);
			SetWindowLongPtr(GetDlgItem(hwndDlg,IDC_STATUSBAR_PROTO_LIST),GWLP_USERDATA,(LONG_PTR)dat);

			SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)TranslateT("<<Global>>"));
			SendMessage(hwndComboBox, CB_SETITEMDATA, 0, 0);

			for (int i=0; i < count; i++ ) {
				szName = accs[i]->szModuleName;
				dat[i].szName = szName;

				DWORD dwNewId = SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)accs[i]->tszAccountName);
				SendMessage(hwndComboBox, CB_SETITEMDATA, dwNewId, (LPARAM)(i+1));

				mir_snprintf(buf, SIZEOF(buf), "SBarAccountIsCustom_%s", szName);
				dat[i].AccountIsCustomized = db_get_b(NULL,"CLUI", buf, SETTING_SBARACCOUNTISCUSTOM_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "HideAccount_%s", szName);
				dat[i].HideAccount = db_get_b(NULL,"CLUI", buf, SETTING_SBARHIDEACCOUNT_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "SBarShow_%s", szName);
				dat[i].SBarShow = db_get_b(NULL,"CLUI", buf, SETTING_SBARSHOW_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "SBarRightClk_%s", szName);
				dat[i].SBarRightClk = db_get_b(NULL,"CLUI", buf, SETTING_SBARRIGHTCLK_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "ShowUnreadEmails_%s", szName);
				dat[i].ShowUnreadEmails = db_get_b(NULL,"CLUI", buf, SETTING_SHOWUNREADEMAILS_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "ShowXStatus_%s", szName);
				dat[i].ShowXStatus = db_get_b(NULL,"CLUI", buf, SETTING_SHOWXSTATUS_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "UseConnectingIcon_%s", szName);
				dat[i].UseConnectingIcon = db_get_b(NULL,"CLUI", buf, SETTING_USECONNECTINGICON_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "PaddingLeft_%s", szName);
				dat[i].PaddingLeft = db_get_dw(NULL,"CLUI", buf, SETTING_PADDINGLEFT_DEFAULT);

				mir_snprintf(buf, SIZEOF(buf), "PaddingRight_%s", szName);
				dat[i].PaddingRight = db_get_dw(NULL,"CLUI", buf, SETTING_PADDINGRIGHT_DEFAULT);
			}

			if (count)
				SendMessage(hwndComboBox, CB_SETCURSEL, 0, 0);
		}

		_GlobalOptions.AccountIsCustomized = TRUE;
		_GlobalOptions.SBarRightClk = db_get_b(NULL,"CLUI", "SBarRightClk", SETTING_SBARRIGHTCLK_DEFAULT);
		_GlobalOptions.ShowUnreadEmails = db_get_b(NULL,"CLUI", "ShowUnreadEmails", SETTING_SHOWUNREADEMAILS_DEFAULT);
		_GlobalOptions.ShowXStatus = db_get_b(NULL,"CLUI", "ShowXStatus", SETTING_SHOWXSTATUS_DEFAULT);
		_GlobalOptions.UseConnectingIcon = db_get_b(NULL,"CLUI", "UseConnectingIcon", SETTING_USECONNECTINGICON_DEFAULT);
		_GlobalOptions.SBarShow = db_get_b(NULL,"CLUI","SBarShow",SETTING_SBARSHOW_DEFAULT);

		CheckDlgButton(hwndDlg, IDC_EQUALSECTIONS, db_get_b(NULL,"CLUI","EqualSections",SETTING_EQUALSECTIONS_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);

		SendDlgItemMessage(hwndDlg,IDC_MULTI_SPIN,UDM_SETRANGE, 0, MAKELONG(50, 0));
		SendDlgItemMessage(hwndDlg,IDC_MULTI_SPIN,UDM_SETPOS, 0, MAKELONG( db_get_b(NULL,"CLUI","StatusBarProtosPerLine",SETTING_PROTOSPERLINE_DEFAULT),0));

		SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN,UDM_SETRANGE, 0, MAKELONG(50, 0));
		SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN,UDM_SETPOS, 0, MAKELONG(db_get_dw(NULL,"CLUI","LeftOffset",SETTING_LEFTOFFSET_DEFAULT),0));

		SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN2,UDM_SETRANGE, 0, MAKELONG(50, 0));
		SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN2,UDM_SETPOS, 0, MAKELONG(db_get_dw(NULL,"CLUI","RightOffset",SETTING_RIGHTOFFSET_DEFAULT),0));

		SendDlgItemMessage(hwndDlg,IDC_SBAR_BORDER_TOP_SPIN,UDM_SETRANGE, 0, MAKELONG(50, 0));
		SendDlgItemMessage(hwndDlg,IDC_SBAR_BORDER_TOP_SPIN,UDM_SETPOS, 0, MAKELONG(db_get_dw(NULL,"CLUI","TopOffset",SETTING_TOPOFFSET_DEFAULT),0));

		SendDlgItemMessage(hwndDlg,IDC_SBAR_BORDER_BOTTOM_SPIN,UDM_SETRANGE, 0, MAKELONG(50, 0));
		SendDlgItemMessage(hwndDlg,IDC_SBAR_BORDER_BOTTOM_SPIN,UDM_SETPOS, 0, MAKELONG(db_get_dw(NULL,"CLUI","BottomOffset",SETTING_BOTTOMOFFSET_DEFAULT),0));

		SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN3,UDM_SETRANGE, 0, MAKELONG(50, 0));
		SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN3,UDM_SETPOS, 0, MAKELONG(db_get_dw(NULL,"CLUI","SpaceBetween",SETTING_SPACEBETWEEN_DEFAULT),2));

		{
			int i, item;
			TCHAR *align[] = {LPGENT("Left"), LPGENT("Center"), LPGENT("Right")};
			for (i=0; i < SIZEOF(align); i++) {
				item = SendDlgItemMessage(hwndDlg,IDC_SBAR_HORIZ_ALIGN,CB_ADDSTRING, 0, (LPARAM)TranslateTS(align[i]));
			}

			SendDlgItemMessage(hwndDlg, IDC_SBAR_HORIZ_ALIGN, CB_SETCURSEL, db_get_b(NULL, "CLUI", "Align", SETTING_ALIGN_DEFAULT), 0);
		}

		{
			int i, item;
			TCHAR *align[] = {_T("Top"), _T("Center"), _T("Bottom")};
			for (i=0; i < SIZEOF(align); i++) {
				item = SendDlgItemMessage(hwndDlg,IDC_SBAR_VERT_ALIGN,CB_ADDSTRING, 0, (LPARAM)TranslateTS(align[i]));
			}

			SendDlgItemMessage(hwndDlg, IDC_SBAR_VERT_ALIGN, CB_SETCURSEL, db_get_b(NULL, "CLUI", "VAlign", SETTING_VALIGN_DEFAULT), 0);
		}

		{
			int en = IsDlgButtonChecked(hwndDlg,IDC_SHOWSBAR);
			int en_icons = IsDlgButtonChecked(hwndDlg,IDC_SHOWICON );

			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWICON),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWPROTO),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWSTATUS),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_RIGHTSTATUS),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_RIGHTMIRANDA),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_EQUALSECTIONS),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_USECONNECTINGICON),en && en_icons);
			EnableWindow(GetDlgItem(hwndDlg,IDC_USEOWNERDRAW),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN2),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON2),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN3),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON3),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_BUTTON_BROWSE),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOW_ONLY_IF_DIFFERENT),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_COLOUR),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWXSTATUSNAME),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWXSTATUS),en && en_icons);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWBOTH),en && en_icons && IsDlgButtonChecked(hwndDlg,IDC_SHOWXSTATUS) && !IsDlgButtonChecked(hwndDlg,IDC_SHOWNORMAL));
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWNORMAL),en && en_icons && IsDlgButtonChecked(hwndDlg,IDC_SHOWXSTATUS) &&  !IsDlgButtonChecked(hwndDlg,IDC_SHOWBOTH));
			EnableWindow(GetDlgItem(hwndDlg,IDC_TRANSPARENTOVERLAY),en && en_icons && IsDlgButtonChecked(hwndDlg,IDC_SHOWXSTATUS) && IsDlgButtonChecked(hwndDlg,IDC_SHOWNORMAL) &&  !IsDlgButtonChecked(hwndDlg,IDC_SHOWBOTH));
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWUNREADEMAIL),en);

			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON_LEFT),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN_LEFT),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON_RIGHT),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN_RIGHT),en);

			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI_2),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI_COUNT),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI_SPIN),en);

			EnableWindow(GetDlgItem(hwndDlg,IDC_STATUSBAR_PER_PROTO),en);
			EnableWindow(GetDlgItem(hwndDlg, IDC_STATUSBAR_PROTO_LIST), en && IsDlgButtonChecked(hwndDlg, IDC_STATUSBAR_PER_PROTO));
			EnableWindow(GetDlgItem(hwndDlg, IDC_SBAR_USE_ACCOUNT_SETTINGS), FALSE);
		}

		UpdateStatusBarOptionsDisplay(hwndDlg);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			if (HIWORD(wParam) == BN_CLICKED)
			{
				CHOOSEFONTA fnt;
				memset(&fnt, 0, sizeof(CHOOSEFONTA));
				fnt.lStructSize = sizeof(CHOOSEFONTA);
				fnt.hwndOwner = hwndDlg;
				fnt.Flags = CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT;
				fnt.lpLogFont = &lf;
				ChooseFontA(&fnt);
				SendMessage(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);
				return 0;
			}
		}
		else if (LOWORD(wParam) == IDC_COLOUR  || (LOWORD(wParam) == IDC_SBAR_HORIZ_ALIGN && HIWORD(wParam) == CBN_SELCHANGE)) SendMessage(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);
		else if (LOWORD(wParam) == IDC_SHOWSBAR) {
			int en = IsDlgButtonChecked(hwndDlg,IDC_SHOWSBAR);
			int en_icons = IsDlgButtonChecked(hwndDlg,IDC_SHOWICON );
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWICON),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWPROTO),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWSTATUS),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_RIGHTSTATUS),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_RIGHTMIRANDA),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_EQUALSECTIONS),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_USECONNECTINGICON),en && en_icons);
			EnableWindow(GetDlgItem(hwndDlg,IDC_USEOWNERDRAW),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN2),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON2),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETSPIN3),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_OFFSETICON3),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_BORDER_TOP),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_BORDER_TOP_SPIN),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_BORDER_BOTTOM),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_BORDER_BOTTOM_SPIN),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_HORIZ_ALIGN),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_COLOUR),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_BUTTON1),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWXSTATUSNAME),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWXSTATUS),en && en_icons);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SHOWUNREADEMAIL),en);

			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI_2),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI_COUNT),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_MULTI_SPIN),en);

			EnableWindow(GetDlgItem(hwndDlg,IDC_STATUSBAR_PER_PROTO),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_STATUSBAR_PROTO_LIST),en && IsDlgButtonChecked(hwndDlg,IDC_STATUSBAR_PER_PROTO));
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_USE_ACCOUNT_SETTINGS),en && IsDlgButtonChecked(hwndDlg,IDC_STATUSBAR_PER_PROTO));

			UpdateStatusBarOptionsDisplay(hwndDlg);

			SendMessage(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);
		}
		else if (LOWORD(wParam) == IDC_STATUSBAR_PER_PROTO)
		{
			int en = IsDlgButtonChecked(hwndDlg,IDC_STATUSBAR_PER_PROTO);
			EnableWindow(GetDlgItem(hwndDlg,IDC_STATUSBAR_PROTO_LIST),en);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_HIDE_ACCOUNT_COMPLETELY), en && perProto);
			EnableWindow(GetDlgItem(hwndDlg,IDC_SBAR_USE_ACCOUNT_SETTINGS), en);

			UpdateStatusBarOptionsDisplay(hwndDlg);

			SendMessage(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);
		}
		else if (
			LOWORD(wParam) == IDC_SHOWXSTATUS  ||
			LOWORD(wParam) == IDC_SHOWBOTH  ||
			LOWORD(wParam) == IDC_SHOWNORMAL  ||
			LOWORD(wParam) == IDC_TRANSPARENTOVERLAY  ||
			LOWORD(wParam) == IDC_SHOWXSTATUSNAME)
		{
			UpdateXStatusIconOptions(hwndDlg, perProto, dat, curSelProto);
		}
		else if (LOWORD(wParam) == IDC_SBAR_USE_ACCOUNT_SETTINGS)
		{
			if (perProto) {
				dat[curSelProto].AccountIsCustomized = IsDlgButtonChecked(hwndDlg, IDC_SBAR_USE_ACCOUNT_SETTINGS);
				UpdateStatusBarOptionsDisplay(hwndDlg);
			}
		}
		else if (LOWORD(wParam) == IDC_SBAR_HIDE_ACCOUNT_COMPLETELY)
		{
			if (perProto)
				dat[curSelProto].HideAccount = IsDlgButtonChecked(hwndDlg, IDC_SBAR_HIDE_ACCOUNT_COMPLETELY);
		}
		else if (LOWORD(wParam) == IDC_USECONNECTINGICON)
		{
			if (perProto)
				dat[curSelProto].UseConnectingIcon = IsDlgButtonChecked(hwndDlg, IDC_USECONNECTINGICON);
			else
				_GlobalOptions.UseConnectingIcon = IsDlgButtonChecked(hwndDlg, IDC_USECONNECTINGICON);
		}
		else if (LOWORD(wParam) == IDC_SHOWUNREADEMAIL)
		{
			if (perProto)
				dat[curSelProto].ShowUnreadEmails = IsDlgButtonChecked(hwndDlg, IDC_SHOWUNREADEMAIL);
			else
				_GlobalOptions.ShowUnreadEmails = IsDlgButtonChecked(hwndDlg, IDC_SHOWUNREADEMAIL);
		}
		else if (LOWORD(wParam) == IDC_SHOWICON || LOWORD(wParam) == IDC_SHOWPROTO || LOWORD(wParam) == IDC_SHOWSTATUS)
		{
			BYTE val = (IsDlgButtonChecked(hwndDlg, IDC_SHOWICON)?1:0)|(IsDlgButtonChecked(hwndDlg, IDC_SHOWPROTO)?2:0)|(IsDlgButtonChecked(hwndDlg, IDC_SHOWSTATUS)?4:0);
			if (perProto)
				dat[curSelProto].SBarShow = val;
			else
				_GlobalOptions.SBarShow = val;

			UpdateStatusBarOptionsDisplay(hwndDlg);
		}
		else if (LOWORD(wParam) == IDC_RIGHTSTATUS || LOWORD(wParam) == IDC_RIGHTMIRANDA)
		{
			if (perProto)
				dat[curSelProto].SBarRightClk = IsDlgButtonChecked(hwndDlg,IDC_RIGHTMIRANDA);
			else
				_GlobalOptions.SBarRightClk = IsDlgButtonChecked(hwndDlg,IDC_RIGHTMIRANDA);
		}
		else if (LOWORD(wParam) == IDC_OFFSETICON_LEFT)
		{
			if (perProto)
				dat[curSelProto].PaddingLeft = (DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN_LEFT,UDM_GETPOS, 0, 0);
			else
				_GlobalOptions.PaddingLeft = (DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN_LEFT,UDM_GETPOS, 0, 0);
		}
		else if (LOWORD(wParam) == IDC_OFFSETICON_RIGHT)
		{
			if (perProto)
				dat[curSelProto].PaddingRight = (DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN_RIGHT,UDM_GETPOS, 0, 0);
			else
				_GlobalOptions.PaddingRight = (DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN_RIGHT,UDM_GETPOS, 0, 0);
		}
		else if ((
				LOWORD(wParam) == IDC_MULTI_COUNT  ||
				LOWORD(wParam) == IDC_OFFSETICON  ||
				LOWORD(wParam) == IDC_OFFSETICON2  ||
				LOWORD(wParam) == IDC_OFFSETICON3  ||
				LOWORD(wParam) == IDC_SBAR_BORDER_BOTTOM  ||
				LOWORD(wParam) == IDC_SBAR_BORDER_TOP
			) && (
				HIWORD(wParam) != EN_CHANGE  ||
				(HWND)lParam != GetFocus()
			))
			return 0; // dont make apply enabled during buddy set crap
		else if ( LOWORD(wParam) == IDC_STATUSBAR_PROTO_LIST )
		{
			UpdateStatusBarOptionsDisplay(hwndDlg);
			return 0;
		}
		SendMessage(GetParent(hwndDlg), PSM_CHANGED, (WPARAM)hwndDlg, 0);
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case PSN_APPLY:
			{
				int count = db_get_dw(0, "Protocols","ProtoCount",-1);
				db_set_b(NULL, "CLUI", "SBarPerProto", IsDlgButtonChecked(hwndDlg, IDC_STATUSBAR_PER_PROTO));

				for (int i=0; i < count; i++) {
					StatusBarProtocolOptions sbpo = dat[i];
					char *defProto = sbpo.szName;

					char settingBuf[256];
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "SBarAccountIsCustom_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,(BYTE)sbpo.AccountIsCustomized);

					mir_snprintf(settingBuf, SIZEOF(settingBuf), "HideAccount_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,(BYTE)sbpo.HideAccount);

					mir_snprintf(settingBuf, SIZEOF(settingBuf), "SBarShow_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,(BYTE)sbpo.SBarShow);
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "SBarRightClk_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,(BYTE)sbpo.SBarRightClk);
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "UseConnectingIcon_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,(BYTE)sbpo.UseConnectingIcon);
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "ShowUnreadEmails_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,(BYTE)sbpo.ShowUnreadEmails);
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "ShowXStatus_%s", defProto);
					db_set_b(NULL,"CLUI",settingBuf,sbpo.ShowXStatus);
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "PaddingLeft_%s", defProto);
					db_set_dw(NULL,"CLUI",settingBuf,sbpo.PaddingLeft);
					mir_snprintf(settingBuf, SIZEOF(settingBuf), "PaddingRight_%s", defProto);
					db_set_dw(NULL,"CLUI",settingBuf,sbpo.PaddingRight);
				}

				db_set_b(NULL,"CLUI","SBarShow",(BYTE)_GlobalOptions.SBarShow);
				db_set_b(NULL,"CLUI","SBarRightClk",(BYTE)_GlobalOptions.SBarRightClk);
				db_set_b(NULL,"CLUI","UseConnectingIcon",(BYTE)_GlobalOptions.UseConnectingIcon);
				db_set_b(NULL,"CLUI","ShowUnreadEmails",(BYTE)_GlobalOptions.ShowUnreadEmails);
				db_set_b(NULL,"CLUI","ShowXStatus",_GlobalOptions.ShowXStatus);
				db_set_dw(NULL,"CLUI","PaddingLeft",_GlobalOptions.PaddingLeft);
				db_set_dw(NULL,"CLUI","PaddingRight",_GlobalOptions.PaddingRight);


				db_set_b(NULL,"CLUI","StatusBarProtosPerLine",(BYTE)SendDlgItemMessage(hwndDlg,IDC_MULTI_SPIN,UDM_GETPOS, 0, 0));
				db_set_b(NULL,"CLUI","EqualSections",(BYTE)IsDlgButtonChecked(hwndDlg,IDC_EQUALSECTIONS));
				db_set_b(NULL,"CLUI","Align",(BYTE)SendDlgItemMessage(hwndDlg,IDC_SBAR_HORIZ_ALIGN,CB_GETCURSEL, 0, 0));
				db_set_b(NULL,"CLUI","VAlign",(BYTE)SendDlgItemMessage(hwndDlg,IDC_SBAR_VERT_ALIGN,CB_GETCURSEL, 0, 0));
				db_set_dw(NULL,"CLUI","LeftOffset",(DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN,UDM_GETPOS, 0, 0));
				db_set_dw(NULL,"CLUI","RightOffset",(DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN2,UDM_GETPOS, 0, 0));
				db_set_dw(NULL,"CLUI","TopOffset",(DWORD)SendDlgItemMessage(hwndDlg,IDC_SBAR_BORDER_TOP_SPIN,UDM_GETPOS, 0, 0));
				db_set_dw(NULL,"CLUI","BottomOffset",(DWORD)SendDlgItemMessage(hwndDlg,IDC_SBAR_BORDER_BOTTOM_SPIN,UDM_GETPOS, 0, 0));
				db_set_dw(NULL,"CLUI","SpaceBetween",(DWORD)SendDlgItemMessage(hwndDlg,IDC_OFFSETSPIN3,UDM_GETPOS, 0, 0));
				db_set_dw(NULL,"ModernData","StatusBarFontCol",SendDlgItemMessage(hwndDlg,IDC_COLOUR,CPM_GETCOLOUR, 0, 0));
				db_set_b(NULL,"CLUI","ShowSBar",(BYTE)IsDlgButtonChecked(hwndDlg,IDC_SHOWSBAR));

				LoadStatusBarData();
				cliCluiProtocolStatusChanged(0, 0);
				return TRUE;
			}
		}
		break;

	case WM_DESTROY:
		mir_free(dat);
		break;
	}
	return FALSE;
}