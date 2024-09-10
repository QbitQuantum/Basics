BOOL CSystemTray::RemoveTaskbarIcon(HWND hWnd)
{
    // Create static invisible window
    if (!::IsWindow(m_hWndInvisible))
    {
		m_hWndInvisible = CreateWindowEx(0, "Static", _T(""), WS_POPUP,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, 0, NULL, 0);

		if (!m_hWndInvisible)
			return FALSE;
    }

    SetParent(hWnd, m_hWndInvisible);

    return TRUE;
}