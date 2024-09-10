static INT_PTR CALLBACK startup_dlgproc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hbmp = NULL;
	HDC hdc;
	
	switch (uMsg) {
		case WM_INITDIALOG: {
			HWND hwnd;
			RECT r, rdlg, chrome, rtab, rcancel, rstart;
			int xoffset = 0, yoffset = 0;

			// Fetch the positions (in screen coordinates) of all the windows we need to tweak
			ZeroMemory(&chrome, sizeof(chrome));
			AdjustWindowRect(&chrome, GetWindowLong(hwndDlg, GWL_STYLE), FALSE);
			GetWindowRect(hwndDlg, &rdlg);
			GetWindowRect(GetDlgItem(hwndDlg, WIN_STARTWIN_TABCTL), &rtab);
			GetWindowRect(GetDlgItem(hwndDlg, WIN_STARTWIN_CANCEL), &rcancel);
			GetWindowRect(GetDlgItem(hwndDlg, WIN_STARTWIN_START), &rstart);

			// Knock off the non-client area of the main dialogue to give just the client area
			rdlg.left -= chrome.left; rdlg.top -= chrome.top;
			rdlg.right -= chrome.right; rdlg.bottom -= chrome.bottom;

			// Translate them to client-relative coordinates wrt the main dialogue window
			rtab.right -= rtab.left - 1; rtab.bottom -= rtab.top - 1;
			rtab.left  -= rdlg.left; rtab.top -= rdlg.top;

			rcancel.right -= rcancel.left - 1; rcancel.bottom -= rcancel.top - 1;
			rcancel.left -= rdlg.left; rcancel.top -= rdlg.top;

			rstart.right -= rstart.left - 1; rstart.bottom -= rstart.top - 1;
			rstart.left -= rdlg.left; rstart.top -= rdlg.top;

			// And then convert the main dialogue coordinates to just width/length
			rdlg.right -= rdlg.left - 1; rdlg.bottom -= rdlg.top - 1;
			rdlg.left = 0; rdlg.top = 0;

			// Load the bitmap into the bitmap control and fetch its dimensions
			hbmp = LoadBitmap((HINSTANCE)win_gethinstance(), MAKEINTRESOURCE(RSRC_BMP));
			hwnd = GetDlgItem(hwndDlg,WIN_STARTWIN_BITMAP);
			SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbmp);
			GetClientRect(hwnd, &r);
			xoffset = r.right;
			yoffset = r.bottom - rdlg.bottom;

			// Shift and resize the controls that require it
			rtab.left += xoffset; rtab.bottom += yoffset;
			rcancel.left += xoffset; rcancel.top += yoffset;
			rstart.left += xoffset; rstart.top += yoffset;
			rdlg.right += xoffset;
			rdlg.bottom += yoffset;

			// Move the controls to their new positions
			MoveWindow(GetDlgItem(hwndDlg, WIN_STARTWIN_TABCTL), rtab.left, rtab.top, rtab.right, rtab.bottom, FALSE);
			MoveWindow(GetDlgItem(hwndDlg, WIN_STARTWIN_CANCEL), rcancel.left, rcancel.top, rcancel.right, rcancel.bottom, FALSE);
			MoveWindow(GetDlgItem(hwndDlg, WIN_STARTWIN_START), rstart.left, rstart.top, rstart.right, rstart.bottom, FALSE);

			// Move the main dialogue to the centre of the screen
			hdc = GetDC(NULL);
			rdlg.left = (GetDeviceCaps(hdc, HORZRES) - rdlg.right) / 2;
			rdlg.top = (GetDeviceCaps(hdc, VERTRES) - rdlg.bottom) / 2;
			ReleaseDC(NULL, hdc);
			MoveWindow(hwndDlg, rdlg.left + chrome.left, rdlg.top + chrome.left,
				rdlg.right + (-chrome.left+chrome.right), rdlg.bottom + (-chrome.top+chrome.bottom), TRUE);

			// Add tabs to the tab control
			{
				TCITEM tab;
				
				hwnd = GetDlgItem(hwndDlg, WIN_STARTWIN_TABCTL);

				ZeroMemory(&tab, sizeof(tab));
				tab.mask = TCIF_TEXT;
				tab.pszText = TEXT("Configuration");
				SendMessage(hwnd, TCM_INSERTITEM, (WPARAM)TAB_CONFIG, (LPARAM)&tab);
				tab.mask = TCIF_TEXT;
				tab.pszText = TEXT("Game");
				SendMessage(hwnd, TCM_INSERTITEM, (WPARAM)TAB_GAME, (LPARAM)&tab);
				tab.mask = TCIF_TEXT;
				tab.pszText = TEXT("Messages");
				SendMessage(hwnd, TCM_INSERTITEM, (WPARAM)TAB_MESSAGES, (LPARAM)&tab);

				// Work out the position and size of the area inside the tab control for the pages
				ZeroMemory(&r, sizeof(r));
				GetClientRect(hwnd, &r);
				SendMessage(hwnd, TCM_ADJUSTRECT, FALSE, (LPARAM)&r);
				r.right -= r.left-1;
				r.bottom -= r.top-1;
				r.top += rtab.top;
				r.left += rtab.left;

				// Create the pages and position them in the tab control, but hide them
				pages[TAB_CONFIG] = CreateDialog((HINSTANCE)win_gethinstance(),
					MAKEINTRESOURCE(WIN_STARTWINPAGE_CONFIG), hwndDlg, ConfigPageProc);
				pages[TAB_GAME] = CreateDialog((HINSTANCE)win_gethinstance(),
					MAKEINTRESOURCE(WIN_STARTWINPAGE_GAME), hwndDlg, GamePageProc);
				pages[TAB_MESSAGES] = GetDlgItem(hwndDlg, WIN_STARTWIN_MESSAGES);
				SetWindowPos(pages[TAB_CONFIG], hwnd,r.left,r.top,r.right,r.bottom,SWP_HIDEWINDOW);
				SetWindowPos(pages[TAB_GAME], hwnd,r.left,r.top,r.right,r.bottom,SWP_HIDEWINDOW);
				SetWindowPos(pages[TAB_MESSAGES], hwnd,r.left,r.top,r.right,r.bottom,SWP_HIDEWINDOW);

				// Tell the editfield acting as the console to exclude the width of the scrollbar
				GetClientRect(pages[TAB_MESSAGES],&r);
				r.right -= GetSystemMetrics(SM_CXVSCROLL)+4;
				r.left = r.top = 0;
				SendMessage(pages[TAB_MESSAGES], EM_SETRECTNP,0,(LPARAM)&r);

				// Set a tab stop in the game data listbox
				{
				DWORD tabs[1] = { 150 };
				ListBox_SetTabStops(GetDlgItem(pages[TAB_GAME], IDGDATA), 1, tabs);
				}

				SetFocus(GetDlgItem(hwndDlg, WIN_STARTWIN_START));
				SetWindowText(hwndDlg, apptitle);
			}
			return FALSE;
		}

		case WM_NOTIFY: {
			LPNMHDR nmhdr = (LPNMHDR)lParam;
			int cur;
			if (nmhdr->idFrom != WIN_STARTWIN_TABCTL) break;
			cur = (int)SendMessage(nmhdr->hwndFrom, TCM_GETCURSEL,0,0);
			switch (nmhdr->code) {
				case TCN_SELCHANGING: {
					if (cur < 0 || !pages[cur]) break;
					ShowWindow(pages[cur],SW_HIDE);
					return TRUE;
				}
				case TCN_SELCHANGE: {
					if (cur < 0 || !pages[cur]) break;
					ShowWindow(pages[cur],SW_SHOW);
					return TRUE;
				}
			}
			break;
		}

		case WM_CLOSE:
			if (mode == TAB_CONFIG) done = 0;
			else quitevent++;
			return TRUE;

		case WM_DESTROY:
			if (hbmp) {
				DeleteObject(hbmp);
				hbmp = NULL;
			}

			if (pages[TAB_GAME]) {
				DestroyWindow(pages[TAB_GAME]);
				pages[TAB_GAME] = NULL;
			}

			if (pages[TAB_CONFIG]) {
				DestroyWindow(pages[TAB_CONFIG]);
				pages[TAB_CONFIG] = NULL;
			}

			startupdlg = NULL;
			return TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case WIN_STARTWIN_CANCEL:
					if (mode == TAB_CONFIG) done = 0;
					else quitevent++;
					return TRUE;
				case WIN_STARTWIN_START: done = 1; return TRUE;
			}
			return FALSE;

		case WM_CTLCOLORSTATIC:
			if ((HWND)lParam == pages[TAB_MESSAGES])
				return (BOOL)GetSysColorBrush(COLOR_WINDOW);
			break;

		default: break;
	}

	return FALSE;
}