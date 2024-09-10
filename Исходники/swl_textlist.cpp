	void TextList::DrawItem( GC& gc, int n, crect rect )
	{
		if ( n >= 0 && n < list.count() )
		{
			UiCondList ucl;

			if ( ( n % 2 ) == 0 ) { ucl.Set( uiOdd, true ); }

			if ( n == this->GetCurrent() ) { ucl.Set( uiCurrentItem, true ); }

			unsigned bg = UiGetColor( uiBackground, uiItem, &ucl, 0xFFFFFF );
			unsigned textColor = UiGetColor( uiColor, uiItem, &ucl, 0 );
			unsigned frameColor = UiGetColor( uiFrameColor, uiItem, &ucl, 0 );;

			bool frame = ( n == this->GetCurrent() );

			gc.SetFillColor( bg );
			gc.FillRect( rect );
			unicode_t* txt = list[n].str.data();

			if ( txt )
			{
				gc.Set( GetFont() );
				gc.SetTextColor( textColor );
				gc.SetFillColor( bg );
				gc.TextOutF( rect.left, rect.top + ( GetItemHeight() - fontH ) / 2, txt );
			}

			if ( frame )
			{
				DrawBorder( gc, rect, frameColor );
			}

		}
		else
		{
			gc.SetFillColor( UiGetColor( uiBackground, uiItem, 0, 0xFFFFFF ) );
			gc.FillRect( rect ); //CCC
		}
	}