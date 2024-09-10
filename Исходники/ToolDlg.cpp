void CToolDlg::OnNcRButtonDown(UINT nHitTest, CPoint point)
{
	SetActiveWindow();	// base class doesn't activate us, though it should
	UpdateWindow();	// else client area doesn't fully paint until button up
	if (m_IsNonBlocking) {
		// If you right-click in the caption bar, the message loop is blocked until
		// you release the mouse button. This is unacceptable in a timer-driven app.
		switch (nHitTest) {
		case HTCAPTION:
			break;	// don't call base class, display context menu in OnNcRButtonUp
		default:
			CPersistDlg::OnNcRButtonDown(nHitTest, point);
		}
	} else	// default behavior
		CPersistDlg::OnNcRButtonDown(nHitTest, point);
}