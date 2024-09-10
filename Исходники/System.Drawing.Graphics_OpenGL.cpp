		Renderer* Graphics::GetRenderer(Renderer_Desc& desc) 
		{
			desc._hDC = GetDC(desc.hWnd);

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 32;
			pfd.cDepthBits = 32;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int nPixelFormat = ChoosePixelFormat(desc._hDC, &pfd);

			if (nPixelFormat == 0) return false;

			BOOL bResult = SetPixelFormat(desc._hDC, nPixelFormat, &pfd);

			if (!bResult) return false;

			HGLRC tempContext = wglCreateContext(desc._hDC);
			wglMakeCurrent(desc._hDC, tempContext);

			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				//AfxMessageBox(_T("GLEW is not initialized!"));
				return NULL;
			}

			//int attribs[] =
			//{
			//	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			//	WGL_CONTEXT_MINOR_VERSION_ARB, 1,
			//	WGL_CONTEXT_FLAGS_ARB, 0,
			//	0
			//};

			//if (wglewIsSupported("WGL_ARB_create_context") == 1)
			//{
			//	desc._hrc = wglCreateContextAttribsARB(desc._hDC, 0, attribs);
			//	wglMakeCurrent(NULL, NULL);
			//	wglDeleteContext(tempContext);
			//	wglMakeCurrent(desc._hDC, desc._hrc);
			//}
			//else
			//{	//It's not possible to make a GL 3.x context. Use the old style context (GL 2.1 and before)
				desc._hrc = tempContext;
			//}

			//Checking GL version
			const GLubyte *GLVersionString = glGetString(GL_VERSION);

			//Or better yet, use the GL3 way to get the version number
			int OpenGLVersion[2];
			glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
			glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

			if (!desc._hrc) return NULL;

			Renderer* pRenderer = new Renderer(desc);
			return pRenderer;				
		}