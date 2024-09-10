BOOL CWinMenu::DrawMenuItems(HDC hDC, LPRECT pRect)
{
	if ( hDC == NULL || pRect == NULL ) return FALSE;

	BOOL bFirst = m_bFirstDraw;
	m_bFirstDraw = FALSE;

	CText		text;
	long		x = pRect->left + 4;
	long		y = pRect->top + 4;
	long		w = pRect->right - pRect->left - 8;

	long		bx = x;
	long		by = y;

	// Set colors
	COLORREF rgbMenu, rgbMenuText, rgbSel, rgbSelText;

	if ( m_bSystemColors )
	{	rgbMenu = GetSysColor( COLOR_MENU );
		rgbMenuText = GetSysColor( COLOR_MENUTEXT );
		rgbSel = GetSysColor( COLOR_HIGHLIGHT );
		rgbSelText = GetSysColor( COLOR_HIGHLIGHTTEXT );
	} // end if
	else
	{	rgbMenu = m_rgbMenu;
		rgbMenuText = m_rgbMenuText;
		rgbSel = m_rgbSel;
		rgbSelText = m_rgbSelText;
	} // end else


	COLORREF	rgbLightPen = ScaleColor( rgbMenu, 100 );
	COLORREF	rgbDarkPen = ScaleColor( rgbMenu, -150 );

	COLORREF	rgbBck = rgbMenu;
	COLORREF	rgbBckLt = ScaleColor( rgbBck, 40 );
	COLORREF	rgbBckDk = ScaleColor( rgbBck, -40 );
	COLORREF	rgbSelLt = ScaleColor( rgbSel, 80 );
	COLORREF	rgbSelDk = ScaleColor( rgbSel, -120 );
	COLORREF	rgbSelTextLt = ScaleColor( rgbSelText, 80 );
	COLORREF	rgbSelTextDk = ScaleColor( rgbSelText, -150 );
	COLORREF	rgbBumpLt = ScaleColor( rgbBck, 120 );
	COLORREF	rgbBumpDk = ScaleColor( rgbBck, -120 );

	COLORREF	rgbText = rgbMenuText;
	COLORREF	rgbTextLt = ScaleColor( rgbBck, 100 );
	COLORREF	rgbTextDk = ScaleColor( rgbBck, -100 );

	if ( GetColorAvg( rgbSel ) > 128 )
	{	COLORREF swap = rgbSelTextLt;
		rgbSelTextLt = rgbSelTextDk; rgbSelTextDk = swap;
	} // end if


	// What font does the user want for menu's?
	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);			
	SystemParametersInfo( SPI_GETNONCLIENTMETRICS, sizeof( info ), &info, 0 );

	// Check for empty menu	
	if ( m_mitems.Size() == 0 )
	{
		COLORREF rgbEmptyLt = ScaleColor( rgbBck, 120 );
		COLORREF rgbEmptyDk = ScaleColor( rgbBck, -120 );

		if ( GetColorAvg( rgbBck ) < 128 ) 
		{	COLORREF swap = rgbEmptyLt;
			rgbEmptyLt = rgbEmptyDk; rgbEmptyDk = swap;
		} // end if

		RECT t;
		CopyRect( &t, pRect );

		text.SetWeight( FW_BOLD );
		text.SetFont( &info.lfMenuFont );
		text.SetFlags( DT_SINGLELINE | DT_CENTER | DT_VCENTER );

		// Make text look recessed
		OffsetRect( &t, -1, -1 );
		text.SetColor( rgbEmptyDk );
		text.DrawText( hDC, EMPTY_STR, &t );

		OffsetRect( &t, 1, 1 );
		text.SetColor( rgbEmptyLt );
		text.DrawText( hDC, EMPTY_STR, &t );

	} // end if
	
	
	// This kinda bites, but we need to know how far to offset the text
	BOOL islots = 0;
	LPMITEMINFO	pmi = NULL;
	while(	islots < 2 && ( pmi = (LPMITEMINFO)m_mitems.GetNext( pmi ) ) != NULL )
	{
		// Do we need both icon slots?
		if ( pmi->icon != NULL && pmi->b != NULL ) islots = 2;

		// Do we have one islot already?
		else if ( islots < 1 )
		{
			if ( pmi->icon != NULL ) islots = 1;
			
			else if ( pmi->b != NULL && m_hCheck == NULL && m_hUncheck == NULL )
				islots = 1;
		} // end else if

	} // end while

	
	// The icon size
	long iconsize = m_th - 4;

	// Draw each item
	pmi = NULL;
	while(	( pmi = (LPMITEMINFO)m_mitems.GetNext( pmi ) ) != NULL &&
			x < pRect->right && y < pRect->bottom )
	{
		// Set base coords
		bx = x; by = y;

		if ( *pmi->name != NULL )
		{
			POINT	pt;
			GetCursorPos( &pt );
			ScreenToClient( &pt );

			// Is this item being selected?
			BOOL bSelected = FALSE;
			RECT hl;
			hl.left = pRect->left + 3;
			hl.right = pRect->right - 4;
			hl.top = by;
			hl.bottom = by + m_th;
//			if (	pt.x > hl.left && pt.x < hl.right &&
//					pt.y > hl.top && pt.y < hl.bottom )

			// Add for toolbar
			if ( pmi->toolbar != NULL && pmi->toolbar->GetNumButtons() )
				hl.left += pmi->toolbar->GetWidth();


			if ( pmi == m_itemover )
			{
				bSelected = TRUE;
//				HPEN whitepen = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
//				HPEN dkgraypen = CreatePen( PS_SOLID, 1, RGB( 50, 50, 50 ) );
				HPEN whitepen = CreatePen( PS_SOLID, 1, rgbLightPen );
				HPEN dkgraypen = CreatePen( PS_SOLID, 1, rgbDarkPen );
				HPEN oldpen = (HPEN)SelectObject( hDC, whitepen );

				// Draw white line
				MoveToEx( hDC, hl.right, hl.top, NULL );
				LineTo( hDC, hl.right, hl.bottom  );
				LineTo( hDC, hl.left, hl.bottom  );

				// Draw dark gray line
				SelectObject( hDC, dkgraypen );
				MoveToEx( hDC, hl.right, hl.top, NULL );
				LineTo( hDC, hl.left, hl.top  );
				LineTo( hDC, hl.left, hl.bottom  );

				SelectObject( hDC, oldpen );
				DeleteObject( whitepen );
				DeleteObject( dkgraypen );

//				InflateRect( &hl, -1, -1 );
				hl.left += 1;
				hl.top += 1;

//				GradientFill( hDC, &hl, RGB( 170, 170, 190 ), RGB( 110, 110, 110 ) );
				CGrDC::VertGradientFill( hDC, &hl, rgbSelLt, rgbSelDk );
/*				HBRUSH brush = CreateSolidBrush( RGB( 120, 120, 120 ) );
				FillRect( hDC, &hl, brush );
				DeleteObject( brush );
*/

			} // end if

			// Draw toolbar
			if ( pmi->toolbar != NULL && pmi->toolbar->GetNumButtons() )
			{	pmi->toolbar->SetHeight( m_th );

				RECT tbar;
				SetRect( &tbar, bx, by, bx + pmi->toolbar->GetWidth(), 
									by + pmi->toolbar->GetHeight() );

				if ( bFirst ) pmi->toolbar->CreateToolTips( GetSafeHwnd(), &tbar );
				pmi->toolbar->SetMessageTarget( GetSafeHwnd(), WM_MENUCMD );
				pmi->toolbar->Draw( GetSafeHwnd(), hDC, &tbar );
			
				bx += pmi->toolbar->GetWidth();
			} // end if

			RECT t;

			// Calc text box
			t.left = bx + 4;
			t.left += islots * iconsize;
			t.right = pRect->right;
			t.top = by;
			t.bottom = by + m_th;

			// Draw Check
			if ( pmi->b != NULL )
			{
				RECT icon;
				SetRect( &icon, bx + 2, by + 2, bx + 2 + iconsize, by + 2 + iconsize );

				if ( *pmi->b != FALSE )
				{
					if ( bSelected && m_hHotCheck != NULL )
						CGrDC::DrawIcon( hDC, &icon, m_hHotCheck );
//						DrawIconEx( hDC, bx + 2, by + 2, m_hHotCheck, iconsize, iconsize, 0, 0, DI_NORMAL );

					else if ( m_hCheck != NULL )
						CGrDC::DrawIcon( hDC, &icon, m_hCheck );
//						DrawIconEx( hDC, bx + 2, by + 2, m_hCheck, iconsize, iconsize, 0, 0, DI_NORMAL );
				} // end if
				else 
				{
					if ( bSelected && m_hHotUncheck != NULL )
						CGrDC::DrawIcon( hDC, &icon, m_hHotUncheck );
//						DrawIconEx( hDC, bx + 2, by + 2, m_hHotUncheck, iconsize, iconsize, 0, 0, DI_NORMAL );

					else if ( m_hUncheck != NULL )
						CGrDC::DrawIcon( hDC, &icon, m_hUncheck );
//						DrawIconEx( hDC, bx + 2, by + 2, m_hUncheck, iconsize, iconsize, 0, 0, DI_NORMAL );
				} // end else
			} // end if

			// Draw icon
			if ( pmi->icon != NULL ) 
			{
				long xoff = 2;
				xoff += iconsize * ( islots - 1 ) + 1;


//				DrawIconEx( hDC, x + xoff, y + 2, pmi->icon,
//							16, 16, 0, 0, DI_NORMAL );

				DrawIconEx( hDC, bx + xoff, by + 2, pmi->icon,
							iconsize, iconsize, 0, 0, DI_NORMAL );



			} // end if

			// Setup the text object
			text.SetFlags( DT_SINGLELINE | DT_VCENTER );

			if ( bSelected )
			{
				text.SetWeight( FW_BOLD );
				text.SetFont( &info.lfMenuFont );
	
				// Make text look recessed
				OffsetRect( &t, -1, -1 );
//				text.SetColor( RGB( 0, 0, 0 ) );
				text.SetColor( rgbSelTextDk );
				text.DrawText( hDC, pmi->name, &t );

				OffsetRect( &t, 1, 1 );
				text.SetColor( rgbSelTextLt );
			} // end if
			else
			{
//				text.SetItalic( FALSE );
				text.SetWeight( FW_BOLD );
				text.SetFont( &info.lfMenuFont );
//				text.SetFont( TFONTSIZE, TFONTTYPE );
//				text.SetColor( RGB( 0, 50, 128 ) );
				text.SetColor( rgbText );
			} // end else
//			else text.SetColor( rgbText );
//			text.SetColor( RGB( 0, 50, 128 ) );
			text.DrawText( hDC, pmi->name, &t );

			// Draw sub menu indicator
			if ( pmi->submenu != NULL )
			{
				// Do we have a tick mark icon?
				if ( m_hTick != NULL )
				{
					RECT ic;
					SetRect( &ic, t.right - 18, t.top + 5, t.right - 8, t.bottom - 7 );

					// Colorize tick icon
					HICON hMono = NULL;
					if ( !pmi->submenu->IsEmpty() ) 
						hMono = CGrDC::CreateMonoChromeIcon( m_hTick, GetSysColor( COLOR_ACTIVECAPTION ) );
					else hMono = CGrDC::CreateMonoChromeIcon( m_hTick, GetSysColor( COLOR_INACTIVECAPTION ) );
//						hMono = CGrDC::CreateMonoChromeIcon( m_hTick, rgbSel );
//					else hMono = CGrDC::CreateMonoChromeIcon( m_hTick, rgbBck );

					// Draw the icon
					if ( hMono != NULL )
					{	
						CGrDC::DrawIcon( hDC, &ic, hMono );
						DestroyIcon( hMono );
					} // end if

				} // end if
				else
				{
					HPEN whitepen = CreatePen( PS_SOLID, 1, rgbLightPen );
					HPEN dkgraypen = CreatePen( PS_SOLID, 1, ScaleColor( rgbBck, -10 ) );
					HPEN blackpen = CreatePen( PS_SOLID, 1, ScaleColor( rgbBck, -40 ) );
					HPEN oldpen = (HPEN)SelectObject( hDC, whitepen );				
					HBRUSH mbrush;
					if ( !pmi->submenu->IsEmpty() ) mbrush = CreateSolidBrush( rgbBck );
					else mbrush = CreateSolidBrush( ScaleColor( rgbBck, -80 ) );
					HBRUSH oldbrush = (HBRUSH)SelectObject( hDC, mbrush );

					POINT	pts[ 3 ];

					pts[ 0 ].x = t.right - 14;
					pts[ 0 ].y = t.top + 5;
					pts[ 1 ].x = t.right - 14;
					pts[ 1 ].y = t.bottom - 7;
					pts[ 2 ].x = t.right - 8;
					pts[ 2 ].y = t.top + ( ( t.bottom - t.top ) / 2 );

					// Draw the shape
					Polygon( hDC, pts, sizeof( pts ) / sizeof( POINT ) );

					// Draw border
					MoveToEx( hDC, pts[ 0 ].x, pts[ 0 ].y, NULL );
					LineTo( hDC, pts[ 1 ].x, pts[ 1 ].y );
					SelectObject( hDC, blackpen );
					LineTo( hDC, pts[ 2 ].x, pts[ 2 ].y );
					SelectObject( hDC, dkgraypen );
					LineTo( hDC, pts[ 0 ].x, pts[ 0 ].y ); 


					// Release drawing objects
					SelectObject( hDC, oldpen );
					DeleteObject( whitepen );
					DeleteObject( dkgraypen );
					DeleteObject( blackpen );
					SelectObject( hDC, oldbrush );
					DeleteObject( mbrush );

				} // end if

			} // end if

			// Next menu item position
			y += m_th;
		} // end if

		else // separator
		{
//			HPEN whitepen = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
//			HPEN dkgraypen = CreatePen( PS_SOLID, 1, RGB( 50, 50, 50 ) );
			HPEN whitepen = CreatePen( PS_SOLID, 1, rgbBumpLt );
			HPEN dkgraypen = CreatePen( PS_SOLID, 1, rgbBumpDk );
			HPEN oldpen = (HPEN)SelectObject( hDC, whitepen );

			// Draw white line
			MoveToEx( hDC, bx + 2, by + 2, NULL );
			LineTo( hDC, ( pRect->right - pRect->left ) - 2, by + 2 );

			// Draw dark gray line
			SelectObject( hDC, dkgraypen );
			MoveToEx( hDC, bx + 2, by + 3, NULL );
			LineTo( hDC, ( pRect->right - pRect->left ) - 2, by + 3 );

			SelectObject( hDC, oldpen );
			DeleteObject( whitepen );
			DeleteObject( dkgraypen );

			y += 6;

		} // end else

	} // end while

	return TRUE;
}