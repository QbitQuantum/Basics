/*
	Initialize().
	We already have a window from the screensaver, so store it and pass along all 0's to initialize
	a child window.
*/
bool	CDisplayDX::Initialize( HWND _hWnd, bool _bPreview )
{
    m_bScreensaver = true;
    m_bPreview = _bPreview;
    m_WindowHandle = _hWnd;

    HMODULE    hInstance = GetModuleHandle( NULL );

    WNDCLASS wc = {0};

    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = (WNDPROC)CDisplayDX::wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(1));
    wc.hCursor = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"ElectricsheepWndClass";
    RegisterClass( &wc );

    if( _bPreview )
    {
        g_bPreview = true;

        RECT rc;
        //GetWindowRect( _hWnd, &rc );
        GetClientRect( _hWnd, &rc );
        int32 cx = rc.right - rc.left;
        int32 cy = rc.bottom - rc.top;

        g_Log->Info( "rc: %d, %d", cx, cy );

        DWORD dwStyle = WS_VISIBLE | WS_CHILD;
        AdjustWindowRect( &rc, dwStyle, FALSE );
        m_WindowHandle = CreateWindow( L"ElectricsheepWndClass", L"Preview", dwStyle, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, _hWnd, NULL, hInstance, NULL );
        g_Log->Info( "CDisplayDX::Initialize x=%u y=%u w=%u h=%u",  rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
        if( m_WindowHandle == NULL )
        {
            g_Log->Error( "CDisplayDX::Initialize unable to create window for preview" );
            //ThrowStr( "Unable to create window..." );
            return false;
        }

        m_Width = cx;
        m_Height = cy;

        g_Log->Info( "Screensaver preview (%dx%d)", cx, cy );

        // In preview mode, "pause" (enter a limited message loop) briefly before proceeding, so the display control panel knows to update itself.
        m_bWaitForInputIdle = true;

        // Post a message to mark the end of the initial group of window messages
        PostMessage( m_WindowHandle, WM_USER, 0, 0 );

        InvalidateRect( GetParent( _hWnd ), NULL, FALSE );    // Invalidate the hwnd so it gets drawn
        UpdateWindow( GetParent( _hWnd ) );
        UpdateWindow( GetParent( _hWnd ) );

        MSG msg;
        while( m_bWaitForInputIdle )
        {
            // If GetMessage returns FALSE, it's quitting time.
            if( !GetMessage( &msg, m_WindowHandle, 0, 0 ) )
            {
                // Post the quit message to handle it later
                PostQuitMessage(0);
                break;
            }

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        if( !InitDX9() )
            return false;

        //ShowWindow( _hWnd, SW_SHOW );
        //SetForegroundWindow( _hWnd );
        SetFocus( _hWnd );
        ShowCursor( true );
    }
    else
    {
//		int32 cx = GetSystemMetrics( SM_CXSCREEN );
//		int32 cy = GetSystemMetrics( SM_CYSCREEN );
        RECT rc;
        GetWindowRect( _hWnd, &rc );
        m_Width = rc.right - rc.left;
        m_Height = rc.bottom - rc.top;
        g_Log->Info( "CDisplayDX::Initialize right=%u left=%u bottom=%u top=%u",  rc.right, rc.left, rc.bottom, rc.top);
        //DWORD exstyle = 0;//WS_EX_TOPMOST;
        //DWORD style = WS_CHILD | WS_VISIBLE;

        m_WindowHandle = _hWnd;//CreateWindowEx( exstyle, "Electricsheep", "Saver", style, 0, 0, cx, cy, _hWnd, NULL, hInstance, NULL );
        if( m_WindowHandle == NULL )
        {
            g_Log->Error( "CDisplayDX::Initialize unable to create window from _hWnd" );
            return false;
        }

        g_Log->Info( "Screensaver (%dx%d)", m_Width, m_Height );

        //	Hide cursor.
        ShowCursor( false );

        if( !InitDX9() )
            return false;
    }

    return true;
}