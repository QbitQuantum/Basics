bool VBA::preInitialize()
{
	switch( cartridgeType )
	{
	case IMAGE_GBA:
		sizeX = 240;
		sizeY = 160;
		break;
	}

	switch( videoOption )
	{
	case VIDEO_1X:
		surfaceSizeX = sizeX;
		surfaceSizeY = sizeY;
		break;
	case VIDEO_2X:
		surfaceSizeX = sizeX * 2;
		surfaceSizeY = sizeY * 2;
		break;
	case VIDEO_3X:
		surfaceSizeX = sizeX * 3;
		surfaceSizeY = sizeY * 3;
		break;
	case VIDEO_4X:
		surfaceSizeX = sizeX * 4;
		surfaceSizeY = sizeY * 4;
		break;
	case VIDEO_320x240:
	case VIDEO_640x480:
	case VIDEO_800x600:
	case VIDEO_1024x768:
	case VIDEO_1280x1024:
	case VIDEO_OTHER:
		float scaleX = (float)fsWidth / sizeX;
		float scaleY = (float)fsHeight / sizeY;
		float min = ( scaleX < scaleY ) ? scaleX : scaleY;
		if( fullScreenStretch ) {
			surfaceSizeX = fsWidth;
			surfaceSizeY = fsHeight;
		} else {
			surfaceSizeX = (int)( sizeX * min );
			surfaceSizeY = (int)( sizeY * min );
		}
		break;
	}

	rect.left = 0;
	rect.top = 0;
	rect.right = sizeX;
	rect.bottom = sizeY;

	dest.left = 0;
	dest.top = 0;
	dest.right = surfaceSizeX;
	dest.bottom = surfaceSizeY;


	DWORD style = WS_POPUP | WS_VISIBLE;
	DWORD styleEx = 0;

	if( videoOption <= VIDEO_4X ) {
		style |= WS_OVERLAPPEDWINDOW;
	} else {
		styleEx = 0;
	}

	if( videoOption <= VIDEO_4X ) {
		AdjustWindowRectEx( &dest, style, TRUE, styleEx );
	} else {
		AdjustWindowRectEx( &dest, style, FALSE, styleEx );
	}

	int winSizeX = dest.right-dest.left;
	int winSizeY = dest.bottom-dest.top;

	if( videoOption > VIDEO_4X ) {
		winSizeX = fsWidth;
		winSizeY = fsHeight;
	}

	int x = 0, y = 0;

	if( videoOption <= VIDEO_4X ) {
		x = windowPositionX;
		y = windowPositionY;
	}


	// Create a window
	MainWnd *pWnd = new MainWnd;
	m_pMainWnd = pWnd;

	pWnd->CreateEx(
		styleEx,
		wndClass,
		_T(VBA_NAME_AND_SUBVERSION),
		style,
		x, y,
		winSizeX, winSizeY,
		NULL,
		0
		);

	if( !((HWND)*pWnd) ) {
		// error creating window
		return false;
	}
	pWnd->DragAcceptFiles( TRUE );
	updateMenuBar();
	adjustDestRect();

	return true;
}