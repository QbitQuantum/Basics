/*
 * set_filter_proc - フィルタ設定のプロシージャ
 */
BOOL CALLBACK set_filter_proc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LV_COLUMN lvc;
	FILTER_INFO *fi;
	int i;
	BOOL enable;
#ifdef OP_XP_STYLE
	static long hThemeUp, hThemeDown;
#endif	// OP_XP_STYLE

	switch (uMsg) {
	case WM_INITDIALOG:
#ifdef OP_XP_STYLE
		// XP
		hThemeUp = open_theme(GetDlgItem(hDlg, IDC_BUTTON_UP), L"SCROLLBAR");
		hThemeDown = open_theme(GetDlgItem(hDlg, IDC_BUTTON_DOWN), L"SCROLLBAR");
#endif	// OP_XP_STYLE
		if (option.filter_all_action == FILTER_ACTION_ADD) {
			CheckDlgButton(hDlg, IDC_RADIO_ALL_ADD, 1);
		} else {
			CheckDlgButton(hDlg, IDC_RADIO_ALL_IGNORE, 1);
		}

		// リストビューのカラムの設定
		i = 0;
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		lvc.fmt = LVCFMT_LEFT;
		lvc.cx = 150;
		lvc.pszText = message_get_res(IDS_FILTER_LIST_NAME);
		lvc.iSubItem = i++;
		ListView_InsertColumn(GetDlgItem(hDlg, IDC_LIST_FILTER), lvc.iSubItem, &lvc);

		lvc.fmt = LVCFMT_LEFT;
		lvc.cx = 100;
		lvc.pszText = message_get_res(IDS_FILTER_LIST_ACTION);
		lvc.iSubItem = i++;
		ListView_InsertColumn(GetDlgItem(hDlg, IDC_LIST_FILTER), lvc.iSubItem, &lvc);

		lvc.fmt = LVCFMT_RIGHT;
		lvc.cx = 80;
		lvc.pszText = message_get_res(IDS_FILTER_LIST_SIZE);
		lvc.iSubItem = i++;
		ListView_InsertColumn(GetDlgItem(hDlg, IDC_LIST_FILTER), lvc.iSubItem, &lvc);

		// リストビューのスタイルの設定
		SetWindowLong(GetDlgItem(hDlg, IDC_LIST_FILTER), GWL_STYLE,
			GetWindowLong(GetDlgItem(hDlg, IDC_LIST_FILTER), GWL_STYLE) | LVS_SHOWSELALWAYS);
		SendDlgItemMessage(hDlg, IDC_LIST_FILTER, LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
			LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT |
			SendDlgItemMessage(hDlg, IDC_LIST_FILTER, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0));

		for (i = 0; i < option.filter_cnt; i++) {
			listview_set_filter(GetDlgItem(hDlg, IDC_LIST_FILTER), option.filter_info + i, TRUE);
		}
		SendMessage(hDlg, WM_LV_EVENT, LVN_ITEMCHANGED, 0);

		if (*cmd_filter != TEXT('\0')) {
			SetTimer(hDlg, ID_ADD_TIMER, 1, NULL);
		}
		break;

	case WM_DESTROY:
		listview_free_filter(GetDlgItem(hDlg, IDC_LIST_FILTER));
#ifdef OP_XP_STYLE
		// XP
		if (hThemeUp != 0 && hThemeDown != 0) {
			close_theme(hThemeUp);
			close_theme(hThemeDown);
		}
#endif	// OP_XP_STYLE
		break;

	case WM_DRAWITEM:
		switch ((UINT)wParam) {
		case IDC_BUTTON_UP:
			i = DFCS_SCROLLUP;
			break;

		case IDC_BUTTON_DOWN:
			i = DFCS_SCROLLDOWN;
			break;

		default:
			return FALSE;
		}
		// ボタンの描画
#ifdef OP_XP_STYLE
		if (hThemeUp != 0 && hThemeDown != 0) {
			draw_theme_scroll((LPDRAWITEMSTRUCT)lParam, i, (i == DFCS_SCROLLUP) ? hThemeUp : hThemeDown);
		} else {
			draw_scroll_sontrol((LPDRAWITEMSTRUCT)lParam, i);
		}
#else	// OP_XP_STYLE
		draw_scroll_sontrol((LPDRAWITEMSTRUCT)lParam, i);
#endif	// OP_XP_STYLE
		break;

#ifdef OP_XP_STYLE
	case WM_THEMECHANGED:
		// テーマの変更
		if (hThemeUp != 0 && hThemeDown != 0) {
			close_theme(hThemeUp);
			close_theme(hThemeDown);
		}
		hThemeUp = open_theme(GetDlgItem(hDlg, IDC_BUTTON_UP), L"SCROLLBAR");
		hThemeDown = open_theme(GetDlgItem(hDlg, IDC_BUTTON_DOWN), L"SCROLLBAR");
		break;
#endif	// OP_XP_STYLE

	case WM_NOTIFY:
		if (listview_notify_proc(hDlg, lParam, GetDlgItem(hDlg, IDC_LIST_FILTER)) == 0) {
			return OptionNotifyProc(hDlg, uMsg, wParam, lParam);
		}
		break;

	case WM_LV_EVENT:
		switch (wParam) {
		case LVN_ITEMCHANGED:
			enable = (ListView_GetSelectedCount(GetDlgItem(hDlg, IDC_LIST_FILTER)) <= 0) ? FALSE : TRUE;
			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_UP), enable);
			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_DOWN), enable);
			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_EDIT), enable);
			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_DELETE), enable);
			break;
		}
		break;

	case WM_TIMER:
		switch (wParam) {
		case ID_ADD_TIMER:
			KillTimer(hDlg, wParam);
			if ((i = filter_get_index(cmd_filter, 0)) == -1) {
				// 追加
				SendMessage(hDlg, WM_COMMAND, IDC_BUTTON_ADD, 0);
			} else {
				ListView_SetItemState(GetDlgItem(hDlg, IDC_LIST_FILTER), i,
					LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
				// 編集
				SendMessage(hDlg, WM_COMMAND, IDC_BUTTON_EDIT, 0);
			}
			break;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_UP:
			if ((i = ListView_GetNextItem(GetDlgItem(hDlg, IDC_LIST_FILTER), -1, LVNI_SELECTED)) == -1) {
				break;
			}
			if (i == 0) {
				break;
			}
			listview_move_item(GetDlgItem(hDlg, IDC_LIST_FILTER), i, -1);
			SetFocus(GetDlgItem(hDlg, LOWORD(wParam)));
			break;

		case IDC_BUTTON_DOWN:
			if ((i = ListView_GetNextItem(GetDlgItem(hDlg, IDC_LIST_FILTER), -1, LVNI_SELECTED)) == -1) {
				break;
			}
			if (i == ListView_GetItemCount(GetDlgItem(hDlg, IDC_LIST_FILTER)) - 1) {
				break;
			}
			listview_move_item(GetDlgItem(hDlg, IDC_LIST_FILTER), i, 1);
			SetFocus(GetDlgItem(hDlg, LOWORD(wParam)));
			break;

		case IDC_BUTTON_ADD:
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG_FILTER_SET), hDlg, set_filter_item_proc, 0);
			break;

		case IDC_BUTTON_EDIT:
			if ((i = ListView_GetNextItem(GetDlgItem(hDlg, IDC_LIST_FILTER), -1, LVNI_SELECTED)) == -1) {
				break;
			}
			DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG_FILTER_SET), hDlg, set_filter_item_proc,
				listview_get_lparam(GetDlgItem(hDlg, IDC_LIST_FILTER), i));
			listview_set_text(GetDlgItem(hDlg, IDC_LIST_FILTER), i);
			break;

		case IDC_BUTTON_DELETE:
			if ((i = ListView_GetNextItem(GetDlgItem(hDlg, IDC_LIST_FILTER), -1, LVNI_SELECTED)) == -1) {
				break;
			}
			if (MessageBox(hDlg, message_get_res(IDS_OPTION_DELETE), WINDOW_TITLE, MB_ICONQUESTION | MB_YESNO) == IDNO) {
				break;
			}
			if ((fi = (FILTER_INFO *)listview_get_lparam(GetDlgItem(hDlg, IDC_LIST_FILTER), i)) != NULL) {
				mem_free(&fi->format_name);
				ini_free_format_name(fi->fn, fi->fn_cnt);
				mem_free(&fi);
			}
			ListView_DeleteItem(GetDlgItem(hDlg, IDC_LIST_FILTER), i);
			ListView_SetItemState(GetDlgItem(hDlg, IDC_LIST_FILTER), i,
				LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			break;

		case IDOK:
			for (i = 0; i < option.filter_cnt; i++) {
				mem_free(&((option.filter_info + i)->format_name));
				ini_free_format_name((option.filter_info + i)->fn, (option.filter_info + i)->fn_cnt);
			}
			mem_free(&option.filter_info);

			option.filter_all_action = IsDlgButtonChecked(hDlg, IDC_RADIO_ALL_IGNORE);
			option.filter_info = listview_get_filter(GetDlgItem(hDlg, IDC_LIST_FILTER), &option.filter_cnt);
			listview_free_filter(GetDlgItem(hDlg, IDC_LIST_FILTER));
			prop_ret = 1;
			break;

		case IDPCANCEL:
			break;
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}