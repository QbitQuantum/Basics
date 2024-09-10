HRESULT BKMainFrame::initDirectDraw()
{
	if ( display ) { delete display; display = NULL; }
	display = new CDisplay();

	if ( isFullScreenMode() ) {
		CDC* dc = CWnd::GetDesktopWindow()->GetDC();
		int bpp = dc->GetDeviceCaps( BITSPIXEL );
		CWnd::GetDesktopWindow()->ReleaseDC( dc );
		if ( display->CreateFullScreenDisplay( this, 512, 256, bpp ) != S_OK ) {
			AfxMessageBox( "Failed initializing DirectDraw." );
			return -1;
		}
		ModifyStyle( WS_OVERLAPPEDWINDOW, 0 );
		SetMenu( NULL );

		fullWindowWidth  = display->getSurfaceDesc()->dwWidth;
		fullWindowHeight = display->getSurfaceDesc()->dwHeight;
	} else {
		if ( display->CreateWindowedDisplay( this, bk_width, bk_height ) != S_OK ) {
			AfxMessageBox( "Failed initializing DirectDraw." );
			return -1;
		}
		ModifyStyle( 0, WS_OVERLAPPEDWINDOW );
		SetMenu( CMenu::FromHandle( ::LoadMenu( NULL, MAKEINTRESOURCE( IDR_MAINFRAME ) ) ) );
	}
	::SystemParametersInfo( SPI_GETWORKAREA, 0, &screenRect, 0 );
	updateBounds();
	ShowCursor( !fullScreenMode );

	bytePerPixel = display->getSurfaceDesc()->ddpfPixelFormat.dwRGBBitCount >> 3;
	if ( bytePerPixel > 1 ) {
		DWORD rMask = display->getSurfaceDesc()->ddpfPixelFormat.dwRBitMask;
		DWORD gMask = display->getSurfaceDesc()->ddpfPixelFormat.dwGBitMask;
		DWORD bMask = display->getSurfaceDesc()->ddpfPixelFormat.dwBBitMask;
		DWORD mask;
		rBits = 0;
		gBits = 0;
		bBits = 0;
		rZero = 0;
		gZero = 0;
		bZero = 0;
		mask = rMask;
		while ( (mask & 0x1) == 0 ) {
			mask = mask >> 1;
			rZero++;
		}
		while ( mask & 0x1 ) {
			mask = mask >> 1;
			rBits++;
		}
		mask = gMask;
		while ( (mask & 0x1) == 0 ) {
			mask = mask >> 1;
			gZero++;
		}
		while ( mask & 0x1 ) {
			mask = mask >> 1;
			gBits++;
		}
		mask = bMask;
		while ( (mask & 0x1) == 0 ) {
			mask = mask >> 1;
			bZero++;
		}
		while ( mask & 0x1 ) {
			mask = mask >> 1;
			bBits++;
		}
		rBits = 8 - rBits;
		gBits = 8 - gBits;
		bBits = 8 - bBits;
	}