void entrypoint( void )
{
    // full screen
#ifdef SETRESOLUTION
    if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return;
#endif
    // create window
    HWND hWnd = CreateWindow( "static",0,WS_POPUP|WS_VISIBLE|WS_MAXIMIZE,0,0,0,0,0,0,0,0);
    HDC hDC = GetDC(hWnd);

    // initalize opengl
    if( !SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd) ) return;

    HGLRC tempOpenGLContext;
    tempOpenGLContext = wglCreateContext(hDC);
    wglMakeCurrent(hDC, tempOpenGLContext);
    // create openGL functions
    for (int i=0; i<NUM_GL_NAMES; i++) glFP[i] = (GenFP)wglGetProcAddress(glnames[i]);
    HGLRC hRC = wglCreateContextAttribsARB(hDC, NULL, glAttribs);
    // Remove temporary context and set new one
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(tempOpenGLContext);
    wglMakeCurrent(hDC, hRC);

    // init intro
    intro_init();

    // open audio device
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    // create music block
    mzk_init();
    // prepare and play music block
    header[0].lpData = (char *)myMuzikBlock[0];
    header[1].lpData = (char *)myMuzikBlock[1];
    header[0].dwBufferLength = AUDIO_BUFFER_SIZE * MZK_NUMCHANNELS * 2;
    header[1].dwBufferLength = AUDIO_BUFFER_SIZE * MZK_NUMCHANNELS * 2;
    waveOutPrepareHeader(hWaveOut, &(header[0]), sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &(header[0]), sizeof(WAVEHDR));
    waveOutPrepareHeader(hWaveOut, &(header[1]), sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &(header[1]), sizeof(WAVEHDR));

    timer.wType = TIME_SAMPLES;
    do
    {
        MSG msg;
        PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

        ShowCursor(0);
        waveOutGetPosition(hWaveOut, &timer, sizeof(timer));
        DWORD t = timer.u.sample;

        intro_do(t);
        //SwapBuffers ( hDC );
        wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );

        // Try to unprepare header
        if (waveOutUnprepareHeader(hWaveOut, &(header[nextPlayBlock]), sizeof(WAVEHDR))
                != WAVERR_STILLPLAYING)
        {
            mzk_prepare_block(myMuzikBlock[nextPlayBlock]);
            waveOutPrepareHeader(hWaveOut, &(header[nextPlayBlock]), sizeof(WAVEHDR));
            waveOutWrite(hWaveOut, &(header[nextPlayBlock]), sizeof(WAVEHDR));
            nextPlayBlock = 1 - nextPlayBlock;
        }
    } while ( !(GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_F4)));

    sndPlaySound(0,0);

    ExitProcess(0);
}