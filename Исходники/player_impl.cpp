BOOL player_impl::full_screen(BOOL fullscreen)
{
	HWND hparent = GetParent(m_hwnd);

	// 不支持非顶层窗口全屏操作.
	if (IsWindow(hparent))
		return FALSE;

	// Save the current windows placement/placement to
	// restore when fullscreen is over
	WINDOWPLACEMENT window_placement;
	window_placement.length = sizeof(WINDOWPLACEMENT);
	GetWindowPlacement(m_hwnd, &window_placement);

	if (fullscreen && !m_full_screen)
	{
		m_full_screen = true;
		m_wnd_style = GetWindowLong(m_hwnd, GWL_STYLE);
		printf("entering fullscreen mode.\n");
		SetWindowLong(m_hwnd, GWL_STYLE, WS_CLIPCHILDREN | WS_VISIBLE);

		if (IsWindow(hparent))
		{
			// Retrieve current window position so fullscreen will happen
			// on the right screen
			HMONITOR hmon = MonitorFromWindow(hparent, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi;
			mi.cbSize = sizeof(MONITORINFO);
			if (::GetMonitorInfo(hmon, &mi))
				::SetWindowPos(m_hwnd, 0,
				mi.rcMonitor.left,
				mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOZORDER | SWP_FRAMECHANGED);
		}
		else
		{
			// Maximize non embedded window
			ShowWindow(m_hwnd, SW_SHOWMAXIMIZED);
		}

		if (IsWindow(hparent))
		{
			// Hide the previous window
			RECT rect;
			GetClientRect(m_hwnd, &rect);
			// SetParent(hwnd, hwnd);
			SetWindowPos(m_hwnd, 0, 0, 0,
				rect.right, rect.bottom,
				SWP_NOZORDER|SWP_FRAMECHANGED);
			HWND topLevelParent = GetAncestor(hparent, GA_ROOT);
			ShowWindow(topLevelParent, SW_HIDE);
		}
		SetForegroundWindow(m_hwnd);
		return TRUE;
	}

	if (!fullscreen && m_full_screen)
	{
		m_full_screen = FALSE;
		printf("leaving fullscreen mode.\n");
		// Change window style, no borders and no title bar
		SetWindowLong(m_hwnd, GWL_STYLE, m_wnd_style);

		if (hparent)
		{
			RECT rect;
			GetClientRect(hparent, &rect);
			// SetParent(hwnd, hparent);
			SetWindowPos(m_hwnd, 0, 0, 0,
				rect.right, rect.bottom,
				SWP_NOZORDER | SWP_FRAMECHANGED);

			HWND topLevelParent = GetAncestor(hparent, GA_ROOT);
			ShowWindow(topLevelParent, SW_SHOW);
			SetForegroundWindow(hparent);
			ShowWindow(m_hwnd, SW_HIDE);
		}
		else
		{
			// return to normal window for non embedded vout
			SetWindowPlacement(m_hwnd, &window_placement);
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
		}
		return TRUE;
	}

	return FALSE;
}