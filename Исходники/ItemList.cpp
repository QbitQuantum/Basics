BOOL CItemList::Draw(HDC hDC, LPRECT pRect, HWND hWnd )
{
	// Reset default colors if needed
	if ( m_bAutoDefaultColors ) DefaultColors();

	// Check for no draw
	if ( m_dwNoDraw ) { m_dwNoDraw--; return TRUE; }

	RECT draw;
	CopyRect( &draw, pRect );

	// Fill in the back ground
	CGrDC::VertGradientFill( hDC, &draw, m_rgbBckTop, m_rgbBckBottom );

	// Draw side bar
	if ( m_bGroups )
	{	draw.right = draw.left + GROUPOFFSET;
		CGrDC::VertGradientFill( hDC, &draw, m_rgbBarTop, m_rgbBarBottom );
		CopyRect( &draw, pRect );
	} // end if

	// Draw the header
	m_header.Draw( hDC, &draw, m_lHScroll, m_bGroups ? GROUPOFFSET : 0 );

	// Draw line under header
	CGrDC::Line(	hDC, m_rgbHorzLines, 1,
					draw.left, draw.top + m_header.GetHeight(), 
					draw.right, draw.top + m_header.GetHeight() );


	// Offset header for groups if needed
	if ( m_bGroups ) draw.left += GROUPOFFSET;

	// Offset the rect below the header
	draw.top += m_header.GetHeight();
	if ( draw.top >= draw.bottom ) return TRUE;

	// Item rect
	RECT ir;				
	ir.left = draw.left;
	ir.top = draw.top;
	ir.right = draw.right;
	ir.bottom = draw.top;

	BOOL bCollapsed = FALSE;

	DWORD i = 0;

	if ( !m_bGroups ) i = m_dwLine;
	else while ( i < m_dwLine && i < m_dwPtr )
	{	
		if ( m_pIndex[ i ] != NULL ) 
		{	
			if ( ( m_pIndex[ i ]->flags & LIF_GROUP ) != 0 )
			{	if ( ( m_pIndex[ i ]->flags & LIF_COLLAPSED ) != 0 ) bCollapsed = TRUE;
				else bCollapsed = FALSE;
			} // end if
		} // end if
		i++;
	} // end while

	while ( i < m_dwPtr && ir.bottom < pRect->bottom )
	{
		LPLISTITEMINFO	plii = m_pIndex[ i ];

		// Skip collapsed items
		if ( bCollapsed ) 
			while ( plii != NULL && ( plii->flags & LIF_GROUP ) == 0 )
				if ( ++i < m_dwPtr ) plii = m_pIndex[ i ]; else plii = NULL;

		if ( plii != NULL )
		{
			// Calculate list item height
			ir.bottom = ir.top + plii->height;

			if ( m_bGroups && ( plii->flags & LIF_GROUP ) == 0 )
			{
				CGrDC::FillSolidRect( hDC, &ir, GetSysColor( COLOR_WINDOW ) );

			} // end if			

//			if ( ir.bottom < pRect->bottom )
			{
				// Draw tab
				if ( m_bGroups && ( plii->flags & LIF_GROUP ) != 0 )
				{
					RECT tab;
					CopyRect( &tab, &ir );
					tab.left = pRect->left; 
					tab.right = ir.left - 1;
					tab.bottom = tab.top + RW( tab );
					InflateRect( &tab, -2, -2 );

					CGrDC::Center( &tab, &ir, FALSE, TRUE ); 

					// Are we using XP themes?
//					if ( FALSE )
					if ( CXpTheme::IsWindowThemed( hWnd ) )
					{
						CXpTheme xpthm( hWnd, "TREEVIEW" );
						if ( ( plii->flags & LIF_COLLAPSED ) != 0 )
							xpthm.DrawThemeBackground( hDC, TVP_GLYPH, GLPS_CLOSED, &tab, NULL );
						else xpthm.DrawThemeBackground( hDC, TVP_GLYPH, GLPS_OPENED, &tab, NULL );

					} // end if

					else
					{
						CGrDC::FillSolidRect( hDC, &tab, m_rgbBckTop );
						CGrDC::Box3d( hDC, &tab, 1, RGB( 0, 0, 0 ), RGB( 0, 0, 0 ) );

						long mh = tab.top + ( RH( tab ) / 2 );
						long mw = tab.left + ( RW( tab ) / 2 );

						CGrDC::Line(	hDC, RGB( 0, 0, 0 ), 1,
										tab.left + 2, mh, tab.right - 2, mh );
						if ( ( plii->flags & LIF_COLLAPSED ) != 0 )
							CGrDC::Line(	hDC, RGB( 0, 0, 0 ), 1,
											mw, tab.top + 2, mw, tab.bottom - 2 );

					} // end else

				} // end if

				// Draw this list item
				DrawItem( i, hDC, &ir );

				if ( m_bHorzLines )
				{
					CGrDC::Line(	hDC, m_rgbHorzLines, 1,
									ir.left, ir.top, ir.right, ir.top );

					if ( m_bGroups && ( plii->flags & LIF_GROUP ) != 0 &&
						 ( plii->flags & LIF_COLLAPSED ) != 0 )
					{	
						HPEN hPen = CreatePen( PS_SOLID, 1, m_rgbSelTop );
						HPEN hOldPen = (HPEN)::SelectObject( hDC, hPen );
						COLORREF oldcolor = SetBkColor( hDC, m_rgbBckTop );

						MoveToEx( hDC, ir.left, ir.bottom - 1, NULL );
						LineTo( hDC, ir.right, ir.bottom - 1 );

						::SelectObject( hDC, hOldPen );
						::DeleteObject( hPen );
						hPen = CreatePen( PS_SOLID, 1, RGB( 220, 220, 220 ) );
						hOldPen = (HPEN)::SelectObject( hDC, hPen );
						MoveToEx( hDC, ir.left, ir.bottom - 2, NULL );
						LineTo( hDC, ir.right, ir.bottom - 2 );

						
						// Release drawing objects
						SetBkColor( hDC, oldcolor );
						::SelectObject( hDC, hOldPen );
						::DeleteObject( hPen );

					} // end else


//					CGrDC::Box3d( hDC, &ir, 1, m_rgbHorzLines, m_rgbHorzLines );

				} // end if

				if ( m_bVertLines && ( plii->flags & LIF_GROUP ) == 0 )
				{
					long x = ir.left;

					CGrDC::Line(	hDC, m_rgbHorzLines, 1,
									x, ir.top, x, ir.bottom );

					x--;
					LPHEADERITEMINFO phii = NULL;
					while( ( phii = GetHeader().GetNext( phii ) ) != NULL &&
							GetHeader().GetNext( phii ) != NULL )
					{
						// Add width
						x += phii->width;

						// Draw vertical line
						CGrDC::Line(	hDC, m_rgbHorzLines, 1,
										x, ir.top, x, ir.bottom );

					} // end while

					CGrDC::Line(	hDC, m_rgbHorzLines, 1,
									ir.right - 1, ir.top, 
									ir.right - 1, ir.bottom );


				} // end if

			} // end if

			// Next item position
			ir.top = ir.bottom;

			// Are we collapsing?
			if ( ( plii->flags & LIF_GROUP ) != 0 )
			{	if ( ( plii->flags & LIF_COLLAPSED ) != 0 ) bCollapsed = TRUE;
				else bCollapsed = FALSE;
			} // end if

		} // end if

		// Next item
		i++;

	} // end while

	// Draw last horz line
	if ( m_bHorzLines )
		CGrDC::Line(	hDC, m_rgbHorzLines, 1,
						ir.left, ir.bottom, ir.right, ir.bottom );

/*	if ( m_bVertLines )
	{
		long x = draw.left;

		CGrDC::Line(	hDC, m_rgbHorzLines, 1,
						x, draw.top, x, ir.bottom );

		x--;
		LPHEADERITEMINFO phii = NULL;
		while( ( phii = GetHeader().GetNext( phii ) ) != NULL )
		{
			// Add width
			x += phii->width;

			// Draw vertical line
			CGrDC::Line(	hDC, m_rgbHorzLines, 1,
							x, draw.top, x, ir.bottom );

		} // end while
	} // end if
*/
	
	return TRUE;
}