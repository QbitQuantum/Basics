LRESULT CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		Init(hDlg);
		return TRUE;

	case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			if (id == IDC_BUTTON_START)
			{
				server.Start();
			}
			if (id == ID_NOTITYICONMENU_EXIT)	// 点击退出菜单，退出应用
			{
				Shell_NotifyIcon(NIM_DELETE,&g_nid);
				EndDialog(hDlg, 0);
			}
			break;
		}
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE)		// 暂时隐藏程序，不退出
		{
			ShowWindow(g_hMainWnd, SW_HIDE);  
		}
		break;

	case WM_AIRSOUND_NOTIFY:
		if(wParam == IDC_NOTIFYICON)
		{  
			if(lParam == WM_LBUTTONDOWN)
			{  
				ShowWindow(g_hMainWnd, SW_SHOWNORMAL);  
				SetForegroundWindow(g_hMainWnd);
				return TRUE;  
			}
			if (lParam == WM_RBUTTONDOWN)
			{
				HMENU hMenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_MENU_NOTIFYICON));
				POINT point;
				GetCursorPos(&point);
				TrackPopupMenu(hMenu, 
					TPM_RIGHTBUTTON, 
					point.x,
					point.y,
					0,
					g_hMainWnd,
					NULL);
				PostMessage(g_hMainWnd, WM_NULL, NULL, NULL);
			}
		}  
	case WM_PAINT:
		{
			BOOL bCompEnabled;
			DwmIsCompositionEnabled(&bCompEnabled);
			if (bCompEnabled)
			{
				PAINTSTRUCT ps;
				HDC hDC = BeginPaint(g_hMainWnd, &ps);
				RECT rcClient;
				GetClientRect(g_hMainWnd, &rcClient);
				HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
				FillRect(hDC, &rcClient, hBrush);
				DrawGlowingText(hDC, IDC_STATIC);
				EndPaint(g_hMainWnd, &ps);
			}
		}
		break;
	}
	return FALSE;
}