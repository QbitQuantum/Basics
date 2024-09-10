		static void OnSize(HWND hwnd, UINT state, int cx, int cy)
		{
			if (state == SIZE_MINIMIZED)
			{
				NOTIFYICONDATAW dta = {};
				dta.cbSize = sizeof(NOTIFYICONDATAW);
				dta.hWnd = hwnd;
				dta.uID = ID_TRAY;
				dta.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
				dta.uCallbackMessage = WM_SHELLNOTIFY;
				dta.hIcon = LoadIconW(GetWindowInstance(hwnd), MAKEINTRESOURCEW(ID_ICON1));
				std::swprintf(dta.szTip, sizeof dta.szTip / sizeof *dta.szTip, L"D2CS Version " D2CS_VERSION_STRING);

				Shell_NotifyIconW(NIM_ADD, &dta);
				ShowWindow(hwnd, SW_HIDE);
				return;
			}

			MoveWindow(ghwndConsole, 0, 0, cx, cy, TRUE);
		}