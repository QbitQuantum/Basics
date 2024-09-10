void RenderTarget_Win32::StartRenderingTo()
{
	m_hOldDeviceContext = wglGetCurrentDC();
	m_hOldRenderContext = wglGetCurrentContext();

	BOOL successful = wglMakeCurrent(GraphicsWindow::GetHDC(), g_HGLRC);
	ASSERT_M( successful == TRUE, "wglMakeCurrent failed in RenderTarget_Win32::StartRenderingTo()" );

	FlushGLErrors();
	glBindTexture( GL_TEXTURE_2D, m_texHandle );
	AssertNoGLError();
}