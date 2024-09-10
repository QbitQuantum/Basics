void CDlgTextSymbolEdit::ShowSymbol(void)
{
	Display::IDisplayPtr pSDisplay( new Display::IDisplay());
	CClientDC dc(this);

	CRect rc;
	GetDlgItem(IDC_STATIC_PREVIEW)->GetClientRect(&rc);
	long bmpWidth = rc.Width()*0.8;
	long bmpHeight = rc.Height()*0.8;
	//设置内存CDC
	CDC MemDC;
	//创建相容的bitmap和dc
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc , bmpWidth , bmpHeight );
	MemDC.CreateCompatibleDC(&dc);
	CBitmap *  oldbitmap = (CBitmap*)MemDC.SelectObject(&bitmap);
	pSDisplay->SetDC( (long)MemDC.GetSafeHdc() , bmpWidth , bmpHeight );

	DIS_RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = bmpWidth;
	rect.bottom= bmpHeight;

	rc.top = rc.left = 0;
	rc.right = bmpWidth;
	rc.bottom = bmpHeight;

	MemDC.FillSolidRect( &rc , RGB(255,255,255) );
	
	CPen pen( PS_DOT , 1 , RGB( 0 , 0 , 0 ) );
	CPen *oldpen = (CPen*)MemDC.SelectObject(&pen);
	POINT po;
	po.x = bmpWidth / 2;
	po.y = 0;

	MemDC.MoveTo(po);
	po.x = bmpWidth / 2;
	po.y = bmpHeight;
	MemDC.LineTo(po);
	po.x = 0;
	po.y = bmpHeight/2;

	MemDC.MoveTo(po);
	po.x = bmpWidth;
	po.y = bmpHeight/2;
	MemDC.LineTo(po);
	MemDC.SelectObject(oldpen);
	
	pSDisplay->DrawLegend( m_pCopySymbol.get() , &rect , 1 );

	MemDC.SelectObject(oldbitmap);
	MemDC.DeleteDC();

	HBITMAP bp = m_picture.SetBitmap((HBITMAP)bitmap.Detach());
	DeleteObject(bp);

}