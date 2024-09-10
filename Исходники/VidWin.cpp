void Vid::SetMode( int ModeValue ) {
	if ( BackBuffer ) {
		Shutdown();
	}

	WindowWidth = ModeList[ModeValue].Width;
	WindowHeight = ModeList[ModeValue].Height;

	BufferHeight = WindowHeight;
	BufferWidth = WindowWidth;

	if ( ModeList[ModeValue].Type == ModeState::WINDOWED ) {
		SetWindowedMode( ModeValue );
	} else {
		SetFullscrenMode( ModeValue );
	}

	ShowWindow( MainWindow, SW_SHOWDEFAULT );

	HDC DeviceContext = GetDC( MainWindow );
	PatBlt( DeviceContext, 0, 0, BufferWidth, BufferHeight, BLACKNESS );
	ReleaseDC( MainWindow, DeviceContext );

	// define our bitmap info
	BitMapInfo.bmiHeader.biSize = sizeof( BitMapInfo.bmiHeader );
	BitMapInfo.bmiHeader.biWidth = BufferWidth;
	BitMapInfo.bmiHeader.biHeight = -BufferHeight;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 8 * BytesPerPixel;
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	BackBuffer = FrameBuffer( BufferWidth, BufferHeight, BytesPerPixel );
}