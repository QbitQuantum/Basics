void COleControl::DestroyTracker()
{
	ASSERT(!m_bOpen);
	ASSERT(m_bUIActive);

	if (m_pRectTracker == NULL)
		return;

	UINT nHandleSize = m_pRectTracker->m_nHandleSize - 1;

	// Destroy the tracker.
	delete m_pRectTracker;
	m_pRectTracker = NULL;

	// Restore window to its original (pre-UIActive) size.
	CWnd* pWndOuter = GetOuterWindow();
	CWnd* pWndParent = pWndOuter->GetParent();
	CRect rectWindow;
	CRect rectParent;
	pWndOuter->GetWindowRect(rectWindow);
	pWndParent->GetClientRect(rectParent);
	pWndParent->ClientToScreen(rectParent);
	rectWindow.OffsetRect(-rectParent.left, -rectParent.top);
	rectWindow.InflateRect(-(int)nHandleSize, -(int)nHandleSize);
	::MoveWindow(pWndOuter->m_hWnd, rectWindow.left, rectWindow.top,
		rectWindow.Width(), rectWindow.Height(), TRUE);
}