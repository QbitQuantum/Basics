bool GSWndEGL::Attach(void* handle, bool managed)
{
	m_NativeWindow = *(Window*)handle;
	m_managed = managed;

	m_NativeDisplay = XOpenDisplay(NULL);
	OpenEGLDisplay();

#ifdef ENABLE_GLES
	// FIXME: update it to GLES 3.1 when  they support it
	CreateContext(3, 0);
#else
	CreateContext(3, 3);
#endif

	AttachContext();

	CheckContext();

	PopulateGlFunction();

	return true;
}