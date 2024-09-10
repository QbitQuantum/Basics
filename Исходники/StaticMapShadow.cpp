void CStaticMapShadow::OnPaint()
{
	int x, y, cy;
	HDC hDC;
	CDC DCTmp;
	CRect rc, rcTmp;
	CRgn rgn;
	CPaintDC dc(this);

	hDC = m_pImgShadow->Lock ();
	DCTmp.Attach (hDC);

	GetWindowRect (rc);
	rgn.CreateRectRgn (0, 0, rc.Width (), rc.Height ());
	dc.SelectClipRgn (&rgn, RGN_COPY);

	ScreenToClient (rc);
	cy = min (rc.Height (), m_pImgShadow->Height ());
	dc.BitBlt (0, 0, m_pImgShadow->Width (), cy, &DCTmp, 0, 0, SRCCOPY);

	x = m_ptCursor.x * 16;
	y = (m_ptCursor.y - m_nPos) * 16;
	cy = y + 15;
	cy = min (cy, rc.Height ());
	rcTmp.SetRect (x, y, x + 15, cy);

	dc.DrawEdge (rcTmp, EDGE_BUMP, BF_FLAT | BF_RECT);

	m_pImgShadow->Unlock ();
	DCTmp.Detach ();
}