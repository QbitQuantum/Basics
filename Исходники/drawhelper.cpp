//-----------------------------------------------------------------------------
// Purpose: Finish up
//-----------------------------------------------------------------------------
CDrawHelper::~CDrawHelper( void )
{
	SelectClipRgn( m_dcMemory, NULL );

	while ( m_ClipRects.Size() > 0 )
	{
		StopClipping();
	}

	BitBlt( m_dcReal, m_x, m_y, m_w, m_h, m_dcMemory, 0, 0, SRCCOPY );

	SetBkColor( m_dcMemory, m_clrOld );

	SelectObject( m_dcMemory, m_bmOld );
	DeleteObject( m_bmMemory );

	DeleteObject( m_dcMemory );

	ReleaseDC( m_hWnd, m_dcReal );

	ValidateRect( m_hWnd, &m_rcClient );
}