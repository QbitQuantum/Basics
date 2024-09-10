bool CStdGLCtx::Init(C4Window * pWindow, C4AbstractApp *pApp)
{
	// safety
	if (!pGL || !pWindow) return false;

	std::unique_ptr<GLTempContext> tempContext;
	if (hrc == 0)
	{
		// Create a temporary context to be able to fetch GL extension pointers
		try
		{
			tempContext.reset(new GLTempContext);
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if(err != GLEW_OK)
			{
				// Problem: glewInit failed, something is seriously wrong.
				pGL->Error(reinterpret_cast<const char*>(glewGetErrorString(err)));
				return false;
			}
		}
		catch (const WinAPIError &e)
		{
			pGL->Error((std::string("  gl: Unable to create temporary context: ") + e.what()).c_str());
			return false;
		}
	}

	// store window
	this->pWindow = pWindow;

	// get DC
	hDC = GetDC(pWindow->renderwnd);
	if(!hDC)
	{
		pGL->Error("  gl: Error getting DC");
		return false;
	}
	if (hrc)
	{
		SetPixelFormat(hDC, pGL->iPixelFormat, &pfd);
	}
	else
	{
		// Choose a good pixel format.
		int pixel_format;
		if((pixel_format = GetPixelFormatForMS(hDC, Config.Graphics.MultiSampling)) == 0)
			if((pixel_format = GetPixelFormatForMS(hDC, 0)) != 0)
				Config.Graphics.MultiSampling = 0;

		if (!pixel_format)
		{
			pGL->Error("  gl: Error choosing pixel format");
		}
		else
		{
			ZeroMemory(&pfd, sizeof(pfd)); pfd.nSize = sizeof(pfd);
			if(!DescribePixelFormat(hDC, pixel_format, sizeof(pfd), &pfd))
			{
				pGL->Error("  gl: Error describing chosen pixel format");
			}
			else if(!SetPixelFormat(hDC, pixel_format, &pfd))
			{
				pGL->Error("  gl: Error setting chosen pixel format");
			}
			else
			{
				// create context
				if (wglCreateContextAttribsARB)
				{
					const int attribs[] = {
						WGL_CONTEXT_FLAGS_ARB, Config.Graphics.DebugOpenGL ? WGL_CONTEXT_DEBUG_BIT_ARB : 0,
						WGL_CONTEXT_MAJOR_VERSION_ARB, REQUESTED_GL_CTX_MAJOR,
						WGL_CONTEXT_MINOR_VERSION_ARB, REQUESTED_GL_CTX_MINOR,
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
						0
					};

					hrc = wglCreateContextAttribsARB(hDC, 0, attribs);
				}
				else
				{
					DebugLog("  gl: wglCreateContextAttribsARB not available; creating default context.");
					hrc = wglCreateContext(hDC);
				}

				if(!hrc)
				{
					pGL->Error("  gl: Error creating gl context");
				}

				pGL->iPixelFormat = pixel_format;
			}
		}
	}
	if (hrc)
	{
		Select();
		// After selecting the new context, we have to reinitialize GLEW to
		// update its function pointers - the driver may elect to expose
		// different extensions depending on the context attributes
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			// Uh. This is a problem.
			pGL->Error(reinterpret_cast<const char*>(glewGetErrorString(err)));
			return false;
		}

		this_context = contexts.insert(contexts.end(), this);
		return true;
	}

	ReleaseDC(pWindow->renderwnd, hDC); hDC = NULL;
	return false;
}