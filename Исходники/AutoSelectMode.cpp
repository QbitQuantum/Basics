BOOL AutoSelectMode::snapshotWindows()
{
	for (HWND hWnd = GetTopWindow(NULL); NULL != hWnd; hWnd = GetWindow(hWnd, GW_HWNDNEXT))
	{
		if (!IsWindow(hWnd)
			|| !IsWindowVisible(hWnd)
			|| IsIconic(hWnd))
		{
			continue;
		}
		EnumChildWindows(hWnd, [](HWND hwnd, LPARAM lParam)->BOOL{
			if (!IsWindow(hwnd)
				|| !IsWindowVisible(hwnd)
				|| IsIconic(hwnd))
			{
				return TRUE;
			}
			RECT rcWnd = { 0 };
			GetWindowRect(hwnd, &rcWnd);
			
			if (ScreenCommon::isRectEmpty(rcWnd))
			{
				return TRUE;
			}

			wchar_t szTxt[MAX_PATH] = { 0 };
			GetWindowText(hwnd, szTxt, MAX_PATH);
			if (wcslen(szTxt) <= 0)
			{
				//continue;
			}

			//combine the rect with the screen rect
			AutoSelectMode* pThis = (AutoSelectMode*)lParam;
			pThis->m_lsWndList.push_back(ScreenCaptureWndInfo(hwnd, rcWnd));
			return TRUE;
		}, (LPARAM)this);
		

		RECT rcWnd = { 0 };
		GetWindowRect(hWnd, &rcWnd);
		adjustRectInScreen(rcWnd);
		if (ScreenCommon::isRectEmpty(rcWnd))
		{
			continue;
		}

		wchar_t szTxt[MAX_PATH] = { 0 };
		GetWindowText(hWnd, szTxt, MAX_PATH);
		if (wcslen(szTxt) <= 0)
		{
			//continue;
		}

		//combine the rect with the screen rect
		m_lsWndList.push_back(ScreenCaptureWndInfo(hWnd, rcWnd));
	}

	return m_lsWndList.size() > 0;
}