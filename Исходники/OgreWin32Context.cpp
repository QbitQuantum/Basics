	GLContext* Win32Context::clone() const
	{
		// Create new context based on own HDC
		HGLRC newCtx = wglCreateContext(mHDC);
		
		if (!newCtx)
		{
			OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, 
				"Error calling wglCreateContext", "Win32Context::clone");
		}

		HGLRC oldrc = wglGetCurrentContext();
		HDC oldhdc = wglGetCurrentDC();
		wglMakeCurrent(NULL, NULL);
		// Share lists with old context
	    if (!wglShareLists(mGlrc, newCtx))
		{
			String errorMsg = translateWGLError();
			wglDeleteContext(newCtx);
			OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, String("wglShareLists() failed: ") + errorMsg, "Win32Context::clone");
		}
		// restore old context
		wglMakeCurrent(oldhdc, oldrc);
		

		return new Win32Context(mHDC, newCtx);
	}