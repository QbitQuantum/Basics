    void OpenGLRenderer::Finalize()
    {
        HDC hdc = GetDC ( static_cast<HWND> ( mWindowId ) );
        wglMakeCurrent ( hdc, static_cast<HGLRC> ( mOpenGLContext ) );
        OPENGL_CHECK_ERROR_NO_THROW;
        ATOM atom = GetClassWord ( static_cast<HWND> ( mWindowId ), GCW_ATOM );
        wglMakeCurrent ( hdc, nullptr );
        wglDeleteContext ( static_cast<HGLRC> ( mOpenGLContext ) );
        mOpenGLContext = nullptr;
        ReleaseDC ( static_cast<HWND> ( mWindowId ), hdc );
        DestroyWindow ( static_cast<HWND> ( mWindowId ) );
        UnregisterClass ( reinterpret_cast<LPCSTR> (
#if defined(_M_X64) || defined(__amd64__)
                              0x0ULL +
#endif
                              MAKELONG ( atom, 0 ) ), nullptr );
    }