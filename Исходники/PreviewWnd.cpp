void CPreviewWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (!m_pBuffer)
		return;

	CRect rect;
	GetClientRect(rect);

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap *pBmp = dcMem.SelectObject(&bmp);

	dcMem.FillSolidRect( rect, RGB(0,0,0));	
	
	dcMem.SelectStockObject(DC_PEN);
	dcMem.SetDCPenColor( RGB(0, 255,0));

	DWORD dwLen = m_dwBufferLen;
	short *p = reinterpret_cast<short *>(m_pBuffer);
	CRect rectChannel(rect);
	rectChannel.bottom = rect.Height()/2;
	dcMem.MoveTo(0,rectChannel.Height()/2);
	long dStep = (double)(dwLen/2)/(double)rect.Width();
	int xpos=0;
	for (int x=0; x < dwLen; x+=dStep)
	{
		double d = ((double)p[x]/(double)0xffff) * (double)rect.Height();
		dcMem.LineTo(xpos++, (rectChannel.Height()/2)+d);
	}
	
	rectChannel.OffsetRect(0, rect.Height()/2);
	dcMem.MoveTo(rectChannel.left, rectChannel.top+(rectChannel.Height()/2));
	xpos = 0;
	for ( int x=1; x < dwLen; x+=dStep)
	{
		double d = ((double)p[x]/(double)0xffff) * (double)rect.Height();
		dcMem.LineTo(xpos++, rectChannel.top+(rectChannel.Height()/2)+d);
	}
	
	dc.BitBlt(0,0,rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
	if (pBmp)
		dcMem.SelectObject(pBmp);
}