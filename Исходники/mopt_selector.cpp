INT_PTR CALLBACK ModernOptSelector_DlgProc(HWND hwndDlg, UINT  msg, WPARAM wParam, LPARAM lParam)
{
	TSelectorData *sd = (TSelectorData *)GetWindowLongPtr(hwndDlg, GWLP_USERDATA);

	switch (msg) {
	case WM_INITDIALOG:
		sd = new TSelectorData;
		sd->obj = (MODERNOPTOBJECT*)lParam;
		sd->active = sttGetActiveSkin(sd->obj);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, (LONG_PTR)sd);

		BuildSkinList(GetDlgItem(hwndDlg, IDC_SKINLIST), _A2T(sd->obj->lpzThemeExtension));
		return FALSE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_SKINLIST) {
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				DeleteObject(sd->hbmpPreview);
				sd->hbmpPreview = 0;
				RedrawWindow(GetDlgItem(hwndDlg, IDC_PREVIEW1), NULL, NULL, RDW_INVALIDATE);
				break;

			case LBN_DBLCLK:
				int idx = SendDlgItemMessage(hwndDlg, IDC_SKINLIST, LB_GETCURSEL, 0, 0);
				if (idx >= 0) {
					TSkinListItem *dat = (TSkinListItem *)SendDlgItemMessage(hwndDlg, IDC_SKINLIST, LB_GETITEMDATA, idx, 0);
					sttApplySkin(sd->obj, dat->filename);
					mir_free(sd->active);
					sd->active = sttGetActiveSkin(sd->obj);
					RedrawWindow(GetDlgItem(hwndDlg, IDC_SKINLIST), NULL, NULL, RDW_INVALIDATE);
				}
				break;
			}
			break;
		}
		return FALSE;

	case WM_MEASUREITEM:
		{
			LPMEASUREITEMSTRUCT lps = (LPMEASUREITEMSTRUCT)lParam;
			if (lps->CtlID != IDC_SKINLIST)
				break;
			TSkinListItem *dat = (TSkinListItem *)lps->itemData;
			if (!dat) break;

			lps->itemWidth = 10;
			lps->itemHeight = 30;

			return FALSE;
		}

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT lps = (LPDRAWITEMSTRUCT)lParam;
			if (lps->CtlID == IDC_SKINLIST) {
				TSkinListItem *dat = (TSkinListItem *)lps->itemData;
				if (!dat) break;

				SetBkMode(lps->hDC, TRANSPARENT);
				COLORREF clLine1, clLine2, clBack;
				if (lps->itemState & ODS_SELECTED) {
					FillRect(lps->hDC, &lps->rcItem, GetSysColorBrush(COLOR_HIGHLIGHT));
					clBack = GetSysColor(COLOR_HIGHLIGHT);
					clLine1 = GetSysColor(COLOR_HIGHLIGHTTEXT);
				}
				else {
					FillRect(lps->hDC, &lps->rcItem, GetSysColorBrush(COLOR_WINDOW));
					clBack = GetSysColor(COLOR_WINDOW);
					clLine1 = GetSysColor(COLOR_WINDOWTEXT);
				}
				clLine2 = RGB(
					GetRValue(clLine1) * 0.66 + GetRValue(clBack) * 0.34,
					GetGValue(clLine1) * 0.66 + GetGValue(clBack) * 0.34,
					GetBValue(clLine1) * 0.66 + GetBValue(clBack) * 0.34);

				lps->rcItem.left += 2;
				lps->rcItem.top += 2;
				lps->rcItem.bottom -= 2;
				lps->rcItem.right -= 5;

				int cxIcon = GetSystemMetrics(SM_CXSMICON);
				int cyIcon = GetSystemMetrics(SM_CYSMICON);

				if (sd->active && !mir_tstrcmp(sd->active, dat->filename)) {
					DrawIconEx(lps->hDC, lps->rcItem.left, (lps->rcItem.top + lps->rcItem.bottom - cyIcon) / 2,
						Skin_LoadIcon(SKINICON_OTHER_EMPTYBLOB),
						cxIcon, cyIcon, 0, NULL, DI_NORMAL);
				}
				else {
					DrawIconEx(lps->hDC, lps->rcItem.left, (lps->rcItem.top + lps->rcItem.bottom - cyIcon) / 2,
						Skin_LoadIcon(SKINICON_OTHER_SMALLDOT),
						cxIcon, cyIcon, 0, NULL, DI_NORMAL);
				}
				lps->rcItem.left += cxIcon;
				lps->rcItem.left += 5;

				SetTextColor(lps->hDC, clLine1);
				DrawText(lps->hDC, dat->title, -1, &lps->rcItem, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_END_ELLIPSIS | DT_TOP);
				lps->rcItem.left += cxIcon;

				SetTextColor(lps->hDC, clLine2);
				DrawText(lps->hDC, dat->path, -1, &lps->rcItem, DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_PATH_ELLIPSIS | DT_BOTTOM);
			}
			else if (lps->CtlID == IDC_PREVIEW1) {
				int idx = SendDlgItemMessage(hwndDlg, IDC_SKINLIST, LB_GETCURSEL, 0, 0);

				if (!sd->hbmpPreview) {
					if (idx >= 0) {
						TSkinListItem *dat = (TSkinListItem *)SendDlgItemMessage(hwndDlg, IDC_SKINLIST, LB_GETITEMDATA, idx, 0);
						CreatePreview(sd, dat->filename, lps);
					}
					else CreatePreview(sd, NULL, lps);
				}

				if (sd->hbmpPreview) {
					HDC hdc = CreateCompatibleDC(lps->hDC);
					SelectObject(hdc, sd->hbmpPreview);
					BitBlt(lps->hDC,
						lps->rcItem.left, lps->rcItem.top,
						lps->rcItem.right - lps->rcItem.left, lps->rcItem.bottom - lps->rcItem.top,
						hdc, 0, 0, SRCCOPY);
					DeleteDC(hdc);
				}
			}

			return TRUE;
		}

	case WM_DELETEITEM:
		{
			LPDELETEITEMSTRUCT lps = (LPDELETEITEMSTRUCT)lParam;
			if (lps->CtlID != IDC_SKINLIST) break;
			TSkinListItem *dat = (TSkinListItem *)lps->itemData;
			if (dat) delete dat;
			return FALSE;
		}

	case WM_DESTROY:
		delete sd;
		return FALSE;
	}
	return FALSE;
}