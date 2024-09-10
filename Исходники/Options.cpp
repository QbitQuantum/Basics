static INT_PTR APIENTRY OptSknWndProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL bEnable;
	char szPercent[20];

	switch ( uMsg ) {
	case WM_INITDIALOG:
		TranslateDialogDefault(hwndDlg);
		// Border
		CheckDlgButton(hwndDlg, IDC_DRAWBORDER, db_get_b(NULL, MODULE, "DrawBorder", FLT_DEFAULT_DRAWBORDER));
		SendMessage(hwndDlg, M_REFRESHBORDERPICKERS, 0, 0);
		SendDlgItemMessage(hwndDlg, IDC_LTEDGESCOLOR, CPM_SETDEFAULTCOLOUR, 0, FLT_DEFAULT_LTEDGESCOLOR);
		SendDlgItemMessage(hwndDlg, IDC_LTEDGESCOLOR, CPM_SETCOLOUR, 0, db_get_dw(NULL, MODULE, "LTEdgesColor", FLT_DEFAULT_LTEDGESCOLOR));
		SendDlgItemMessage(hwndDlg, IDC_RBEDGESCOLOR, CPM_SETDEFAULTCOLOUR, 0, FLT_DEFAULT_RBEDGESCOLOR);
		SendDlgItemMessage(hwndDlg, IDC_RBEDGESCOLOR, CPM_SETCOLOUR, 0, db_get_dw(NULL, MODULE, "RBEdgesColor", FLT_DEFAULT_RBEDGESCOLOR));

		// Background
		CheckDlgButton(hwndDlg, IDC_CHK_WIDTH, (fcOpt.bFixedWidth ? BST_CHECKED : BST_UNCHECKED));

		SendDlgItemMessage(hwndDlg, IDC_BKGCOLOUR, CPM_SETDEFAULTCOLOUR, 0, FLT_DEFAULT_BKGNDCOLOR);
		SendDlgItemMessage(hwndDlg, IDC_BKGCOLOUR, CPM_SETCOLOUR, 0, db_get_dw(NULL, MODULE, "BkColor", FLT_DEFAULT_BKGNDCOLOR));
		CheckDlgButton(hwndDlg, IDC_BITMAP, db_get_b(NULL, MODULE, "BkUseBitmap", FLT_DEFAULT_BKGNDUSEBITMAP));
		SendMessage(hwndDlg, M_REFRESHBKGBOXES, 0, 0);
		{
			DBVARIANT dbv;
			if ( !db_get_ts(NULL, MODULE, "BkBitmap", &dbv)) {
				SetDlgItemText(hwndDlg, IDC_FILENAME, dbv.ptszVal);
				db_free(&dbv);
			}

			WORD bmpUse = (WORD)db_get_w(NULL, MODULE, "BkBitmapOpt", FLT_DEFAULT_BKGNDBITMAPOPT);
			CheckDlgButton(hwndDlg, IDC_STRETCHH, ((bmpUse & CLB_STRETCHH) ? BST_CHECKED : BST_UNCHECKED));
			CheckDlgButton(hwndDlg, IDC_STRETCHV, ((bmpUse & CLB_STRETCHV) ? BST_CHECKED : BST_UNCHECKED));
			CheckDlgButton(hwndDlg, IDC_TILEH, ((bmpUse & CLBF_TILEH) ? BST_CHECKED : BST_UNCHECKED));
			CheckDlgButton(hwndDlg, IDC_TILEV, ((bmpUse & CLBF_TILEV) ? BST_CHECKED : BST_UNCHECKED));
			CheckDlgButton(hwndDlg, IDC_PROPORTIONAL, ((bmpUse & CLBF_PROPORTIONAL) ? BST_CHECKED : BST_UNCHECKED));

			SHAutoComplete(GetDlgItem(hwndDlg, IDC_FILENAME), 1);

			// Windows 2K/XP
			BYTE btOpacity = (BYTE)db_get_b(NULL, MODULE, "Opacity", 100);
			SendDlgItemMessage(hwndDlg, IDC_SLIDER_OPACITY, TBM_SETRANGE, TRUE, MAKELONG(0, 100));
			SendDlgItemMessage(hwndDlg, IDC_SLIDER_OPACITY, TBM_SETPOS, TRUE, btOpacity);
				
			mir_snprintf(szPercent, SIZEOF(szPercent), "%d%%", btOpacity);
			SetDlgItemTextA(hwndDlg, IDC_OPACITY, szPercent);

			EnableWindow(GetDlgItem(hwndDlg, IDC_SLIDER_OPACITY), SetLayeredWindowAttributes != 0);
			EnableWindow(GetDlgItem(hwndDlg, IDC_OPACITY), SetLayeredWindowAttributes != 0);
		}
		return TRUE;

	case M_REFRESHBKGBOXES:
		bEnable = IsDlgButtonChecked(hwndDlg, IDC_BITMAP);
		EnableWindow(GetDlgItem(hwndDlg, IDC_FILENAME), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_BROWSE), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_STRETCHH), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_STRETCHV), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_TILEH), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_TILEV), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_PROPORTIONAL), bEnable);
		break;

	case M_REFRESHBORDERPICKERS:
		bEnable = IsDlgButtonChecked(hwndDlg, IDC_DRAWBORDER);
		EnableWindow(GetDlgItem(hwndDlg, IDC_LTEDGESCOLOR), bEnable);
		EnableWindow(GetDlgItem(hwndDlg, IDC_RBEDGESCOLOR), bEnable);
		break;

	case WM_HSCROLL:
		if (wParam != TB_ENDTRACK) {
			int nPos = (int)SendDlgItemMessage(hwndDlg, IDC_SLIDER_OPACITY, TBM_GETPOS, 0, 0);
			fcOpt.thumbAlpha = (BYTE)(( nPos * 255 ) / 100 );
			SetThumbsOpacity(fcOpt.thumbAlpha);

			mir_snprintf(szPercent, SIZEOF(szPercent), "%d%%", nPos);
			SetDlgItemTextA(hwndDlg, IDC_OPACITY, szPercent);
			SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_DRAWBORDER:
			SendMessage(hwndDlg, M_REFRESHBORDERPICKERS, 0, 0);
			break;

		case IDC_BROWSE:
			{
				char str[MAX_PATH];
				OPENFILENAMEA ofn = {0};
				char filter[512];

				GetDlgItemTextA(hwndDlg, IDC_FILENAME, str, sizeof(str));
				ofn.lStructSize = sizeof(OPENFILENAMEA);
				ofn.hwndOwner = hwndDlg;
				ofn.hInstance = NULL;
				CallService(MS_UTILS_GETBITMAPFILTERSTRINGS, sizeof(filter), (LPARAM)filter);
				ofn.lpstrFilter = filter;
				ofn.lpstrFile = str;
				ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				ofn.nMaxFile = sizeof(str);
				ofn.nMaxFileTitle = MAX_PATH;
				ofn.lpstrDefExt = "bmp";
				if (!GetOpenFileNameA(&ofn))
					return FALSE;
				SetDlgItemTextA(hwndDlg, IDC_FILENAME, str);
			}
			break;

		case IDC_FILENAME:
			if (EN_CHANGE != HIWORD(wParam) || (HWND)lParam != GetFocus())
				return FALSE;
			break;

		case IDC_BITMAP:
			SendMessage(hwndDlg, M_REFRESHBKGBOXES, 0, 0);
			break;
		}

		SendMessage(GetParent(hwndDlg), PSM_CHANGED, 0, 0);
		break;

	case WM_NOTIFY:
		if (0 == ((LPNMHDR)lParam)->idFrom) {
			switch (((LPNMHDR)lParam)->code) {
			case PSN_RESET:
				fcOpt.thumbAlpha = (BYTE)((double)db_get_b(NULL, MODULE, "Opacity", 100) * 2.55);
				SetThumbsOpacity(fcOpt.thumbAlpha);
				break;

			case PSN_APPLY:
				// Border
				db_set_b(NULL, MODULE, "DrawBorder", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_DRAWBORDER));

				COLORREF col = SendDlgItemMessage(hwndDlg, IDC_LTEDGESCOLOR, CPM_GETCOLOUR, 0, 0);
				db_set_dw(NULL, MODULE, "LTEdgesColor", col);
				col = SendDlgItemMessage(hwndDlg, IDC_RBEDGESCOLOR, CPM_GETCOLOUR, 0, 0);
				db_set_dw(NULL, MODULE, "RBEdgesColor", col);

				db_set_b(NULL, MODULE, "Opacity", (BYTE)SendDlgItemMessage(hwndDlg, IDC_SLIDER_OPACITY, TBM_GETPOS, 0, 0));

				// Backgroud
				col = SendDlgItemMessage(hwndDlg, IDC_BKGCOLOUR, CPM_GETCOLOUR, 0, 0);
				db_set_dw(NULL, MODULE, "BkColor", col);

				db_set_b(NULL, MODULE, "BkUseBitmap", (BYTE)IsDlgButtonChecked(hwndDlg, IDC_BITMAP));

				TCHAR str[MAX_PATH];
				GetDlgItemText(hwndDlg, IDC_FILENAME, str, SIZEOF(str));
				db_set_ts(NULL, MODULE, "BkBitmap", str);

				WORD flags = 0;
				if (IsDlgButtonChecked(hwndDlg, IDC_STRETCHH))
					flags |= CLB_STRETCHH;
				if (IsDlgButtonChecked(hwndDlg, IDC_STRETCHV))
					flags |= CLB_STRETCHV;
				if (IsDlgButtonChecked(hwndDlg, IDC_TILEH))
					flags |= CLBF_TILEH;
				if (IsDlgButtonChecked(hwndDlg, IDC_TILEV))
					flags |= CLBF_TILEV;
				if (IsDlgButtonChecked(hwndDlg, IDC_PROPORTIONAL))
					flags |= CLBF_PROPORTIONAL;
				db_set_w(NULL, MODULE, "BkBitmapOpt", flags);

				ApplyOptionsChanges();
				OnStatusChanged();
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}