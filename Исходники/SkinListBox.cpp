void CSkinListBox::OnNcPaint()
{
	//如果资源没有就是不想绘制边框了
	if ( m_pBackImgN == NULL ) 
	{
		__super::OnNcPaint();
		return;
	}

	CRect rcWindow;
	GetWindowRect(&rcWindow);

	CRect rcClient;
	GetClientRect(&rcClient);

	ClientToScreen(&rcClient);
	rcClient.OffsetRect(-rcWindow.left, -rcWindow.top);

	rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	CDC *pWindowDC = GetWindowDC();
	CMemoryDC MemDC(pWindowDC,rcWindow);

	DrawParentWndBg(GetSafeHwnd(),MemDC.GetSafeHdc());

	if (m_pBackImgN != NULL && !m_pBackImgN->IsNull())
		m_pBackImgN->Draw(&MemDC, rcWindow);
	
	pWindowDC->BitBlt(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),&MemDC,0,0,SRCCOPY);

	ReleaseDC(pWindowDC);
}