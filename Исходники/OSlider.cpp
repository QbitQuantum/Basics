void COSlider::DrawH()
{
	CRect rect;
	GetClientRect(&rect);
	if(!issize)
		max_size=rect.bottom;
	CDC *pdc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pdc);
	CBitmap map,*old;
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	old=dc.SelectObject(&map);
	CPen pen,*oldpen;
	pen.CreatePen(BS_SOLID,1,RGB(255,255,255));
	oldpen=dc.SelectObject(&pen);

	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(239,248,255));
	oldbrush=dc.SelectObject(&brush);
	dc.Rectangle(0,0,rect.right,rect.bottom);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();

	brush.CreateSolidBrush(RGB(140,206,238));
	oldbrush=dc.SelectObject(&brush);
	dc.Rectangle(0,hx,20,max_size+hx);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
	pdc->BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	pen.DeleteObject();
	dc.DeleteDC();
	this->ReleaseDC(pdc);
}