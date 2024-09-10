INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char error[1000];
	static bool pause = false;

	switch (uMsg)
	{
	case WM_INITDIALOG:
		// Set Class icon
		SetClassLongPtr(hDlg, GCL_HICON, (LONG_PTR)LoadIcon(g_instance, MAKEINTRESOURCE(IDI_ICON)));

		SetTimer(hDlg, 1, 500, NULL);

		return TRUE;  // return FALSE if modeless and SetFocus is called

	case WM_DROPFILES:
		DragQueryFile((HDROP)wParam, 0, filename, MAX_PATH);
		DragFinish((HDROP)wParam);
		g_new = true;
		return TRUE;

	case WM_TIMER:
		if (!pause)
		{
			LoadFile(hDlg, filename, error, &g_ftLastWriteTime, g_new);
			g_new = false;

			if (*error)
			{
				pause = true;
				*filename = 0;
				MessageBox(hDlg, error, "Error", MB_OK);
				SetWindowText(hDlg, "Tail");
				pause = false;
			}
		}
		return TRUE;

	case WM_SIZE:
		MoveWindow(GetDlgItem(hDlg, IDC_TEXT), 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			return TRUE;

		case IDCANCEL:
			// Quit program...
			EndDialog(hDlg, wParam);  // Close dialogwindow
			return TRUE;
		}
	}

	return FALSE;
}