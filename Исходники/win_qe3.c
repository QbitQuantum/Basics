void QEW_StopGL( HWND hWnd, HGLRC hGLRC, HDC hDC )
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( hGLRC );
	ReleaseDC( hWnd, hDC );
}