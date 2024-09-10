	void Button::Paint( GC& gc, const crect& paintRect )
	{
		unsigned colorBg = UiGetColor(uiBackground, uiClassButton, 0, 0x808080); //GetColor(0);
		crect cr = this->ClientRect();
		crect rect = cr;
		DrawBorder( gc, rect, ColorTone( colorBg, +20 ) );
		rect.Dec();
		DrawBorder( gc, rect, ColorTone( colorBg, -200 ) );
		rect.Dec();

		gc.SetFillColor( colorBg );
		gc.FillRect( rect );

		if ( pressed )
		{
#if USE_3D_BUTTONS
			Draw3DButtonW2( gc, rect, colorBg, false );
#endif
			rect.Dec();
			rect.Dec();
		}
		else
		{
#if USE_3D_BUTTONS
			Draw3DButtonW2( gc, rect, colorBg, true );
#endif
			rect.Dec();

			if ( InFocus() )
			{
				DrawBorder( gc, rect, /*GetColor(IC_FOCUS_MARK)*/ UiGetColor( uiFocusFrameColor, 0, 0, 0 ) );
			}

#if USE_3D_BUTTONS
			rect.Dec();
#endif
		}

		//gc.SetTextColor( /*GetColor(IsEnabled() ? IC_TEXT : IC_GRAY_TEXT)*/ UiGetColor( uiColor, 0, 0, 0 ) );
		gc.Set( GetFont() );
		cpoint tsize = text.GetTextExtents(gc);

		/*
		int l = tsize.x + (icon.ptr() ? icon->Width() + ICONX_RIGHTSPACE : 0);

		int w = rect.Width() - LEFTSPACE - RIGHTSPACE;

		if (icon.ptr()) w-=ICONX_RIGHTSPACE;

		//int x = rect.left + LEFTSPACE + (w > l ? (w - l)/2 : 0) +(pressed?2:0);
		int x = rect.left + LEFTSPACE + (w-l)/2 +(pressed?2:0);
		*/

		int l = tsize.x + ( icon.ptr() ? icon->Width() + ICONX_RIGHTSPACE : 0 );
		int w = rect.Width();
		int x = rect.left + ( w > l ? ( w - l ) / 2 : 0 ) + ( pressed ? 2 : 0 );


		if ( icon.ptr() )
		{
			gc.DrawIcon( x, rect.top + ( rect.Height() - icon->Height() ) / 2 + ( pressed ? 2 : 0 ), icon.ptr() );
			x += icon->Width() + ICONX_RIGHTSPACE;
		}

		gc.SetClipRgn( &rect );
		text.DrawItem(gc, x, rect.top + (rect.Height() - tsize.y) / 2 + (pressed ? 2 : 0), 
			UiGetColor(uiColor, uiClassButton, 0, 0), 
			UiGetColor(uiHotkeyColor, uiClassButton, 0, 0));
	}