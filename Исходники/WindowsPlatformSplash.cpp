/**
 * Splash screen thread entry function
 */
uint32 WINAPI StartSplashScreenThread( LPVOID unused )
{
	WNDCLASS wc;
	wc.style       = CS_HREDRAW | CS_VREDRAW; 
	wc.lpfnWndProc = (WNDPROC) SplashScreenWindowProc; 
	wc.cbClsExtra  = 0; 
	wc.cbWndExtra  = 0; 
	wc.hInstance   = hInstance; 

	wc.hIcon       = LoadIcon(hInstance, MAKEINTRESOURCE(FWindowsPlatformMisc::GetAppIcon()));
	if(wc.hIcon == NULL)
	{
		wc.hIcon   = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION); 
	}

	wc.hCursor     = LoadCursor((HINSTANCE) NULL, IDC_ARROW); 
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = TEXT("SplashScreenClass"); 
 
	if(!RegisterClass(&wc)) 
	{
		return 0; 
	} 

	// Load splash screen image, display it and handle all window's messages
	GSplashScreenBitmap = (HBITMAP) LoadImage(hInstance, (LPCTSTR)*GSplashScreenFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(GSplashScreenBitmap)
	{
		BITMAP bm;
		GetObject(GSplashScreenBitmap, sizeof(bm), &bm);

		const int32 BorderWidth = GetSystemMetrics(SM_CXBORDER);
		const int32 BorderHeight = GetSystemMetrics(SM_CYBORDER);
		const int32 WindowWidth = bm.bmWidth + BorderWidth;
		const int32 WindowHeight = bm.bmHeight + BorderHeight;
		int32 ScreenPosX = (GetSystemMetrics(SM_CXSCREEN) - WindowWidth) / 2;
		int32 ScreenPosY = (GetSystemMetrics(SM_CYSCREEN) - WindowHeight) / 2;

		const bool bAllowFading = true;

		// Force the editor splash screen to show up in the taskbar and alt-tab lists
		uint32 dwWindowStyle = (GIsEditor ? WS_EX_APPWINDOW : 0) | WS_EX_TOOLWINDOW;
		if( bAllowFading )
		{
			dwWindowStyle |= WS_EX_LAYERED;
		}

		GSplashScreenWnd = CreateWindowEx(
			dwWindowStyle,
			wc.lpszClassName, 
			TEXT("SplashScreen"),
			WS_BORDER|WS_POPUP,
			ScreenPosX,
			ScreenPosY,
			WindowWidth,
			WindowHeight,
			(HWND) NULL,
			(HMENU) NULL,
			hInstance,
			(LPVOID) NULL); 

		if( bAllowFading )
		{
			// Set window to fully transparent to start out
			SetLayeredWindowAttributes( GSplashScreenWnd, 0, 0, LWA_ALPHA );
		}


		// Setup font
		{
			HFONT SystemFontHandle = ( HFONT )GetStockObject( DEFAULT_GUI_FONT );

			// Create small font
			{
				LOGFONT MyFont;
				FMemory::Memzero( &MyFont, sizeof( MyFont ) );
				GetObject( SystemFontHandle, sizeof( MyFont ), &MyFont );
				MyFont.lfHeight = 10;
				// MyFont.lfQuality = ANTIALIASED_QUALITY;
				GSplashScreenSmallTextFontHandle = CreateFontIndirect( &MyFont );
				if( GSplashScreenSmallTextFontHandle == NULL )
				{
					// Couldn't create font, so just use a system font
					GSplashScreenSmallTextFontHandle = SystemFontHandle;
				}
			}

			// Create normal font
			{
				LOGFONT MyFont;
				FMemory::Memzero( &MyFont, sizeof( MyFont ) );
				GetObject( SystemFontHandle, sizeof( MyFont ), &MyFont );
				MyFont.lfHeight = 12;
				// MyFont.lfQuality = ANTIALIASED_QUALITY;
				GSplashScreenNormalTextFontHandle = CreateFontIndirect( &MyFont );
				if( GSplashScreenNormalTextFontHandle == NULL )
				{
					// Couldn't create font, so just use a system font
					GSplashScreenNormalTextFontHandle = SystemFontHandle;
				}
			}
		}
		
		// Setup bounds for version info text 1
		GSplashScreenTextRects[ SplashTextType::VersionInfo1 ].top = bm.bmHeight - 60;
		GSplashScreenTextRects[ SplashTextType::VersionInfo1 ].bottom = bm.bmHeight - 40;
		GSplashScreenTextRects[ SplashTextType::VersionInfo1 ].left = 10;
		GSplashScreenTextRects[ SplashTextType::VersionInfo1 ].right = bm.bmWidth - 20;

		// Setup bounds for copyright info text
		if( GIsEditor )
		{
			GSplashScreenTextRects[ SplashTextType::CopyrightInfo ].top = bm.bmHeight - 44;
			GSplashScreenTextRects[ SplashTextType::CopyrightInfo ].bottom = bm.bmHeight - 34;
		}
		else
		{
			GSplashScreenTextRects[ SplashTextType::CopyrightInfo ].top = bm.bmHeight - 16;
			GSplashScreenTextRects[ SplashTextType::CopyrightInfo ].bottom = bm.bmHeight - 6;
		}
		GSplashScreenTextRects[ SplashTextType::CopyrightInfo ].left = 10;
		GSplashScreenTextRects[ SplashTextType::CopyrightInfo ].right = bm.bmWidth - 20;

		// Setup bounds for startup progress text
		GSplashScreenTextRects[ SplashTextType::StartupProgress ].top = bm.bmHeight - 20;
		GSplashScreenTextRects[ SplashTextType::StartupProgress ].bottom = bm.bmHeight;
		GSplashScreenTextRects[ SplashTextType::StartupProgress ].left = 10;
		GSplashScreenTextRects[ SplashTextType::StartupProgress ].right = bm.bmWidth - 20;

		if (GSplashScreenWnd)
		{
			SetWindowText(GSplashScreenWnd, *GSplashScreenAppName.ToString());
			ShowWindow(GSplashScreenWnd, SW_SHOW); 
			UpdateWindow(GSplashScreenWnd); 
		 
			const double FadeStartTime = FPlatformTime::Seconds();
			const float FadeDuration = 0.2f;
			int32 CurrentOpacityByte = 0;

			MSG message;
			bool bIsSplashFinished = false;
			while( !bIsSplashFinished )
			{
				if( PeekMessage(&message, NULL, 0, 0, PM_REMOVE) )
				{
					TranslateMessage(&message);
					DispatchMessage(&message);

					if( message.message == WM_QUIT )
					{
						bIsSplashFinished = true;
					}
				}

				// Update window opacity
				if( bAllowFading && CurrentOpacityByte < 255 )
				{
					// Set window to fully transparent to start out
					const float TimeSinceFadeStart = (float)( FPlatformTime::Seconds() - FadeStartTime );
					const float FadeAmount = FMath::Clamp( TimeSinceFadeStart / FadeDuration, 0.0f, 1.0f );
					const int32 NewOpacityByte = 255 * FadeAmount;
					if( NewOpacityByte != CurrentOpacityByte )
					{
						CurrentOpacityByte = NewOpacityByte;
						SetLayeredWindowAttributes( GSplashScreenWnd, 0, CurrentOpacityByte, LWA_ALPHA );
					}

					// We're still fading, but still yield a timeslice
					FPlatformProcess::Sleep( 0.0f );
				}
				else
				{
					// Give up some time
					FPlatformProcess::Sleep( 1.0f / 60.0f );
				}
			}
		}

		DeleteObject(GSplashScreenBitmap);
		GSplashScreenBitmap = NULL;
	}

	UnregisterClass(wc.lpszClassName, hInstance);
	return 0; 
}