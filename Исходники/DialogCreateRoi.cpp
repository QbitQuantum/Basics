HBITMAP CDialogCreateRoi::CoverBitmap( Display::ISymbolPtr pSymbol )
{
	Display::IDisplay SimpleDisplay;
	CDC * dc=GetDC();
	CDC MemDC;//创建相容的bitmap和dc
	HBITMAP hbitmap = CreateCompatibleBitmap( dc->GetSafeHdc(), m_cx, m_cy );
	HBITMAP hBitmapTemp;
	MemDC.CreateCompatibleDC( dc );
	hBitmapTemp=( HBITMAP )SelectObject( MemDC, hbitmap );

	RECT rc1;
	rc1.top = rc1.left = 0;
	rc1.right = m_cx;
	rc1.bottom = m_cy;
	CBrush brush( RGB(255,254,253) );
	MemDC.FillRect( &rc1, &brush );

	SimpleDisplay.SetBgColor( RGB(255,255,255) );
	SimpleDisplay.SetDC( (long)MemDC.GetSafeHdc(), rc1.right, rc1.bottom );
	DIS_RECT rc;
	rc.left = rc.top = 0;
	rc.right = m_cx;
	rc.bottom= m_cy;
	HRGN hr = 0;
	SimpleDisplay.DrawLegend( pSymbol.get(), &rc, 0 );
	hbitmap=(HBITMAP)SelectObject(MemDC.m_hDC,hBitmapTemp);
	MemDC.DeleteDC();
	return hbitmap;
}