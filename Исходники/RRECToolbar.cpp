BOOL CRRECToolbar::Create( CWnd* parent, CRect& rc )
/* ============================================================
	Function :		CRRECToolbar::Create
	Description :	Creates the toolbar control
	Access :		Public
					
	Return :		BOOL			-	"TRUE" if success
	Parameters :	CWnd* parent	-	Parent editor
					CRect& rc		-	Rectangle to place 
										toolbar in.

	Usage :			Called from the parent editor

   ============================================================*/
{

	BOOL result = FALSE;

	HINSTANCE hInstance = AfxFindResourceHandle( MAKEINTRESOURCE( TOOLBAR_CONTROL ), RT_TOOLBAR );
	if(!hInstance)
		return FALSE;

	HRSRC hRsrc = ::FindResource( hInstance, MAKEINTRESOURCE( TOOLBAR_CONTROL ), RT_TOOLBAR );
	if( !hRsrc )
		return FALSE;

	HGLOBAL hGlobal = LoadResource( hInstance, hRsrc );
	if (hGlobal == NULL)
		return FALSE;

	CToolBarData* pData = ( CToolBarData* ) LockResource( hGlobal );
	if (pData == NULL)
		return FALSE;

	ASSERT( pData->wVersion == 1 );

	TBBUTTON tb, tbSep;
	memset ( &tb, 0, sizeof( tb ) );
	memset ( &tbSep, 0, sizeof( tbSep ) );

	result = CToolBarCtrl::Create(WS_VISIBLE|WS_CHILD, rc, parent, TOOLBAR_CONTROL);

	if( result )
	{
		SetButtonStructSize( sizeof ( tb ) );

		CSize sz ( pData->wWidth, pData->wHeight );
		SetBitmapSize( sz );
		sz.cx += 4;
		sz.cy += 4;
		SetButtonSize( sz );

		// Loop through adding buttons.
		tb.fsState = TBSTATE_ENABLED;
		tb.fsStyle = TBSTYLE_BUTTON;
		tb.iString = -1;
		tb.iBitmap = 0;

		tbSep.iString = -1;
		tbSep.fsStyle = TBSTYLE_SEP;

		for( WORD w = 0; w < pData->wItemCount; w++ )
		{
			if ( pData->items()[ w ] == 0 )
				AddButtons( 1, &tbSep );
			else
			{
				tb.idCommand = pData->items()[ w ];
				AddButtons( 1, &tb );
				tb.iBitmap++;
			}
		}

		HBITMAP	hBitmap = (HBITMAP) ::LoadImage( hInstance, MAKEINTRESOURCE( TOOLBAR_CONTROL ), IMAGE_BITMAP, 0,0, LR_LOADMAP3DCOLORS );
		if( !hBitmap )
			return FALSE;

		BITMAP bm;
		memset( &bm, 0, sizeof ( bm ) );
		::GetObject( hBitmap, sizeof ( bm ), &bm );
		AddBitmap( bm.bmWidth / pData->wWidth, CBitmap::FromHandle ( hBitmap ) );

		UnlockResource( hGlobal );
		FreeResource( hGlobal );

		/////////////////////////////////////
		// Map in combo boxes
		//

		CRect rect;

		TBBUTTONINFO tbi;
		tbi.cbSize = sizeof( TBBUTTONINFO );
		tbi.cx = FONT_COMBO_WIDTH;
		tbi.dwMask = TBIF_SIZE | 0x80000000;  // By index

		SetButtonInfo( FONT_NAME_POS, &tbi );
		GetItemRect( FONT_NAME_POS, &rect );
		rect.bottom += COMBO_HEIGHT;

		// The font name combo
		if( m_font.Create( WS_CHILD | 
							WS_VSCROLL |
							WS_VISIBLE |
							CBS_AUTOHSCROLL | 
							CBS_DROPDOWN | 
							CBS_SORT | 
							CBS_HASSTRINGS, 
							rect, this, DROPDOWN_FONT ) )
		{

			m_font.SetFont( CFont::FromHandle( ( HFONT ) ::GetStockObject( ANSI_VAR_FONT ) ) );
			m_font.FillCombo();

			tbi.cx = COMBO_WIDTH;
			SetButtonInfo( FONT_SIZE_POS, &tbi );
			GetItemRect( FONT_SIZE_POS, &rect );
			rect.bottom += COMBO_HEIGHT;

			// The font size combo
			if( m_size.Create( WS_CHILD | 
								WS_VISIBLE | 
								CBS_AUTOHSCROLL | 
								CBS_DROPDOWNLIST | 
								CBS_HASSTRINGS, 
								rect, this, DROPDOWN_SIZE ) )
			{

				m_size.SetFont( CFont::FromHandle( ( HFONT ) ::GetStockObject( ANSI_VAR_FONT ) ) );
				m_size.FillCombo();
				CString color;
				CString defaultText;
				CString customText;
				color.LoadString( STRING_COLOR );
				defaultText.LoadString( STRING_DEFAULT );
				customText.LoadString( STRING_CUSTOM );

				tbi.cx = COLOR_WIDTH;
				SetButtonInfo( FONT_COLOR_POS, &tbi );
				GetItemRect( FONT_COLOR_POS, &rect );

				// The color picker
				if( m_color.Create( color,
									WS_VISIBLE|
									WS_CHILD,
									rect, this, BUTTON_COLOR ) )
				{

					m_color.SetDefaultText( defaultText );
					m_color.SetCustomText( customText );
					m_color.SetSelectionMode( CP_MODE_TEXT );
					m_color.SetBkColour( RGB( 255, 255, 255 ) );

					m_color.SetFont( CFont::FromHandle( ( HFONT ) ::GetStockObject( ANSI_VAR_FONT ) ) );
					result = TRUE;

				}

			}

		}

	}

	return result;

}