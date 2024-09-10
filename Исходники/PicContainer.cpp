void CPicContainer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	CDC *pDC =GetDC();

	//绘制背景图片
	if(m_pBitmap)
	{
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);

		BITMAP bmpInfo;
		m_pBitmap->GetBitmap(&bmpInfo);

		CBitmap* pOldBitmap = dcMemory.SelectObject(m_pBitmap);

		CRect rect;
		GetClientRect(&rect);
	
		pDC->SetStretchBltMode(COLORONCOLOR);
		BOOL bsuc =pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 
			0, 0,bmpInfo.bmWidth,bmpInfo.bmHeight, SRCCOPY);

		dcMemory.SelectObject(pOldBitmap);

	}
	if(m_text!="")
	{
		//背景色设置成透明
		int oldMode =pDC->SetBkMode(TRANSPARENT);
		CRect rect;
		rect.left =50;
		rect.top =50;
		rect.bottom =rect.right =100;
		pDC->DrawText(m_text,&rect,DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);
		pDC->SetBkMode(oldMode);
	}
	for(size_t i=0;i<m_buttons.size();i++)
	{
		m_buttons[i]->Invalidate();
	}
}