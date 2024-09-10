		void init()
		{
			input_handler = 0;
			init_keytable();

			//_ui_events.reserve(40);

			_ui_key = 0;

			WNDCLASS wc = { 0 };
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.lpfnWndProc = wnd_proc;
			wc.hInstance = GetModuleHandle(0);
			wc.hIcon = LoadIcon(0, IDI_WINLOGO);
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.lpszClassName = "shiva_wc";

			if (!RegisterClass(&wc)) {
				TRACE("Failed to register window class\n");
				return;
			}

			init_gl();

			DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPEDWINDOW;
			DWORD xstyle = WS_EX_APPWINDOW;

			PIXELFORMATDESCRIPTOR pfd = {
				sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
			};



			if (0/*fulscreen*/) {
				style = WS_POPUP | WS_MAXIMIZE;
				xstyle |= WS_EX_TOPMOST;

				DEVMODE deviceMode = { 0 };
				deviceMode.dmSize = sizeof(DEVMODE);
				EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &deviceMode);

				if (ChangeDisplaySettings(&deviceMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
					TRACE("Failed to set fullscreen window");
				}
			}

			RECT wr = { 0, 0, 800, 600 };
			AdjustWindowRectEx(&wr, style, 0, xstyle);
			int w = wr.right - wr.left;
			int h = wr.bottom - wr.top;

			wnd = CreateWindowEx(xstyle, wc.lpszClassName, "OpenVG", style, 10, 10, w, h, 0, 0, wc.hInstance, 0);
			if (!wnd) {
				TRACE("Failed to create system window!\n");
				return;
			}

			dc = GetDC(wnd);

			int pixelFormat;
			BOOL valid;
			UINT numFormats;
			int iAttributes[] = {
				WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
				WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
				WGL_COLOR_BITS_ARB, 24,
				WGL_ALPHA_BITS_ARB, 8,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
				0, 0 };

			    // WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
				// WGL_SAMPLES_ARB, 4,                        // Check For 4x Multisampling


			if (wglChoosePixelFormatARB == NULL)
			{
				if (wglGetCurrentContext() == NULL) {
					// 
					MessageBoxA(0, (char*)glGetString(GL_VERSION), "Context lost", 0);

				}


				MessageBoxA(0, (char*)glGetString(GL_VERSION), "Cannot find extension, wglChoosePixelFormatARB", 0);
			}
			else
			{

				valid = wglChoosePixelFormatARB(dc, iAttributes, 0, 1, &pixelFormat, &numFormats);

				int pf = ChoosePixelFormat(dc, &pfd);
				BOOL ok = SetPixelFormat(dc, pixelFormat, &pfd);

			}

			int attr[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
				WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
				0
			};

			                                                                 
			if (wglCreateContextAttribsARB == NULL)
			{
				MessageBoxA(0, (char*)glGetString(GL_VERSION), "Cannot find extension, wglCreateContextAttribsARB", 0);
				return;
			}


			glrc = wglCreateContextAttribsARB(dc, 0, attr);

			/*
			for (int i = 0; i < 2; ++i) {
			GLuint swap_group = 1;
			if (!wglJoinSwapGroupNV(context.channels[i].dc, swap_group)) {
			TRACE("ERROR: failed to join sawp group");
			}
			if (!wglBindSwapBarrierNV(swap_group, 1)) {
			TRACE("ERROR: failed to bind sawp barrier");
			}
			}
			*/

			// set channel 0 to current so graphics can initiate correctly
			wglMakeCurrent(dc, glrc);

			glDebugMessageCallbackARB = (PFGLDEBUGMESSAGECALLBACKARB) wglGetProcAddress("glDebugMessageCallbackARB");
			if (glDebugMessageCallbackARB == NULL)
			{
				MessageBoxA(0, (char*)glGetString(GL_VERSION), "Unimplemented glDebugMessageCallbackARB", 0);
			}
			else
			{
				glDebugMessageCallbackARB(&gl_debug_msg_proc, 0);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			}

			ShowWindow(wnd, SW_SHOW);
			UpdateWindow(wnd);

			vgCreateContextSH(800, 600);
		}