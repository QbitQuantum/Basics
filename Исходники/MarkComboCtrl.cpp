void CMarkComboCtrl::Paint (CDC& dc) {
	CSize szShape;
	CRect rectCtrl, rectLabel;
	CMark mrkStyle;
	CFont fntDeflt;
	uvar32_64 szKernel;

	dc.FillSolidRect (m_rectText, ::GetSysColor (COLOR_WINDOW));
	mrkStyle = theApp.MarkStyles[aimActive].GetStyle();
	szShape = mrkStyle.GetShapeSize ();
	szKernel = mrkStyle.GetKernelSize ();

	m_rectText.DeflateRect (4, 4);
	rectLabel = m_rectText;
	m_rectText.right -= 100;
	rectLabel.left = m_rectText.right + 1;
	m_rectText.left -= (m_rectText.Height() - m_rectText.Width ()) / 2;
	m_rectText.right += (m_rectText.Height() - m_rectText.Width ()) / 2;
	if (szShape.cx >= szShape.cy) {
		m_rectText.top += (szShape.cx - szShape.cy) / 2;
		m_rectText.bottom -= (szShape.cx - szShape.cy) / 2;
	} else {
		m_rectText.left += (szShape.cy - szShape.cx) / 2;
		m_rectText.right -= (szShape.cy - szShape.cx) / 2;
	}
	GetClientRect (&rectCtrl);
	mrkStyle.SetPoint (CPoint ((rectCtrl.Width () - 115 )/ 2, rectCtrl.Height () / 2));
	mrkStyle.SetShapeSize (CSize (m_rectText.Width () - 2, m_rectText.Height () - 2));
	mrkStyle.SetKernelSize ((szKernel > m_rectText.Height())?m_rectText.Height():szKernel);
	mrkStyle.Paint (dc);

	fntDeflt.CreatePointFont (80, "Tahoma", &dc);
	CFont *pFont = dc.SelectObject (&fntDeflt);
	dc.DrawText (theApp.MarkStyles[aimActive].GetName (), rectLabel, DT_END_ELLIPSIS | DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_WORD_ELLIPSIS);
	dc.SelectObject (pFont);
	fntDeflt.DeleteObject ();
}