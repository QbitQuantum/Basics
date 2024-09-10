	/*
	types:
	   1 -left 2 - right 3 - horisontal slider
	   4 - up 5 - down   6 - vert. slider
	*/
	void SBCDrawButton( GC& gc, crect rect, int type, unsigned bg, bool pressed )
	{
		static unsigned short up[] = {6, 0x10, 0x38, 0x7c, 0xee, 0x1c7, 0x82};
		static unsigned short down[] = {6, 0x82, 0x1c7, 0xee, 0x7c, 0x38, 0x10,};
		static unsigned short left[] = {9, 0x10, 0x38, 0x1c, 0x0e, 0x07, 0x0e, 0x1c, 0x38, 0x10};
		static unsigned short right[] = {9, 0x02, 0x07, 0x0E, 0x1c, 0x38, 0x1c, 0x0e, 0x07, 0x02};
		DrawBorder( gc, rect, ColorTone( bg, -100 ) );
		rect.Dec();
		Draw3DButtonW1( gc, rect, bg, !pressed );
		//rect.Dec();
		rect.Dec();
		gc.SetFillColor( bg );
		gc.FillRect( rect );
		int xPlus = 0;
		int yPlus = 0;

		if ( pressed )
		{
			// xPlus = 1;
			yPlus = 1;
		}

		unsigned color = ColorTone( bg, -200 );

		switch ( type )
		{
			case 1:
				DrawPixelList( gc, left, rect.left + ( rect.Width() - 6 ) / 2 + xPlus, rect.top + ( rect.Height() - 9 ) / 2 + yPlus, color );
				break;

			case 2:
				DrawPixelList( gc, right, rect.left + ( rect.Width() - 6 ) / 2 + xPlus, rect.top + ( rect.Height() - 9 ) / 2 + yPlus, color );
				break;

			case 4:
				DrawPixelList( gc, up, rect.left + ( rect.Width() - 9 ) / 2 + xPlus, rect.top + ( rect.Height() - 6 ) / 2 + yPlus, color );
				break;

			case 5:
				DrawPixelList( gc, down, rect.left + ( rect.Width() - 9 ) / 2 + xPlus, rect.top + ( rect.Height() - 6 ) / 2 + yPlus, color );
				break;
		};
	}