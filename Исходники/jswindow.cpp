bool TrackMouseLeave( HWND hWnd ) {

	TRACKMOUSEEVENT trackMouseEvent;
	trackMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
	trackMouseEvent.dwFlags = TME_LEAVE;
	trackMouseEvent.hwndTrack = hWnd;
	return TrackMouseEvent(&trackMouseEvent) != 0;
//	JL_ASSERT( status != 0, "Unable to TrackMouseEvent.(%d)", GetLastError() );
}