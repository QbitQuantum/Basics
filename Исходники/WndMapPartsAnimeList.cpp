void CWndMapPartsAnimeList::OnPaint()
{
	int x, cx, cy;
	HDC hDC;
	CDC DCTmp;
	CRect rc, rcTmp;
	CRgn rgn;
	CPaintDC dc(this);

	hDC = m_pImgParts->Lock ();
	DCTmp.Attach (hDC);

	GetClientRect (rc);
	rgn.CreateRectRgn (0, 0, rc.Width (), rc.Height ());
	dc.SelectClipRgn (&rgn, RGN_COPY);

	x = GetScrollPos (SB_HORZ);

	cx = min (rc.Width (), m_pImgParts->Width ());
	cy = min (rc.Height (), m_pImgParts->Height ());
	dc.FillSolidRect (rc, RGB (128, 128, 128));
	dc.BitBlt (0, 0, cx, cy, &DCTmp, x * 16, 0, SRCCOPY);

	m_pImgParts->Unlock ();
	DCTmp.Detach ();
}