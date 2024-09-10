	bool FSWinWatcher::IsCurrentFS ()
	{
#if !__GNUC__ 
// Not defined in my MinGW headers even on Vista 
// Maybe it will work later with MinGW
		QUERY_USER_NOTIFICATION_STATE state;
		if (SHQueryUserNotificationState (&state) != S_OK)
			return false;
		return state != QUNS_ACCEPTS_NOTIFICATIONS;
#else
		HWND hWnd = GetForegroundWindow ();
		if (!hWnd)
			return false;

		HMONITOR monitor = MonitorFromWindow (hWnd, MONITOR_DEFAULTTONULL);
		if (!monitor)
			return false;

		MONITORINFO lpmi;
		lpmi.cbSize = sizeof (lpmi);
		if (!GetMonitorInfo (monitor, &lpmi))
			return false;

		RECT monitorRect = lpmi.rcMonitor;
		RECT windowRect;
		GetWindowRect (hWnd, &windowRect);
		return EqualRect (&windowRect, &monitorRect) &&
				Proxy_->GetRootWindowsManager ()->GetPreferredWindow ()->effectiveWinId () != hWnd;
#endif
	}