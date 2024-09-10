void CSrmmProxyWindow::OnTimer(int)
{
	g_pTaskbarList->UnregisterTab(m_hwndParent);

	if (!m_refreshPreview) return;
	if (!IsWindowVisible(m_hwndWindow) || !IsWindowVisible(m_hwndParent) || IsIconic(m_hwndParent)) return;
	if (m_hbmpPreview) DeleteObject(m_hbmpPreview);

	m_refreshPreview = false;

	RECT rc;
	GetWindowRect(m_hwndWindow, &rc);

	m_hbmpPreview = CreateDwmBitmap(rc.right - rc.left, rc.bottom - rc.top);
	HDC hdc = CreateCompatibleDC(0);
	HBITMAP hbmpSave = (HBITMAP)SelectObject(hdc, m_hbmpPreview);
	PrintWindow(m_hwndWindow, hdc, PW_CLIENTONLY);
	SelectObject(hdc, hbmpSave);
	DeleteDC(hdc);

	MakeBitmapOpaque(m_hbmpPreview);

	InvalidateThumbnail();
}