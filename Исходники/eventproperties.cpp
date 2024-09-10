void CBaseEventPropertiesDialog::DrawSpline( HDC hdc, HWND placeholder, CChoreoEvent *e )
{
	RECT rcOut;

	GetSplineRect( placeholder, rcOut );

	HBRUSH bg = CreateSolidBrush( GetSysColor( COLOR_BTNFACE ) );
	FillRect( hdc, &rcOut, bg );
	DeleteObject( bg );

	if ( !e )
		return;

	// Draw spline
	float range = ( float )( rcOut.right - rcOut.left );
	if ( range <= 1.0f )
		return;

	float height = ( float )( rcOut.bottom - rcOut.top );

	HPEN pen = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_BTNTEXT ) );
	HPEN oldPen = (HPEN)SelectObject( hdc, pen );

	float duration = e->GetDuration();
	float starttime = e->GetStartTime();

	for ( int i = 0; i < (int)range; i++ )
	{
		float frac = ( float )i / ( range - 1 );

		float scale = 1.0f - e->GetIntensity( starttime + frac * duration );

		int h = ( int ) ( scale * ( height - 1 ) );

		if ( i == 0 )
		{
			MoveToEx( hdc, rcOut.left + i, rcOut.top + h, NULL );
		}
		else
		{
			LineTo( hdc, rcOut.left + i, rcOut.top + h );
		}
	}

	SelectObject( hdc, oldPen );

	HBRUSH frame = CreateSolidBrush( GetSysColor( COLOR_BTNSHADOW ) );
	InflateRect( &rcOut, 1, 1 );
	FrameRect( hdc, &rcOut, frame );
	DeleteObject( frame );
}