INT_PTR CALLBACK ConnDlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch( Msg ) {
	case WM_INITDIALOG:
		{
			HWND hList = GetDlgItem(hWnd, IDC_CONNLIST);

			ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT);
			LV_COLUMN lvc = { 0 };
			lvc.mask = LVCF_TEXT|LVCF_FMT|LVCF_WIDTH;
			lvc.fmt = LVCFMT_LEFT;
			lvc.cx = 40;
			lvc.pszText = _T("ID");
			ListView_InsertColumn(hList, 0, &lvc);
			lvc.cx = 50;
			lvc.pszText = TranslateT("User");
			ListView_InsertColumn(hList, 1, &lvc);
			lvc.cx = 250;
			lvc.pszText = TranslateT("File");
			ListView_InsertColumn(hList, 2, &lvc);
			lvc.cx = 50;
			lvc.pszText = TranslateT("Access");
			ListView_InsertColumn(hList, 3, &lvc);
			KillTimer(NULL, 777);
			lst = cpy_list(&list);
			if (IsUserAnAdmin())
				SetTimer(NULL, 777, TIME, TimerProc);
			else
				MessageBox(NULL, TranslateT("Plugin WhoUsesMyFiles requires admin privileges in order to work."), _T("Miranda NG"), MB_OK);
			ShowList(lst, hList);
		}
		Utils_RestoreWindowPosition(hWnd, NULL, MODULENAME,"conn");
		return TRUE;

	case WM_CLOSE:
		PostMessage( hWnd, WM_COMMAND, IDCANCEL, 0l );
		break;

	case WM_COMMAND:
		switch( LOWORD(wParam)) {
		case IDOK:
		case IDCANCEL:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;

	case WM_SIZE:
		{
			UTILRESIZEDIALOG urd = { sizeof(urd) };
			urd.hwndDlg = hWnd;
			urd.hInstance = hInst;
			urd.lpTemplate = MAKEINTRESOURCEA(IDD_CONNLIST);
			urd.lParam = (LPARAM)NULL;
			urd.pfnResizer = DlgResizer;
			CallService(MS_UTILS_RESIZEDIALOG, 0, (LPARAM)&urd);
		}
		Utils_SaveWindowPosition(hWnd, NULL, MODULENAME,"conn");
		return TRUE;

	case WM_MOVE:
		Utils_SaveWindowPosition(hWnd, NULL, MODULENAME,"conn");
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code) { 
		case LVN_GETDISPINFO: 
			OnGetDispInfo((NMLVDISPINFO*)lParam); 
			break; 
		}
		break;

	case WM_DESTROY:
		del_all(&lst);
		PostQuitMessage(0);
		break;
	}
	return FALSE;
}