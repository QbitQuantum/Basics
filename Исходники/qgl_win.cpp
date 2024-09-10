/* state:done?(simple version) */
bool QGLContext::chooseContext( const QGLContext* shareContext )
{
    qDebug( "qgl_win.cpp:QGLContext::chooseContext()" );
    // Some kind of workaround, to force loading of opengl module....
    // Seems to be neccessary....why?
    if ( !force_opengl_loading ) {
        GLint params;
        glGetIntegerv( GL_DEPTH_BITS, &params );
        force_opengl_loading = TRUE;
    }
    /* simple implementation:
       assumes that:
       1.colordepth is SAME as desktop
       2.RGBA pixels
       3.no alpna
       4.no acc
       5.32-bit depth buffer
       6.no aux/stencil buffers
       7.
       More correct implementation would use glGetXXX to
       for example:glGetbooleanv for GL_DOUBLEBUFFER...*/ 
    //TODO:what if setContext is NOT yet called and so dc is invalid?
    HDC aDc;
    if ( deviceIsPixmap() ) {
        win = 0;
        aDc = d->paintDevice->handle();
    } else {
        win = ( ( QWidget* ) d->paintDevice ) ->winId();
        aDc = GetDC( win ); //wglGetCurrentDC();
    }
    if ( !aDc ) { // needs a device context
#if defined(QT_CHECK_NULL)
        qWarning( "qgl_win.cpp: QGLContext::chooseContext(): Paint device cannot be null" );
#endif

        if ( win ) {
            ReleaseDC( win, aDc );
        }
        return FALSE;
    }

    PIXELFORMATDESCRIPTOR pfd;
    pixelFormatId = choosePixelFormat( &pfd, aDc );
    if ( ( !SetPixelFormat( aDc, pixelFormatId, &pfd ) ) ) {
        qglError( "qgl_win.cpp: QGLContext::choosePixelFormat()", "SetPixelFormat" );
        if ( win ) {
            ReleaseDC( win, aDc );
            return FALSE;
        }
    }
    rc = wglCreateContext( aDc );
    if ( !rc ) {
        qglError( "qgl_win.cpp: QGLContext:chooseContext()", "wglCreateContext" );
        if ( win )
            ReleaseDC( win, aDc );
        return FALSE;
    }
    return TRUE;
}