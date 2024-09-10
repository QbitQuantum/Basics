	void GlContext::create(uint32_t /*_width*/, uint32_t /*_height*/)
	{
		m_opengl32dll = bx::dlopen("opengl32.dll");
		BGFX_FATAL(NULL != m_opengl32dll, Fatal::UnableToInitialize, "Failed to load opengl32.dll.");

		wglGetProcAddress = (PFNWGLGETPROCADDRESSPROC)bx::dlsym(m_opengl32dll, "wglGetProcAddress");
		BGFX_FATAL(NULL != wglGetProcAddress, Fatal::UnableToInitialize, "Failed get wglGetProcAddress.");

		// If g_bgfxHwnd is NULL, the assumption is that GL context was created
		// by user (for example, using SDL, GLFW, etc.)
		BX_WARN(NULL != g_bgfxHwnd
			, "bgfx::winSetHwnd with valid window is not called. This might "
			  "be intentional when GL context is created by the user."
			);

		if (NULL != g_bgfxHwnd)
		{
			wglMakeCurrent = (PFNWGLMAKECURRENTPROC)bx::dlsym(m_opengl32dll, "wglMakeCurrent");
			BGFX_FATAL(NULL != wglMakeCurrent, Fatal::UnableToInitialize, "Failed get wglMakeCurrent.");

			wglCreateContext = (PFNWGLCREATECONTEXTPROC)bx::dlsym(m_opengl32dll, "wglCreateContext");
			BGFX_FATAL(NULL != wglCreateContext, Fatal::UnableToInitialize, "Failed get wglCreateContext.");

			wglDeleteContext = (PFNWGLDELETECONTEXTPROC)bx::dlsym(m_opengl32dll, "wglDeleteContext");
			BGFX_FATAL(NULL != wglDeleteContext, Fatal::UnableToInitialize, "Failed get wglDeleteContext.");

			m_hdc = GetDC(g_bgfxHwnd);
			BGFX_FATAL(NULL != m_hdc, Fatal::UnableToInitialize, "GetDC failed!");

			// Dummy window to peek into WGL functionality.
			//
			// An application can only set the pixel format of a window one time.
			// Once a window's pixel format is set, it cannot be changed.
			// MSDN: http://msdn.microsoft.com/en-us/library/windows/desktop/dd369049%28v=vs.85%29.aspx
			HWND hwnd = CreateWindowA("STATIC"
				, ""
				, WS_POPUP|WS_DISABLED
				, -32000
				, -32000
				, 0
				, 0
				, NULL
				, NULL
				, GetModuleHandle(NULL)
				, 0
				);

			HDC hdc = GetDC(hwnd);
			BGFX_FATAL(NULL != hdc, Fatal::UnableToInitialize, "GetDC failed!");

			HGLRC context = createContext(hdc);

			wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
			wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

			if (NULL != wglGetExtensionsStringARB)
			{
				const char* extensions = (const char*)wglGetExtensionsStringARB(hdc);
				BX_TRACE("WGL extensions:");
				dumpExtensions(extensions);
			}

			if (NULL != wglChoosePixelFormatARB
			&&  NULL != wglCreateContextAttribsARB)
			{
				int32_t attrs[] =
				{
					WGL_SAMPLE_BUFFERS_ARB, 0,
					WGL_SAMPLES_ARB, 0,
					WGL_SUPPORT_OPENGL_ARB, true,
					WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
					WGL_DRAW_TO_WINDOW_ARB, true,
					WGL_DOUBLE_BUFFER_ARB, true,
					WGL_COLOR_BITS_ARB, 32,
					WGL_DEPTH_BITS_ARB, 24,
					WGL_STENCIL_BITS_ARB, 8,
					0
				};

				int result;
				int pixelFormat;
				uint32_t numFormats = 0;
				do 
				{
					result = wglChoosePixelFormatARB(m_hdc, attrs, NULL, 1, &pixelFormat, &numFormats);
					if (0 == result
						||  0 == numFormats)
					{
						attrs[3] >>= 1;
						attrs[1] = attrs[3] == 0 ? 0 : 1;
					}

				} while (0 == numFormats);

				PIXELFORMATDESCRIPTOR pfd;
				DescribePixelFormat(m_hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

				BX_TRACE("Pixel format:\n"
					"\tiPixelType %d\n"
					"\tcColorBits %d\n"
					"\tcAlphaBits %d\n"
					"\tcDepthBits %d\n"
					"\tcStencilBits %d\n"
					, pfd.iPixelType
					, pfd.cColorBits
					, pfd.cAlphaBits
					, pfd.cDepthBits
					, pfd.cStencilBits
					);

				result = SetPixelFormat(m_hdc, pixelFormat, &pfd);
				// When window is created by SDL and SDL_WINDOW_OPENGL is set SetPixelFormat
				// will fail. Just warn and continue. In case it failed for some other reason
				// create context will fail and it will error out there.
				BX_WARN(result, "SetPixelFormat failed (last err: 0x%08x)!", GetLastError() );

				uint32_t flags = BGFX_CONFIG_DEBUG ? WGL_CONTEXT_DEBUG_BIT_ARB : 0;
				BX_UNUSED(flags);
				int32_t contextAttrs[9] =
				{
#if BGFX_CONFIG_RENDERER_OPENGL >= 31
					WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
					WGL_CONTEXT_MINOR_VERSION_ARB, 1,
					WGL_CONTEXT_FLAGS_ARB, flags,
					WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
#else
					WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
					WGL_CONTEXT_MINOR_VERSION_ARB, 1,
					0, 0,
					0, 0,
#endif // BGFX_CONFIG_RENDERER_OPENGL >= 31
					0
				};

				m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
				if (NULL == m_context)
				{
					// nVidia doesn't like context profile mask for contexts below 3.2?
					contextAttrs[6] = WGL_CONTEXT_PROFILE_MASK_ARB == contextAttrs[6] ? 0 : contextAttrs[6];
					m_context = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
				}
				BGFX_FATAL(NULL != m_context, Fatal::UnableToInitialize, "Failed to create context 0x%08x.", GetLastError() );
			}