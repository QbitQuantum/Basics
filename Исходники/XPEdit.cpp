void CXPEdit::DrawEdge(void)
{
	if ( !( GetStyle() & WS_BORDER ) && !( GetExStyle() & WS_EX_CLIENTEDGE ) )
		return;

	BOOL bHaveScrollBar = FALSE;
	
	CRect rect;
	GetWindowRect ( rect );
	ScreenToClient( rect );

	CDC *pDC = GetDC ();
	int nSaveDC = pDC->SaveDC();

	COLORREF BorderColor, HotColor;
	
	BorderColor = RGB(127, 157, 185);
	HotColor = pDC->GetPixel( rect.left + 2, rect.top + 2 );
	
	if ( !( GetStyle() & ES_READONLY ) && IsWindowEnabled() ) 
	{
		HotColor = RGB( 255, 255, 255 );
		if ( m_bIsFocused )
			BorderColor = RGB(127, 157, 255);

		if ( m_bIsMouseOver )
			HotColor = RGB( 253, 216, 137 );
		else if ( (GetStyle() & WS_VSCROLL) || (GetStyle() & WS_HSCROLL) ) 
			bHaveScrollBar = TRUE;
	}

	CPen pen1, pen2, pen3;
	pen1.CreatePen( PS_SOLID, 1, BorderColor );
	pen2.CreatePen( PS_SOLID, 1, HotColor );
	pen3.CreatePen( PS_SOLID, 1, GetSysColor(COLOR_BTNFACE) );

	pDC->SelectStockObject( NULL_BRUSH );
	pDC->SelectObject( &pen1 );

	pDC->Rectangle( rect );

	
    rect.DeflateRect( 1, 1 );
	pDC->SelectObject( &pen2 );
	
	if ( !bHaveScrollBar )
		pDC->Rectangle( rect );
	else
	{
		rect.DeflateRect(0,0,1,1);

		pDC->MoveTo( rect.left, rect.bottom );
		pDC->LineTo( rect.left, rect.top );
		pDC->LineTo( rect.right, rect.top );

		if ( GetStyle() & WS_VSCROLL )
			pDC->SelectObject( &pen3 );
		pDC->LineTo( rect.right, rect.bottom );

		pDC->SelectObject( &pen2 );
		if ( GetStyle() & WS_HSCROLL )
			pDC->SelectObject( &pen3 );
		pDC->LineTo( rect.left, rect.bottom );
	}
	

	pDC->RestoreDC( nSaveDC );
	ReleaseDC ( pDC);
}