void CMultiSelTreeCtrl::SetItemFocus(HTREEITEM item) 
{
    if( item == m_LastMouseOver )
        return;

    if( m_LastMouseOver != NULL )
	{
		CRect rect;
		GetItemRect( m_LastMouseOver, &rect, TRUE );
		rect.DeflateRect(0,1,0,1);
	
		CDC *pDC= GetDC();
		CBrush brush;
		if( IsSelected( m_LastMouseOver ) )
		{
			if( GetTextColor() != -1 )
				brush.CreateSolidBrush( GetTextColor() );
			else
				brush.CreateSolidBrush( GetSysColor( COLOR_WINDOWTEXT ) );
		}
		else
			brush.CreateSolidBrush( GetSysColor( COLOR_WINDOW ) );
		pDC->FrameRect( &rect, &brush );

		ReleaseDC( pDC );
	}
    	
    m_LastMouseOver= item;

    if( m_LastMouseOver != NULL )
    {
		CRect rect;
		GetItemRect( item, &rect, TRUE );
		rect.DeflateRect(0,1,0,1);

		CDC *pDC= GetDC();
		pDC->DrawFocusRect(&rect);

		ReleaseDC( pDC );
	}
		
}