INT_PTR CALLBACK DialogProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam) {
	size_t i;
	switch (uMsg) {
	case WM_INITDIALOG:
		SendMessage(hwndDlg, WM_SETICON, 0, 0);
		for (i = 0; i < sizeof(primary)/sizeof(line); i++)
			SendDlgItemMessage(hwndDlg, IDC_PRIMARY, CB_ADDSTRING, 0, (LPARAM)primary[i].name);
		for (i = 0; i < sizeof(sub)/sizeof(line); i++)
			SendDlgItemMessage(hwndDlg, IDC_SUB, CB_ADDSTRING, 0, (LPARAM)sub[i].name);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hwndDlg, 0);
			PostQuitMessage(0);
		}
		else if (HIWORD(wParam) == CBN_SELCHANGE) {
			if (SendDlgItemMessage(hwndDlg, IDC_PRIMARY, CB_GETCURSEL, 0, 0) != CB_ERR && SendDlgItemMessage(hwndDlg, IDC_SUB, CB_GETCURSEL, 0, 0) != CB_ERR) {
				TCHAR lang[512];
				wsprintf(lang, _T("Language ID: %d"), MAKELANGID(primary[SendDlgItemMessage(hwndDlg, IDC_PRIMARY, CB_GETCURSEL, 0, 0)].id, sub[SendDlgItemMessage(hwndDlg, IDC_SUB, CB_GETCURSEL, 0, 0)].id));
				SetDlgItemText(hwndDlg, IDC_RESULT, lang);
			}
		}
		else if (LOWORD(wParam) == IDOK) {
			if (SendDlgItemMessage(hwndDlg, IDC_PRIMARY, CB_GETCURSEL, 0, 0) != CB_ERR && SendDlgItemMessage(hwndDlg, IDC_SUB, CB_GETCURSEL, 0, 0) != CB_ERR) {
				HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, 16*sizeof(TCHAR));
				if (!hMem) return 0;
				TCHAR *lang_id = (TCHAR *)GlobalLock(hMem);
				wsprintf(lang_id, _T("%u"), MAKELANGID(primary[SendDlgItemMessage(hwndDlg, IDC_PRIMARY, CB_GETCURSEL, 0, 0)].id, sub[SendDlgItemMessage(hwndDlg, IDC_SUB, CB_GETCURSEL, 0, 0)].id));
				GlobalUnlock(hMem);
				if (!OpenClipboard(hwndDlg)) return 0;
				EmptyClipboard();
#ifdef _UNICODE
				SetClipboardData(CF_UNICODETEXT,hMem);
#else
				SetClipboardData(CF_TEXT,hMem);
#endif
				CloseClipboard();
			}
		}
		break;
	}
	return 0;
}