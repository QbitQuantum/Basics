void COleResizeBar::OnLButtonDown(UINT /*nFlags*/, CPoint point)
{
	// track to parent of the parent
	CWnd* pFrameWnd = GetParentFrame();
	ASSERT_VALID(pFrameWnd);
	CWnd* pParent = pFrameWnd->GetParent();

	pFrameWnd->UpdateWindow();  // update ourselves

	// limit tracking to parent client rectangle
	if (pParent != NULL)
	{
		pParent->UpdateWindow();    // always update before tracking

		// clip cursor to parent window
		CRect rect;
		pParent->GetClientRect(&rect);
		pParent->ClientToScreen(&rect);
		::ClipCursor(&rect);
	}

	// save the rect, track, then restore
	CRect rectSave = m_tracker.m_rect;
	BOOL bNotify = m_tracker.Track(this, point, FALSE, pParent);
	CRect rectNew = m_tracker.m_rect;
	m_tracker.m_rect = rectSave;

	// allow full mouse movement again
	::ClipCursor(NULL);

	// notify owner window if tracker changed
	if (bNotify)
	{
		CWnd* pOwner = GetOwner();
		ASSERT_VALID(pOwner);

		// convert relative to parent coordinates
		ClientToScreen(&rectNew);
		pOwner->ScreenToClient(&rectNew);

		// send notification to owner
		pOwner->SendMessage(WM_SIZECHILD, (WPARAM)_AfxGetDlgCtrlID(m_hWnd),
			(LPARAM)(LPCRECT)&rectNew);
	}
}