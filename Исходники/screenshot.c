/*
 * Take a screenshot of this sessions default input desktop on WinSta0
 * and send it as a JPEG image to a named pipe.
 */
DWORD screenshot( int quality, DWORD dwPipeName )
{
	DWORD dwResult             = ERROR_ACCESS_DENIED;
	HWINSTA hWindowStation     = NULL;
	HWINSTA hOrigWindowStation = NULL;
	HDESK hInputDesktop        = NULL;
	HDESK hOrigDesktop         = NULL;
	HWND hDesktopWnd           = NULL;	
	HDC hdc                    = NULL;
	HDC hmemdc                 = NULL;
	HBITMAP hbmp               = NULL;
	BYTE * pJpegBuffer         = NULL;
	OSVERSIONINFO os           = {0};
	char cNamedPipe[MAX_PATH]  = {0};
	// If we use SM_C[X|Y]VIRTUALSCREEN we can screenshot the whole desktop of a multi monitor display.
	int xmetric               = SM_CXVIRTUALSCREEN;
	int ymetric               = SM_CYVIRTUALSCREEN;
	DWORD dwJpegSize          = 0;
	int sx                    = 0;
	int sy                    = 0;

	do
	{
		_snprintf( cNamedPipe, MAX_PATH, "\\\\.\\pipe\\%08X", dwPipeName );

		os.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

		if( !GetVersionEx( &os ) )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot: GetVersionEx failed" )
		
		// On NT we cant use SM_CXVIRTUALSCREEN/SM_CYVIRTUALSCREEN.
		if( os.dwMajorVersion <= 4 )
		{
			xmetric = SM_CXSCREEN;
			ymetric = SM_CYSCREEN;
		}
		
		// open the WinSta0 as some services are attached to a different window station.
		hWindowStation = OpenWindowStation( "WinSta0", FALSE, WINSTA_ALL_ACCESS );
		if( !hWindowStation )
		{
			if( RevertToSelf() )
				hWindowStation = OpenWindowStation( "WinSta0", FALSE, WINSTA_ALL_ACCESS );
		}
		
		// if we cant open the defaut input station we wont be able to take a screenshot
		if( !hWindowStation )
			BREAK_WITH_ERROR( "[SCREENSHOT] screenshot: Couldnt get the WinSta0 Window Station", ERROR_INVALID_HANDLE );
		
		// get the current process's window station so we can restore it later on.
		hOrigWindowStation = GetProcessWindowStation();
		
		// set the host process's window station to this sessions default input station we opened
		if( !SetProcessWindowStation( hWindowStation ) )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot: SetProcessWindowStation failed" );

		// grab a handle to the default input desktop (e.g. Default or WinLogon)
		hInputDesktop = OpenInputDesktop( 0, FALSE, MAXIMUM_ALLOWED );
		if( !hInputDesktop )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot: OpenInputDesktop failed" );

		// get the threads current desktop so we can restore it later on
		hOrigDesktop = GetThreadDesktop( GetCurrentThreadId() );

		// set this threads desktop to that of this sessions default input desktop on WinSta0
		SetThreadDesktop( hInputDesktop );

		// and now we can grab a handle to this input desktop
		hDesktopWnd = GetDesktopWindow();

		// and get a DC from it so we can read its pixels!
		hdc = GetDC( hDesktopWnd );
		if( !hdc )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot. GetDC failed" );

		// back up this DC with a memory DC
		hmemdc = CreateCompatibleDC( hdc );
		if( !hmemdc )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot. CreateCompatibleDC failed" );

		// calculate the width and height
		sx = GetSystemMetrics( xmetric );
		sy = GetSystemMetrics( ymetric );

		// and create a bitmap
		hbmp = CreateCompatibleBitmap( hdc, sx, sy );
		if( !hbmp )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot. CreateCompatibleBitmap failed" );
		
		// this bitmap is backed by the memory DC
		if( !SelectObject( hmemdc, hbmp ) )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot. SelectObject failed" );

		// BitBlt the screenshot of this sessions default input desktop on WinSta0 onto the memory DC we created 
		if( !BitBlt( hmemdc, 0, 0, sx, sy, hdc, 0, 0, SRCCOPY ) )
			BREAK_ON_ERROR( "[SCREENSHOT] screenshot. BitBlt failed" );

		// finally convert the BMP we just made into a JPEG...
		if( bmp2jpeg( hbmp, hmemdc, quality, &pJpegBuffer, &dwJpegSize ) != 1 )
			BREAK_WITH_ERROR( "[SCREENSHOT] screenshot. bmp2jpeg failed", ERROR_INVALID_HANDLE );

		// we have succeded
		dwResult = ERROR_SUCCESS;
		
	} while( 0 );

	// if we have successfully taken a screenshot we send it back via the named pipe
	// but if we have failed we send back a zero byte result to indicate this failure.
	if( dwResult == ERROR_SUCCESS )
		screenshot_send( cNamedPipe, pJpegBuffer, dwJpegSize );
	else
		screenshot_send( cNamedPipe, NULL, 0 );

	if( hdc )
		ReleaseDC( hDesktopWnd, hdc );

	if( hmemdc )
		DeleteDC( hmemdc );

	if( hbmp )
		DeleteObject( hbmp );

	// free the jpeg images buffer
	if( pJpegBuffer )
		free( pJpegBuffer );

	// restore the origional process's window station
	if( hOrigWindowStation )
		SetProcessWindowStation( hOrigWindowStation );

	// restore the threads origional desktop
	if( hOrigDesktop )
		SetThreadDesktop( hOrigDesktop );

	// close the WinSta0 window station handle we opened
	if( hWindowStation )
		CloseWindowStation( hWindowStation );

	// close this last to avoid a handle leak...
	if( hInputDesktop )
		CloseDesktop( hInputDesktop );

	return dwResult;
}