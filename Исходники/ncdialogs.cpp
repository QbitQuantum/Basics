void clSelectDriveDlgMenu::Paint( wal::GC& gc, const crect& paintRect )
{
	cfont* font = GetFont();
	gc.Set( font );
	int y = 0;

	int bgColor = UiGetColor( uiBackground, 0, 0, 0xB0B000 );

	int count = _data->Count();

	int Splitters = 0;
	int SplitterTop = 0;
	int SplitterBottom = 0;

	for ( int i = 0; i < count; i++ )
	{
		if ( _data->list[i].cmd == 0 )
		{
			gc.SetFillColor( bgColor );
			gc.FillRect( crect( 0, y, _width, y + _splitterH ) );
			crect rect( 0, y + 1, 0 + _width, y + 2 );
			gc.SetFillColor( ColorTone( bgColor, -150 ) );
			gc.FillRect( rect );
			rect.top += 1;
			rect.bottom += 1;
			gc.SetFillColor( ColorTone( bgColor, +50 ) );
			gc.FillRect( rect );
			y += _splitterH;
			Splitters++;

			if ( Splitters == 1 ) { SplitterTop = y; }

			if ( Splitters == 2 ) { SplitterBottom = y - _splitterH; }
		}
		else
		{
			UiCondList ucl;

			if ( i == _current ) { ucl.Set( uiCurrentItem, true ); }

			unsigned bg = UiGetColor( uiBackground, uiItem, &ucl, 0xFFFFFF );
			unsigned textColor = UiGetColor( uiColor, uiItem, &ucl, 0 );
			unsigned fcColor = UiGetColor( uiFcColor, uiItem, &ucl, 0xFF );
			unsigned commentColor = UiGetColor( uiCommentColor, uiItem, &ucl, 0 );

			gc.SetFillColor( bg );
			gc.FillRect( crect( 0, y, _width, y + _itemH ) );

			cicon icon;

			if ( _data->list[i].icon >= 0 )
			{
				icon.Load( _data->list[i].icon, 16, 16 );
			}
			else
			{
				icon.Load( _data->list[i].cmd, 16, 16 );
			}

			gc.DrawIcon( 0, y, &icon );
			gc.SetTextColor( textColor );
			int x = 16 + 5;

			const unicode_t* name = _data->list[i].name.data();
			const unicode_t* comment1 = _data->list[i].comment1.data();
			const unicode_t* comment2 = _data->list[i].comment2.data();

			if ( name )
			{
				gc.TextOutF( x, y, name );
				gc.SetTextColor( fcColor );
				gc.TextOutF( x, y, name, 1 );
			}

			if ( comment1 )
			{
				gc.SetTextColor( commentColor );
				gc.TextOutF( x + _nameW + 5, y, comment1 );
			}

			if ( comment2 )
			{
				gc.SetTextColor( commentColor );
				gc.TextOutF( x + _nameW + 5 + _comment1W + 30, y, comment2 );
			}

			y += _itemH;
		}
	}

	if ( _comment2W && SplitterTop && SplitterBottom )
	{
		int cx = _nameW + 5 + _comment1W + 30;
		gc.SetFillColor( ColorTone( bgColor, -150 ) );
		gc.FillRect( crect( cx, SplitterTop, cx + _splitterW, SplitterBottom ) );
	}
}