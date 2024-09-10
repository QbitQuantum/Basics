void CSkinTab::OnPaint()
{
	int i = 0;
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect r;
	GetClientRect(&r);	

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap btScreen;
	btScreen.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	memDC.SelectObject(&btScreen);
	btScreen.DeleteObject();

	//画背景 
	memDC.BitBlt(r.left, r.top, r.Width(), r.Height(), &m_memDC, 0, 0, SRCCOPY);

	//memDC.Rectangle(r);
	for( i=0;i<m_nTabCount;i++)
	{
		CRect rect=m_pTabRect[m_nTabCount-i-1];
		
		rect.top +=22;
		DrawRangeImage(&m_BitmapBack[0],&memDC,rect);

	}
	if(m_nCurDownIndex!=-1)
	{
		CRect rect=m_pTabRect[m_nCurDownIndex];
		DrawRangeImage(&m_BitmapBack[1],&memDC,rect);

	
	}

	for(i = 0; i < MAX_TEXT_COUNT;i++)
	{
		if(strlen(m_TextTitle[i]) > 0)
		{
			CRect rect=m_pTabRect[i];
			CSize sizeTemp=memDC.GetTextExtent(m_TextTitle[i],_tcslen(m_TextTitle[i]));
			int xPos = (rect.Width() - sizeTemp.cx )/ 2 + rect.left;
			int YPos = (rect.Height() - sizeTemp.cy )/ 2 + rect.top + 11 ;
			if(xPos < 0)
				xPos = rect.left + 2;
			if(YPos < 0)
				YPos = rect.top + 2;
			memDC.SetBkMode(TRANSPARENT);
			memDC.TextOut(xPos ,YPos,m_TextTitle[i]);
		}
	}

	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.DeleteDC();
	// 不为绘图消息调用 CStatic::OnPaint()
}