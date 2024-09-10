void CDL便签Dlg::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnNcPaint()
	//Default();
	CDC * pDC;
	pDC = this->GetWindowDC();

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_NCPAINT);
	CBitmap * oldbitmap;
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	oldbitmap = MemDC.SelectObject(&bitmap);

	CRect rect;
	this->GetWindowRect(rect);
	pDC->StretchBlt(0,0,
		rect.Width(),GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
		&MemDC,
		10,10,200,GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME),
		SRCCOPY);

	CRect rectClient;
	this->GetClientRect(rectClient);

	m_rcLEdge.left = 0;
	m_rcLEdge.right = GetSystemMetrics(SM_CYFRAME);
	m_rcLEdge.top = GetSystemMetrics(SM_CYCAPTION)+ GetSystemMetrics(SM_CYFRAME);
	m_rcLEdge.bottom = rect.Height();

	m_rcREdge.left = rect.Width() - GetSystemMetrics(SM_CYFRAME);
	m_rcREdge.right = rect.Width();
	m_rcREdge.top = m_rcLEdge.top;
	m_rcREdge.bottom = m_rcLEdge.bottom;

	m_rcBEdge.left = GetSystemMetrics(SM_CYFRAME);
	m_rcBEdge.right = rect.Width() - GetSystemMetrics(SM_CYFRAME);
	m_rcBEdge.top = rect.Height() - GetSystemMetrics(SM_CYFRAME);
	m_rcBEdge.bottom = rect.Height();

	pDC->StretchBlt(m_rcLEdge.left,m_rcLEdge.top,
		m_rcLEdge.Width(),m_rcLEdge.Height(),
		&MemDC,
		10-GetSystemMetrics(SM_CYFRAME),
		10+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME),
		m_rcLEdge.Width(),
		100,
		SRCCOPY);

	pDC->StretchBlt(m_rcREdge.left,m_rcREdge.top,
		m_rcREdge.Width(),m_rcREdge.Height(),
		&MemDC,
		10+GetSystemMetrics(SM_CYFRAME)+200,
		10+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME),
		m_rcREdge.Width(),
		100,
		SRCCOPY);

	pDC->StretchBlt(m_rcBEdge.left,m_rcBEdge.top,
		m_rcBEdge.Width(),m_rcBEdge.Height(),
		&MemDC,
		10,
		10+GetSystemMetrics(SM_CYCAPTION)+GetSystemMetrics(SM_CYFRAME)+rectClient.Height(),
		200+GetSystemMetrics(SM_CYFRAME)*2,
		m_rcBEdge.Height(),
		SRCCOPY);

	CRect closeRect;
	closeRect.left = rect.right - rect.left - 20;
	closeRect.top = GetSystemMetrics(SM_CYFRAME);
	closeRect.right = rect.right - rect.left - 5;
	closeRect.bottom = GetSystemMetrics( SM_CYSIZE ) ;

	/*
	pDC->DrawFrameControl(closeRect,
	DFC_CAPTION,
	DFCS_CAPTIONCLOSE );
	*/
	this->ReleaseDC(pDC);
	MemDC.SelectObject(oldbitmap);
	m_rcClose = closeRect;
}