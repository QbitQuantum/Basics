void ProcessShellMessage( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	UINT cmdId = 0;
	switch (lParam) {
        case WM_LBUTTONUP:
			cmdId = ID_SHELL_ACTIVATE;
			break;
        case WM_RBUTTONUP: 
		{

			CMenu menu;
			menu.LoadMenu(MAKEINTRESOURCE(IDR_SHELLTRAY));
//			HMENU hMenu = AfxGetApp()->LoadMenu(MAKEINTRESOURCE(IDR_SHELLTRAY));
//			HWND hWndMain = AfxGetMainWnd()->GetSafeHwnd();
			HMENU hMenuTrackPopup = *menu.GetSubMenu (0); // convert to a HMENU
			POINT pt;
			GetCursorPos(&pt);
			// This is required when using a notify icon -- see KB article 
			// PRB: Menus for Notification Icons Don't Work Correctly 
			SetForegroundWindow (hWnd);
			SetMenuDefaultItem(hMenuTrackPopup, 0, MF_BYPOSITION);
			cmdId = TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);

			// This is required when using a notify icon -- see KB article 
			// PRB: Menus for Notification Icons Don't Work Correctly 
			::PostMessage (hWnd, WM_USER, 0, 0);
			break;
		}
		break;
	}

	switch (cmdId) {
		case ID_SHELL_ACTIVATE: 
		{
			HWND hwndMain = AfxGetMainWnd()->GetSafeHwnd();
			BOOL ok = (hwndMain != NULL);
			if (ok)
				::SetForegroundWindow(hwndMain);
			if (ok) {
				WINDOWPLACEMENT wp;
				wp.length = sizeof(wp);
				ok = ::GetWindowPlacement(hwndMain, &wp);
				if (ok && wp.showCmd==SW_SHOWMINIMIZED)
					::ShowWindow(hwndMain, SW_RESTORE);
			}
			break;
		}
		case ID_SHELL_BREAK:
			// set a flag to tell the process to break;
			PyErr_SetInterrupt();
			break;
		default:
			break;
	}
}