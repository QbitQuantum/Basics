OpenGLWindowRenderTarget::~OpenGLWindowRenderTarget(void)
{
	wglDeleteContext(mHGLRenderContext);
}