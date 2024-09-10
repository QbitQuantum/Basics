	void GLContextWin32::Unbind( void)
	{
		wglMakeCurrent( NULL, NULL);
		m_currentGLContextBound = NULL;
	}