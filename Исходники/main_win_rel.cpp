void entrypoint( void )
{              
    // full screen
    if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return;
    ShowCursor( 0 );
    // create window
    HWND hWnd = CreateWindow( "static",0,WS_POPUP|WS_VISIBLE|WS_MAXIMIZE,0,0,0,0,0,0,0,0);
    if( !hWnd ) return;
    HDC hDC = GetDC(hWnd);
    // initalize opengl
    if( !SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd) ) return;
    wglMakeCurrent(hDC,wglCreateContext(hDC));

    // init intro
    if( !intro_init() ) return;

    // init mzk
    mzk_init( myMuzik+22 );
    memcpy( myMuzik, wavHeader, 44 );

    // play mzk
    sndPlaySound( (const char*)&myMuzik, SND_ASYNC|SND_MEMORY );

    // play intro
    long t;
    long to = timeGetTime();
    do 
    {
        t = timeGetTime() - to;
        intro_do( t );
        wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE ); //SwapBuffers( hDC );
    }while ( !GetAsyncKeyState(VK_ESCAPE) && t<(MZK_DURATION*1000) );

    #ifdef CLEANDESTROY
    sndPlaySound(0,0);
    ChangeDisplaySettings( 0, 0 );
    ShowCursor(1);
    #endif

    ExitProcess(0);
}