//KMemDC
KMemDC::KMemDC(HDC hDC, const RECT* pRect):KDC(){
	assert(hDC!=NULL);
	// Some initialization
	m_hDCPaint=hDC;

	// Get the rectangle to draw
	if(!pRect)
		::GetClipBox(hDC,&m_rect);
	else 
		m_rect=*pRect;

	// Create a Memory DC
	CreateCompatibleDC(hDC);
	::LPtoDP(hDC,(POINT*)(&m_rect),2);

	m_bitmap=::CreateCompatibleBitmap(hDC, m_rect.right-m_rect.left,m_rect.bottom-m_rect.top);
	m_oldBitmap=(HBITMAP)SelectObject(m_bitmap);

	SetMapMode(::GetMapMode(hDC));

	SIZE size;
	::GetWindowExtEx(hDC,&size);	
	SetWindowExt(size);
	::GetViewportExtEx(hDC,&size);
	SetViewportExt(size);

	::DPtoLP(hDC,(POINT*)(&m_rect),2);
	SetWindowOrg(m_rect.left, m_rect.top);

	// Fill background
	FillSolidRect(&m_rect, ::GetBkColor(hDC));
}