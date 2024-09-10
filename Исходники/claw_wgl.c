static void create_opengl_context (struct claw_window *window) {
	window->device_context = GetDC (window->hwnd);
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_GENERIC_ACCELERATED|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, // accumulation buffer
		0, 0, 0, 0,
		0, // depth buffer
		0, // stencil buffer
		0, // aux buffers
		0, 0, 0, 0, 0
	};
	int pixel_format = ChoosePixelFormat (window->device_context, &pfd);
	SetPixelFormat (window->device_context, pixel_format, &pfd);
	window->opengl_context = wglCreateContext (window->device_context);
	if (first_context)
		wglShareLists (first_context, window->opengl_context);
	else
		first_context = window->opengl_context;
	wglMakeCurrent (window->device_context, window->opengl_context);
}