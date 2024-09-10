//********************************************************************
void CHeaderView::OnPaint(HDC hDC) 
{
	
	
	CPaintDC	dc(GetSafeHwnd()); // device context for painting
	CGDI		MemDC;
	CBitmap		m_BitmapMemDC;
	CRect		rcClient;
	CRect		rcWin;
	CBrush		m_brush;
	//******************************************
	GetWindowRect( &rcWin);
	GetClientRect( &rcClient );
	MemDC.CreateCompatibleDC(dc.m_hDC);
	m_BitmapMemDC.CreateCompatibleBitmap(dc.m_hDC,
				  rcClient.Width(),rcClient.Height());	

	CBitmap m_bitmapOld=MemDC.SelectObject(&m_BitmapMemDC);
	m_brush.CreateSysColorBrush(COLOR_3DFACE);
	MemDC.FillRect((LPCRECT)rcClient,&m_brush); //evita el horrible color negro
	CGradient M(CSize(rcClient.Width(),rcClient.Height()));	
	M.PrepareVertical(&MemDC);
	M.Draw(&MemDC,rcClient.left,rcClient.top,0,0,rcClient.Width(),rcClient.Height(),SRCCOPY);

	ScreenToClient(rcWin);
	BiselaBoton(rcWin,&MemDC);
	int iNumItems=GetItemCount();
	int sizeOfBuffer = 256 ;
	LPSTR  lpBuffer= new TCHAR[sizeOfBuffer];
	
		
	for (int i =0; i < iNumItems; i++)
	{	
		HDITEM hdi;
		memset(lpBuffer,0x00,sizeOfBuffer);
		memset(&hdi,0x00,sizeof(HDITEM/*struct _HD_ITEMW*/));
		GetItemFull(i,&hdi,lpBuffer,sizeOfBuffer);
		DrawItem(hdi,&MemDC);
		
	}
	delete[] lpBuffer;
	MemDC.Draw3dRect((LPCRECT)rcClient,CDrawLayer::GetRGBSemiShadow(),CDrawLayer::GetRGBSemiShadow());
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),MemDC.m_hDC,
		      rcClient.left,rcClient.top,SRCCOPY);
	MemDC.SelectObject(&m_bitmapOld);
	m_BitmapMemDC.DeleteObject();
	MemDC.DeleteDC();

}