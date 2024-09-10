void Cycle::OnPaint()
{
	CPaintDC dc(this); 
		
	CDC memDC;
	
	RECT dialog_Rect;
	this->GetClientRect(&dialog_Rect);

	CBitmap b;

	b.CreateCompatibleBitmap( &dc, dialog_Rect.right, dialog_Rect.bottom);
	memDC.CreateCompatibleDC( &dc ) ;
	
	memDC.SelectObject( &b );

	CRect rect(0, 0, 0 + lenghtBalloon, 0 + lenghtBalloon);	

	HBRUSH hBrush = CreateSolidBrush(lRGBMas[numRGB]);
	memDC.SelectObject(hBrush);
	memDC.Ellipse(&rect);

	DeleteObject(hBrush);
	
	dc.BitBlt(0, 0, dialog_Rect.right, dialog_Rect.bottom,
           &memDC,
           0, 0,
           SRCCOPY);
}