static LRESULT CALLBACK MDescButtonWndProc(HWND hwndDlg, UINT  msg, WPARAM wParam, LPARAM lParam)
{
	MDescButtonCtrl *dat = (MDescButtonCtrl *)GetWindowLongPtr(hwndDlg, 0);
	switch (msg) {
	case WM_NCCREATE:
		dat = (MDescButtonCtrl*)mir_alloc(sizeof(MDescButtonCtrl));
		if (dat == NULL)
			return FALSE;

		memset(dat, 0, sizeof(MDescButtonCtrl));
		SetWindowLongPtr(hwndDlg, 0, (LONG_PTR)dat);
		MDescButton_SetupColors(dat);
		return TRUE;

	case WM_SETFONT:
		dat->hFont = (HFONT)wParam;
		break;

	case WM_SIZE:
		GetClientRect(hwndDlg, &dat->rc);
		dat->width = dat->rc.right - dat->rc.left;
		dat->height = dat->rc.bottom - dat->rc.top;
		return TRUE;

	case WM_THEMECHANGED:
	case WM_STYLECHANGED:
		MDescButton_SetupColors(dat);
		return TRUE;

	case WM_MOUSEMOVE:
		if (!dat->bMouseInside) {
			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hwndDlg;
			_TrackMouseEvent(&tme);
			dat->bMouseInside = TRUE;
			RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
		}
		return 0;

	case WM_MOUSELEAVE:
		dat->bMouseInside = FALSE;
		RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
		return 0;

	case WM_LBUTTONUP:
		SendMessage(GetParent(hwndDlg), WM_COMMAND, MAKEWPARAM(GetWindowLongPtr(hwndDlg, GWL_ID), 0), 0);
		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_NCPAINT:
		InvalidateRect(hwndDlg, NULL, FALSE);
		break;

	case WM_PAINT:
		MDescButton_OnPaint(hwndDlg, dat);
		break;

	case DBCM_SETTITLE:
		if (dat->lpzTitle)
			mir_free(dat->lpzTitle);
		if (wParam & MDBCF_UNICODE)
			dat->lpzTitle = mir_u2t((WCHAR *)lParam);
		else
			dat->lpzTitle = mir_a2t((char *)lParam);
		RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
		return TRUE;

	case DBCM_SETDESCRIPTION:
		if (dat->lpzDescription)
			mir_free(dat->lpzDescription);
		if (wParam & MDBCF_UNICODE)
			dat->lpzDescription = mir_u2t((WCHAR *)lParam);
		else
			dat->lpzDescription = mir_a2t((char *)lParam);
		RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
		return TRUE;

	case DBCM_SETICON:
		if (dat->hIcon && !dat->bSharedIcon)
			DestroyIcon(dat->hIcon);

		if (wParam & MDBCF_SHAREDICON) {
			dat->bSharedIcon = TRUE;
			dat->hIcon = (HICON)lParam;
		}
		else {
			dat->bSharedIcon = FALSE;
			dat->hIcon = CopyIcon((HICON)lParam);
		}
		RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
		return TRUE;

	case WM_DESTROY:
		if (dat->lpzTitle)
			mir_free(dat->lpzTitle);
		if (dat->lpzDescription)
			mir_free(dat->lpzDescription);
		if (dat->hIcon && !dat->bSharedIcon)
			DestroyIcon(dat->hIcon);
		mir_free(dat);
		return TRUE;
	}

	return DefWindowProc(hwndDlg, msg, wParam, lParam);
}