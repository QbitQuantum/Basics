void CFXStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting


	CRect rect;
	GetClientRect(rect); 

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);	// Select the bitmap into the in-memory DC
	dcMemory.SetBkMode(TRANSPARENT);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	CBitmap* pOldBitmap = dcMemory.SelectObject(CBitmap::FromHandle(bmp));

	if (m_bselected)
		dcMemory.FillSolidRect(rect,RGB(120,120,120));
	else
		dcMemory.FillSolidRect(rect,m_colorbk);

	dcMemory.SelectObject(&m_font);

	dcMemory.SetTextColor(RGB(255,255,255));
	dcMemory.TextOutA(5,0,m_strcurrency);

	dcMemory.SetTextColor(m_colornow);
	dcMemory.TextOutA(75,0,m_strdisplayprice);

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcMemory,0,0,SRCCOPY);
	dcMemory.SelectObject(pOldBitmap);
	dcMemory.DeleteDC();
	DeleteObject(bmp);
}