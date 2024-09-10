void CIperfView::PaintYMaps(CPaintDC &dc)
{
	CRect rect;
	GetClientRect(&rect);
	double y, ystep, k, j;

	ystep =  rect.Height() / HEIGHT;
	for(j = 1; j < 10000000000; j*=10)
	{
		for(k = 1; k < 10; k++)
		{
			y = rect.Height() - 10*log10(k*j) * ystep;
			if(y < 0) goto over;
			CPen pen(PS_SOLID, 1, ((k != 1) ? RGB(240,240,240) : RGB(120,120,120)) );
			CPen* pOldPen = dc.SelectObject(&pen);
			dc.MoveTo(CPoint( 1, (int)y));
			dc.LineTo(CPoint( (int)rect.Width() -1, (int)y));
			dc.SelectObject(pOldPen);
		}
	}
over:
	return;
}