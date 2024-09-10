void CBlist::OnPaint()
{
	CPaintDC pdc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CBitmap map,*oldmap;
	CDC dc;
	dc.CreateCompatibleDC(&pdc);
	map.CreateCompatibleBitmap(&pdc,rect.right,rect.bottom);
	oldmap=dc.SelectObject(&map);
	pdc.SetStretchBltMode(SBM_ENABLE_ARROWS);
	dc.SetStretchBltMode(SBM_ENABLE_ARROWS);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,SRCCOPY);
	int cx=0;
	cx=(rect.bottom-5)/2;
	dc.FillSolidRect(0,cx,rect.right,cx,RGB(223,233,222));
	CRect hrect;
	hrect.SetRect(x,2,x+5,14);
	dc.FillSolidRect(hrect,RGB(255,rand()%255,255));
	pdc.BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.DeleteDC();
	pdc.SelectObject(oldmap);
}