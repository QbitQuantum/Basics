	void PopupMenu::DrawItem( GC& gc, int n )
	{
		if ( n < 0 || n >= list.count() ) { return; }

		UiCondList ucl;

		if ( n == selected ) { ucl.Set( uiCurrentItem, true ); }

		int color_text = UiGetColor( uiColor, uiItem, &ucl, 0x0 );
		int color_hotkey = UiGetColor( uiHotkeyColor, uiItem, &ucl, 0x0 );
		int color_bg = UiGetColor( uiBackground, uiItem, &ucl, 0xFFFFFF );
		int color_left = UiGetColor( uiBackground, 0, 0, 0xFFFFFF );

		crect r = list[n].rect;
		int height = r.Height();
		r.right = MENU_LEFT_BLOCK;
		gc.SetFillColor( n == selected ? color_bg : color_left );
		gc.FillRect( r );
		r = list[n].rect;
		r.left = MENU_LEFT_BLOCK ;
		gc.SetFillColor( color_bg );
		gc.FillRect( r );

		unsigned colorLine = UiGetColor( uiLineColor, uiItem, &ucl, 0 );
		gc.SetLine( colorLine );
		gc.MoveTo( r.left, r.top );
		gc.LineTo( r.left, r.bottom );

		if ( IsSplit( n ) )
		{
			gc.SetLine( colorLine );
			int y = r.top + ( r.Height() - 1 ) / 2;
			gc.MoveTo( 1, y );
			gc.LineTo( r.right, y );
		}
		else
		{
			gc.Set( GetFont() );
			MenuTextInfo& lText = ( list[n].data->leftText );
			//unicode_t* lText = list[n].data->leftText.data();
			unicode_t* rText = list[n].data->rightText.data();

			//if ( lText ) { gc.TextOutF( MENU_LEFT_BLOCK + MENU_TEXT_OFFSET, r.top + ( height - fontHeight ) / 2, lText ); }
			if ( !lText.isEmpty() )
			{
				lText.DrawItem( gc, MENU_LEFT_BLOCK + MENU_TEXT_OFFSET, r.top + ( height - fontHeight ) / 2, color_text, color_hotkey );
			}

			if ( rText )
			{
				gc.SetTextColor( color_text );
				gc.TextOutF( MENU_LEFT_BLOCK + MENU_TEXT_OFFSET + leftWidth + fontHeight, r.top + ( height - fontHeight ) / 2, rText );
			}

			if ( IsSub( n ) )
			{
				int y = r.top + ( height - RightMenuPointer[0] ) / 2;
				DrawPixelList( gc, RightMenuPointer, r.right - 10 , y, UiGetColor( uiPointerColor, uiItem, &ucl, 0 ) );
			}

			if ( IsCmd( n ) )
			{
				int y = r.top + ( height - MENU_ICON_SIZE ) / 2;
				int x =  ( MENU_LEFT_BLOCK - MENU_ICON_SIZE ) / 2;
				gc.DrawIcon( x, y, GetCmdIcon( list[n].data->id ) );
			}

		}
	}