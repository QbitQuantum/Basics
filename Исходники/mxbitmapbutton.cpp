void mxBitmapButton::redraw()
{
	HWND wnd = (HWND)getHandle();
	if ( !wnd )
		return;

	if ( !m_bmImage.valid )
		return;

	RECT rc;
	GetClientRect( wnd, &rc );
	
	HDC dc = GetDC( wnd );

	DrawBitmapToDC( dc, 0, 0, w(), h(), m_bmImage );

	ReleaseDC( wnd, dc );

	ValidateRect( wnd, &rc );
}