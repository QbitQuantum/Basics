void mxExpressionSlider::DrawThumb( int barnum, HDC& dc )
{
	RECT rcThumb;

	GetThumbRect( barnum, rcThumb );

	// Draw it


	HPEN oldPen;

	HPEN shadow;
	HBRUSH face;
	HPEN hilight;

	shadow = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DDKSHADOW ) );
	hilight = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DHIGHLIGHT ) );
	
	switch ( barnum )
	{
	default:
	case MAGNITUDE_BAR:

		if ( m_flCurrent[ barnum ] != m_flMin[ barnum ] )
		{
			// float frac = ( m_flCurrent[ barnum ] - m_flMin[ barnum ] ) / (  m_flMax[ barnum ] - m_flMin[ barnum ] );
			float frac;
			if (m_flCurrent[ barnum ] < 0)
			{
				frac = m_flCurrent[ barnum ] / m_flMin[ barnum ];
			}
			else
			{
				frac = m_flCurrent[ barnum ] / m_flMax[ barnum ];
			}
			frac = min( 1.0f, frac );
			frac = max( 0.0f, frac );

			COLORREF clr = GetSysColor( COLOR_3DFACE );
			int r, g, b;
			r = GetRValue( clr );
			g = GetRValue( clr );
			b = GetRValue( clr );

			// boost colors
			r = (int)( (1-frac) * b );
			b = min( 255, (int)(r + ( 255 - r ) * frac ) );
			g = (int)( (1-frac) * g );

			face = CreateSolidBrush( RGB( r, g, b ) );
		}
		else
		{
			face = CreateSolidBrush( GetSysColor( COLOR_3DFACE ) );
		}
		break;
	case BALANCE_BAR:
		{
			float frac = ( m_flCurrent[ barnum ] - m_flMin[ barnum ] ) / (  m_flMax[ barnum ] - m_flMin[ barnum ] );
			frac = min( 1.0f, frac );
			frac = max( 0.0f, frac );

			COLORREF clr = GetSysColor( COLOR_3DFACE );
			int r, g, b;
			r = GetRValue( clr );
			g = GetRValue( clr );
			b = GetRValue( clr );

			// boost colors toward red if we are not at 0.5
			float boost = 2.0 * ( fabs( frac - 0.5f ) );

			r = r + ( 255 - r ) * boost;
			g = ( 1 - boost ) * g;
			b = ( 1 - boost ) * b;

			face = CreateSolidBrush( RGB( r, g, b ) );
		}
		break;
	}

	//rcThumb.left += 1;
	//rcThumb.right -= 1;
	//rcThumb.top += 1;
	//rcThumb.bottom -= 1;

	//FillRect( dc, &rcThumb, face );
	POINT region[3];
	int cPoints = 3;

	InflateRect( &rcThumb, -2, 0 );

//	int height = rcThumb.bottom - rcThumb.top;
//	int offset = height / 2 + 1;
	int offset = 2;

	switch ( barnum )
	{
	case MAGNITUDE_BAR:
	default:
		{
			region[ 0 ].x = rcThumb.left;
			region[ 0 ].y = rcThumb.top;
			
			region[ 1 ].x = rcThumb.right;
			region[ 1 ].y = rcThumb.top;
			
			region[ 2 ].x = ( rcThumb.left + rcThumb.right ) / 2;
			region[ 2 ].y = rcThumb.bottom - offset;
		}
		break;
	case BALANCE_BAR:
		{
			region[ 0 ].x = ( rcThumb.left + rcThumb.right ) / 2;
			region[ 0 ].y = rcThumb.top + offset;

			region[ 1 ].x = rcThumb.left;
			region[ 1 ].y = rcThumb.bottom;

			region[ 2 ].x = rcThumb.right;
			region[ 2 ].y = rcThumb.bottom;

		}
		break;
	}

	HRGN rgn = CreatePolygonRgn( region, cPoints, ALTERNATE );

	int oldPF = SetPolyFillMode( dc, ALTERNATE );
	FillRgn( dc, rgn, face );
	SetPolyFillMode( dc, oldPF );

	DeleteObject( rgn );

	oldPen = (HPEN)SelectObject( dc, hilight );

	MoveToEx( dc, region[0].x, region[0].y, NULL );
	LineTo( dc, region[1].x, region[1].y );
	SelectObject( dc, shadow );
	LineTo( dc, region[2].x, region[2].y );
	SelectObject( dc, hilight );
	LineTo( dc, region[0].x, region[0].y );

	SelectObject( dc, oldPen );

	DeleteObject( face );
	DeleteObject( shadow );
	DeleteObject( hilight );
}