void COpenGL::FinitGL()
{
	if (wglGetCurrentContext())
		MakeGLContextNotCurrent();
	
	if (m_hGLContext)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}