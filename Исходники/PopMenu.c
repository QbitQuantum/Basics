LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int		idColor[5] = {WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH};
	static int		iSelection = IDM_BKGND_WHITE;
	static HMENU	hMenu, hSubMenu;
	POINT			point;
	int				cnt;
	HDC				hdc;
	TCHAR			szBuffer[10];

	switch (message) {
	//case WM_CREATE:
	//	hMenu = LoadMenu(hInst, szAppName);
	//	hMenu = GetSubMenu(hMenu, 0);
	//	return 0;

	case WM_RBUTTONUP:
		hMenu = LoadMenu(hInst, szAppName);
		hMenu = GetSubMenu(hMenu, 1);
		
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		ClientToScreen(hwnd, &point);
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hwnd, NULL);


		//Show count
		hSubMenu = GetSubMenu(hMenu, 0);
		hdc = GetDC(hwnd);
		TextOut(hdc,0 ,0, szBuffer, wsprintf(szBuffer, TEXT("File: %i"), GetMenuItemCount(hSubMenu))); 
		ReleaseDC(hwnd, hdc);
		DestroyMenu(hSubMenu);

		hSubMenu = GetSubMenu(hMenu, 3);
		hdc = GetDC(hwnd);
		TextOut(hdc,0 ,20, szBuffer, wsprintf(szBuffer, TEXT("Timer: %i"), GetMenuItemCount(hSubMenu))); 
		ReleaseDC(hwnd, hdc);
		DestroyMenu(hSubMenu);

		DestroyMenu(hMenu);

		return 0;

	case WM_COMMAND:
		hMenu = GetMenu(hwnd);
		switch (LOWORD (wParam)) {
		case IDM_FILE_NEW:
		case IDM_FILE_OPEN:
		case IDM_FILE_SAVE:
		case IDM_FILE_SAVE_AS:
			MessageBeep(0);
			return 0;

		case IDM_APP_EXIT:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;

		case IDM_EDIT_UNDO:
		case IDM_EDIT_CUT:
		case IDM_EDIT_COPY:
		case IDM_EDIT_PASTE:
		case IDM_EDIT_CLEAR:
			MessageBeep(0);
			return 0;

		case IDM_BKGND_WHITE:
		case IDM_BKGND_LTGRAY:
		case IDM_BKGND_GRAY:
		case IDM_BKGND_DKGRAY:
		case IDM_BKGND_BLACK:
			CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
			iSelection = LOWORD(wParam);
			CheckMenuItem(hMenu, iSelection, MF_CHECKED);

			SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG) GetStockObject(idColor[LOWORD(wParam) - IDM_BKGND_WHITE]));
			InvalidateRect(hwnd, NULL, TRUE);
			return 0;

		case IDM_TIMER_START:
			if (SetTimer(hwnd, ID_TIMER, 1000, NULL)) {
				EnableMenuItem(hMenu, IDM_TIMER_START, MF_GRAYED);
				EnableMenuItem(hMenu, IDM_TIMER_STOP, MF_ENABLED);
			}
			return 0;

		case IDM_TIMER_STOP:
			KillTimer(hwnd, ID_TIMER);
			EnableMenuItem(hMenu, IDM_TIMER_START, MF_ENABLED);
			EnableMenuItem(hMenu, IDM_TIMER_STOP, MF_GRAYED);
			return 0;

		case IDM_APP_HELP:
			MessageBox(hwnd, TEXT("Help not yet implemented!"), szAppName, MB_ICONEXCLAMATION | MB_OK);
			return 0;

		case IDM_APP_ABOUT:
			MessageBox(hwnd, TEXT("Menu Demonstration Program\n") TEXT("(c) hogehoge, 2013"), szAppName, MB_ICONINFORMATION | MB_OK);
			return 0;
		}
		//break;
		return 0;

	case WM_TIMER:
		MessageBeep(0);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}