BOOL CSplitter::OnPaint(HDC hDC)
{
	CPaintDC dc(GetSafeHwnd()); // device context for painting
	CBrush cbr;
	CRect rcClient;
	GetClientRect(&rcClient);
	cbr.CreateSolidBrush(clrBg);
	
	CGDI		MemDC;
	CBitmap		m_BitmapMemDC;
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height());	
	
	CBitmap *m_bitmapOld=new CBitmap(MemDC.SelectObject(&m_BitmapMemDC));
	
	MemDC.FillRect(&rcClient,&cbr);
	DrawSplitter(m_rcSpplitter,m_rectLeft,m_rectRight,&MemDC);
	
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();
	cbr.DeleteObject();
	dc.DeleteDC();
	m_bitmapOld->DeleteObject();
	delete m_bitmapOld;
	return TRUE;
}