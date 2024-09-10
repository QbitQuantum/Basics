int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR, int ) {
	LARGE_INTEGER performanceFrequencyResult;
	QueryPerformanceFrequency( &performanceFrequencyResult );
	performanceFrequency = performanceFrequencyResult.QuadPart;

	win32State_t *state = &win32State;
	Win32GetExeFileName( state );
	char gameDllFullPath[ 256 ];
	Win32BuildExePathFileName( state, "tiny.dll", sizeof( gameDllFullPath ), gameDllFullPath );
	char tempGameDllFullPath[ 256 ];
	Win32BuildExePathFileName( state, "tiny_temp.dll", sizeof( tempGameDllFullPath ), tempGameDllFullPath );

	UINT desiredSchedulerMs = 1;
	b32 sleepIsGranular = ( timeBeginPeriod( desiredSchedulerMs ) == TIMERR_NOERROR );

	WNDCLASSA wndClass = { 0 };
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = "tinyrenderer";

	if ( !RegisterClassA( &wndClass ) ) {
		printf( "Failed RegisterClass()\n" );
		return 1;
	}

	HWND hWnd = CreateWindow(
		wndClass.lpszClassName, "Tiny Renderer",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0, 0, 0, 0 );
	if ( !hWnd ) {
		printf( "Failed CreateWindowA()\n" );
		return 1;
	}

	Win32_ResizeDibSection( &backBuffer, RENDER_WIDTH, RENDER_HEIGHT );

	int monitorRefreshHz = 60;
	HDC refreshDC = GetDC( hWnd );
	int win32RefreshRate = GetDeviceCaps( refreshDC, VREFRESH );
	if ( win32RefreshRate > 1 ) {
		monitorRefreshHz = win32RefreshRate;
	}
	float gameUpdateHz = ( monitorRefreshHz / 2.0f );
	float targetMsPerFrame = 1000.0f * ( 1.0f / ( float ) gameUpdateHz );

	LARGE_INTEGER lastCounter = Win32GetWallClock( );
	LARGE_INTEGER flipWallClock = Win32GetWallClock( );

	win32GameCode_t game = Win32LoadGameCode( gameDllFullPath, tempGameDllFullPath );

	//uint64_t lastCycleCount = __rdtsc();
	running = true;
	while ( running ) {
		FILETIME dllWriteTime = Win32GetLastWriteTime( gameDllFullPath );
		if ( CompareFileTime( &dllWriteTime, &game.lastWriteTime ) != 0 ) {
			Win32UnloadGameCode( &game );
			game = Win32LoadGameCode( gameDllFullPath, tempGameDllFullPath );
		}

		MSG msg = { 0 };
		while ( PeekMessageA( &msg, hWnd, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessageA( &msg );
		}
		if ( running ) {

			gameBackBuffer_t gameBuffer = {};
			gameBuffer.memory = backBuffer.memory;
			gameBuffer.width = backBuffer.width;
			gameBuffer.height = backBuffer.height;
			gameBuffer.pitch = backBuffer.pitch;

			// Render the things
			if ( game.updateAndRender ) {
				game.updateAndRender( &gameBuffer );
			}

			LARGE_INTEGER workCounter = Win32GetWallClock( );
			float workMsElapsed = Win32GetMsElapsed( lastCounter, workCounter );
			float msElapsedForFrame = workMsElapsed;
			if ( msElapsedForFrame < targetMsPerFrame ) {
				if ( sleepIsGranular ) {
					DWORD sleepMs = ( DWORD ) ( targetMsPerFrame - msElapsedForFrame );
					if ( sleepMs > 0 ) {
						Sleep( sleepMs );
					}
				}

				while ( msElapsedForFrame < targetMsPerFrame ) {
					msElapsedForFrame = Win32GetMsElapsed( lastCounter, Win32GetWallClock( ) );
				}
			}

			LARGE_INTEGER endCounter = Win32GetWallClock( );
			float msPerFrame = Win32GetMsElapsed( lastCounter, endCounter );
			lastCounter = endCounter;

			char title[ 256 ];
			sprintf_s( title, "%.2fms/f", msPerFrame );
			SetWindowTextA( hWnd, title );

			// Put the things on the screen
			HDC dc = GetDC( hWnd );
			RECT rect;
			GetClientRect( hWnd, &rect );
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			Win32_AspectBlt( dc, &backBuffer, width, height );
			ReleaseDC( hWnd, dc );

			flipWallClock = Win32GetWallClock( );
		}
	}

	return 0;
}