INT_PTR CALLBACK DlgProcGenOpts(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_USER + 1:
		{
			MCONTACT hContact = wParam;
			DBCONTACTWRITESETTING *ws = (DBCONTACTWRITESETTING *)lParam;
			if (hContact == NULL && ws != NULL && ws->szModule != NULL && ws->szSetting != NULL && mir_strcmpi(ws->szModule, "CList") == 0 && mir_strcmpi(ws->szSetting, "UseGroups") == 0 && IsWindowVisible(hwndDlg))
				CheckDlgButton(hwndDlg, IDC_DISABLEGROUPS, ws->value.bVal == 0 ? BST_CHECKED : BST_UNCHECKED);
		}
		break;

	case WM_DESTROY:
		UnhookEvent((HANDLE)GetWindowLongPtr(hwndDlg, GWLP_USERDATA));
		break;

	case WM_INITDIALOG:
		opt_gen_opts_changed = 0;
		TranslateDialogDefault(hwndDlg);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)HookEventMessage(ME_DB_CONTACT_SETTINGCHANGED, hwndDlg, WM_USER + 1));
		CheckDlgButton(hwndDlg, IDC_ONTOP, cfg::getByte("CList", "OnTop", SETTING_ONTOP_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_HIDEOFFLINE, cfg::getByte(NULL, "CList", "HideOffline", SETTING_HIDEOFFLINE_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_HIDEEMPTYGROUPS, cfg::getByte("CList", "HideEmptyGroups", SETTING_HIDEEMPTYGROUPS_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_DISABLEGROUPS, cfg::getByte("CList", "UseGroups", SETTING_USEGROUPS_DEFAULT) ? BST_UNCHECKED : BST_CHECKED);
		CheckDlgButton(hwndDlg, IDC_CONFIRMDELETE, cfg::getByte("CList", "ConfirmDelete", SETTING_CONFIRMDELETE_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		{
			DWORD caps = CallService(MS_CLUI_GETCAPS, CLUICAPS_FLAGS1, 0);
			if (!(caps & CLUIF_HIDEEMPTYGROUPS))
				ShowWindow(GetDlgItem(hwndDlg, IDC_HIDEEMPTYGROUPS), SW_HIDE);
			if (!(caps & CLUIF_DISABLEGROUPS))
				ShowWindow(GetDlgItem(hwndDlg, IDC_DISABLEGROUPS), SW_HIDE);
			if (caps & CLUIF_HASONTOPOPTION)
				ShowWindow(GetDlgItem(hwndDlg, IDC_ONTOP), SW_HIDE);
			if (caps & CLUIF_HASAUTOHIDEOPTION) {
			}
		}

		CheckDlgButton(hwndDlg, IDC_SHOWBOTTOMBUTTONS, cfg::dat.dwFlags & CLUI_FRAME_SHOWBOTTOMBUTTONS ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_CLISTSUNKEN, cfg::dat.dwFlags & CLUI_FRAME_CLISTSUNKEN ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_EVENTAREAAUTOHIDE, cfg::dat.dwFlags & CLUI_FRAME_AUTOHIDENOTIFY ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_EVENTAREASUNKEN, (cfg::dat.dwFlags & CLUI_FRAME_EVENTAREASUNKEN) ? BST_CHECKED : BST_UNCHECKED);

		CheckDlgButton(hwndDlg, IDC_ONECLK, cfg::getByte("CList", "Tray1Click", SETTING_TRAY1CLICK_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_ALWAYSSTATUS, cfg::getByte("CList", "AlwaysStatus", SETTING_ALWAYSSTATUS_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_ALWAYSMULTI, !cfg::getByte("CList", "AlwaysMulti", SETTING_ALWAYSMULTI_DEFAULT) ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_DONTCYCLE, cfg::getByte("CList", "TrayIcon", SETTING_TRAYICON_DEFAULT) == SETTING_TRAYICON_SINGLE ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_CYCLE, cfg::getByte("CList", "TrayIcon", SETTING_TRAYICON_DEFAULT) == SETTING_TRAYICON_CYCLE ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_MULTITRAY, cfg::getByte("CList", "TrayIcon", SETTING_TRAYICON_DEFAULT) == SETTING_TRAYICON_MULTI ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_DISABLEBLINK, cfg::getByte("CList", "DisableTrayFlash", 0) == 1 ? BST_CHECKED : BST_UNCHECKED);
		CheckDlgButton(hwndDlg, IDC_ICONBLINK, cfg::getByte("CList", "NoIconBlink", 0) == 1 ? BST_CHECKED : BST_UNCHECKED);
		if (IsDlgButtonChecked(hwndDlg, IDC_DONTCYCLE)) {
			Utils::enableDlgControl(hwndDlg, IDC_CYCLETIMESPIN, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_CYCLETIME, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_ALWAYSMULTI, FALSE);
		}
		if (IsDlgButtonChecked(hwndDlg, IDC_CYCLE)) {
			Utils::enableDlgControl(hwndDlg, IDC_PRIMARYSTATUS, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_ALWAYSMULTI, FALSE);
		}
		if (IsDlgButtonChecked(hwndDlg, IDC_MULTITRAY)) {
			Utils::enableDlgControl(hwndDlg, IDC_CYCLETIMESPIN, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_CYCLETIME, FALSE);
			Utils::enableDlgControl(hwndDlg, IDC_PRIMARYSTATUS, FALSE);
		}
		SendDlgItemMessage(hwndDlg, IDC_CYCLETIMESPIN, UDM_SETRANGE, 0, MAKELONG(120, 1));
		SendDlgItemMessage(hwndDlg, IDC_CYCLETIMESPIN, UDM_SETPOS, 0, MAKELONG(cfg::getWord("CList", "CycleTime", SETTING_CYCLETIME_DEFAULT), 0));
		{
			ptrA szPrimaryStatus(db_get_sa(NULL, "CList", "PrimaryStatus"));

			int item = SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_ADDSTRING, 0, (LPARAM)TranslateT("Global"));
			SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_SETITEMDATA, item, (LPARAM)0);

			int count;
			PROTOACCOUNT **accs;
			Proto_EnumAccounts(&count, &accs);
			for (int i = 0; i < count; i++) {
				if (!Proto_IsAccountEnabled(accs[i]) || CallProtoService(accs[i]->szModuleName, PS_GETCAPS, PFLAGNUM_2, 0) == 0)
					continue;

				item = SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_ADDSTRING, 0, (LPARAM)accs[i]->tszAccountName);
				SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_SETITEMDATA, item, (LPARAM)accs[i]);
				if (!mir_strcmp(szPrimaryStatus, accs[i]->szModuleName))
					SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_SETCURSEL, item, 0);
			}
		}
		if (CB_ERR == (int)SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_GETCURSEL, 0, 0))
			SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_SETCURSEL, 0, 0);
		SendDlgItemMessage(hwndDlg, IDC_BLINKSPIN, UDM_SETBUDDY, (WPARAM)GetDlgItem(hwndDlg, IDC_BLINKTIME), 0);
		SendDlgItemMessage(hwndDlg, IDC_BLINKSPIN, UDM_SETRANGE, 0, MAKELONG(0x3FFF, 250));
		SendDlgItemMessage(hwndDlg, IDC_BLINKSPIN, UDM_SETPOS, 0, MAKELONG(cfg::getWord("CList", "IconFlashTime", 550), 0));
		CheckDlgButton(hwndDlg, IDC_NOTRAYINFOTIPS, cfg::dat.bNoTrayTips ? 1 : 0);
		CheckDlgButton(hwndDlg, IDC_APPLYLASTVIEWMODE, cfg::getByte("CList", "AutoApplyLastViewMode", 0) ? BST_CHECKED : BST_UNCHECKED);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_DONTCYCLE || LOWORD(wParam) == IDC_CYCLE || LOWORD(wParam) == IDC_MULTITRAY) {
			Utils::enableDlgControl(hwndDlg, IDC_PRIMARYSTATUS, IsDlgButtonChecked(hwndDlg, IDC_DONTCYCLE));
			Utils::enableDlgControl(hwndDlg, IDC_CYCLETIME, IsDlgButtonChecked(hwndDlg, IDC_CYCLE));
			Utils::enableDlgControl(hwndDlg, IDC_CYCLETIMESPIN, IsDlgButtonChecked(hwndDlg, IDC_CYCLE));
			Utils::enableDlgControl(hwndDlg, IDC_ALWAYSMULTI, IsDlgButtonChecked(hwndDlg, IDC_MULTITRAY));
		}
		if (LOWORD(wParam) == IDC_CYCLETIME && HIWORD(wParam) != EN_CHANGE)
			break;
		if (LOWORD(wParam) == IDC_PRIMARYSTATUS && HIWORD(wParam) != CBN_SELCHANGE)
			break;
		if (LOWORD(wParam) == IDC_CYCLETIME && (HIWORD(wParam) != EN_CHANGE || (HWND)lParam != GetFocus()))
			return 0;
		if (LOWORD(wParam) == IDC_BLINKTIME && (HIWORD(wParam) != EN_CHANGE || (HWND)lParam != GetFocus()))
			return 0;
		SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		opt_gen_opts_changed = TRUE;
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom) {
		case 0:
			switch (((LPNMHDR)lParam)->code) {
			case PSN_APPLY:
				if (!opt_gen_opts_changed)
					return TRUE;

				cfg::writeByte("CList", "HideOffline", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_HIDEOFFLINE));
				{
					DWORD caps = CallService(MS_CLUI_GETCAPS, CLUICAPS_FLAGS1, 0);
					if (caps & CLUIF_HIDEEMPTYGROUPS)
						cfg::writeByte("CList", "HideEmptyGroups", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_HIDEEMPTYGROUPS));
					if (caps & CLUIF_DISABLEGROUPS)
						cfg::writeByte("CList", "UseGroups", (BYTE)BST_UNCHECKED == IsDlgButtonChecked(hwndDlg, IDC_DISABLEGROUPS));
					if (!(caps & CLUIF_HASONTOPOPTION)) {
						cfg::writeByte("CList", "OnTop", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_ONTOP));
						SetWindowPos(pcli->hwndContactList, IsDlgButtonChecked(hwndDlg, IDC_ONTOP) ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
					}
				}
				cfg::writeByte("CList", "ConfirmDelete", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_CONFIRMDELETE));
				cfg::writeByte("CList", "Tray1Click", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_ONECLK));
				cfg::writeByte("CList", "AlwaysStatus", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_ALWAYSSTATUS));
				cfg::writeByte("CList", "AlwaysMulti", (BYTE)BST_UNCHECKED == IsDlgButtonChecked(hwndDlg, IDC_ALWAYSMULTI));
				cfg::writeByte("CList", "TrayIcon", (BYTE)(IsDlgButtonChecked(hwndDlg, IDC_DONTCYCLE) ? SETTING_TRAYICON_SINGLE : (IsDlgButtonChecked(hwndDlg, IDC_CYCLE) ? SETTING_TRAYICON_CYCLE : SETTING_TRAYICON_MULTI)));
				cfg::writeWord("CList", "CycleTime", (WORD)SendDlgItemMessage(hwndDlg, IDC_CYCLETIMESPIN, UDM_GETPOS, 0, 0));
				cfg::writeWord("CList", "IconFlashTime", (WORD)SendDlgItemMessage(hwndDlg, IDC_BLINKSPIN, UDM_GETPOS, 0, 0));
				cfg::writeByte("CList", "DisableTrayFlash", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_DISABLEBLINK));
				cfg::writeByte("CList", "NoIconBlink", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_ICONBLINK));
				cfg::writeByte("CList", "AutoApplyLastViewMode", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_APPLYLASTVIEWMODE));

				__setFlag(CLUI_FRAME_EVENTAREASUNKEN, IsDlgButtonChecked(hwndDlg, IDC_EVENTAREASUNKEN));
				__setFlag(CLUI_FRAME_AUTOHIDENOTIFY, IsDlgButtonChecked(hwndDlg, IDC_EVENTAREAAUTOHIDE));

				__setFlag(CLUI_FRAME_SHOWBOTTOMBUTTONS, IsDlgButtonChecked(hwndDlg, IDC_SHOWBOTTOMBUTTONS));
				__setFlag(CLUI_FRAME_CLISTSUNKEN, IsDlgButtonChecked(hwndDlg, IDC_CLISTSUNKEN));

				cfg::dat.bNoTrayTips = IsDlgButtonChecked(hwndDlg, IDC_NOTRAYINFOTIPS) ? 1 : 0;
				cfg::writeByte("CList", "NoTrayTips", (BYTE)cfg::dat.bNoTrayTips);
				{
					int cursel = SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_GETCURSEL, 0, 0);
					PROTOACCOUNT *pa = (PROTOACCOUNT *)SendDlgItemMessage(hwndDlg, IDC_PRIMARYSTATUS, CB_GETITEMDATA, cursel, 0);
					if (!pa)
						db_unset(NULL, "CList", "PrimaryStatus");
					else
						cfg::writeString(NULL, "CList", "PrimaryStatus", pa->szModuleName);
				}
				pcli->pfnTrayIconIconsChanged();
				cfg::writeDword("CLUI", "Frameflags", cfg::dat.dwFlags);
				ConfigureFrame();
				ConfigureCLUIGeometry(1);
				ConfigureEventArea();
				HideShowNotifyFrame();
				SendMessage(pcli->hwndContactTree, WM_SIZE, 0, 0);
				SendMessage(pcli->hwndContactList, WM_SIZE, 0, 0);
				LoadContactTree(); /* this won't do job properly since it only really works when changes happen */
				pcli->pfnClcBroadcast(CLM_AUTOREBUILD, 0, 0);
				PostMessage(pcli->hwndContactList, CLUIINTM_REDRAW, 0, 0);

				opt_gen_opts_changed = 0;
				return TRUE;
			}
			break;
		}
		break;
	}
	return FALSE;
}