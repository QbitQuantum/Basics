void CDlg_Control_InfoTrack::AddPoint(INT nX, INT nY)
{
	CDC* pDC = GetDC();
	
	CDC dcBmp;
	dcBmp.CreateCompatibleDC(pDC);
	CBitmap* pOld = (CBitmap*)(dcBmp.SelectObject(&m_bmpInfo));

	if(m_ptLastPoint.x < 0 || m_ptLastPoint.y < 0)
	{
		dcBmp.SetPixel(nX, nY, RGB(0, 0, 0));
	}
	else
	{
		dcBmp.MoveTo(m_ptLastPoint.x, m_ptLastPoint.y);
		dcBmp.LineTo(nX, nY);
	}

	m_ptLastPoint.x = nX;
	m_ptLastPoint.y = nY;

	dcBmp.SelectObject(pOld);
	ReleaseDC(pDC);

	m_staInfoTrack.InvalidateRect(0, FALSE);
}