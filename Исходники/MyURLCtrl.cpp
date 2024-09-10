void CMyURLCtrl::OnPaint (void)
{
	CPaintDC dc (this);

	// Set Current Drawing Properties
	CFont* pCurrentFont = dc.SelectObject (&o_Font);
	COLORREF crCurrentTextColor = dc.SetTextColor (RGB (0, 0, 255));

	CRect rc;
	GetWindowRect (&rc);
	ScreenToClient (rc);
	
	dc.SetBkMode (TRANSPARENT);

	dc.DrawText (s_Text, rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS);
	
	// Reset Drawing Properties
	dc.SelectObject (pCurrentFont);
	dc.SetTextColor (crCurrentTextColor);
}