/**-----------------------------------------------------------------------------
 * 프로그램 시작점
 *------------------------------------------------------------------------------
 */
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    /// 윈도우 클래스 등록
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "BasicFrame", NULL
                    };
    RegisterClassEx( &wc );

    /// 윈도우 생성
    HWND hWnd = CreateWindow( "BasicFrame", WINDOW_TITLE,
                              WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_W, WINDOW_H,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );

    g_hwnd = hWnd;

    g_pLog = new ZFLog( ZF_LOG_TARGET_CONSOLE | ZF_LOG_TARGET_WINDOW );
    // g_pCamera = new ZCamera;
    g_pCamera = (ZCamera*)_aligned_malloc( sizeof( ZCamera ), 16 );

    /// Direct3D 초기화
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        if( SUCCEEDED( InitGeometry() ) )
        {

            /// 윈도우 출력
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            /// 메시지 루프
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                /// 메시지큐에 메시지가 있으면 메시지 처리
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                {
                    /// 처리할 메시지가 없으면 Render()함수 호출
                    Render();
                }
            }
        }
    }

    delete g_pLog;
    // delete g_pCamera;
    if ( g_pCamera )
    {
        g_pCamera->~ZCamera();
        _aligned_free( g_pCamera );
    }

    /// 등록된 클래스 소거
    UnregisterClass( "D3D Tutorial", wc.hInstance );
    return 0;
}