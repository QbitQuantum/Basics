BOOL CALLBACK DialogFunc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		HEdit1 = GetDlgItem(hwndDlg, IDC_EDIT1);
		HEdit2 = GetDlgItem(hwndDlg, IDC_EDIT2);

		SetFocus(HEdit2);

//		SendMessage(HEdit1, EM_LIMITTEXT, 1000, 0);
		HEdit1_size = SendMessage(HEdit1, EM_GETLIMITTEXT, 0, 0) + 1;
		HEdit1_buf = (char *) Q_malloc (HEdit1_size);
//Sys_Printf("%d\n", HEdit1_size);
		break;

	case WM_CTLCOLORSTATIC:
		if ((HWND)lParam != HEdit1)
			break;

		SetTextColor((HDC)wParam, EditBoxColor);
		SetBkColor((HDC)wParam, EditBoxBgColor);

		return (LONG)g_hbrBackground;
	case WM_TRAY:
		switch (lParam)
		{
		case 515:
			ShowWindow(hwndDlg,SW_RESTORE);
			SetForegroundWindow(hwndDlg);
			RemoveNotifyIcon();
			break;
		case 516:
			{
				static DWORD id;

				CreateThread(NULL, 0, TrackPopup, NULL, 0, &id);
				break;
			}
		}
		break;
	case WM_SIZE:
		// we don't care until window is fully created
		if (DlgHwnd == NULL)
			break;

		if ((int)wParam == SIZE_MINIMIZED)
		{
			ShowWindow(hwndDlg,SW_HIDE);
			ShowNotifyIcon();
		}
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_OK:
			{
				char str[1024];

				SendMessage(HEdit2, WM_GETTEXT, (WPARAM)sizeof(str),(LPARAM)str);

				if (!str[0])
					break;

				SendMessage(HEdit2, WM_SETTEXT, 0, (LPARAM)0);

				// normalize text before add to console.
				ConsoleAddText(Q_normalizetext(va("] %s\n", str)));

				Cbuf_AddText (str);
				Cbuf_AddText ("\n");

				return TRUE;
			}
		case IDC_QUIT:
			Cbuf_AddText("quit\n");
			return TRUE;
		case IDC_RESTORE:
			ShowWindow(hwndDlg,SW_RESTORE);
			RemoveNotifyIcon();
			return TRUE;
		case IDC_CLEAR:
			SendMessage(HEdit1, WM_SETTEXT, 0, (LPARAM)0);
			SetFocus(HEdit2);
			break;
		}
		break;
	case WM_ACTIVATE:
		break;

	case WM_CLOSE:
		SV_Quit_f();
		break;
	}

	return FALSE;
}