BOOL CMovableObj::Draw(HDC hDC, LPRECT pRect)
{_STT();
	RECT rect, intersection;
	CopyRect( &rect, &m_rect );
	OffsetRect( &rect, -m_lXOff, -m_lYOff );

	// Punt if off the canvas
	if ( !IntersectRect( &intersection, pRect, &rect ) )
		return FALSE;	

	// Draw the object
	OnDraw( hDC, &rect );

	if ( m_bSelected )
	{
		// Draw the rect frame
		HBRUSH hBrush = CreateHatchBrush( HS_BDIAGONAL, RGB( 0, 0, 0 ) );
		FrameRect( hDC, &rect, hBrush );
		DeleteObject( hBrush );

		// Draw a focus rect
		DrawFocusRect( hDC, &rect );

	} // end if

	return TRUE;
}