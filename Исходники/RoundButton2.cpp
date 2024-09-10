void CRoundButton2::OnCaptureChanged(CWnd *pWnd)
{
	// Check, if we lost the mouse-capture
	if (GetCapture() != this)
	{
		// We have lost the mouse-capture, so the mouse has left the buttons face
		m_bMouseOnButton = false;

		// Redraw Control, if Button is hot
		if (m_bIsHotButton)
			Invalidate();
	}

	CButton::OnCaptureChanged(pWnd);
}