LRESULT CALLBACK SplashWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT_PTR iRes = 0;	// for SetTimer ret val
	switch (message) 
	{
		case WM_CREATE:
			TRACE( _T("SplashWndProc> WM_CREATE\n") );
			iRes = SetTimer( hWnd, 1, g_dwSplashScreenTimeToLive, NULL );
//			InvalidateRect( hWnd, NULL, FALSE );
//			OnSplashWndPaint(hWnd);
			CenterWindow( hWnd );
			MakeWindowTransparent( hWnd, transparentFactor, crTransparent );
			SetCursor( LoadCursor( NULL, MAKEINTRESOURCE(IDC_ARROW) ) );
			break;

		case WM_PAINT:
//			TRACE( _T("SplashWndProc> WM_PAINT\n") );
			OnSplashWndPaint(hWnd);
			break;

		case WM_LBUTTONUP:
			if( g_bDragSplash )
			{
				g_bDragSplash = FALSE;
				ReleaseCapture();
			}
			break;

		case WM_MOUSEMOVE:
			if( g_bDragSplash )
			{
				POINT	p1 = g_ptMouseDragBegin;
				RECT	r = g_rWindowDragBegin;
				POINT	p2;
				GetCursorPos( &p2 );
				int dx = p2.x - p1.x;
				int dy = p2.y - p1.y;

				MoveWindow( hWnd, r.left + dx, r.top + dy, r.right - r.left, r.bottom - r.top, TRUE );
			}
			break;

		case WM_LBUTTONDOWN:
			#ifdef EXIT_ON_MOUSE_CLICK
				::DestroyWindow(hWnd);
			#else
			SetCapture(hWnd);
			GetCursorPos( &g_ptMouseDragBegin );
			GetWindowRect( hWnd, &g_rWindowDragBegin );
			g_bDragSplash = TRUE;	// Set flag to check for key down in mouse move
									// message.
			#endif
			break;
			
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
//			TRACE( _T("SplashWndProc> Mouse click\n") );
			#ifdef EXIT_ON_MOUSE_CLICK
				::DestroyWindow(hWnd);
			#else
				#ifdef TOGGLE_SPLASH
					g_bStopSplashOnTimer = !g_bStopSplashOnTimer;
				#endif
			#endif
			break;


		case WM_KEYDOWN:
//			TRACE( _T("SplashWndProc> WM_KEYDOWN: VK = %X\n"), wParam );
			if( wParam == VK_ESCAPE )
			{
				::DestroyWindow(hWnd);
			}
			else
			{
				#ifdef EXIT_ON_KBD_HIT
					::DestroyWindow(hWnd);
				#else
					#ifdef TOGGLE_SPLASH
						g_bStopSplashOnTimer = !g_bStopSplashOnTimer;
					#endif
				#endif
			}

			//return DefWindowProc(hWnd, message, wParam, lParam);
			break;

		case WM_TIMER:
			TRACE( _T("SplashWndProc> WM_TIMER\n") );
			if( g_bStopSplashOnTimer )
			{
				::DestroyWindow(hWnd);
			}
			break;

		case WM_DESTROY:
			TRACE( _T("SplashWndProc> WM_DESTROY\n") );
			#ifdef EXIT_AFTER_SPLASH
				PostQuitMessage( 0 );
			#endif
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}