HBRUSH CIconEditEx::CtlColor(CDC* pDC, UINT nCtlColor)
{
	HBRUSH hbr;
	hbr = (HBRUSH)m_brBkgnd; // Passing a Handle to the Brush
	CRect rcClient;
	GetClientRect(&rcClient);
	if (m_progressValue > 0.0)
	{
		CRect rc;
		GetRect(&rc);
		pDC->FillSolidRect(&rc, m_colors[COL_Bk]);
		GetClientRect(&rc);
		CRgn rgn;
		rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
		pDC->SelectClipRgn(&rgn, RGN_COPY);
		pDC->FillSolidRect(0, 0, INT(rc.Width() * m_progressValue), rc.Height(), m_colors[COL_Progress]);
		pDC->SetBkMode(TRANSPARENT);
	}
	//if (m_hIcon != NULL)
	//{
	//	CRgn rgn;
	//	rgn.CreateRectRgn(cMargin, cMargin, cMargin + m_cx, cMargin + m_cy);
	//	pDC->SelectClipRgn(&rgn, RGN_OR);
	//	INT top = (rcClient.Height() - m_cy) / 2;
	//	::DrawIconEx(pDC->m_hDC, cMargin, top, m_hIcon, m_cx, m_cy, 0, NULL, DI_NORMAL );
	//}
	//if (m_hClearIcon != NULL)
	//{
	//	INT top = (rcClient.Height() - m_cy) / 2;
	//	::DrawIconEx(pDC->m_hDC, cMargin, top, m_hIcon, m_cx, m_cy, 0, NULL, DI_NORMAL );
	//}
	pDC->SetBkColor(m_colors[COL_Bk]); // Setting the Color of the Text Background to the one passed by the Dialog
	pDC->SetTextColor(m_colors[COL_Text]); // Setting the Text Color to the one Passed by the Dialog
	return hbr;
}