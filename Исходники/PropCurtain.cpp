void CPropCurtain::OnPaint()
{
	//擦除已画图形
	this->Invalidate(true);

	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CPropertyPage::OnPaint()
	
	/*
	//CClientDC dc(this);
	CDC* pDC=GetDC();
	CDC* pMemDC=new CDC;
	CBitmap* pMemBitmap=new CBitmap;
	CBitmap* pMemBitmapOld;
	CRect rectTemp;
	pMemDC->CreateCompatibleDC(NULL);
	pMemBitmap->CreateCompatibleBitmap(pDC,rectTemp.Width(),rectTemp.Height());
	pMemBitmapOld=pMemDC->SelectObject(pMemBitmap);
	//CBitmap* pBitmapOld=MemDC.SelectObject(&MemBitmap);
	//MemDC.FillSolidRect(0,0,rectTemp.Width(),rectTemp.Height(),RGB(255,255,255));
	CBrush brush2(RGB(0,128,255));
	pMemDC->SelectObject(brush2);
	pMemDC->Rectangle(90,66,90+width,250);
	pMemDC->Rectangle(290+(200-width),66,490,250);

	pDC->BitBlt(rectTemp.left,rectTemp.top,rectTemp.Width(),rectTemp.Height(),
		pMemDC,0,0,SRCCOPY);
	pMemDC->SelectObject(pMemBitmapOld);
	pMemBitmap->DeleteObject();
	pMemDC->DeleteDC();
	*/

	
	//窗帘上部
	CBrush brush1(RGB(128,0,0));
	dc.SelectObject(brush1);
	HRGN hRgn,hRgn1,hRgn2;
	hRgn = CreateRectRgn(50, 50, 530, 66);
	hRgn1 = CreateEllipticRgn(42, 50, 58, 66);
	hRgn2 = CreateEllipticRgn(522, 50, 538, 66);
	CombineRgn(hRgn, hRgn, hRgn1, RGN_OR);
	CombineRgn(hRgn, hRgn, hRgn2, RGN_OR);
	CRgn* rgn=CRgn::FromHandle(hRgn);
	dc.FillRgn(rgn, &brush1);
	DeleteObject(hRgn);
	DeleteObject(hRgn1);
	DeleteObject(hRgn2);

	//窗帘绘制
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	//CBrush* pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush brush2(RGB(0,128,255));
	dc.SelectObject(brush2);
	//CClientDC dc(this);
	dc.SelectObject(&pen);
	dc.Rectangle(90,66,90+width,250);
	dc.Rectangle(290+(200-width),66,490,250);
	
}