const bool gleIsOpenGLCurrent()
{
#ifdef WIN32
	return wglGetCurrentContext() != NULL;
#elif __MACOSX__
	#error "Not yet implemented"
#else // POSIX
	return glXGetCurrentContext() != NULL;
#endif
}