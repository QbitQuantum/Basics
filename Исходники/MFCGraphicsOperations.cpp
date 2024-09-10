std::unique_ptr<os::Viewport> MFCGraphicsOperations::createViewport(const os::ViewPortProperties& props)
{
	int PixelFormat;
	PIXELFORMATDESCRIPTOR pfd_test;
	PIXELFORMATDESCRIPTOR GL_pfd;

	mprintf(("  Initializing WGL...\n"));

	memset(&GL_pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	memset(&pfd_test, 0, sizeof(PIXELFORMATDESCRIPTOR));

	GL_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	GL_pfd.nVersion = 1;
	GL_pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	if (props.enable_opengl)
	{
		GL_pfd.dwFlags |= PFD_SUPPORT_OPENGL;
	}

	GL_pfd.iPixelType = PFD_TYPE_RGBA;
	GL_pfd.cColorBits = (BYTE)(props.pixel_format.red_size + props.pixel_format.green_size + props.pixel_format.blue_size + props.pixel_format.alpha_size);
	GL_pfd.cRedBits = (BYTE)(props.pixel_format.red_size);
	GL_pfd.cGreenBits = (BYTE)(props.pixel_format.green_size);
	GL_pfd.cBlueBits = (BYTE)(props.pixel_format.blue_size);
	GL_pfd.cAlphaBits = (BYTE)(props.pixel_format.alpha_size);
	GL_pfd.cDepthBits = (BYTE)(props.pixel_format.depth_size);
	GL_pfd.cStencilBits = (BYTE)(props.pixel_format.stencil_size);

	Assert(_windowHandle != NULL);

	auto device_context = GetDC(_windowHandle);

	if (!device_context)
	{
		mprintf(("Unable to get device context for OpenGL W32!\n"));
		return nullptr;
	}

	PixelFormat = ChoosePixelFormat(device_context, &GL_pfd);

	if (!PixelFormat)
	{
		mprintf(("Unable to choose pixel format for OpenGL W32!\n"));
		ReleaseDC(_windowHandle, device_context);
		return nullptr;
	}
	else
	{
		DescribePixelFormat(device_context, PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd_test);
	}

	if (!SetPixelFormat(device_context, PixelFormat, &GL_pfd))
	{
		mprintf(("Unable to set pixel format for OpenGL W32!\n"));
		ReleaseDC(_windowHandle, device_context);
		return nullptr;
	}

	mprintf(("  Requested SDL Video values = R: %d, G: %d, B: %d, depth: %d, stencil: %d\n",
		props.pixel_format.red_size, props.pixel_format.green_size, props.pixel_format.blue_size,
		props.pixel_format.depth_size, props.pixel_format.stencil_size));

	return std::unique_ptr<os::Viewport>(new MFCViewport(_windowHandle, device_context));
}