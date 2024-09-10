void CNormalButton::Draw(CDC &dc, const CPoint point, CRect rcUpdate, BOOL bIsPressDown)
{
	CDC TempDC;
	TempDC.CreateCompatibleDC(&dc);
	
// 	CBitmap memBmp;
// 	memBmp.CreateCompatibleBitmap(&dc, m_rc.right, m_rc.Height());
	CBitmap *pOldmap =  TempDC.SelectObject(&m_bitmap);

	
	int nStart = 0;
	CRect rc = m_rc;
	if (m_rc.PtInRect(point))
	{
		nStart += m_sizeBitmap.cx / 4;
		if (bIsPressDown)
		{
			nStart += m_sizeBitmap.cx / 4;
			rc.OffsetRect(1, 1);
		}
	}
	dc.SetBkMode(TRANSPARENT);
	dc.StretchBlt(m_rc.left, m_rc.top, m_rc.Width(), m_rc.Height(), &TempDC, nStart, 0, m_sizeBitmap.cx / 4, m_sizeBitmap.cy, SRCCOPY);
	dc.DrawText(m_strTitle, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	TempDC.SelectObject(pOldmap);
	//memBmp.DeleteObject();
	TempDC.DeleteDC();
}