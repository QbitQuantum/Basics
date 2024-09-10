bool GSWndOGL::Attach(void* handle, bool managed)
{
	m_NativeWindow = *(Window*)handle;
	m_managed = managed;

	m_NativeDisplay = XOpenDisplay(NULL);

	if (theApp.GetConfig("reduce_gl_requirement_for_free_driver", 0) == 1)
		CreateContext(3, 0);
	else
		CreateContext(3, 3);

	AttachContext();

	CheckContext();

	m_swapinterval = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((const GLubyte*) "glXSwapIntervalEXT");

	PopulateGlFunction();

	return true;
}