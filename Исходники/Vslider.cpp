void CVslider::DrawH()
{
	CDC *pdc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pdc);
	CBitmap map,*old;
	CRect rect;
	GetClientRect(&rect);
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	old=dc.SelectObject(&map);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,SRCCOPY);
	int center=(rect.right-4)/2;
	dc.FillSolidRect(center,0,4,rect.bottom,RGB(239,248,255));
	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(140,206,238));
	oldbrush=dc.SelectObject(&brush);
	dc.Ellipse(0,hx,rect.right,14+hx);
	pdc->BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
	//pdc->Rectangle(0,hx,rect.right,8+hx);
	dc.SelectObject(old);
	dc.DeleteDC();
	this->ReleaseDC(pdc);
}