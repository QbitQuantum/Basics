void CRemoteWnd::TrackScaler()
{
	MSG* pMsg = &AfxGetThreadState()->m_msgCur;
	CRect rcTrack( &m_rcsScalerTrack );
	CPoint point;

	ClientToScreen( &rcTrack );
	ClipCursor( &rcTrack );
	ScreenToClient( &rcTrack );
	SetCapture();

	rcTrack.DeflateRect( m_rcScalerTab.Width() / 2, 0 );

	while ( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 )
	{
		while ( ::PeekMessage( pMsg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_REMOVE ) );

		if ( ! AfxGetThread()->PumpMessage() )
		{
			AfxPostQuitMessage( 0 );
			break;
		}

		GetCursorPos( &point );
		ScreenToClient( &point );

		int nPosition = (int)( 105.0f * (float)( point.x - rcTrack.left ) / (float)rcTrack.Width() );
		if ( nPosition < 0 ) nPosition = 0;
		else if ( nPosition >= 102 ) nPosition = 101;
		else if ( nPosition >= 100 ) nPosition = 100;

		// ToDo: Settings.Live.BandwidthScaleOut
		if ( nPosition != (int)Settings.Live.BandwidthScaleIn )
		{
			Settings.Live.BandwidthScaleIn = (DWORD)nPosition;
			Invalidate();
		}
	}

	ReleaseCapture();
	ClipCursor( NULL );
	Invalidate();
}