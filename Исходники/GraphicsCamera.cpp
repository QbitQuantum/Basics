CRect CGraphicsCamera::GetViewportRect( )
{
	GLint viewport[4];
	CRect r;
	HGLRC currentRC = wglGetCurrentContext();
	if( currentRC || wglMakeCurrent( m_hDC, m_hGLRC ) )
	{
		glGetIntegerv( GL_VIEWPORT, viewport );
		r = CRect( CPoint( viewport[0], viewport[1] ), CPoint( viewport[2], viewport[3] ) );
	}
	return r;
}