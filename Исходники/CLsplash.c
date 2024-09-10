static BOOL CALLBACK 
sSplashDlgProc (
		HWND	hDlg, 
		UINT	uMsg, 
		WPARAM	wParam, 
		LPARAM	lParam) 
{
	PSPLASHSTRUCT	pss;

	switch (uMsg) {

	case WM_INITDIALOG:
		{
			HWND hWndControl;

			SetWindowLong (hDlg, GWL_USERDATA, lParam);
			pss = (PSPLASHSTRUCT)lParam;

			g_hWndSplash = hDlg;
			SetWindowPos (hDlg, HWND_TOP, pss->uXpos, pss->uYpos, 
											pss->uXsize, pss->uYsize, 0);

			hWndControl = GetDlgItem (hDlg, IDOK);
			EnableWindow (hWndControl, FALSE);
			ShowWindow (hWndControl, SW_HIDE);
			hWndControl = GetDlgItem (hDlg, IDC_BUYNOW);
			EnableWindow (hWndControl, FALSE);
			ShowWindow (hWndControl, SW_HIDE);
			pss->uTimerTime = 0;
			SetTimer (hDlg, TIMER_ID, TIMER_PERIOD, NULL);
		}
		return TRUE;

	case WM_PAINT:
		{
			HDC			hDC, hMemDC;
			PAINTSTRUCT ps;
			HBITMAP		hBitmapOld;

			pss = (PSPLASHSTRUCT)GetWindowLong (hDlg, GWL_USERDATA);

			hDC = BeginPaint (hDlg, &ps);
			hMemDC = CreateCompatibleDC (hDC);
			if (pss->hPaletteSplash) {
				SelectPalette (hDC, pss->hPaletteSplash, FALSE);
				RealizePalette (hDC);
			}
			hBitmapOld = SelectObject (hMemDC, pss->hBitmapSplash);
			CLPaintUserInfo (MemMgr, hDlg, hMemDC, NULL);
			BitBlt (hDC, 0, 0, pss->uXsize, pss->uYsize, 
											hMemDC, 0, 0, SRCCOPY);
			SelectObject (hMemDC, hBitmapOld);
			DeleteDC (hMemDC);
			EndPaint (hDlg, &ps);
		}
		return FALSE;

	case WM_LBUTTONDOWN:
		if (hWndSplashParent) EndDialog (hDlg, 0);
		return TRUE;

	case WM_DESTROY:
		KillTimer (hDlg, TIMER_ID);
		return FALSE;

	case WM_TIMER:
		pss = (PSPLASHSTRUCT)GetWindowLong (hDlg, GWL_USERDATA);
		if (pss->uTimerTime < pss->uTimeOut) 
			pss->uTimerTime += TIMER_PERIOD;
		else 
			if (hWndSplashParent) EndDialog (hDlg, 0);
		return TRUE;

	case WM_CLOSE :
		EndDialog (hDlg, 0);
		break;

	case WM_COMMAND :
		switch(LOWORD (wParam)) {

		case IDOK: 
			if (hWndSplashParent) EndDialog (hDlg, 0);
			break;
		}
		return TRUE;

	default:
		return FALSE;

	}

	return FALSE;
}