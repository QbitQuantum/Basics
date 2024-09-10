void CAimComboCtrl::OnPaint () {
	CRect rect;
	CPaintDC dc (this);
	GetClientRect (&rect);

	m_rectBtn = rect;
	m_rectBtn.left = rect.right - 13;
	m_rectText = rect;
	m_rectText.right = rect.right - 13;
	m_rectText.DeflateRect (2, 1);
	dc.FillSolidRect (rect, ::GetSysColor (COLOR_WINDOW));
	dc.FillSolidRect (m_rectBtn, ::GetSysColor (COLOR_BTNFACE));
	dc.DrawIcon (m_rectBtn.CenterPoint () - CSize (5, 5), theApp.LoadIcon (IDI_PIC_DOWNARROW));
	dc.DrawEdge (m_rectBtn, BDR_RAISEDINNER, BF_RECT);

	CDC dcMem;
	dcMem.CreateCompatibleDC (&dc);
	CBitmap *pOld = dcMem.GetCurrentBitmap ();
	dcMem.SelectObject (m_pbmpImage);
	dc.SetBkMode (TRANSPARENT);
	//dc.SetROP2 (R2_NOP);
	//dc.SetStretchBltMode (STRETCH_HALFTONE);
	//dc.StretchBlt (m_rectText.left, m_rectText.top, m_rectText.Width(), m_rectText.Height (), &dcMem, 0, 0, 
	//               16, 16, SRCCOPY);
	dcMem.SelectObject (pOld);
	dcMem.DeleteDC ();

	Paint (dc);
}