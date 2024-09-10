void PBuffer_GL1_Impl::create(OpenGLWindowProvider &window_provider, const Size &size)
{
	reset();

	OpenGL::set_active(gc_provider);

	if (glWglCreatePbufferARB == 0)
	{
		throw Exception("WGL_ARB_pbuffer OpenGL extension not supported by this card");
	}

	int attribList[1] = { 0 };

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd 
		1,                              // version number
		// PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL //|            // support OpenGL
		//PFD_DOUBLEBUFFER |              // double buffered
		//PFD_DEPTH_DONTCARE
		,             // do you care about a zbuffer?
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		8,                              // alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		0,                              // z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int pixelformat = ChoosePixelFormat(wglGetCurrentDC(), &pfd);

	pbuffer = glWglCreatePbufferARB(
		wglGetCurrentDC(),
		pixelformat,
		size.width,
		size.height,
		attribList);
	pbuffer_dc = glWglGetPbufferDCARB(pbuffer);
	pbuffer_context = wglCreateContext(pbuffer_dc);

	HGLRC share_context = window_provider.get_share_context();
	if (share_context == 0)
		throw Exception("Shared OpenGL Context is not valid");

	wglShareLists(share_context, pbuffer_context);

	pbuffer_size = size;
}