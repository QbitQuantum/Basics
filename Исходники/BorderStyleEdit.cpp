void CBorderStyleEdit::DrawEditFrame( CDC* pDC )
{	
	CRect rcItem;
	GetClientRect( &rcItem );

	if( m_bNowEditing )
		pDC->SetTextColor( m_dwActiveTextColor );
	else
		pDC->SetTextColor( m_dwTextColor );

	pDC->SetBkColor( m_dwBgColor );

	if( m_bShowBorder )
	{
		DWORD dwBorderColor = m_dwBorderColor;
		if( m_bWarning )
		{
			dwBorderColor = (m_bBlink == TRUE ? RGB(255, 0, 0) : m_dwBorderColor);
		}

		rcItem.InflateRect( 1, 1, 1, 1 );
		CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject( NULL_BRUSH );
		CPen BorderPen;
		BorderPen.CreatePen( PS_SOLID, m_nBorderWidth, dwBorderColor );
		CPen* pOldPen = pDC->SelectObject( &BorderPen );

		//pDC->Rectangle( rcItem );

		pDC->SelectObject( pOldPen );
		pDC->SelectObject( pOldBrush );
	}
}