void CDrawContext::SetClipRect( const CRect &rc )
{
	HRGN hrgn = CreateRectRgnIndirect( &rc );
	::SelectClipRgn( m_hdc, hrgn );
	POINT pt;
	GetWindowOrgEx( m_hdc, &pt );
	OffsetClipRgn( m_hdc, -pt.x, -pt.y );
	VAPI( ::DeleteObject( hrgn ) );
}