BOOL CXTPHeaderCtrl::RecalcLayout()
{
	if (!::IsWindow(m_hWnd))
		return FALSE;

	HD_LAYOUT hdl;

	CXTPClientRect rcClient(this);
	hdl.prc = &rcClient;

	WINDOWPOS wp;
	ZeroMemory(&wp, sizeof(WINDOWPOS));
	hdl.pwpos = &wp;

	if (!Header_Layout(m_hWnd, &hdl))
		return FALSE;

	// Set the size, position, and visibility of the header window.
	::SetWindowPos(m_hWnd, wp.hwndInsertAfter, wp.x, wp.y,
		wp.cx, wp.cy, wp.flags | SWP_FRAMECHANGED);

	CWnd* pWndParent = GetParent();
	if (!::IsWindow(pWndParent->GetSafeHwnd()))
		return FALSE;

	// Force list control to recalculate it's layout.
	CXTPWindowRect rcWindow(pWndParent);

	const int cx = rcWindow.Width();
	const int cy = rcWindow.Height();

	pWndParent->SetWindowPos(NULL, 0, 0, cx, cy+1,
		SWP_NOMOVE | SWP_FRAMECHANGED);

	pWndParent->SetWindowPos(NULL, 0, 0, cx, cy,
		SWP_NOMOVE | SWP_FRAMECHANGED);

	return TRUE;
}