SOFTGL_API BOOL softglCreateContext(HDC hdc)
{
	FUNC_HOOK("softglCreateContext");
	return WGLCreateContext(hdc);
}