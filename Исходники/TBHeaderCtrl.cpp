void CTBHeaderCtrl::DrawHeader(CDC* pDC)
{
	bool bGet = false;
	if (NULL == pDC)
	{
		pDC = GetDC();
		bGet = true;
	} 
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap memBmp;
	CRect memRect;
	GetClientRect(&memRect);
	memBmp.CreateCompatibleBitmap(pDC, memRect.Width(), memRect.Height());
	CBitmap* pOldBmp = dc.SelectObject(&memBmp);
	dc.FillSolidRect(0, 0, memRect.Width(), memRect.Height(), RGB(m_R, m_G, m_B));

	int nItem; 
	nItem = GetItemCount();
	for(int i = 0; i<nItem;i ++) 
	{ 
		CRect tRect;
		GetItemRect(i,&tRect);
		int R = m_R,G = m_G,B = m_B;
		CRect nRect(tRect);
		nRect.left++;

		for(int j = tRect.top;j<=tRect.bottom;j++) 
		{ 
			nRect.bottom = nRect.top+1; 
			CBrush _brush; 
			_brush.CreateSolidBrush(RGB(R,G,B));
			dc.FillRect(&nRect,&_brush); 
			_brush.DeleteObject(); 
			R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
			if (R<0)R = 0;
			if (G<0)G = 0;
			if (B<0)B= 0;
			nRect.top = nRect.bottom; 
		} 
		dc.SetBkMode(TRANSPARENT);
		CFont nFont ,* nOldFont; 
		//dc.SetTextColor(RGB(250,50,50)); 
		dc.SetTextColor(m_color);
		HDITEM hdItem;
		ZeroMemory(&hdItem, sizeof(hdItem));
		hdItem.mask = HDI_TEXT;
		hdItem.pszText = new TCHAR[256];
		ZeroMemory(hdItem.pszText, 256);
		hdItem.cchTextMax = 256;
		if (GetItem(i, &hdItem))
		{
			nFont.CreateFont(m_fontHeight,m_fontWith,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("SimSun"));
			nOldFont = dc.SelectObject(&nFont);

			TEXTMETRIC metric;
			dc.GetTextMetrics(&metric);
			int ofst = 0;
			ofst = tRect.Height() - metric.tmHeight;
			tRect.OffsetRect(0,ofst/2);
			dc.DrawText(hdItem.pszText,&tRect,DT_CENTER);

			dc.SelectObject(nOldFont); 
			nFont.DeleteObject(); 
		}
		delete []hdItem.pszText;
	} 

	CRect rtRect;
	CRect clientRect;
	GetItemRect(nItem - 1,rtRect);
	GetClientRect(clientRect);
	rtRect.left = rtRect.right+1;
	rtRect.right = clientRect.right;
	int R = m_R,G = m_G,B = m_B;
	CRect nRect(rtRect);

	for(int j = rtRect.top;j<=rtRect.bottom;j++) 
	{ 
		nRect.bottom = nRect.top+1; 
		CBrush _brush; 
		_brush.CreateSolidBrush(RGB(R,G,B));
		dc.FillRect(&nRect,&_brush);
		_brush.DeleteObject(); 
		R-=m_Gradient;G-=m_Gradient;B-=m_Gradient;
		if (R<0)R = 0;
		if (G<0)G = 0;
		if (B<0)B= 0;
		nRect.top = nRect.bottom; 
	} 

	pDC->BitBlt(0, 0, memRect.Width(), memRect.Height(), &dc, 0, 0, SRCCOPY);
	dc.SelectObject(pOldBmp);
	memBmp.DeleteObject();
	dc.DeleteDC();

	if (bGet)
	{
		ReleaseDC(pDC);
	}
}