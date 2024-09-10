void SetGeneralInfo(HWND hwnd)
{
	TCHAR	 ach[256];
	HWND	 hwndDlg = WinSpyTab[GENERAL_TAB].hwnd;
	RECT	 rect;
	int		 x1, y1;
	int		 i, numbytes, index;
	LONG_PTR lp;
	DWORD    dwLastError;

	if(hwnd == 0) return;

	//handle
	wsprintf(ach, szHexFmt, hwnd);
	SetDlgItemText(hwndDlg, IDC_HANDLE, ach);

	//caption
	ShowDlgItem(hwndDlg, IDC_CAPTION1, SW_SHOW);
	ShowDlgItem(hwndDlg, IDC_CAPTION2, SW_HIDE);

	SendDlgItemMessage(hwndDlg, IDC_CAPTION2, CB_RESETCONTENT, 0, 0);

	if(!IsWindow(hwnd))
	{
		SetDlgItemText(hwndDlg, IDC_CAPTION1, L"(invalid window)");	// edit box
		SetDlgItemText(hwndDlg, IDC_CAPTION2, L"(invalid window)");	// combo box
		SetDlgItemText(hwndDlg, IDC_CLASS, L"(invalid window)");
		return;
	}

	// SendMessage is better than GetWindowText, 
	// because it gets text of children in other processes
	if(spy_fPassword == FALSE)
	{
		ach[0] = 0;

		if(!SendMessageTimeout(hwnd, WM_GETTEXT, sizeof(ach) / sizeof(TCHAR), (LPARAM)ach,
			SMTO_ABORTIFHUNG, 100, NULL))
		{
			GetWindowText(hwnd, ach, sizeof(ach) / sizeof(TCHAR));
		}

		SetDlgItemText(hwndDlg, IDC_CAPTION1, ach);	// edit box
		SetDlgItemText(hwndDlg, IDC_CAPTION2, ach);	// combo box
	}
	else
	{
		SetDlgItemText(hwndDlg, IDC_CAPTION1, spy_szPassword);	// edit box
		SetDlgItemText(hwndDlg, IDC_CAPTION2, spy_szPassword);	// combo box
	}

	//class name
	GetClassName(hwnd, ach, sizeof(ach)/sizeof(TCHAR));

	if(IsWindowUnicode(hwnd))	lstrcat(ach, _T("  (Unicode)"));

	SetDlgItemText(hwndDlg, IDC_CLASS, ach);

	//style
	wsprintf(ach, szHexFmt, GetWindowLong(hwnd, GWL_STYLE));
	
	if(IsWindowVisible(hwnd))	lstrcat(ach, _T("  (visible, "));
	else						lstrcat(ach, _T("  (hidden, "));

	if(IsWindowEnabled(hwnd))	lstrcat(ach, _T("enabled)"));
	else						lstrcat(ach, _T("disabled)"));

	SetDlgItemText(hwndDlg, IDC_STYLE, ach);

	//rectangle
	GetWindowRect(hwnd, &rect);
	x1 = rect.left;
	y1 = rect.top;

	wsprintf(ach, _T("(%d,%d) - (%d,%d)  -  %dx%d"), 
		rect.left,rect.top, rect.right,rect.bottom,
		(rect.right-rect.left), (rect.bottom-rect.top));

	SetDlgItemText(hwndDlg, IDC_RECTANGLE, ach);

	//client rect
	GetClientRect(hwnd, &rect);
	MapWindowPoints(hwnd, 0, (POINT *)&rect, 2);
	x1 = rect.left-x1;
	y1 = rect.top-y1;

	OffsetRect(&rect, -rect.left, -rect.top);
	OffsetRect(&rect, x1, y1);
	
	wsprintf(ach, _T("(%d,%d) - (%d,%d)  -  %dx%d"), 
		rect.left,rect.top, rect.right,rect.bottom,
		(rect.right-rect.left), (rect.bottom-rect.top));

	SetDlgItemText(hwndDlg, IDC_CLIENTRECT, ach);	

	//restored rect
	/*GetWindowPlacement(hwnd, &wp);
	wsprintf(ach, _T("(%d,%d) - (%d,%d)  -  %dx%d"), 
		wp.rcNormalPosition.left, wp.rcNormalPosition.top,
		wp.rcNormalPosition.right, wp.rcNormalPosition.bottom,
		(wp.rcNormalPosition.right-wp.rcNormalPosition.left),
		(wp.rcNormalPosition.bottom-wp.rcNormalPosition.top));

	SetDlgItemText(hwndDlg, IDC_RESTOREDRECT, ach);*/

	//window procedure
	if(spy_WndProc == 0)
	{
		wsprintf(ach, _T("N/A"));
		SetDlgItemText(hwndDlg, IDC_WINDOWPROC, ach);

		ShowDlgItem(hwndDlg, IDC_WINDOWPROC,  SW_SHOW);
		ShowDlgItem(hwndDlg, IDC_WINDOWPROC2, SW_HIDE);
	}
	else					
	{
		wsprintf(ach, szPtrFmt, spy_WndProc);
		SetDlgItemText(hwndDlg, IDC_WINDOWPROC2, ach);

		ShowDlgItem(hwndDlg, IDC_WINDOWPROC,  SW_HIDE);
		ShowDlgItem(hwndDlg, IDC_WINDOWPROC2, SW_SHOW);
	}

	//instance handle
	wsprintf(ach, szPtrFmt, GetWindowLongPtr(hwnd, GWLP_HINSTANCE));
	SetDlgItemText(hwndDlg, IDC_INSTANCE, ach);

	//user data
	wsprintf(ach, szPtrFmt, GetWindowLongPtr(hwnd, GWLP_USERDATA));
	SetDlgItemText(hwndDlg, IDC_USERDATA, ach);

	//control ID
	lp = GetWindowLongPtr(hwnd, GWLP_ID);
	wsprintf(ach, _T("%p  (%Id)"), lp, lp);
	SetDlgItemText(hwndDlg, IDC_CONTROLID, ach);

	//extra window bytes
	numbytes = GetClassLong(hwnd, GCL_CBWNDEXTRA);
	i = 0;

	SendDlgItemMessage(hwndDlg, IDC_WINDOWBYTES, CB_RESETCONTENT, 0, 0);	
	EnableDlgItem(hwndDlg, IDC_WINDOWBYTES, numbytes != 0);

	// Retrieve all the window bytes + add to combo box
	while(numbytes > 0)
	{
		SetLastError(ERROR_SUCCESS);

		if(numbytes <= sizeof(long))
			lp = GetWindowLong(hwnd, i);
		else
			lp = GetWindowLongPtr(hwnd, i);

		dwLastError = GetLastError();
		if(dwLastError == ERROR_PRIVATE_DIALOG_INDEX)
			break;

		if(dwLastError == ERROR_SUCCESS)
		{
			if(numbytes < sizeof(LONG_PTR))
			{
				switch(numbytes)
				{
				case 4:
					wsprintf(ach, _T("+%-8d %08X"), i, lp);
					break;

				case 2:
					wsprintf(ach, _T("+%-8d %04X"), i, lp);
					break;

				default:
					wsprintf(ach, _T("+%-8d %X"), i, lp);
					break;
				}
			}
			else
				wsprintf(ach, _T("+%-8d %08p"), i, lp);
		}
		else
			wsprintf(ach, _T("+%-8d Unavailable (0x%08X)"), i, dwLastError);

		i += sizeof(LONG_PTR);
		numbytes -= sizeof(LONG_PTR);

		index = (int)SendDlgItemMessage(hwndDlg, IDC_WINDOWBYTES, CB_ADDSTRING, 0, (LPARAM)ach);

		if(dwLastError == ERROR_SUCCESS)
			SendDlgItemMessage(hwndDlg, IDC_WINDOWBYTES, CB_SETITEMDATA, index, lp);
		else
			SendDlgItemMessage(hwndDlg, IDC_WINDOWBYTES, CB_SETITEMDATA, index, dwLastError);
	}

	SendDlgItemMessage(hwndDlg, IDC_WINDOWBYTES, CB_SETCURSEL, 0, 0);
}