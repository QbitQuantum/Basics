HGLRC CL_GL1CreationHelper::create_opengl2_context(HGLRC share_context)
{
	HGLRC opengl2_context = wglCreateContext(hdc);
	if (opengl2_context)
		wglShareLists(share_context, opengl2_context);
	return opengl2_context;
}