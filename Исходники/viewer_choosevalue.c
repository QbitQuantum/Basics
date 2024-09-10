INT_PTR CALLBACK viewerChooseValueWndProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND scrollbar;
	SCROLLINFO sbinfo;
	int val;
	switch(message) {
		case WM_INITDIALOG:
			SetWindowText(hwndDlg, viewer_cvwin_caption);
			SetDlgItemInt(hwndDlg, 103, viewer_cvwin_minval, TRUE);
			SetDlgItemInt(hwndDlg, 104, viewer_cvwin_maxval, TRUE);
			SetDlgItemInt(hwndDlg, 105, viewer_cvwin_newval, TRUE);
			scrollbar = GetDlgItem(hwndDlg, 102);
			sbinfo.cbSize = sizeof(SCROLLINFO);
			sbinfo.fMask = SIF_POS|SIF_RANGE;
			sbinfo.nMin = 0;
			sbinfo.nMax = viewer_cvwin_maxval-viewer_cvwin_minval;
			sbinfo.nPos = viewer_cvwin_newval-viewer_cvwin_minval;
			SetScrollInfo(scrollbar, SB_CTL, &sbinfo, TRUE);
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case 100:
					scrollbar = GetDlgItem(hwndDlg, 102);
					val = GetScrollPos(scrollbar, SB_CTL)+viewer_cvwin_minval;
					if((val-viewer_cvwin_newval)%viewer_cvwin_step == 0)
						viewer_cvwin_newval = val;
				case 101:
					EndDialog(hwndDlg, wParam);
					return TRUE;
			}
		case WM_HSCROLL:
		case WM_VSCROLL:
			switch(LOWORD(wParam)) {
				case SB_THUMBPOSITION:
				case SB_THUMBTRACK:
					scrollbar = GetDlgItem(hwndDlg, 102);
					if((HIWORD(wParam)+viewer_cvwin_minval-viewer_cvwin_newval)%viewer_cvwin_step == 0)
						viewer_cvwin_newval = HIWORD(wParam)+viewer_cvwin_minval;
					SetDlgItemInt(hwndDlg, 105, viewer_cvwin_newval, TRUE);
					SetScrollPos(scrollbar, SB_CTL, HIWORD(wParam), TRUE);
			}
			
			return TRUE;
	}
	return FALSE;
}