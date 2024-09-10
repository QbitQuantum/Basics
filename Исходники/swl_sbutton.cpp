	void SButton::Paint( GC& gc, const crect& paintRect )
	{
		crect cr = ClientRect();

		unsigned colorBg = UiGetColor( uiBackground, 0, 0, 0xFFFFFF );

		gc.SetFillColor( colorBg ); //CCC
		gc.FillRect( cr );

		if ( group > 0 )
		{
			DrawCE( gc, 1, ( cr.Height() - 13 ) / 2, IsSet() );
		}
		else
		{
			DrawCB( gc, 1, ( cr.Height() - 13 ) / 2, IsSet() );
		}

		gc.Set( GetFont() );
		cpoint tsize = text.GetTextExtents(gc);

		gc.SetFillColor( colorBg );
		//gc.SetTextColor( UiGetColor( uiColor, 0, 0, 0 ) );

		//gc.TextOutF( 14 + 1 + 1 + 1 , ( cr.Height() - tsize.y ) / 2, text.data() );
		UiCondList ucl;
		int color_text = UiGetColor(uiColor, uiItem, &ucl, 0x0);
		int color_hotkey = UiGetColor(uiHotkeyColor, uiItem, &ucl, 0x0);
		text.DrawItem(gc, 14 + 1 + 1 + 1, (cr.Height() - tsize.y) / 2, color_text, color_hotkey);

		if ( InFocus() )
		{
			crect rect;
			rect.left = 14 + 2;
			rect.top = ( cr.Height() - tsize.y - 2 ) / 2;
			rect.right = rect.left + tsize.x + 4;
			rect.bottom = rect.top + tsize.y + 2;
			DrawBorder( gc, rect, UiGetColor( uiFocusFrameColor, 0, 0, 0 ) ); //CCC
		}
	}