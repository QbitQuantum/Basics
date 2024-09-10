void hm_wmp_drawtrigger_nca::_doTrigger( hm_keel_obj* pKeelObj, HDC hDC, HWND hWnd ) {
	RECT rcWnd;
	RECT rcClient;
	RECT rcC2W;
	SIZE sizeWnd;

	if ( !::GetWindowRect( hWnd, &rcWnd ) )
		return;
	sizeWnd.cx = rcWnd.right - rcWnd.left;
	sizeWnd.cy = rcWnd.bottom - rcWnd.top;

	//
	pKeelObj->doDrawAll( m_hmCanvas.GetMemDC(), hWnd );

	//
	::GetClientRect( hWnd, &rcClient );
	rcC2W = rcClient;
	::ClientToScreen( hWnd, (LPPOINT)(&rcC2W) );
	::ClientToScreen( hWnd, ((LPPOINT)(&rcC2W)) + 1 );
	rcC2W.left -= rcWnd.left;
	rcC2W.top -= rcWnd.top;
	rcC2W.right -= rcWnd.left;
	rcC2W.bottom -= rcWnd.top;
	ExcludeClipRect( hDC, rcC2W.left, rcC2W.top, rcC2W.right, rcC2W.bottom );
	::BitBlt( hDC, 0, 0, sizeWnd.cx, sizeWnd.cy, m_hmCanvas.GetMemDC(), 0, 0, SRCCOPY );


}